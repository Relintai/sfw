
#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H

//--STRIP
#include "core/error_list.h"
#include "core/ustring.h"
//--STRIP

class FileAccess {
public:
	//TODO should probably have some simple buffered open / close / write / read api.

	String read_file(const String &path);

	Vector<uint8_t> read_file_bin(const String &path);
	Error read_file_into_bin(const String &path, Vector<uint8_t> *data);

	Error write_file(const String &path, const String &str);
	Error write_file_bin(const String &path, const Vector<uint8_t> &data);

	FileAccess();
	virtual ~FileAccess();

private:
};

#endif
