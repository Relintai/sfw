
#ifndef DIRECTORY_H
#define DIRECTORY_H

//--STRIP
#include "core/error_list.h"
#include "core/ustring.h"
//--STRIP

struct tinydir_file;
struct tinydir_dir;

class Directory {
public:
	Error open_dir(const String &path, bool skip_specials = true);
	Error open_dir(const char *path, bool skip_specials = true);
	void close_dir();

	bool has_next();
	bool read();
	bool next();

	bool current_is_ok();
	String current_get_name();
	String current_get_path();
	String current_get_extension();
	const char *current_get_name_cstr();
	const char *current_get_path_cstr();
	const char *current_get_extension_cstr();
	bool current_is_file();
	bool current_is_dir();
	bool current_is_special_dir();

	bool is_dir_open();
	bool is_dir_closed();

	Directory();
	virtual ~Directory();

private:
	bool _skip_specials;
	int _read_file_result;
	tinydir_dir *_dir;
	tinydir_file *_file;

	bool _dir_open;
};

#endif
