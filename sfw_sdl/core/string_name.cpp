/*************************************************************************/
/*  string_name.cpp                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/string_name.h"
//--STRIP

StaticCString StaticCString::create(const char *p_ptr) {
	StaticCString scs;
	scs.ptr = p_ptr;
	return scs;
}

StringName::_Data *StringName::_table[STRING_TABLE_LEN];

StringName _scs_create(const char *p_chr, bool p_static) {
	return (p_chr[0] ? StringName(StaticCString::create(p_chr), p_static) : StringName());
}

bool StringName::configured = false;
Mutex StringName::lock;

#ifdef DEBUG_ENABLED
bool StringName::debug_stringname = false;
#endif

void StringName::setup() {
	ERR_FAIL_COND(configured);
	for (int i = 0; i < STRING_TABLE_LEN; i++) {
		_table[i] = nullptr;
	}
	configured = true;
}

void StringName::cleanup() {
	lock.lock();

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		Vector<_Data *> data;
		for (int i = 0; i < STRING_TABLE_LEN; i++) {
			_Data *d = _table[i];
			while (d) {
				data.push_back(d);
				d = d->next;
			}
		}

		LOG_MSG("\nStringName reference ranking (from most to least referenced):\n");

		data.sort_custom<DebugSortReferences>();
		int unreferenced_stringnames = 0;
		int rarely_referenced_stringnames = 0;
		for (int i = 0; i < data.size(); i++) {
			LOG_MSG(itos(i + 1) + ": " + data[i]->get_name() + " - " + itos(data[i]->debug_references));
			if (data[i]->debug_references == 0) {
				unreferenced_stringnames += 1;
			} else if (data[i]->debug_references < 5) {
				rarely_referenced_stringnames += 1;
			}
		}

		LOG_MSG(vformat("\nOut of %d StringNames, %d StringNames were never referenced during this run (0 times) (%.2f%%).", data.size(), unreferenced_stringnames, unreferenced_stringnames / float(data.size()) * 100));
		LOG_MSG(vformat("Out of %d StringNames, %d StringNames were rarely referenced during this run (1-4 times) (%.2f%%).", data.size(), rarely_referenced_stringnames, rarely_referenced_stringnames / float(data.size()) * 100));
	}
#endif

	//int lost_strings = 0;
	for (int i = 0; i < STRING_TABLE_LEN; i++) {
		while (_table[i]) {
			_Data *d = _table[i];

			/*
			if (d->static_count.get() != d->refcount.get()) {
				lost_strings++;
				if (OS::get_singleton()->is_stdout_verbose()) {
					if (d->cname) {
						LOG_MSG("Orphan StringName: " + String(d->cname));
					} else {
						LOG_MSG("Orphan StringName: " + String(d->name));
					}
				}
			}
			*/

			_table[i] = _table[i]->next;
			memdelete(d);
		}
	}

	/*
	if (lost_strings) {
		print_verbose("StringName: " + itos(lost_strings) + " unclaimed string names at exit.");
	}
	*/

	configured = false;

	lock.unlock();
}

void StringName::unref() {
	ERR_FAIL_COND(!configured);

	if (_data && _data->refcount.unref()) {
		lock.lock();

		if (_data->static_count.get() > 0) {
			if (_data->cname) {
				ERR_PRINT("BUG: Unreferenced static string to 0: " + String(_data->cname));
			} else {
				ERR_PRINT("BUG: Unreferenced static string to 0: " + String(_data->name));
			}
		}

		if (_data->prev) {
			_data->prev->next = _data->next;
		} else {
			if (_table[_data->idx] != _data) {
				ERR_PRINT("BUG!");
			}

			_table[_data->idx] = _data->next;
		}

		if (_data->next) {
			_data->next->prev = _data->prev;
		}

		memdelete(_data);
		lock.unlock();
	}

	_data = nullptr;
}

bool StringName::operator==(const String &p_name) const {
	if (!_data) {
		return (p_name.length() == 0);
	}

	return (_data->get_name() == p_name);
}

bool StringName::operator==(const char *p_name) const {
	if (!_data) {
		return (p_name[0] == 0);
	}

	return (_data->get_name() == p_name);
}

bool StringName::operator!=(const String &p_name) const {
	return !(operator==(p_name));
}

bool StringName::operator!=(const StringName &p_name) const {
	// the real magic of all this mess happens here.
	// this is why path comparisons are very fast
	return _data != p_name._data;
}

void StringName::operator=(const StringName &p_name) {
	if (this == &p_name) {
		return;
	}

	unref();

	if (p_name._data && p_name._data->refcount.ref()) {
		_data = p_name._data;
	}
}

StringName::StringName(const StringName &p_name) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (p_name._data && p_name._data->refcount.ref()) {
		_data = p_name._data;
	}
}

StringName::StringName(const char *p_name, bool p_static) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (!p_name || p_name[0] == 0) {
		return; //empty, ignore
	}

	lock.lock();

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			if (p_static) {
				_data->static_count.increment();
			}

#ifdef DEBUG_ENABLED
			if (unlikely(debug_stringname)) {
				_data->debug_references++;
			}
#endif

			lock.unlock();
			return;
		}
	}

	_data = memnew(_Data);
	_data->name = p_name;
	_data->refcount.init();
	_data->static_count.set(p_static ? 1 : 0);
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = NULL;
	_data->next = _table[idx];
	_data->prev = NULL;

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		// Keep in memory, force static.
		_data->refcount.ref();
		_data->static_count.increment();
	}
#endif

	if (_table[idx]) {
		_table[idx]->prev = _data;
	}

	_table[idx] = _data;

	lock.unlock();
}

StringName::StringName(const StaticCString &p_static_string, bool p_static) {
	_data = NULL;

	ERR_FAIL_COND(!configured);

	ERR_FAIL_COND(!p_static_string.ptr || !p_static_string.ptr[0]);

	lock.lock();

	uint32_t hash = String::hash(p_static_string.ptr);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_static_string.ptr) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			if (p_static) {
				_data->static_count.increment();
			}

#ifdef DEBUG_ENABLED
			if (unlikely(debug_stringname)) {
				_data->debug_references++;
			}
#endif

			lock.unlock();
			return;
		}
	}

	_data = memnew(_Data);

	_data->refcount.init();
	_data->static_count.set(p_static ? 1 : 0);
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = p_static_string.ptr;
	_data->next = _table[idx];
	_data->prev = NULL;

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		// Keep in memory, force static.
		_data->refcount.ref();
		_data->static_count.increment();
	}
#endif

	if (_table[idx]) {
		_table[idx]->prev = _data;
	}

	_table[idx] = _data;

	lock.unlock();
}

StringName::StringName(const String &p_name, bool p_static) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (p_name.empty()) {
		return;
	}

	lock.lock();

	uint32_t hash = p_name.hash();

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}

		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			if (p_static) {
				_data->static_count.increment();
			}

#ifdef DEBUG_ENABLED
			if (unlikely(debug_stringname)) {
				_data->debug_references++;
			}
#endif

			lock.unlock();
			return;
		}
	}

	_data = memnew(_Data);
	_data->name = p_name;
	_data->refcount.init();
	_data->static_count.set(p_static ? 1 : 0);
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = NULL;
	_data->next = _table[idx];
	_data->prev = NULL;

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		// Keep in memory, force static.
		_data->refcount.ref();
		_data->static_count.increment();
	}
#endif

	if (_table[idx]) {
		_table[idx]->prev = _data;
	}

	_table[idx] = _data;

	lock.unlock();
}

StringName StringName::search(const char *p_name) {
	ERR_FAIL_COND_V(!configured, StringName());

	ERR_FAIL_COND_V(!p_name, StringName());
	if (!p_name[0]) {
		return StringName();
	}

	lock.lock();

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
#ifdef DEBUG_ENABLED
		if (unlikely(debug_stringname)) {
			_data->debug_references++;
		}
#endif

		lock.unlock();

		return StringName(_data);
	}

	lock.unlock();
	return StringName(); //does not exist
}

StringName StringName::search(const CharType *p_name) {
	ERR_FAIL_COND_V(!configured, StringName());

	ERR_FAIL_COND_V(!p_name, StringName());
	if (!p_name[0]) {
		return StringName();
	}

	lock.lock();

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}

		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
		lock.unlock();
		return StringName(_data);
	}

	lock.unlock();
	return StringName(); //does not exist
}
StringName StringName::search(const String &p_name) {
	ERR_FAIL_COND_V(p_name == "", StringName());

	lock.lock();

	uint32_t hash = p_name.hash();

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && p_name == _data->get_name()) {
			break;
		}

		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
#ifdef DEBUG_ENABLED
		if (unlikely(debug_stringname)) {
			_data->debug_references++;
		}
#endif
		lock.unlock();
		return StringName(_data);
	}

	lock.unlock();
	return StringName(); //does not exist
}

StringName::StringName() {
	_data = nullptr;
}

/*
bool operator==(const String &p_name, const StringName &p_string_name) {
	return p_name == p_string_name.operator String();
}
bool operator!=(const String &p_name, const StringName &p_string_name) {
	return p_name != p_string_name.operator String();
}

bool operator==(const char *p_name, const StringName &p_string_name) {
	return p_name == p_string_name.operator String();
}
bool operator!=(const char *p_name, const StringName &p_string_name) {
	return p_name != p_string_name.operator String();
}
*/
