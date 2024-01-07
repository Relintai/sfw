
//--STRIP
#include "psignal.h"
//--STRIP

void Signal::connect_static(void (*func)(Signal *)) {
	StaticSignalEntry *se = new StaticSignalEntry();
	se->func = func;

	entries.push_back(se);
}
void Signal::disconnect_static(void (*func)(Signal *)) {
	for (int i = 0; i < entries.size(); ++i) {
		SignalEntry *e = entries[i];

		if (e->type == SIGNAL_ENTRY_TYPE_STATIC) {
			StaticSignalEntry *se = static_cast<StaticSignalEntry *>(e);

			if (se->func == func) {
				entries.remove(i);
				return;
			}
		}
	}
}
bool Signal::is_connected_static(void (*func)(Signal *)) {
	for (int i = 0; i < entries.size(); ++i) {
		SignalEntry *e = entries[i];

		if (e->type == SIGNAL_ENTRY_TYPE_STATIC) {
			StaticSignalEntry *se = static_cast<StaticSignalEntry *>(e);

			if (se->func == func) {
				return true;
			}
		}
	}

	return false;
}

void Signal::emit(Object *p_emitter) {
	emitter = p_emitter;

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}
}

void Signal::emit(Object *p_emitter, const Variant &p1) {
	emitter = p_emitter;

	params.push_back(p1);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}
void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}
void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);
	params.push_back(p3);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}

void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);
	params.push_back(p3);
	params.push_back(p4);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}

void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4, const Variant &p5) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);
	params.push_back(p3);
	params.push_back(p4);
	params.push_back(p5);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}

Signal::Signal() {
}
Signal::~Signal() {
}
