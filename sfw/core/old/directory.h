#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "core/string.h"
#include "core/error_list.h"
#include "3rd_tinydir.h"

#include "core/reference.h"

class Directory : public Reference {
	SFW_OBJECT(Directory, Reference);
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

	String read_file(const String &path);
	Error read_file_into(const String &path, String *str);
	Vector<uint8_t> read_file_bin(const String &path);
	Error read_file_into_bin(const String &path, Vector<uint8_t> *data);

	Error write_file(const String &path, const String &str);
	Error write_file_bin(const String &path, const Vector<uint8_t> &data);

	bool is_dir_open();
	bool is_dir_closed();

	Directory();
	virtual ~Directory();

private:
	bool _skip_specials;
	int _read_file_result;
	tinydir_dir _dir;
	tinydir_file _file;

	bool _dir_open;
};

#endif
