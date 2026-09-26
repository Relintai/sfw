//--STRIP
#ifndef SUB_PROCESS_H
#define SUB_PROCESS_H
//--STRIP

/*************************************************************************/
/*  sub_process.h                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/error_list.h"
#include "core/hash_map.h"
#include "core/list.h"
#include "core/local_vector.h"
#include "core/math_defs.h"
#include "core/memory.h"
#include "core/mutex.h"
#include "core/string_name.h"
#include "core/typedefs.h"
#include "core/ustring.h"

#include <stdio.h>
//--STRIP

/**
 * Multi-Platform abstraction for running and communicating with sub processes
 */

class SubProcess {
public:
	typedef int64_t ProcessID;

#if defined(_WIN64) || defined(_WIN32)
	struct SubProcessWindowsData;
#endif

	static SubProcess *create();

	enum SubProcessCommunicationFlags {
		COMMUNICATION_FLAGS_NONE = 0,
		COMMUNICATION_FLAGS_STDOUT = 1 << 0,
		COMMUNICATION_FLAGS_STDERR = 1 << 1,
		COMMUNICATION_FLAGS_STDIN = 1 << 2,

		COMMUNICATION_FLAGS_READ = COMMUNICATION_FLAGS_STDOUT | COMMUNICATION_FLAGS_STDERR,
		COMMUNICATION_FLAGS_WRITE = COMMUNICATION_FLAGS_STDIN,
		COMMUNICATION_FLAGS_ALL = COMMUNICATION_FLAGS_STDOUT | COMMUNICATION_FLAGS_STDERR | COMMUNICATION_FLAGS_STDIN,
	};

	String get_executable_path() const;
	void set_executable_path(const String &p_executable_path);

	Vector<String> get_arguments() const;
	void set_arguments(const Vector<String> &p_arguments);

	bool get_blocking() const;
	void set_blocking(const bool p_value);

	int get_communication_flags() const;
	void set_communication_flags(const int p_flags);

	bool get_use_pipe_mutex() const;
	void set_use_pipe_mutex(const bool p_value);

	bool get_open_console() const;
	void set_open_console(const bool p_value);

	// Environment

	bool get_inherit_environment() const;
	void set_inherit_environment(const bool p_value);

	bool has_environment_variable(const StringName &p_key);
	String get_environment_variable(const StringName &p_key);
	void set_environment_variable(const StringName &p_key, const String &p_value);
	void unset_environment_variable(const StringName &p_key);
	void clear_environment_variables();

	Vector<String> get_environment_variable_keys();

	// Other getters

	String get_std_out();
	String get_std_err();

	int get_process_id() const {
		return _process_id;
	}

	int get_exitcode() const {
		return _exitcode;
	}

	virtual Error start();
	virtual Error stop();
	virtual Error poll();
	virtual Error send_signal(const int p_signal);

	virtual Error write_to_stdin(const String &p_data);
	virtual Error write_to_stdin_utf8(const String &p_data);
	virtual Error write_to_stdin_utf16(const String &p_data);
	virtual Error write_to_stdin_utf32(const String &p_data);
	virtual Error write_data_to_stdin(const Vector<uint8_t> &p_data);

	virtual bool is_process_running() const;

	Error run(const String &p_executable_path, const Vector<String> &p_arguments = Vector<String>(), const int p_communication_flags = COMMUNICATION_FLAGS_STDOUT, bool p_blocking = true, bool p_use_pipe_mutex = false, bool p_open_console = false);

	SubProcess();
	virtual ~SubProcess();

protected:
	void _setup_pipe_mutex();

	String _executable_path;
	Vector<String> _arguments;

	bool _blocking;

	int _communication_flags;

	String _std_out;
	String _std_err;

	bool _use_pipe_mutex;

	bool _inherit_environment;
	HashMap<StringName, String> _environment_variables;

	Mutex *_std_out_mutex;
	Mutex *_std_err_mutex;
	Mutex *_std_in_mutex;

	bool _open_console;

	ProcessID _process_id;
	int _exitcode;

#if defined(_WIN64) || defined(_WIN32)

	bool _read_from_std_out(int &bytes_in_buffer);
	bool _read_from_std_err(int &err_bytes_in_buffer);

	bool _poll_read_from_std_out();
	bool _poll_read_from_std_err();

	String _quote_command_line_argument(const String &p_text) const;
	void _append_to_std_out(char *p_bytes, int p_size);
	void _append_to_std_err(char *p_bytes, int p_size);

	bool _process_started;

	LocalVector<char> _bytes;
	LocalVector<char> _err_bytes;

	SubProcessWindowsData *_data;

#else
	bool _read_from_std_out(int &bytes_in_buffer);
	bool _read_from_std_err(int &err_bytes_in_buffer);

	bool _poll_read_from_std_out();
	bool _poll_read_from_std_err();

	void _append_to_std_out(char *p_bytes, int p_size);
	void _append_to_std_err(char *p_bytes, int p_size);

	LocalVector<char> _bytes;
	LocalVector<char> _err_bytes;

	// Pipes are unidirectional, [0] is the read end, [1] is the write end
	int _read_std_pipes[2];
	int _read_std_err_pipes[2];
	int _write_pipes[2];
#endif
};

struct SubProcessRef {
	SubProcess *f;

	_FORCE_INLINE_ bool is_null() const { return f == nullptr; }
	_FORCE_INLINE_ bool is_valid() const { return f != nullptr; }

	_FORCE_INLINE_ operator bool() const { return f != nullptr; }
	_FORCE_INLINE_ operator SubProcess *() { return f; }

	_FORCE_INLINE_ SubProcess *operator->() {
		return f;
	}

	SubProcessRef(SubProcess *fa) { f = fa; }
	SubProcessRef(SubProcessRef &&other) {
		f = other.f;
		other.f = nullptr;
	}
	~SubProcessRef() {
		if (f) {
			memdelete(f);
		}
	}
};

//--STRIP
#endif
//--STRIP
