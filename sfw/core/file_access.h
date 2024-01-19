//--STRIP
#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H
//--STRIP

/*************************************************************************/
/*  file_access.h                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_list.h"
#include "core/math_defs.h"
#include "core/ustring.h"
//--STRIP

#if defined(_WIN64) || defined(_WIN32)

// Mingw
struct _iobuf;
typedef struct _iobuf FILE;

#elif defined(__APPLE__)

struct __sFILE;
typedef struct __sFILE FILE;

typedef void (*FileCloseNotificationFunc)(const String &p_file, int p_flags);

#else
struct _IO_FILE;
typedef struct _IO_FILE FILE;

typedef void (*FileCloseNotificationFunc)(const String &p_file, int p_flags);
#endif

class FileAccess {
public:
	typedef void (*FileCloseFailNotify)(const String &);

	bool endian_swap;
	bool real_is_double;

	virtual uint32_t _get_unix_permissions(const String &p_file);
	virtual Error _set_unix_permissions(const String &p_file, uint32_t p_permissions);

protected:
	String fix_path(const String &p_path) const;
	virtual Error _open(const String &p_path, int p_mode_flags); ///< open a file
	virtual uint64_t _get_modified_time(const String &p_file);

	static FileCloseFailNotify close_fail_notify;

private:
	static bool backup_save;

public:
	static void set_file_close_fail_notify_callback(FileCloseFailNotify p_cbk) { close_fail_notify = p_cbk; }

	enum ModeFlags {
		READ = 1,
		WRITE = 2,
		READ_WRITE = 3,
		WRITE_READ = 7,
	};

	virtual void close(); ///< close a file
	virtual bool is_open() const; ///< true when file is open

	virtual String get_path() const; /// returns the path for the current open file
	virtual String get_path_absolute() const; /// returns the absolute path for the current open file

	virtual void seek(uint64_t p_position); ///< seek to a given position
	virtual void seek_end(int64_t p_position = 0); ///< seek from the end of file with negative offset
	virtual uint64_t get_position() const; ///< get position in the file
	virtual uint64_t get_len() const; ///< get size of the file

	virtual bool eof_reached() const; ///< reading passed EOF

	virtual uint8_t get_8() const; ///< get a byte
	virtual uint16_t get_16() const; ///< get 16 bits uint
	virtual uint32_t get_32() const; ///< get 32 bits uint
	virtual uint64_t get_64() const; ///< get 64 bits uint

	virtual float get_float() const;
	virtual double get_double() const;
	virtual real_t get_real() const;

	virtual uint64_t get_buffer(uint8_t *p_dst, uint64_t p_length) const; ///< get an array of bytes
	virtual String get_line() const;
	virtual String get_token() const;
	virtual Vector<String> get_csv_line(const String &p_delim = ",") const;
	virtual String get_as_utf8_string(bool p_skip_cr = true) const; // Skip CR by default for compat.

	/**< use this for files WRITTEN in _big_ endian machines (ie, amiga/mac)
	 * It's not about the current CPU type but file formats.
	 * this flags get reset to false (little endian) on each open
	 */

	virtual void set_endian_swap(bool p_swap) { endian_swap = p_swap; }
	inline bool get_endian_swap() const { return endian_swap; }

	virtual Error get_error() const; ///< get last error

	virtual void flush();
	virtual void store_8(uint8_t p_dest); ///< store a byte
	virtual void store_16(uint16_t p_dest); ///< store 16 bits uint
	virtual void store_32(uint32_t p_dest); ///< store 32 bits uint
	virtual void store_64(uint64_t p_dest); ///< store 64 bits uint

	virtual void store_float(float p_dest);
	virtual void store_double(double p_dest);
	virtual void store_real(real_t p_real);

	virtual void store_string(const String &p_string);
	virtual void store_line(const String &p_line);
	virtual void store_csv_line(const Vector<String> &p_values, const String &p_delim = ",");

	virtual void store_pascal_string(const String &p_string);
	virtual String get_pascal_string();

	void store_buffer_vec(const Vector<uint8_t> &data); ///< store an array of bytes
	virtual void store_buffer(const uint8_t *p_src, uint64_t p_length); ///< store an array of bytes

	virtual bool file_exists(const String &p_name); ///< return true if a file exists

	virtual Error reopen(const String &p_path, int p_mode_flags); ///< does not change the AccessType

	static FileAccess *create(); /// Helper that Creates a file access
	static FileAccess *create_and_open(const String &p_path, int p_mode_flags, Error *r_error = nullptr); /// Create a file access (for the current platform) this is the only portable way of accessing files.
	static bool exists(const String &p_name); ///< return true if a file exists
	static uint64_t get_modified_time(const String &p_file);
	static uint32_t get_unix_permissions(const String &p_file);
	static Error set_unix_permissions(const String &p_file, uint32_t p_permissions);

	static void set_backup_save(bool p_enable) { backup_save = p_enable; };
	static bool is_backup_save_enabled() { return backup_save; };

	static Vector<uint8_t> get_file_as_array(const String &p_path, Error *r_error = nullptr);
	static String get_file_as_string(const String &p_path, Error *r_error = nullptr);

	FileAccess();
	virtual ~FileAccess();

#if defined(_WIN64) || defined(_WIN32)
#else
	static FileCloseNotificationFunc close_notification_func;
#endif

protected:
#if defined(_WIN64) || defined(_WIN32)
	void check_errors() const;

	FILE *f;
	int flags;
	mutable int prev_op;
	mutable Error last_error;
	String path;
	String path_src;
	String save_path;
#else
	void check_errors() const;

	FILE *f;
	int flags;

	mutable Error last_error;
	String save_path;
	String path;
	String path_src;
#endif
};

struct FileAccessRef {
	FileAccess *f;

	_FORCE_INLINE_ bool is_null() const { return f == nullptr; }
	_FORCE_INLINE_ bool is_valid() const { return f != nullptr; }

	_FORCE_INLINE_ operator bool() const { return f != nullptr; }
	_FORCE_INLINE_ operator FileAccess *() { return f; }

	_FORCE_INLINE_ FileAccess *operator->() {
		return f;
	}

	FileAccessRef(FileAccess *fa) { f = fa; }
	FileAccessRef(FileAccessRef &&other) {
		f = other.f;
		other.f = nullptr;
	}
	~FileAccessRef() {
		if (f) {
			memdelete(f);
		}
	}
};

//--STRIP
#endif
//--STRIP
