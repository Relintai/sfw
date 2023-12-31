#ifndef RESOURCE_H
#define RESOURCE_H

#include "reference.h"

#include "psignal.h"

class Resource : public Reference {
	SFW_OBJECT(Resource, Reference);

public:
	Signal changed;

	void emit_changed();

	virtual Error load(const String &path);
	virtual Error save(const String &path);

	Resource();
	virtual ~Resource();
};

#endif