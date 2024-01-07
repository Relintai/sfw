
//--STRIP
#include "file_access.h"

#include <cstdio>
//--STRIP


String FileAccess::read_file(const String &path) {
	FILE *f = fopen(path.utf8().get_data(), "r");

	ERR_FAIL_COND_V_MSG(!f, String(), "Error opening file! " + path);

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	CharString cs;
	cs.resize(fsize + 1); // +1 for the null terminator

	fread(cs.ptrw(), 1, fsize, f);
	fclose(f);

	return String::utf8(cs.ptr());
}

Vector<uint8_t> FileAccess::read_file_bin(const String &path) {
	FILE *f = fopen(path.utf8().get_data(), "rb");

	Vector<uint8_t> fd;

	ERR_FAIL_COND_V_MSG(!f, fd, "Error opening file! " + path);

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	fd.resize(fsize);

	fread(fd.ptrw(), 1, fsize, f);
	fclose(f);

	return fd;
}

Error FileAccess::read_file_into_bin(const String &path, Vector<uint8_t> *data) {
	if (!data) {
		return ERR_PARAMETER_RANGE_ERROR;
	}

	FILE *f = fopen(path.utf8().get_data(), "rb");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	data->resize(fsize);

	fread(data->ptrw(), 1, fsize, f);
	fclose(f);

	return OK;
}

Error FileAccess::write_file(const String &path, const String &str) {
	FILE *f = fopen(path.utf8().get_data(), "w");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fwrite(str.utf8().ptr(), sizeof(char), str.size(), f);
	fclose(f);

	return OK;
}

Error FileAccess::write_file_bin(const String &path, const Vector<uint8_t> &data) {
	FILE *f = fopen(path.utf8().get_data(), "wb");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fwrite(data.ptr(), sizeof(uint8_t), data.size(), f);
	fclose(f);

	return OK;
}

FileAccess::FileAccess() {
}
FileAccess::~FileAccess() {
}
