
/*************************************************************************/
/*  file_access.cpp                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "file_access.h"

#include "core/marshalls.h"

#include <cstdio>
//--STRIP

#if defined(_WIN64) || defined(_WIN32)

#include <share.h> // _SH_DENYNO
#include <shlwapi.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <tchar.h>
#include <wchar.h>

#ifdef _MSC_VER
#define S_ISREG(m) ((m)&_S_IFREG)
#endif

//--STRIP
#include "core/sfw_time.h"
//--STRIP

#else

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>

#include <unistd.h>

#ifdef MSVC
#define S_ISREG(m) ((m)&_S_IFREG)
#include <io.h>
#endif
#ifndef S_ISREG
#define S_ISREG(m) ((m)&S_IFREG)
#endif

#ifndef NO_FCNTL
#include <fcntl.h>
#else
#include <sys/ioctl.h>
#endif

#endif

#if defined(_WIN64) || defined(_WIN32)

void FileAccess::check_errors() const {
	ERR_FAIL_COND(!f);

	if (feof(f)) {
		last_error = ERR_FILE_EOF;
	}
}

Error FileAccess::_open(const String &p_path, int p_mode_flags) {
	path_src = p_path;
	path = fix_path(p_path);

	if (f) {
		close();
	}

	const WCHAR *mode_string;

	if (p_mode_flags == READ) {
		mode_string = L"rb";
	} else if (p_mode_flags == WRITE) {
		mode_string = L"wb";
	} else if (p_mode_flags == READ_WRITE) {
		mode_string = L"rb+";
	} else if (p_mode_flags == WRITE_READ) {
		mode_string = L"wb+";
	} else {
		return ERR_INVALID_PARAMETER;
	}

	/* pretty much every implementation that uses fopen as primary
	   backend supports utf8 encoding */

	struct _stat st;
	if (_wstat((LPCWSTR)(path.utf16().get_data()), &st) == 0) {
		if (!S_ISREG(st.st_mode)) {
			return ERR_FILE_CANT_OPEN;
		}
	};

#ifdef TOOLS_ENABLED
	// Windows is case insensitive, but all other platforms are sensitive to it
	// To ease cross-platform development, we issue a warning if users try to access
	// a file using the wrong case (which *works* on Windows, but won't on other
	// platforms).
	if (p_mode_flags == READ) {
		WIN32_FIND_DATAW d;
		HANDLE f = FindFirstFileW((LPCWSTR)(path.utf16().get_data()), &d);

		if (f != INVALID_HANDLE_VALUE) {
			String fname = String::utf16((const char16_t *)(d.cFileName));

			if (fname != String()) {
				String base_file = path.get_file();
				if (base_file != fname && base_file.findn(fname) == 0) {
					LOG_WARN("Case mismatch opening requested file '" + base_file + "', stored as '" + fname + "' in the filesystem. This file will not open when exported to other case-sensitive platforms.");
				}
			}

			FindClose(f);
		}
	}
#endif

	if (is_backup_save_enabled() && p_mode_flags & WRITE && !(p_mode_flags & READ)) {
		save_path = path;
		path = path + ".tmp";
	}

	f = _wfsopen((LPCWSTR)(path.utf16().get_data()), mode_string, _SH_DENYNO);

	if (f == nullptr) {
		switch (errno) {
			case ENOENT: {
				last_error = ERR_FILE_NOT_FOUND;
			} break;
			default: {
				last_error = ERR_FILE_CANT_OPEN;
			} break;
		}
		return last_error;
	} else {
		last_error = OK;
		flags = p_mode_flags;
		return OK;
	}
}

void FileAccess::close() {
	if (!f) {
		return;
	}

	fclose(f);
	f = NULL;

	if (save_path != "") {
		bool rename_error = true;
		int attempts = 4;
		while (rename_error && attempts) {
			// This workaround of trying multiple times is added to deal with paranoid Windows
			// antiviruses that love reading just written files even if they are not executable, thus
			// locking the file and preventing renaming from happening.

#ifdef UWP_ENABLED
			// UWP has no PathFileExists, so we check attributes instead
			DWORD fileAttr;

			fileAttr = GetFileAttributesW((LPCWSTR)(save_path.utf16().get_data()));
			if (INVALID_FILE_ATTRIBUTES == fileAttr) {
#else
			if (!PathFileExistsW((LPCWSTR)(save_path.utf16().get_data()))) {
#endif
				//creating new file
				rename_error = _wrename((LPCWSTR)((save_path + ".tmp").utf16().get_data()), (LPCWSTR)(save_path.utf16().get_data())) != 0;
			} else {
				//atomic replace for existing file
				rename_error = !ReplaceFileW((LPCWSTR)(save_path.utf16().get_data()), (LPCWSTR)((save_path + ".tmp").utf16().get_data()), NULL, 2 | 4, NULL, NULL);
			}
			if (rename_error) {
				attempts--;
				SFWTime::sleep_us(100000); // wait 100msec and try again
			}
		}

		if (rename_error) {
			if (close_fail_notify) {
				close_fail_notify(save_path);
			}
		}

		save_path = "";

		ERR_FAIL_COND_MSG(rename_error, "Safe save failed. This may be a permissions problem, but also may happen because you are running a paranoid antivirus. If this is the case, please switch to Windows Defender or disable the 'safe save' option in editor settings. This makes it work, but increases the risk of file corruption in a crash.");
	}
}

String FileAccess::get_path() const {
	return path_src;
}

String FileAccess::get_path_absolute() const {
	return path;
}

bool FileAccess::is_open() const {
	return (f != NULL);
}

void FileAccess::seek(uint64_t p_position) {
	ERR_FAIL_COND(!f);

	last_error = OK;

	if (_fseeki64(f, p_position, SEEK_SET)) {
		check_errors();
	}

	prev_op = 0;
}

void FileAccess::seek_end(int64_t p_position) {
	ERR_FAIL_COND(!f);

	if (_fseeki64(f, p_position, SEEK_END)) {
		check_errors();
	}

	prev_op = 0;
}

uint64_t FileAccess::get_position() const {
	int64_t aux_position = _ftelli64(f);

	if (aux_position < 0) {
		check_errors();
	}

	return aux_position;
}

uint64_t FileAccess::get_len() const {
	ERR_FAIL_COND_V(!f, 0);

	uint64_t pos = get_position();
	_fseeki64(f, 0, SEEK_END);
	uint64_t size = get_position();
	_fseeki64(f, pos, SEEK_SET);

	return size;
}

bool FileAccess::eof_reached() const {
	check_errors();
	return last_error == ERR_FILE_EOF;
}

uint8_t FileAccess::get_8() const {
	ERR_FAIL_COND_V(!f, 0);
	if (flags == READ_WRITE || flags == WRITE_READ) {
		if (prev_op == WRITE) {
			fflush(f);
		}
		prev_op = READ;
	}
	uint8_t b;
	if (fread(&b, 1, 1, f) == 0) {
		check_errors();
		b = '\0';
	};

	return b;
}

uint64_t FileAccess::get_buffer(uint8_t *p_dst, uint64_t p_length) const {
	ERR_FAIL_COND_V(!p_dst && p_length > 0, -1);
	ERR_FAIL_COND_V(!f, -1);

	if (flags == READ_WRITE || flags == WRITE_READ) {
		if (prev_op == WRITE) {
			fflush(f);
		}
		prev_op = READ;
	}
	uint64_t read = fread(p_dst, 1, p_length, f);
	check_errors();
	return read;
};

Error FileAccess::get_error() const {
	return last_error;
}

void FileAccess::flush() {
	ERR_FAIL_COND(!f);
	fflush(f);

	if (prev_op == WRITE) {
		prev_op = 0;
	}
}

void FileAccess::store_8(uint8_t p_dest) {
	ERR_FAIL_COND(!f);
	if (flags == READ_WRITE || flags == WRITE_READ) {
		if (prev_op == READ) {
			if (last_error != ERR_FILE_EOF) {
				fseek(f, 0, SEEK_CUR);
			}
		}
		prev_op = WRITE;
	}
	fwrite(&p_dest, 1, 1, f);
}

void FileAccess::store_buffer(const uint8_t *p_src, uint64_t p_length) {
	ERR_FAIL_COND(!f);
	ERR_FAIL_COND(!p_src && p_length > 0);

	if (flags == READ_WRITE || flags == WRITE_READ) {
		if (prev_op == READ) {
			if (last_error != ERR_FILE_EOF) {
				fseek(f, 0, SEEK_CUR);
			}
		}
		prev_op = WRITE;
	}
	ERR_FAIL_COND(fwrite(p_src, 1, p_length, f) != (size_t)p_length);
}

bool FileAccess::file_exists(const String &p_name) {
	String filename = fix_path(p_name);

	FILE *g = _wfsopen((LPCWSTR)(filename.utf16().get_data()), L"rb", _SH_DENYNO);

	if (g == nullptr) {
		return false;
	} else {
		fclose(g);
		return true;
	}
}

uint64_t FileAccess::_get_modified_time(const String &p_file) {
	String file = fix_path(p_file);
	if (file.ends_with("/") && file != "/")
		file = file.substr(0, file.length() - 1);

	struct _stat st;
	int rv = _wstat((LPCWSTR)(file.utf16().get_data()), &st);

	if (rv == 0) {
		return st.st_mtime;
	} else {
		LOG_TRACE("Failed to get modified time for: " + p_file + "");
		return 0;
	}
}

uint32_t FileAccess::_get_unix_permissions(const String &p_file) {
	return 0;
}

Error FileAccess::_set_unix_permissions(const String &p_file, uint32_t p_permissions) {
	return ERR_UNAVAILABLE;
}

FileAccess::FileAccess() :
		f(NULL),
		flags(0),
		prev_op(0),
		last_error(OK) {
}
FileAccess::~FileAccess() {
	close();
}

#else

void FileAccess::check_errors() const {
	ERR_FAIL_COND_MSG(!f, "File must be opened before use.");

	if (feof(f)) {
		last_error = ERR_FILE_EOF;
	}
}

Error FileAccess::_open(const String &p_path, int p_mode_flags) {
	if (f) {
		fclose(f);
	}
	f = nullptr;

	path_src = p_path;
	path = fix_path(p_path);
	//printf("opening %s, %i\n", path.utf8().get_data(), Memory::get_static_mem_usage());

	ERR_FAIL_COND_V_MSG(f, ERR_ALREADY_IN_USE, "File is already in use.");
	const char *mode_string;

	if (p_mode_flags == READ) {
		mode_string = "rb";
	} else if (p_mode_flags == WRITE) {
		mode_string = "wb";
	} else if (p_mode_flags == READ_WRITE) {
		mode_string = "rb+";
	} else if (p_mode_flags == WRITE_READ) {
		mode_string = "wb+";
	} else {
		return ERR_INVALID_PARAMETER;
	}

	/* pretty much every implementation that uses fopen as primary
	   backend (unix-compatible mostly) supports utf8 encoding */

	//printf("opening %s as %s\n", p_path.utf8().get_data(), path.utf8().get_data());
	struct stat st;
	int err = stat(path.utf8().get_data(), &st);
	if (!err) {
		switch (st.st_mode & S_IFMT) {
			case S_IFLNK:
			case S_IFREG:
				break;
			default:
				return ERR_FILE_CANT_OPEN;
		}
	}

	if (is_backup_save_enabled() && (p_mode_flags & WRITE) && !(p_mode_flags & READ)) {
		save_path = path;
		path = path + ".tmp";
	}

	f = fopen(path.utf8().get_data(), mode_string);

	if (f == nullptr) {
		switch (errno) {
			case ENOENT: {
				last_error = ERR_FILE_NOT_FOUND;
			} break;
			default: {
				last_error = ERR_FILE_CANT_OPEN;
			} break;
		}
		return last_error;
	}

	// Set close on exec to avoid leaking it to subprocesses.
	int fd = fileno(f);

	if (fd != -1) {
#if defined(NO_FCNTL)
		unsigned long par = 0;
		ioctl(fd, FIOCLEX, &par);
#else
		int opts = fcntl(fd, F_GETFD);
		fcntl(fd, F_SETFD, opts | FD_CLOEXEC);
#endif
	}

	last_error = OK;
	flags = p_mode_flags;
	return OK;
}

void FileAccess::close() {
	if (!f) {
		return;
	}

	fclose(f);
	f = nullptr;

	if (close_notification_func) {
		close_notification_func(path, flags);
	}

	if (save_path != "") {
		int rename_error = rename((save_path + ".tmp").utf8().get_data(), save_path.utf8().get_data());

		if (rename_error && close_fail_notify) {
			close_fail_notify(save_path);
		}

		save_path = "";
		ERR_FAIL_COND(rename_error != 0);
	}
}

bool FileAccess::is_open() const {
	return (f != nullptr);
}

String FileAccess::get_path() const {
	return path_src;
}

String FileAccess::get_path_absolute() const {
	return path;
}

void FileAccess::seek(uint64_t p_position) {
	ERR_FAIL_COND_MSG(!f, "File must be opened before use.");

	last_error = OK;
	if (fseeko(f, p_position, SEEK_SET)) {
		check_errors();
	}
}

void FileAccess::seek_end(int64_t p_position) {
	ERR_FAIL_COND_MSG(!f, "File must be opened before use.");

	if (fseeko(f, p_position, SEEK_END)) {
		check_errors();
	}
}

uint64_t FileAccess::get_position() const {
	ERR_FAIL_COND_V_MSG(!f, 0, "File must be opened before use.");

	int64_t pos = ftello(f);
	if (pos < 0) {
		check_errors();
		ERR_FAIL_V(0);
	}
	return pos;
}

uint64_t FileAccess::get_len() const {
	ERR_FAIL_COND_V_MSG(!f, 0, "File must be opened before use.");

	int64_t pos = ftello(f);
	ERR_FAIL_COND_V(pos < 0, 0);
	ERR_FAIL_COND_V(fseeko(f, 0, SEEK_END), 0);
	int64_t size = ftello(f);
	ERR_FAIL_COND_V(size < 0, 0);
	ERR_FAIL_COND_V(fseeko(f, pos, SEEK_SET), 0);

	return size;
}

bool FileAccess::eof_reached() const {
	return last_error == ERR_FILE_EOF;
}

uint8_t FileAccess::get_8() const {
	ERR_FAIL_COND_V_MSG(!f, 0, "File must be opened before use.");
	uint8_t b;
	if (fread(&b, 1, 1, f) == 0) {
		check_errors();
		b = '\0';
	}
	return b;
}

uint64_t FileAccess::get_buffer(uint8_t *p_dst, uint64_t p_length) const {
	ERR_FAIL_COND_V(!p_dst && p_length > 0, -1);
	ERR_FAIL_COND_V_MSG(!f, -1, "File must be opened before use.");

	uint64_t read = fread(p_dst, 1, p_length, f);
	check_errors();
	return read;
};

Error FileAccess::get_error() const {
	return last_error;
}

void FileAccess::flush() {
	ERR_FAIL_COND_MSG(!f, "File must be opened before use.");
	fflush(f);
}

void FileAccess::store_8(uint8_t p_dest) {
	ERR_FAIL_COND_MSG(!f, "File must be opened before use.");
	ERR_FAIL_COND(fwrite(&p_dest, 1, 1, f) != 1);
}

void FileAccess::store_buffer(const uint8_t *p_src, uint64_t p_length) {
	ERR_FAIL_COND_MSG(!f, "File must be opened before use.");
	ERR_FAIL_COND(!p_src && p_length > 0);
	ERR_FAIL_COND(fwrite(p_src, 1, p_length, f) != p_length);
}

bool FileAccess::file_exists(const String &p_path) {
	int err;
	struct stat st;
	String filename = fix_path(p_path);

	// Does the name exist at all?
	err = stat(filename.utf8().get_data(), &st);
	if (err) {
		return false;
	}

#if defined(_WIN64) || defined(_WIN32)
	if (_access(filename.utf8().get_data(), 4) == -1) {
		return false;
	}
#else
	// See if we have access to the file
	if (access(filename.utf8().get_data(), F_OK)) {
		return false;
	}
#endif

	// See if this is a regular file
	switch (st.st_mode & S_IFMT) {
		case S_IFLNK:
		case S_IFREG:
			return true;
		default:
			return false;
	}
}

uint64_t FileAccess::_get_modified_time(const String &p_file) {
	String file = fix_path(p_file);
	struct stat flags;
	int err = stat(file.utf8().get_data(), &flags);

	if (!err) {
		return flags.st_mtime;
	} else {
		LOG_TRACE("Failed to get modified time for: " + p_file + "");
		return 0;
	};
}

uint32_t FileAccess::_get_unix_permissions(const String &p_file) {
	String file = fix_path(p_file);
	struct stat flags;
	int err = stat(file.utf8().get_data(), &flags);

	if (!err) {
		return flags.st_mode & 0x7FF; //only permissions
	} else {
		ERR_FAIL_V_MSG(0, "Failed to get unix permissions for: " + p_file + ".");
	};
}

Error FileAccess::_set_unix_permissions(const String &p_file, uint32_t p_permissions) {
	String file = fix_path(p_file);

	int err = chmod(file.utf8().get_data(), p_permissions);
	if (!err) {
		return OK;
	}

	return FAILED;
}

FileCloseNotificationFunc FileAccess::close_notification_func = nullptr;

FileAccess::FileAccess() :
		f(nullptr),
		flags(0),
		last_error(OK) {
	endian_swap = false;
	real_is_double = false;
}

FileAccess::~FileAccess() {
	close();
}

#endif

FileAccess::FileCloseFailNotify FileAccess::close_fail_notify = nullptr;

bool FileAccess::backup_save = false;

FileAccess *FileAccess::create() {
	return memnew(FileAccess());
}

bool FileAccess::exists(const String &p_name) {
	FileAccess *f = create_and_open(p_name, READ);
	if (!f) {
		return false;
	}
	memdelete(f);
	return true;
}

Error FileAccess::reopen(const String &p_path, int p_mode_flags) {
	return _open(p_path, p_mode_flags);
};

Error FileAccess::open(const String &p_path, int p_mode_flags) {
	return _open(p_path, p_mode_flags);
}

FileAccess *FileAccess::create_and_open(const String &p_path, int p_mode_flags, Error *r_error) {
	//try packed data first

	FileAccess *ret = nullptr;

	ret = create();
	Error err = ret->_open(p_path, p_mode_flags);

	if (r_error) {
		*r_error = err;
	}
	if (err != OK) {
		memdelete(ret);
		ret = nullptr;
	}

	return ret;
}

String FileAccess::fix_path(const String &p_path) const {
	//helper used by file accesses that use a single filesystem

	String r_path = p_path.replace("\\", "/");

	return r_path;
}

/* these are all implemented for ease of porting, then can later be optimized */

uint16_t FileAccess::get_16() const {
	uint16_t res;
	uint8_t a, b;

	a = get_8();
	b = get_8();

	if (endian_swap) {
		SWAP(a, b);
	}

	res = b;
	res <<= 8;
	res |= a;

	return res;
}
uint32_t FileAccess::get_32() const {
	uint32_t res;
	uint16_t a, b;

	a = get_16();
	b = get_16();

	if (endian_swap) {
		SWAP(a, b);
	}

	res = b;
	res <<= 16;
	res |= a;

	return res;
}
uint64_t FileAccess::get_64() const {
	uint64_t res;
	uint32_t a, b;

	a = get_32();
	b = get_32();

	if (endian_swap) {
		SWAP(a, b);
	}

	res = b;
	res <<= 32;
	res |= a;

	return res;
}

float FileAccess::get_float() const {
	MarshallFloat m;
	m.i = get_32();
	return m.f;
};

real_t FileAccess::get_real() const {
	if (real_is_double) {
		return get_double();
	} else {
		return get_float();
	}
}

double FileAccess::get_double() const {
	MarshallDouble m;
	m.l = get_64();
	return m.d;
};

String FileAccess::get_token() const {
	CharString token;

	CharType c = get_8();

	while (!eof_reached()) {
		if (c <= ' ') {
			if (token.length()) {
				break;
			}
		} else {
			token += c;
		}
		c = get_8();
	}

	return String::utf8(token.get_data());
}

class CharBuffer {
	Vector<char> vector;
	char stack_buffer[256];

	char *buffer;
	int capacity;
	int written;

	bool grow() {
		if (vector.resize(next_power_of_2(1 + written)) != OK) {
			return false;
		}

		if (buffer == stack_buffer) { // first chunk?

			for (int i = 0; i < written; i++) {
				vector.write[i] = stack_buffer[i];
			}
		}

		buffer = vector.ptrw();
		capacity = vector.size();
		ERR_FAIL_COND_V(written >= capacity, false);

		return true;
	}

public:
	_FORCE_INLINE_ CharBuffer() :
			buffer(stack_buffer),
			capacity(sizeof(stack_buffer) / sizeof(char)),
			written(0) {
	}

	_FORCE_INLINE_ void push_back(char c) {
		if (written >= capacity) {
			ERR_FAIL_COND(!grow());
		}

		buffer[written++] = c;
	}

	_FORCE_INLINE_ const char *get_data() const {
		return buffer;
	}
};

String FileAccess::get_line() const {
	CharBuffer line;

	CharType c = get_8();

	while (!eof_reached()) {
		if (c == '\n' || c == '\0') {
			line.push_back(0);
			return String::utf8(line.get_data());
		} else if (c != '\r') {
			line.push_back(c);
		}

		c = get_8();
	}
	line.push_back(0);
	return String::utf8(line.get_data());
}

Vector<String> FileAccess::get_csv_line(const String &p_delim) const {
	ERR_FAIL_COND_V_MSG(p_delim.length() != 1, Vector<String>(), "Only single character delimiters are supported to parse CSV lines.");
	ERR_FAIL_COND_V_MSG(p_delim[0] == '"', Vector<String>(), "The double quotation mark character (\") is not supported as a delimiter for CSV lines.");

	String line;

	// CSV can support entries with line breaks as long as they are enclosed
	// in double quotes. So our "line" might be more than a single line in the
	// text file.
	int qc = 0;
	do {
		if (eof_reached()) {
			break;
		}
		line += get_line() + "\n";
		qc = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '"') {
				qc++;
			}
		}
	} while (qc % 2);

	// Remove the extraneous newline we've added above.
	line = line.substr(0, line.length() - 1);

	Vector<String> strings;

	bool in_quote = false;
	String current;
	for (int i = 0; i < line.length(); i++) {
		CharType c = line[i];
		// A delimiter ends the current entry, unless it's in a quoted string.
		if (!in_quote && c == p_delim[0]) {
			strings.push_back(current);
			current = String();
		} else if (c == '"') {
			// Doubled quotes are escapes for intentional quotes in the string.
			if (line[i + 1] == '"' && in_quote) {
				current += '"';
				i++;
			} else {
				in_quote = !in_quote;
			}
		} else {
			current += c;
		}
	}
	strings.push_back(current);

	return strings;
}

/*
uint64_t FileAccess::get_buffer(uint8_t *p_dst, uint64_t p_length) const {
	ERR_FAIL_COND_V(!p_dst && p_length > 0, -1);

	uint64_t i = 0;
	for (i = 0; i < p_length && !eof_reached(); i++) {
		p_dst[i] = get_8();
	}

	return i;
}
*/

String FileAccess::get_as_utf8_string(bool p_skip_cr) const {
	Vector<uint8_t> sourcef;
	uint64_t len = get_len();
	sourcef.resize(len + 1);

	uint8_t *w = sourcef.ptrw();
	uint64_t r = get_buffer(w, len);
	ERR_FAIL_COND_V(r != len, String());
	w[len] = 0;

	String s;
	if (s.parse_utf8((const char *)w, -1, p_skip_cr)) {
		return String();
	}

	return s;
}

void FileAccess::store_16(uint16_t p_dest) {
	uint8_t a, b;

	a = p_dest & 0xFF;
	b = p_dest >> 8;

	if (endian_swap) {
		SWAP(a, b);
	}

	store_8(a);
	store_8(b);
}
void FileAccess::store_32(uint32_t p_dest) {
	uint16_t a, b;

	a = p_dest & 0xFFFF;
	b = p_dest >> 16;

	if (endian_swap) {
		SWAP(a, b);
	}

	store_16(a);
	store_16(b);
}
void FileAccess::store_64(uint64_t p_dest) {
	uint32_t a, b;

	a = p_dest & 0xFFFFFFFF;
	b = p_dest >> 32;

	if (endian_swap) {
		SWAP(a, b);
	}

	store_32(a);
	store_32(b);
}

void FileAccess::store_real(real_t p_real) {
	if (sizeof(real_t) == 4) {
		store_float(p_real);
	} else {
		store_double(p_real);
	}
}

void FileAccess::store_float(float p_dest) {
	MarshallFloat m;
	m.f = p_dest;
	store_32(m.i);
};

void FileAccess::store_double(double p_dest) {
	MarshallDouble m;
	m.d = p_dest;
	store_64(m.l);
};

uint64_t FileAccess::get_modified_time(const String &p_file) {
	FileAccess *fa = create();
	ERR_FAIL_COND_V_MSG(!fa, 0, "Cannot create FileAccess for path '" + p_file + "'.");

	uint64_t mt = fa->_get_modified_time(p_file);
	memdelete(fa);
	return mt;
}

uint32_t FileAccess::get_unix_permissions(const String &p_file) {
	FileAccess *fa = create();
	ERR_FAIL_COND_V_MSG(!fa, 0, "Cannot create FileAccess for path '" + p_file + "'.");

	uint32_t mt = fa->_get_unix_permissions(p_file);
	memdelete(fa);
	return mt;
}

Error FileAccess::set_unix_permissions(const String &p_file, uint32_t p_permissions) {
	FileAccess *fa = create();
	ERR_FAIL_COND_V_MSG(!fa, ERR_CANT_CREATE, "Cannot create FileAccess for path '" + p_file + "'.");

	Error err = fa->_set_unix_permissions(p_file, p_permissions);
	memdelete(fa);
	return err;
}

void FileAccess::store_string(const String &p_string) {
	if (p_string.length() == 0) {
		return;
	}

	CharString cs = p_string.utf8();
	store_buffer((uint8_t *)&cs[0], cs.length());
}

void FileAccess::store_pascal_string(const String &p_string) {
	CharString cs = p_string.utf8();
	store_32(cs.length());
	store_buffer((uint8_t *)&cs[0], cs.length());
};

String FileAccess::get_pascal_string() {
	uint32_t sl = get_32();
	CharString cs;
	cs.resize(sl + 1);
	get_buffer((uint8_t *)cs.ptr(), sl);
	cs[sl] = 0;

	String ret;
	ret.parse_utf8(cs.ptr());

	return ret;
};

void FileAccess::store_line(const String &p_line) {
	store_string(p_line);
	store_8('\n');
}

void FileAccess::store_csv_line(const Vector<String> &p_values, const String &p_delim) {
	ERR_FAIL_COND(p_delim.length() != 1);

	String line = "";
	int size = p_values.size();
	for (int i = 0; i < size; ++i) {
		String value = p_values[i];

		if (value.find("\"") != -1 || value.find(p_delim) != -1 || value.find("\n") != -1) {
			value = "\"" + value.replace("\"", "\"\"") + "\"";
		}
		if (i < size - 1) {
			value += p_delim;
		}

		line += value;
	}

	store_line(line);
}

void FileAccess::store_buffer_vec(const Vector<uint8_t> &data) {
	store_buffer(data.ptr(), data.size());
}

/*
void FileAccess::store_buffer(const uint8_t *p_src, uint64_t p_length) {
	ERR_FAIL_COND(!p_src && p_length > 0);
	for (uint64_t i = 0; i < p_length; i++) {
		store_8(p_src[i]);
	}
}
*/

Vector<uint8_t> FileAccess::get_file_as_array(const String &p_path, Error *r_error) {
	FileAccess *f = FileAccess::create_and_open(p_path, READ, r_error);
	if (!f) {
		if (r_error) { // if error requested, do not throw error
			return Vector<uint8_t>();
		}
		ERR_FAIL_V_MSG(Vector<uint8_t>(), "Can't open file from path '" + String(p_path) + "'.");
	}
	Vector<uint8_t> data;
	data.resize(f->get_len());
	f->get_buffer(data.ptrw(), data.size());
	memdelete(f);
	return data;
}

String FileAccess::get_file_as_string(const String &p_path, Error *r_error) {
	Error err;
	Vector<uint8_t> array = get_file_as_array(p_path, &err);
	if (r_error) {
		*r_error = err;
	}
	if (err != OK) {
		if (r_error) {
			return String();
		}
		ERR_FAIL_V_MSG(String(), "Can't get file as string from path '" + String(p_path) + "'.");
	}

	String ret;
	ret.parse_utf8((const char *)array.ptr(), array.size());
	return ret;
}

void FileAccess::write_file(const String &p_path, const String &data, Error *r_error) {
	FileAccess *f = FileAccess::create_and_open(p_path, WRITE, r_error);
	if (!f) {
		if (r_error) { // if error requested, do not throw error
			return;
		}

		ERR_FAIL_MSG("Can't open file from path '" + String(p_path) + "'.");
	}

	f->store_string(data);
	f->close();
	memdelete(f);
}
void FileAccess::write_file_buffer(const String &p_path, const Vector<uint8_t> &data, Error *r_error) {
	FileAccess *f = FileAccess::create_and_open(p_path, WRITE, r_error);
	if (!f) {
		if (r_error) { // if error requested, do not throw error
			return;
		}

		ERR_FAIL_MSG("Can't open file from path '" + String(p_path) + "'.");
	}

	f->store_buffer_vec(data);
	f->close();
	memdelete(f);
}

/*
FileAccess::FileAccess() {
	endian_swap = false;
	real_is_double = false;
};
*/
