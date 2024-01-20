//--STRIP
#ifndef REF_PTR_H
#define REF_PTR_H
//--STRIP

/*************************************************************************/
/*  ref_ptr.h                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

/**
	@author Juan Linietsky <reduzio@gmail.com>
 * This class exists to workaround a limitation in C++ but keep the design OK.
 * It's basically an opaque container of a Reference reference, so Variant can use it.
*/

//--STRIP
#include "core/typedefs.h"
//--STRIP

class RefPtr {
	enum {
		DATASIZE = sizeof(void *) //*4 -ref was shrunk
	};

	mutable char data[DATASIZE]; // too much probably, virtual class + pointer
public:
	bool is_null() const;
	void operator=(const RefPtr &p_other);
	bool operator==(const RefPtr &p_other) const;
	bool operator!=(const RefPtr &p_other) const;
	void unref();

	_FORCE_INLINE_ void *get_data() const { return data; }
	RefPtr(const RefPtr &p_other);
	RefPtr();
	~RefPtr();
};

//--STRIP
#endif // REF_PTR_H
//--STRIP
