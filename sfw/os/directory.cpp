#include "directory.h"

Error Directory::open_dir(const String &path, bool skip_specials) {
	if (_dir_open) {
		return ERR_CANT_ACQUIRE_RESOURCE;
	}

	_skip_specials = skip_specials;

	if (tinydir_open(&_dir, path.c_str()) == -1) {
		return FAILED;
	}

	_dir_open = true;

	return OK;
}

Error Directory::open_dir(const char *path, bool skip_specials) {
	if (_dir_open) {
		return ERR_CANT_ACQUIRE_RESOURCE;
	}

	_skip_specials = skip_specials;

	if (tinydir_open(&_dir, path) == -1) {
		return FAILED;
	}

	_dir_open = true;

	return OK;
}

void Directory::close_dir() {
	if (!_dir_open) {
		return;
	}

	tinydir_close(&_dir);

	_dir_open = false;
}

bool Directory::has_next() {
	return _dir.has_next;
}
bool Directory::read() {
	_read_file_result = tinydir_readfile(&_dir, &_file);

	return _read_file_result != -1;
}
bool Directory::next() {
	if (!_dir.has_next) {
		return false;
	}

	bool rres = read();
	while (!rres && _dir.has_next) {
		tinydir_next(&_dir);
		rres = read();
	}

	if (!rres) {
		return false;
	}

	if (_dir.has_next) {
		tinydir_next(&_dir);
	}

	if (_skip_specials && current_is_dir() && current_is_special_dir()) {
		return next();
	}

	return true;
}

bool Directory::current_is_ok() {
	return _read_file_result == 01;
}
String Directory::current_get_name() {
	return String(_file.name);
}
String Directory::current_get_path() {
	return String(_file.path);
}
String Directory::current_get_extension() {
	return String(_file.extension);
}
const char *Directory::current_get_name_cstr() {
	return _file.name;
}
const char *Directory::current_get_path_cstr() {
	return _file.path;
}
const char *Directory::current_get_extension_cstr() {
	return _file.extension;
}
bool Directory::current_is_file() {
	return !_file.is_dir;
}
bool Directory::current_is_dir() {
	return _file.is_dir;
}
bool Directory::current_is_special_dir() {
	if (_file.name[0] == '.' && _file.name[1] == '\0' || _file.name[0] == '.' && _file.name[1] == '.') {
		return true;
	}

	return false;
}

String Directory::read_file(const String &path) {
	FILE *f = fopen(path.c_str(), "r");

	String fd;

	ERR_FAIL_COND_V_MSG(!f, fd, "Error opening file! " + path);

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	fd.resize(fsize);

	fread(fd.dataw(), 1, fsize, f);
	fclose(f);

	return fd;
}

Error Directory::read_file_into(const String &path, String *str) {
	if (!str) {
		return ERR_PARAMETER_RANGE_ERROR;
	}

	FILE *f = fopen(path.c_str(), "r");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	str->resize(fsize);

	fread(str->dataw(), 1, fsize, f);
	fclose(f);

	return OK;
}

Vector<uint8_t> Directory::read_file_bin(const String &path) {
	FILE *f = fopen(path.c_str(), "rb");

	Vector<uint8_t> fd;

	ERR_FAIL_COND_V_MSG(!f, fd, "Error opening file! " + path);

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	fd.resize(fsize);

	fread(fd.dataw(), 1, fsize, f);
	fclose(f);

	return fd;
}

Error Directory::read_file_into_bin(const String &path, Vector<uint8_t> *data) {
	if (!data) {
		return ERR_PARAMETER_RANGE_ERROR;
	}

	FILE *f = fopen(path.c_str(), "rb");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	data->resize(fsize);

	fread(data->dataw(), 1, fsize, f);
	fclose(f);

	return OK;
}

Error Directory::write_file(const String &path, const String &str) {
	FILE *f = fopen(path.c_str(), "w");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fwrite(str.data(), sizeof(char), str.size(), f);
	fclose(f);

	return OK;
}

Error Directory::write_file_bin(const String &path, const Vector<uint8_t> &data) {
	FILE *f = fopen(path.c_str(), "wb");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fwrite(data.data(), sizeof(uint8_t), data.size(), f);
	fclose(f);

	return OK;
}

bool Directory::is_dir_open() {
	return _dir_open;
}
bool Directory::is_dir_closed() {
	return !_dir_open;
}

Directory::Directory() {
	_skip_specials = true;
	_read_file_result = 0;
	_dir_open = false;
}
Directory::~Directory() {
	if (is_dir_open()) {
		close_dir();
	}
}
