#ifndef SIGNAL_H
#define SIGNAL_H

#include "core/vector.h"
#include "core/ustring.h"

#include "object/variant.h"
#include "object/reference.h"

class Signal {
public:
	Object *emitter;
	Vector<Variant> params;
	Vector<Variant> static_data;

	template <class T>
	void connect(T *obj, void (*func)(T*, Signal *));
	template <class T>
	void disconnect(T *obj, void (*func)(T*, Signal *));
	template <class T>
	bool is_connected(T *obj, void (*func)(T*, Signal *));

	void connect_static(void (*func)(Signal *));
	void disconnect_static(void (*func)(Signal *));
	bool is_connected_static(void (*func)(Signal *));

	void emit(Object *p_emitter);
	void emit(Object *p_emitter, const Variant &p1);
	void emit(Object *p_emitter, const Variant &p1, const Variant &p2);
	void emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3);
	void emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4);
	void emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4, const Variant &p5);

	Signal();
	~Signal();

protected:
	enum SignalEntryType {
		SIGNAL_ENTRY_TYPE_NONE = 0,
		SIGNAL_ENTRY_TYPE_STATIC = 1,
		SIGNAL_ENTRY_TYPE_CLASS = 2,
	};

	struct SignalEntry {
		SignalEntryType type;

		virtual void call(Signal *s) {
		}

		SignalEntry() {
			type = SIGNAL_ENTRY_TYPE_NONE;
		}
	};

	struct StaticSignalEntry : public SignalEntry {
		void (*func)(Signal *);

		virtual void call(Signal *s) {
			func(s);
		}

		StaticSignalEntry() {
			type = SIGNAL_ENTRY_TYPE_STATIC;
			func = nullptr;
		}
	};

	struct ClassSignalEntry : public SignalEntry {

		virtual void* get_obj_ptr() {
			return nullptr;
		}

		virtual void* get_func_ptr() {
			return nullptr;
		}

		ClassSignalEntry() {
			type = SIGNAL_ENTRY_TYPE_CLASS;
		}
	};

	template<typename T>
	struct ClassSignalEntrySpec : public ClassSignalEntry {
		union {
			T* obj;
			void* obj_ptr;
		};
		union {
			void (*func)(T*, Signal *);
			void* func_ptr;
		};

		virtual void call(Signal *s) {
			func(obj, s);
		}

		void* get_obj_ptr() {
			return obj_ptr;
		}

		void* get_func_ptr() {
			return func_ptr;
		}

		ClassSignalEntrySpec() {
			obj = nullptr;
			func = nullptr;
		}
	};

protected:
	Vector<SignalEntry *> entries;
};

template <typename T>
void Signal::connect(T *obj, void (*func)(T*, Signal *)) {
	ClassSignalEntrySpec<T> *ce = new ClassSignalEntrySpec<T>();
	ce->obj = obj;
	ce->func = func;

	entries.push_back(ce);
}

template <typename T>
void Signal::disconnect(T *obj, void (*func)(T*, Signal *)) {
	ClassSignalEntrySpec<T> t;
	t.obj = obj;
	t.func = func;

	void* obj_ptr = t.obj_ptr;
	void* func_ptr = t.func_ptr;

	for (int i = 0; i < entries.size(); ++i) {
		SignalEntry *e = entries[i];

		if (e->type == SIGNAL_ENTRY_TYPE_CLASS) {
			ClassSignalEntry *se = static_cast<ClassSignalEntry *>(e);

			if (se->get_obj_ptr() == obj_ptr && se->get_func_ptr() == func_ptr) {
				entries.remove(i);
				return;
			}
		}
	}
}

template <typename T>
bool Signal::is_connected(T *obj, void (*func)(T*, Signal *)) {
	ClassSignalEntrySpec<T> t;
	t.obj = obj;
	t.func = func;

	void* obj_ptr = t.obj_ptr;
	void* func_ptr = t.func_ptr;

	for (int i = 0; i < entries.size(); ++i) {
		SignalEntry *e = entries[i];

		if (e->type == SIGNAL_ENTRY_TYPE_CLASS) {
			ClassSignalEntry *se = static_cast<ClassSignalEntry *>(e);

			if (se->get_obj_ptr() == obj_ptr && se->get_func_ptr() == func_ptr) {
				return true;
			}
		}
	}

	return false;
}

#endif