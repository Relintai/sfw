//--STRIP
#ifndef DIR_ACCESS_H
#define DIR_ACCESS_H
//--STRIP

/*************************************************************************/
/*  dir_access.h                                                         */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_list.h"
#include "core/ustring.h"
//--STRIP

#if defined(_WIN64) || defined(_WIN32)
struct DirAccessWindowsPrivate;
#else
struct __dirstream;
typedef struct __dirstream DIR;
#endif

class DirAccess {
	Error _copy_dir(DirAccess *p_target_da, String p_to, int p_chmod_flags, bool p_copy_links);

public:
	virtual Error list_dir_begin(bool skip_specials = false); ///< This starts dir listing
	virtual String get_next();
	virtual bool current_is_dir() const;
	virtual bool current_is_hidden() const;
	virtual bool current_is_file() const;
	virtual bool current_is_special_dir() const;

	virtual void list_dir_end(); ///<

	virtual int get_drive_count();
	virtual String get_drive(int p_drive);
	virtual int get_current_drive();
	virtual bool drives_are_shortcuts();

	virtual Error change_dir(String p_dir); ///< can be relative or absolute, return false on success
	virtual String get_current_dir(); ///< return current dir location
	virtual String get_current_dir_without_drive();
	virtual Error make_dir(String p_dir);
	virtual Error make_dir_recursive(String p_dir);
	virtual Error erase_contents_recursive(); //super dangerous, use with care!

	virtual bool file_exists(String p_file);
	virtual bool dir_exists(String p_dir);
	static bool exists(String p_dir);
	virtual uint64_t get_space_left();

	Error copy_dir(String p_from, String p_to, int p_chmod_flags = -1, bool p_copy_links = false);
	virtual Error copy(String p_from, String p_to, int p_chmod_flags = -1);
	virtual Error rename(String p_from, String p_to);
	virtual Error remove(String p_name);

	virtual bool is_link(String p_file);
	virtual String read_link(String p_file);
	virtual Error create_link(String p_source, String p_target);

	virtual uint64_t get_modified_time(String p_file);

	virtual String get_filesystem_type() const;
	static String get_full_path(const String &p_path);

	static DirAccess *create_for_path(const String &p_path);
	static DirAccess *create();

	Error open(const String &p_path);

	static String get_filesystem_abspath_for(String p_path);

	static bool is_special(const String &p_path);

	DirAccess();
	virtual ~DirAccess();

protected:
#if defined(_WIN64) || defined(_WIN32)
#else
	virtual String fix_unicode_name(const char *p_name) const { return String::utf8(p_name); }
	virtual bool is_hidden(const String &p_name);
#endif

	bool next_is_dir;
	bool _skip_specials;

#if defined(_WIN64) || defined(_WIN32)
	enum {
		MAX_DRIVES = 26
	};

	DirAccessWindowsPrivate *p;
	/* Windows stuff */

	char drives[MAX_DRIVES]; // a-z:
	int drive_count;

	String current_dir;

	bool _cisdir;
	bool _cishidden;
#else
	String current_dir;
	DIR *dir_stream;

	bool _cisdir;
	bool _cishidden;
	bool _cisspecial;
#endif
};

struct DirAccessRef {
	DirAccess *f;

	_FORCE_INLINE_ bool is_null() const { return f == nullptr; }
	_FORCE_INLINE_ bool is_valid() const { return f != nullptr; }

	_FORCE_INLINE_ operator bool() const { return f != nullptr; }
	_FORCE_INLINE_ operator DirAccess *() { return f; }

	_FORCE_INLINE_ DirAccess *operator->() {
		return f;
	}

	DirAccessRef(DirAccess *fa) { f = fa; }
	DirAccessRef(DirAccessRef &&other) {
		f = other.f;
		other.f = nullptr;
	}
	~DirAccessRef() {
		if (f) {
			memdelete(f);
		}
	}
};

//--STRIP
#endif
//--STRIP
