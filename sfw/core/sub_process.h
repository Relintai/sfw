//--STRIP
#ifndef SUB_PROCESS_H
#define SUB_PROCESS_H
//--STRIP

/*************************************************************************/
/*  sub_process.h                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/list.h"
#include "core/math_defs.h"
#include "core/memory.h"
#include "core/mutex.h"
#include "core/typedefs.h"
#include "core/ustring.h"
#include "core/error_list.h"

#include <stdio.h>
//--STRIP

#if defined(_WIN64) || defined(_WIN32)

//--STRIP
#include "core/local_vector.h"
//--STRIP

#endif

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

	String get_executable_path() const;
	void set_executable_path(const String &p_executable_path);

	Vector<String> get_arguments() const;
	void set_arguments(const Vector<String> &p_arguments);

	bool get_blocking() const;
	void set_blocking(const bool p_value);

	bool get_read_output() const;
	void set_read_output(const bool p_value);

	bool get_read_std() const;
	void set_read_std(const bool p_value);

	bool get_read_std_err() const;
	void set_read_std_err(const bool p_value);

	bool get_use_pipe_mutex() const;
	void set_use_pipe_mutex(const bool p_value);

	bool get_open_console() const;
	void set_open_console(const bool p_value);

	String get_data() const {
		return _pipe;
	}

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
	virtual Error send_data(const String &p_data);
	virtual bool is_process_running() const;

	Error run(const String &p_executable_path, const Vector<String> &p_arguments = Vector<String>(), bool p_output = true, bool p_blocking = true, bool p_read_std_err = false, bool p_use_pipe_mutex = false, bool p_open_console = false);

	SubProcess();
	virtual ~SubProcess();

protected:
	void _setup_pipe_mutex();

	String _executable_path;
	Vector<String> _arguments;

	bool _blocking;

	bool _read_output;

	bool _read_std;
	bool _read_std_err;

	String _pipe;

	bool _use_pipe_mutex;

	Mutex *_pipe_mutex;

	bool _open_console;

	ProcessID _process_id;
	int _exitcode;

#if defined(_WIN64) || defined(_WIN32)

	String _quote_command_line_argument(const String &p_text) const;
	void _append_to_pipe(char *p_bytes, int p_size);

	bool _process_started;
	LocalVector<char> _bytes;

	SubProcessWindowsData *_data;

#else
	FILE *_process_fp;
	char _process_buf[65535];
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
