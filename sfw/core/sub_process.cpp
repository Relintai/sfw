/*************************************************************************/
/*  sub_process.cpp                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "sub_process.h"
//--STRIP

#if defined(_WIN64) || defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef struct tagLOGCONTEXTW {
	WCHAR lcName[40];
	UINT lcOptions;
	UINT lcStatus;
	UINT lcLocks;
	UINT lcMsgBase;
	UINT lcDevice;
	UINT lcPktRate;
	DWORD lcPktData;
	DWORD lcPktMode;
	DWORD lcMoveMask;
	DWORD lcBtnDnMask;
	DWORD lcBtnUpMask;
	LONG lcInOrgX;
	LONG lcInOrgY;
	LONG lcInOrgZ;
	LONG lcInExtX;
	LONG lcInExtY;
	LONG lcInExtZ;
	LONG lcOutOrgX;
	LONG lcOutOrgY;
	LONG lcOutOrgZ;
	LONG lcOutExtX;
	LONG lcOutExtY;
	LONG lcOutExtZ;
	DWORD lcSensX;
	DWORD lcSensY;
	DWORD lcSensZ;
	BOOL lcSysMode;
	int lcSysOrgX;
	int lcSysOrgY;
	int lcSysExtX;
	int lcSysExtY;
	DWORD lcSysSensX;
	DWORD lcSysSensY;
} LOGCONTEXTW;

typedef HANDLE(WINAPI *WTOpenPtr)(HWND p_window, LOGCONTEXTW *p_ctx, BOOL p_enable);

// TODO clean these up
#include <avrt.h>
#include <direct.h>
#include <knownfolders.h>
#include <process.h>
#include <regstr.h>
#include <shlobj.h>
#include <wchar.h>

struct SubProcess::SubProcessWindowsData {
	struct ProcessInfo {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
	};

	HANDLE _pipe_handles[2];
	ProcessInfo _process_info;
};

Error SubProcess::start() {
	if (_executable_path.empty()) {
		return ERR_FILE_BAD_PATH;
	}

	if (is_process_running()) {
		return ERR_BUSY;
	}

	String path = _executable_path.replace("/", "\\");

	String cmdline = _quote_command_line_argument(path);
	for (int i = 0; i < _arguments.size(); ++i) {
		cmdline += " " + _quote_command_line_argument(_arguments[i]);
	}

	ZeroMemory(&_data->_process_info.si, sizeof(_data->_process_info.si));
	_data->_process_info.si.cb = sizeof(_data->_process_info.si);
	ZeroMemory(&_data->_process_info.pi, sizeof(_data->_process_info.pi));
	LPSTARTUPINFOW si_w = (LPSTARTUPINFOW)&_data->_process_info.si;

	Char16String modstr = cmdline.utf16(); // Windows wants to change this no idea why.

	bool inherit_handles = false;

	if (_read_output) {
		// Create pipe for StdOut and StdErr.
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;
		sa.lpSecurityDescriptor = NULL;

		ERR_FAIL_COND_V(!CreatePipe(&_data->_pipe_handles[0], &_data->_pipe_handles[1], &sa, 0), ERR_CANT_FORK);
		ERR_FAIL_COND_V(!SetHandleInformation(_data->_pipe_handles[0], HANDLE_FLAG_INHERIT, 0), ERR_CANT_FORK); // Read handle is for host process only and should not be inherited.

		_data->_process_info.si.dwFlags |= STARTF_USESTDHANDLES;
		_data->_process_info.si.hStdOutput = _data->_pipe_handles[1];
		if (_read_std_err) {
			_data->_process_info.si.hStdError = _data->_pipe_handles[1];
		}
		inherit_handles = true;
	}

	DWORD creaton_flags = NORMAL_PRIORITY_CLASS;
	if (_open_console) {
		creaton_flags |= CREATE_NEW_CONSOLE;
	} else {
		creaton_flags |= CREATE_NO_WINDOW;
	}

	int ret = CreateProcessW(nullptr, (LPWSTR)(modstr.ptrw()), nullptr, nullptr, inherit_handles, creaton_flags, nullptr, nullptr, si_w, &_data->_process_info.pi);
	if (!ret && _read_output) {
		CloseHandle(_data->_pipe_handles[0]); // Cleanup pipe handles.
		CloseHandle(_data->_pipe_handles[1]);

		_data->_pipe_handles[0] = NULL;
		_data->_pipe_handles[1] = NULL;
	}

	ERR_FAIL_COND_V(ret == 0, ERR_CANT_FORK);

	if (_blocking) {
		if (_read_output) {
			CloseHandle(_data->_pipe_handles[1]); // Close pipe write handle (only child process is writing).

			int bytes_in_buffer = 0;

			const int CHUNK_SIZE = 4096;
			DWORD read = 0;
			for (;;) { // Read StdOut and StdErr from pipe.
				_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
				const bool success = ReadFile(_data->_pipe_handles[0], _bytes.ptr() + bytes_in_buffer, CHUNK_SIZE, &read, NULL);
				if (!success || read == 0) {
					break;
				}
				// Assume that all possible encodings are ASCII-compatible.
				// Break at newline to allow receiving long output in portions.
				int newline_index = -1;
				for (int i = read - 1; i >= 0; i--) {
					if (_bytes[bytes_in_buffer + i] == '\n') {
						newline_index = i;
						break;
					}
				}

				if (newline_index == -1) {
					bytes_in_buffer += read;
					continue;
				}

				const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
				_append_to_pipe(_bytes.ptr(), bytes_to_convert);

				bytes_in_buffer = read - (newline_index + 1);
				memmove(_bytes.ptr(), _bytes.ptr() + bytes_to_convert, bytes_in_buffer);
			}

			if (bytes_in_buffer > 0) {
				_append_to_pipe(_bytes.ptr(), bytes_in_buffer);
			}

			CloseHandle(_data->_pipe_handles[0]); // Close pipe read handle.
		}

		WaitForSingleObject(_data->_process_info.pi.hProcess, INFINITE);

		DWORD ret2;
		GetExitCodeProcess(_data->_process_info.pi.hProcess, &ret2);
		_exitcode = ret2;

		CloseHandle(_data->_process_info.pi.hProcess);
		CloseHandle(_data->_process_info.pi.hThread);
	} else {
		if (_read_output) {
			//eventually we will need to keep this
			CloseHandle(_data->_pipe_handles[1]); // Close pipe write handle (only child process is writing).
			_data->_pipe_handles[1] = NULL;
		}

		_process_started = true;

		ProcessID pid = _data->_process_info.pi.dwProcessId;
		_process_id = pid;
	}

	return OK;
}

Error SubProcess::stop() {
	if (!_process_started) {
		return OK;
	}

	if (_data->_pipe_handles[0]) {
		CloseHandle(_data->_pipe_handles[0]); // Cleanup pipe handles.
		_data->_pipe_handles[0] = NULL;
	}

	if (_data->_pipe_handles[1]) {
		CloseHandle(_data->_pipe_handles[1]);
		_data->_pipe_handles[1] = NULL;
	}

	const int ret = TerminateProcess(_data->_process_info.pi.hProcess, 0);

	CloseHandle(_data->_process_info.pi.hProcess);
	CloseHandle(_data->_process_info.pi.hThread);

	ZeroMemory(&_data->_process_info.si, sizeof(_data->_process_info.si));
	_data->_process_info.si.cb = sizeof(_data->_process_info.si);
	ZeroMemory(&_data->_process_info.pi, sizeof(_data->_process_info.pi));

	_process_started = false;

	return ret != 0 ? OK : FAILED;
}

Error SubProcess::poll() {
	if (!_process_started) {
		return FAILED;
	}

	if (!_data->_pipe_handles[0]) {
		return FAILED;
	}

	_pipe.clear();

	int bytes_in_buffer = 0;

	const int CHUNK_SIZE = 4096;
	DWORD read = 0;

	_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
	const bool success = ReadFile(_data->_pipe_handles[0], _bytes.ptr() + bytes_in_buffer, CHUNK_SIZE, &read, NULL);

	if (!success) {
		stop();
		return ERR_FILE_EOF;
	}

	if (read == 0) {
		return OK;
	}

	// Assume that all possible encodings are ASCII-compatible.
	// Break at newline to allow receiving long output in portions.
	int newline_index = -1;
	for (int i = read - 1; i >= 0; i--) {
		if (_bytes[bytes_in_buffer + i] == '\n') {
			newline_index = i;
			break;
		}
	}

	if (newline_index == -1) {
		bytes_in_buffer += read;
		return OK;
	}

	const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
	_append_to_pipe(_bytes.ptr(), bytes_to_convert);

	bytes_in_buffer = read - (newline_index + 1);
	memmove(_bytes.ptr(), _bytes.ptr() + bytes_to_convert, bytes_in_buffer);

	if (bytes_in_buffer > 0) {
		_append_to_pipe(_bytes.ptr(), bytes_in_buffer);
	}

	return OK;
}

Error SubProcess::send_signal(const int p_signal) {
	//Not Yet Impl
	ERR_FAIL_V(ERR_BUG);
}

Error SubProcess::send_data(const String &p_data) {
	//Not Yet Impl
	ERR_FAIL_V(ERR_BUG);
}

bool SubProcess::is_process_running() const {
	if (_process_id == 0) {
		return false;
	}

	if (!_process_started) {
		return false;
	}

	DWORD dw_exit_code = 0;
	if (!GetExitCodeProcess(_data->_process_info.pi.hProcess, &dw_exit_code)) {
		return false;
	}

	if (dw_exit_code != STILL_ACTIVE) {
		return false;
	}

	return true;
}

String SubProcess::_quote_command_line_argument(const String &p_text) const {
	for (int i = 0; i < p_text.size(); i++) {
		CharType c = p_text[i];
		if (c == ' ' || c == '&' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '^' || c == '=' || c == ';' || c == '!' || c == '\'' || c == '+' || c == ',' || c == '`' || c == '~') {
			return "\"" + p_text + "\"";
		}
	}
	return p_text;
}

void SubProcess::_append_to_pipe(char *p_bytes, int p_size) {
	// Try to convert from default ANSI code page to Unicode.
	LocalVector<wchar_t> wchars;
	int total_wchars = MultiByteToWideChar(CP_ACP, 0, p_bytes, p_size, nullptr, 0);
	if (total_wchars > 0) {
		wchars.resize(total_wchars);
		if (MultiByteToWideChar(CP_ACP, 0, p_bytes, p_size, wchars.ptr(), total_wchars) == 0) {
			wchars.clear();
		}
	}

	if (_pipe_mutex) {
		_pipe_mutex->lock();
	}
	if (wchars.empty()) {
		// Let's hope it's compatible with UTF-8.
		_pipe += String::utf8(p_bytes, p_size);
	} else {
		_pipe += String(wchars.ptr(), total_wchars);
	}
	if (_pipe_mutex) {
		_pipe_mutex->unlock();
	}
}

SubProcess::SubProcess() {
	_data = memnew(SubProcessWindowsData);
	
	_blocking = false;

	_read_output = true;

	_read_std = true;
	_read_std_err = false;

	_use_pipe_mutex = false;

	_pipe_mutex = NULL;

	_open_console = false;

	_process_id = ProcessID();
	_exitcode = 0;

	_data->_pipe_handles[0] = NULL;
	_data->_pipe_handles[1] = NULL;

	_process_started = false;

	ZeroMemory(&_data->_process_info.si, sizeof(_data->_process_info.si));
	_data->_process_info.si.cb = sizeof(_data->_process_info.si);
	ZeroMemory(&_data->_process_info.pi, sizeof(_data->_process_info.pi));
}
SubProcess::~SubProcess() {
	stop();

	memdelete(_data);
}

#else

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

Error SubProcess::start() {
#ifdef __EMSCRIPTEN__
	// Don't compile this code at all to avoid undefined references.
	// Actual virtual call goes to OS_JavaScript.
	ERR_FAIL_V(ERR_BUG);
#else
	if (_executable_path.empty()) {
		return ERR_FILE_BAD_PATH;
	}

	if (is_process_running()) {
		return ERR_BUSY;
	}

	if (_blocking && _read_output) {
		String argss;
		argss = "\"" + _executable_path + "\"";

		for (int i = 0; i < _arguments.size(); i++) {
			argss += String(" \"") + _arguments[i] + "\"";
		}

		if (_read_std_err) {
			argss += " 2>&1"; // Read stderr too
		} else {
			argss += " 2>/dev/null"; //silence stderr
		}
		FILE *f = popen(argss.utf8().get_data(), "r");

		ERR_FAIL_COND_V_MSG(!f, ERR_CANT_OPEN, "Cannot pipe stream from process running with following arguments '" + argss + "'.");

		char buf[65535];

		while (fgets(buf, 65535, f)) {
			if (_pipe_mutex) {
				_pipe_mutex->lock();
			}
			_pipe += String::utf8(buf);
			if (_pipe_mutex) {
				_pipe_mutex->unlock();
			}
		}
		int rv = pclose(f);

		_exitcode = WEXITSTATUS(rv);

		return OK;
	}

	if (!_blocking && _read_output) {
		String argss;
		argss = "\"" + _executable_path + "\"";

		for (int i = 0; i < _arguments.size(); i++) {
			argss += String(" \"") + _arguments[i] + "\"";
		}

		if (_read_std_err) {
			argss += " 2>&1"; // Read stderr too
		} else {
			argss += " 2>/dev/null"; //silence stderr
		}

		_process_fp = popen(argss.utf8().get_data(), "r");

		ERR_FAIL_COND_V_MSG(!_process_fp, ERR_CANT_OPEN, "Cannot pipe stream from process running with following arguments '" + argss + "'.");

		return OK;
	}

	// We just run it, no need to worry about output

	pid_t pid = fork();
	ERR_FAIL_COND_V(pid < 0, ERR_CANT_FORK);

	if (pid == 0) {
		// is child

		if (!_blocking) {
			// For non blocking calls, create a new session-ID so parent won't wait for it.
			// This ensures the process won't go zombie at end.
			setsid();
		}

		Vector<CharString> cs;
		cs.push_back(_executable_path.utf8());
		for (int i = 0; i < _arguments.size(); i++) {
			cs.push_back(_arguments[i].utf8());
		}

		Vector<char *> args;
		for (int i = 0; i < cs.size(); i++) {
			args.push_back((char *)cs[i].get_data());
		}
		args.push_back(0);

		execvp(_executable_path.utf8().get_data(), &args[0]);
		// still alive? something failed..
		fprintf(stderr, "**ERROR** SubProcess::execute - Could not create child process while executing: %s\n", _executable_path.utf8().get_data());
		raise(SIGKILL);
	}

	if (_blocking) {
		int status;
		waitpid(pid, &status, 0);

		_exitcode = WIFEXITED(status) ? WEXITSTATUS(status) : status;
	} else {
		_process_id = pid;
	}

	return OK;
#endif
}

Error SubProcess::stop() {
#ifdef __EMSCRIPTEN__
	// Don't compile this code at all to avoid undefined references.
	// Actual virtual call goes to OS_JavaScript.
	ERR_FAIL_V(ERR_BUG);
#else
	if (_process_fp) {
		int rv = pclose(_process_fp);
		_process_fp = NULL;
		_exitcode = WEXITSTATUS(rv);
		_process_id = 0;
		return OK;
	}

	if (_process_id) {
		int ret = ::kill(_process_id, SIGKILL);

		if (!ret) {
			//avoid zombie process
			int st;
			::waitpid(_process_id, &st, 0);
		}

		_process_id = 0;

		return ret ? ERR_INVALID_PARAMETER : OK;
	}

	return OK;
#endif
}

Error SubProcess::poll() {
#ifdef __EMSCRIPTEN__
	// Don't compile this code at all to avoid undefined references.
	// Actual virtual call goes to OS_JavaScript.
	ERR_FAIL_V(ERR_BUG);
#else

	if (_process_fp) {
		if (fgets(_process_buf, 65535, _process_fp)) {
			if (_pipe_mutex) {
				_pipe_mutex->lock();
			}
			_pipe = String::utf8(_process_buf);
			if (_pipe_mutex) {
				_pipe_mutex->unlock();
			}
		} else {
			// The process finished
			// Cleanup:
			stop();
			return ERR_FILE_EOF;
		}
	}

	return OK;
#endif
}

Error SubProcess::send_signal(const int p_signal) {
	//Not Yet Impl
	ERR_FAIL_V(ERR_BUG);
}

Error SubProcess::send_data(const String &p_data) {
	//Not Yet Impl
	ERR_FAIL_V(ERR_BUG);
}

bool SubProcess::is_process_running() const {
#ifdef __EMSCRIPTEN__
	// Don't compile this code at all to avoid undefined references.
	// Actual virtual call goes to OS_JavaScript.
	ERR_FAIL_V(false);
#else

	if (_process_fp) {
		return !feof(_process_fp);
	}

	if (_process_id == 0) {
		return false;
	}

	int status = 0;
	if (waitpid(_process_id, &status, WNOHANG) != 0) {
		return false;
	}

	return true;
#endif
}

SubProcess::SubProcess() {
	_blocking = false;

	_read_output = true;

	_read_std = true;
	_read_std_err = false;

	_use_pipe_mutex = false;

	_pipe_mutex = NULL;

	_open_console = false;

	_process_id = ProcessID();
	_exitcode = 0;

	_process_fp = NULL;
}
SubProcess::~SubProcess() {
	stop();
}

#endif

SubProcess *SubProcess::create() {
	return memnew(SubProcess());
}

String SubProcess::get_executable_path() const {
	return _executable_path;
}
void SubProcess::set_executable_path(const String &p_executable_path) {
	ERR_FAIL_COND(is_process_running());

	_executable_path = p_executable_path;
}

Vector<String> SubProcess::get_arguments() const {
	return _arguments;
}
void SubProcess::set_arguments(const Vector<String> &p_arguments) {
	ERR_FAIL_COND(is_process_running());

	_arguments = p_arguments;
}

bool SubProcess::get_blocking() const {
	return _blocking;
}
void SubProcess::set_blocking(const bool p_value) {
	ERR_FAIL_COND(is_process_running());

	_blocking = p_value;
}

bool SubProcess::get_read_output() const {
	return _read_output;
}
void SubProcess::set_read_output(const bool p_value) {
	ERR_FAIL_COND(is_process_running());

	_read_output = p_value;
}

bool SubProcess::get_read_std() const {
	return _read_std;
}
void SubProcess::set_read_std(const bool p_value) {
	ERR_FAIL_COND(is_process_running());

	_read_std = p_value;
}

bool SubProcess::get_read_std_err() const {
	return _read_std_err;
}
void SubProcess::set_read_std_err(const bool p_value) {
	ERR_FAIL_COND(is_process_running());

	_read_std_err = p_value;
}

bool SubProcess::get_use_pipe_mutex() const {
	return _use_pipe_mutex;
}
void SubProcess::set_use_pipe_mutex(const bool p_value) {
	ERR_FAIL_COND(is_process_running());

	_use_pipe_mutex = p_value;
}

bool SubProcess::get_open_console() const {
	return _open_console;
}
void SubProcess::set_open_console(const bool p_value) {
	ERR_FAIL_COND(is_process_running());

	_open_console = p_value;
}

Error SubProcess::run(const String &p_executable_path, const Vector<String> &p_arguments, bool p_output, bool p_blocking, bool p_read_std_err, bool p_use_pipe_mutex, bool p_open_console) {
	if (is_process_running()) {
		return ERR_ALREADY_IN_USE;
	}

	_executable_path = p_executable_path;
	_arguments = p_arguments;

	_blocking = p_blocking;

	_read_output = p_output;

	_read_std = true;
	_read_std_err = p_read_std_err;

	_use_pipe_mutex = p_use_pipe_mutex;

	_open_console = p_open_console;

	_setup_pipe_mutex();

	return start();
}

/*
SubProcess::SubProcess() {
	_blocking = false;

	_read_output = true;

	_read_std = true;
	_read_std_err = false;

	_use_pipe_mutex = false;

	_pipe_mutex = NULL;

	_open_console = false;

	_process_id = ProcessID();
	_exitcode = 0;
};
*/

void SubProcess::_setup_pipe_mutex() {
	if (_use_pipe_mutex) {
		if (!_pipe_mutex) {
			_pipe_mutex = memnew(Mutex);
		}
	} else {
		if (_pipe_mutex) {
			memdelete(_pipe_mutex);
			_pipe_mutex = NULL;
		}
	}
}
