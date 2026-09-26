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

	// Pipes are unidirectional, [0] is the read end, [1] is the write end
	HANDLE _read_std_handles[2];
	HANDLE _read_std_err_handles[2];
	HANDLE _write_handles[2];

	ProcessInfo _process_info;
};

Error SubProcess::start() {
	if (_executable_path.empty()) {
		return ERR_FILE_BAD_PATH;
	}

	if (is_process_running()) {
		return ERR_BUSY;
	}

	_setup_pipe_mutex();

	if (_std_out_mutex) {
		_std_out_mutex->lock();
	}
	_std_out = String();
	if (_std_out_mutex) {
		_std_out_mutex->unlock();
	}

	if (_std_err_mutex) {
		_std_err_mutex->lock();
	}
	_std_err = String();
	if (_std_err_mutex) {
		_std_err_mutex->unlock();
	}

	_bytes.clear();
	_err_bytes.clear();

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

	// Setup Pipes
	if (_communication_flags != COMMUNICATION_FLAGS_NONE) {
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;
		sa.lpSecurityDescriptor = NULL;

		_data->_process_info.si.dwFlags |= STARTF_USESTDHANDLES;

		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
			// Create pipe for StdOut

			ERR_FAIL_COND_V(!CreatePipe(&_data->_read_std_handles[0], &_data->_read_std_handles[1], &sa, 0), ERR_CANT_FORK);
			ERR_FAIL_COND_V(!SetHandleInformation(_data->_read_std_handles[0], HANDLE_FLAG_INHERIT, 0), ERR_CANT_FORK); // Read handle is for host process only and should not be inherited.

			_data->_process_info.si.hStdOutput = _data->_read_std_handles[1];

			inherit_handles = true;
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			// Create pipe for StdOut

			ERR_FAIL_COND_V(!CreatePipe(&_data->_read_std_err_handles[0], &_data->_read_std_err_handles[1], &sa, 0), ERR_CANT_FORK);
			ERR_FAIL_COND_V(!SetHandleInformation(_data->_read_std_err_handles[0], HANDLE_FLAG_INHERIT, 0), ERR_CANT_FORK); // Read handle is for host process only and should not be inherited.

			_data->_process_info.si.hStdError = _data->_read_std_err_handles[1];

			inherit_handles = true;
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDIN) != 0) {
			// Create pipe for StdOut and StdErr.

			ERR_FAIL_COND_V(!CreatePipe(&_data->_write_handles[0], &_data->_write_handles[1], &sa, 0), ERR_CANT_FORK);
			ERR_FAIL_COND_V(!SetHandleInformation(_data->_write_handles[1], HANDLE_FLAG_INHERIT, 0), ERR_CANT_FORK); // Write handle is for host process only and should not be inherited.

			_data->_process_info.si.hStdInput = _data->_write_handles[0];

			inherit_handles = true;
		}
	}

	// Setup process
	DWORD creation_flags = NORMAL_PRIORITY_CLASS;
	if (_open_console) {
		creation_flags |= CREATE_NEW_CONSOLE;
	} else {
		creation_flags |= CREATE_NO_WINDOW;
	}

	// Setup environment vars

	// This is a series of null terminated strings with a double null at the end
	// in key=value format. You can't have = in the name
	// MSDN:
	// All strings in the environment block must be sorted alphabetically by name.
	// The sort is case-insensitive, Unicode order, without regard to locale.
	// Because the equal sign is a separator, it must not be used in the name of an environment variable.
	wchar_t *current_env = NULL;

	if (_inherit_environment && _environment_variables.size() == 0) {
		// No need to do anything, just keep current_env as NULL.
	} else {
		HashMap<String, String> new_env_map;

		if (_inherit_environment) {
			wchar_t *initial_env = GetEnvironmentStringsW();

			if (initial_env) {
				wchar_t *temp_env = initial_env;

				while (*temp_env != L'\0') {
					String p = String::utf16((const char16_t *)temp_env);

					temp_env += p.size();

					if (p.length() > 0) {
						int indx = p.find("=");

						if (indx != -1) {
							String key = p.substr_index(0, indx);
							String value = p.substr_index(indx + 1, p.length()); // +1 to skip =

							new_env_map[key] = value;
						}
					}

					FreeEnvironmentStringsW(initial_env);
				}
			}
		}

		for (const HashMap<StringName, String>::Element *E = _environment_variables.front(); E; E = E->next) {
			new_env_map[E->key()] = E->value();
		}

		// Unless MSDN is lying we need to write them in a sorted order.

		Vector<String> psa;

		// Also let's count lengths for later
		int length_count = 0;

		for (const HashMap<String, String>::Element *E = new_env_map.front(); E; E = E->next) {
			String sk = E->key();
			psa.push_back(sk);
			length_count += sk.length();
			length_count += E->value().length();
		}

		if (length_count > 0) {
			// Hopefully is enough
			psa.sort();

			// We only just need to write out everything
			// All chars + each entry has an = and \0. and closing \0
			current_env = memnew_arr(wchar_t, length_count + psa.size() * 2 + 1);

			// MSDN: Note that an ANSI environment block is terminated by two zero bytes: one for the last string,
			// one more to terminate the block. A Unicode environment block is terminated by four zero bytes:
			// two for the last string, two more to terminate the block.
			// So if this is not set, only the first env var will be used.
			creation_flags |= CREATE_UNICODE_ENVIRONMENT;

			// Write data

			uint64_t current_offset = 0;
			int psa_size = psa.size();
			for (int i = 0; i < psa_size; ++i) {
				String key = psa[i];

				// Write key
				{
					Char16String cs = key.utf16();
					// Length does not includes a \0
					uint64_t str_byte_length = cs.length() * sizeof(char16_t);

					memcpy(&current_env[current_offset], (const char *)cs.get_data(), str_byte_length);
					current_offset += cs.length();
				}

				// Add =
				current_env[current_offset] = L'=';
				++current_offset;

				// Write value
				{
					String value = new_env_map[key];
					Char16String cs = value.utf16();
					// Size includes a \0
					uint64_t str_byte_length = cs.size() * sizeof(char16_t);

					memcpy(&current_env[current_offset], (const char *)cs.get_data(), str_byte_length);
					current_offset += cs.size();
				}
			}

			current_env[current_offset] = L'\0';
		}
	}

	int ret = CreateProcessW(NULL, (LPWSTR)(modstr.ptrw()), NULL, NULL, inherit_handles, creation_flags, current_env, nullptr, si_w, &_data->_process_info.pi);

	if (current_env) {
		memdelete_arr(current_env);
		current_env = NULL;
	}

	if (!ret) {
		if (_communication_flags != COMMUNICATION_FLAGS_NONE) {
			// Cleanup pipe handles.
			for (int i = 0; i < 2; ++i) {
				if (_data->_read_std_handles[i]) {
					CloseHandle(_data->_read_std_handles[i]);
					_data->_read_std_handles[i] = NULL;
				}

				if (_data->_read_std_err_handles[i]) {
					CloseHandle(_data->_read_std_err_handles[i]);
					_data->_read_std_err_handles[i] = NULL;
				}

				if (_data->_write_handles[i]) {
					CloseHandle(_data->_write_handles[i]);
					_data->_write_handles[i] = NULL;
				}
			}
		}

		return ERR_CANT_FORK;
	}

	// Close handles that were passed to the subprocess.

	if (_communication_flags != COMMUNICATION_FLAGS_NONE) {
		if (_data->_read_std_handles[1]) {
			CloseHandle(_data->_read_std_handles[1]);
			_data->_read_std_handles[1] = NULL;
		}

		if (_data->_read_std_err_handles[1]) {
			CloseHandle(_data->_read_std_err_handles[1]);
			_data->_read_std_err_handles[1] = NULL;
		}

		if (_data->_write_handles[0]) {
			CloseHandle(_data->_write_handles[0]);
			_data->_write_handles[0] = NULL;
		}
	}

	if (_blocking) {
		int bytes_in_buffer = 0;
		int err_bytes_in_buffer = 0;

		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0 ||
				(_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			for (;;) { // Read StdOut and StdErr from pipe.
				bool had_error = false;

				// First go for stdin
				if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
					if (_read_from_std_out(bytes_in_buffer)) {
						had_error = true;
					}
				}

				// StdErr
				if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
					// We want to read even if stdin errored!
					if (_read_from_std_err(err_bytes_in_buffer)) {
						had_error = true;
					}
				}

				// Note that we don't worry about stdin here, as it can only happen if a thread launches a process in blocking mode, an an another writes to it.

				// This is needed to detect if the subprocess have terminated. even if the stdout and stderr is not connected.
				if (had_error) {
					break;
				}
			}

			// StdIn
			if (bytes_in_buffer > 0) {
				_append_to_std_out(_bytes.ptr(), bytes_in_buffer);
			}

			// StdErr
			if (err_bytes_in_buffer > 0) {
				_append_to_std_err(_err_bytes.ptr(), err_bytes_in_buffer);
			}

			if (_data->_read_std_handles[0]) {
				CloseHandle(_data->_read_std_handles[0]);
				_data->_read_std_handles[0] = NULL;
			}

			if (_data->_read_std_err_handles[0]) {
				CloseHandle(_data->_read_std_err_handles[0]);
				_data->_read_std_err_handles[0] = NULL;
			}

		} else {
			WaitForSingleObject(_data->_process_info.pi.hProcess, INFINITE);
		}

		if (_data->_write_handles[1]) {
			CloseHandle(_data->_write_handles[1]);
			_data->_write_handles[1] = NULL;
		}

		DWORD ret2;
		GetExitCodeProcess(_data->_process_info.pi.hProcess, &ret2);
		_exitcode = ret2;

		CloseHandle(_data->_process_info.pi.hProcess);
		CloseHandle(_data->_process_info.pi.hThread);
	} else {
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

	if (!_blocking) {
		// Process remaining data when doing a non-blocking call, if there any

		// StdIn
		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
			if (_bytes.size() > 0) {
				_append_to_std_out(_bytes.ptr(), _bytes.size());
			}
		}

		// StdErr
		if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			if (_err_bytes.size() > 0) {
				_append_to_std_err(_err_bytes.ptr(), _err_bytes.size());
			}
		}
	}

	// Cleanup pipe handles.
	for (int i = 0; i < 2; ++i) {
		if (_data->_read_std_handles[i]) {
			CloseHandle(_data->_read_std_handles[i]);
			_data->_read_std_handles[i] = NULL;
		}

		if (_data->_read_std_err_handles[i]) {
			CloseHandle(_data->_read_std_err_handles[i]);
			_data->_read_std_err_handles[i] = NULL;
		}

		if (_data->_write_handles[i]) {
			CloseHandle(_data->_write_handles[i]);
			_data->_write_handles[i] = NULL;
		}
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
		return ERR_UNAVAILABLE;
	}

	if (_blocking) {
		// If it's blocking, and we want to read output from an another thread, we can just do it without poll
		// Just ignore poll calls

		// This should the api more convenient to use.
		if (!is_process_running()) {
			return ERR_FILE_EOF;
		}

		return OK;
	}

	if (!_data->_read_std_handles[0] && !_data->_read_std_err_handles[0]) {
		return ERR_UNAVAILABLE;
	}

	bool had_error = false;

	if (_data->_read_std_handles[0]) {
		if (_poll_read_from_std_out()) {
			had_error = true;
		}
	}

	if (_data->_read_std_err_handles[0]) {
		if (_poll_read_from_std_err()) {
			had_error = true;
		}
	}

	// This should the api more convenient to use.
	if (had_error) {
		stop();
		return ERR_FILE_EOF;
	}

	return OK;
}

Error SubProcess::send_signal(const int p_signal) {
	// Signals doesn't exists on Windows.
	return ERR_UNAVAILABLE;
}

Error SubProcess::write_to_stdin(const String &p_data) {
	return write_to_stdin_utf16(p_data);
}

Error SubProcess::write_to_stdin_utf8(const String &p_data) {
	if (!is_process_running()) {
		return ERR_UNCONFIGURED;
	}

	if (p_data.length() == 0) {
		return OK;
	}

	CharString cs = p_data.utf8();

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	DWORD total_written = 0;

	// Note, we are using length() to skip sending null terminators!
	for (;;) {
		DWORD written;
		const bool success = WriteFile(_data->_write_handles[1], (cs.get_data()) + total_written, cs.length() - total_written, &written, NULL);

		if (!success) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		total_written += written;

		if ((int)total_written >= cs.length()) {
			break;
		}
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}

Error SubProcess::write_to_stdin_utf16(const String &p_data) {
	if (!is_process_running()) {
		return ERR_UNCONFIGURED;
	}

	if (p_data.length() == 0) {
		return OK;
	}

	Char16String cs = p_data.utf16();
	// Note, we are using length() to skip sending null terminators!
	int length_bytes = cs.length() * sizeof(char16_t);

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	DWORD total_written = 0;

	for (;;) {
		DWORD written;
		const bool success = WriteFile(_data->_write_handles[1], ((const char *)cs.get_data()) + total_written, length_bytes - total_written, &written, NULL);

		if (!success) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		total_written += written;

		if ((int)total_written >= length_bytes) {
			break;
		}
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}

Error SubProcess::write_to_stdin_utf32(const String &p_data) {
	if (!is_process_running()) {
		return ERR_UNCONFIGURED;
	}

	if (p_data.length() == 0) {
		return OK;
	}

	Char16String cs = p_data.utf16();

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	DWORD total_written = 0;
	// Note, we are using length() to skip sending null terminators!
	int length_bytes = p_data.length() * sizeof(CharType);

	for (;;) {
		DWORD written;
		const bool success = WriteFile(_data->_write_handles[1], ((const char *)cs.get_data()) + total_written, length_bytes - total_written, &written, NULL);

		if (!success) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		total_written += written;

		if ((int)total_written >= length_bytes) {
			break;
		}
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}
Error SubProcess::write_data_to_stdin(const Vector<uint8_t> &p_data) {
	if (!is_process_running()) {
		return ERR_UNCONFIGURED;
	}

	if (p_data.size() == 0) {
		return OK;
	}

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	int size = p_data.size();

	DWORD total_written = 0;

	for (;;) {
		DWORD written;
		const bool success = WriteFile(_data->_write_handles[1], p_data.ptr() + total_written, size - total_written, &written, NULL);

		if (!success) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		total_written += written;

		if ((int)total_written >= size) {
			break;
		}
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
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

bool SubProcess::_read_from_std_out(int &bytes_in_buffer) {
	const int CHUNK_SIZE = 4096;
	DWORD read = 0;
	_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
	// Unlike in linux, here ReadFile blocks, until either it can read up to chunk size, or an error happens
	// So if read is 0, there was an issue.
	const bool success = ReadFile(_data->_read_std_handles[0], _bytes.ptr() + bytes_in_buffer, CHUNK_SIZE, &read, NULL);
	if (!success || read == 0) {
		// No need
		//_bytes.resize(bytes_in_buffer);
		return true;
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
		return false;
	}

	const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
	_append_to_std_out(_bytes.ptr(), bytes_to_convert);

	bytes_in_buffer = read - (newline_index + 1);
	memmove(_bytes.ptr(), _bytes.ptr() + bytes_to_convert, bytes_in_buffer);

	return false;
}

bool SubProcess::_read_from_std_err(int &err_bytes_in_buffer) {
	const int CHUNK_SIZE = 4096;
	DWORD err_read = 0;
	_err_bytes.resize(err_bytes_in_buffer + CHUNK_SIZE);
	const bool success = ReadFile(_data->_read_std_err_handles[0], _err_bytes.ptr() + err_bytes_in_buffer, CHUNK_SIZE, &err_read, NULL);
	if (!success || err_read == 0) {
		// No need
		//_err_bytes.resize(err_bytes_in_buffer);
		return true;
	}

	// Assume that all possible encodings are ASCII-compatible.
	// Break at newline to allow receiving long output in portions.
	int newline_index = -1;
	for (int i = err_read - 1; i >= 0; i--) {
		if (_err_bytes[err_bytes_in_buffer + i] == '\n') {
			newline_index = i;
			break;
		}
	}

	if (newline_index == -1) {
		err_bytes_in_buffer += err_read;
		return false;
	}

	const int bytes_to_convert = err_bytes_in_buffer + (newline_index + 1);
	_append_to_std_err(_err_bytes.ptr(), bytes_to_convert);

	err_bytes_in_buffer = err_read - (newline_index + 1);
	memmove(_err_bytes.ptr(), _err_bytes.ptr() + bytes_to_convert, err_bytes_in_buffer);
	return false;
}

bool SubProcess::_poll_read_from_std_out() {
	int bytes_in_buffer = _bytes.size();

	const int CHUNK_SIZE = 4096;
	int read_size = CHUNK_SIZE;

	DWORD total_available_bytes;
	if (!PeekNamedPipe(_data->_read_std_handles[0], 0, 0, 0, &total_available_bytes, 0)) {
		return true;
	}

	if (total_available_bytes == 0) {
		return false;
	}

	if (total_available_bytes < CHUNK_SIZE) {
		read_size = total_available_bytes;
	}

	DWORD read = 0;

	_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
	const bool success = ReadFile(_data->_read_std_handles[0], _bytes.ptr() + bytes_in_buffer, read_size, &read, NULL);

	if (!success || read == 0) {
		// Note, stop() will process remaning bytes, we had an error, so get rid of the new chunk, as it's empty.
		_bytes.resize(bytes_in_buffer);
		//stop();
		return true;
	}

	if (read != 0) {
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
		} else {
			const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
			_append_to_std_out(_bytes.ptr(), bytes_to_convert);

			bytes_in_buffer = read - (newline_index + 1);
			memmove(_bytes.ptr(), _bytes.ptr() + bytes_to_convert, bytes_in_buffer);
		}

		_bytes.resize(bytes_in_buffer);
	} else {
		// 0 read, remove chunk. Should probably save actual size as a variable eventually.
		_bytes.resize(bytes_in_buffer);
	}

	return false;
}
bool SubProcess::_poll_read_from_std_err() {
	int bytes_in_buffer = _err_bytes.size();

	const int CHUNK_SIZE = 4096;
	int read_size = CHUNK_SIZE;

	DWORD total_available_bytes;
	if (!PeekNamedPipe(_data->_read_std_handles[0], 0, 0, 0, &total_available_bytes, 0)) {
		return true;
	}

	if (total_available_bytes == 0) {
		return false;
	}

	if (total_available_bytes < CHUNK_SIZE) {
		read_size = total_available_bytes;
	}

	DWORD read = 0;

	_err_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
	const bool success = ReadFile(_data->_read_std_err_handles[0], _err_bytes.ptr() + bytes_in_buffer, read_size, &read, NULL);

	if (!success || read == 0) {
		// Note, stop() will process remaning bytes, we had an error, so get rid of the new chunk, as it's empty.
		_err_bytes.resize(bytes_in_buffer);
		//stop();
		return true;
	}

	if (read != 0) {
		// Assume that all possible encodings are ASCII-compatible.
		// Break at newline to allow receiving long output in portions.
		int newline_index = -1;
		for (int i = read - 1; i >= 0; i--) {
			if (_err_bytes[bytes_in_buffer + i] == '\n') {
				newline_index = i;
				break;
			}
		}

		if (newline_index == -1) {
			bytes_in_buffer += read;
		} else {
			const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
			_append_to_std_err(_err_bytes.ptr(), bytes_to_convert);

			bytes_in_buffer = read - (newline_index + 1);
			memmove(_err_bytes.ptr(), _err_bytes.ptr() + bytes_to_convert, bytes_in_buffer);
		}

		_err_bytes.resize(bytes_in_buffer);
	} else {
		// 0 read, remove chunk. Should probably save actual size as a variable eventually.
		_err_bytes.resize(bytes_in_buffer);
	}

	return false;
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

void SubProcess::_append_to_std_out(char *p_bytes, int p_size) {
	// Try to convert from default ANSI code page to Unicode.
	LocalVector<wchar_t> wchars;
	int total_wchars = MultiByteToWideChar(CP_ACP, 0, p_bytes, p_size, nullptr, 0);
	if (total_wchars > 0) {
		wchars.resize(total_wchars);
		if (MultiByteToWideChar(CP_ACP, 0, p_bytes, p_size, wchars.ptr(), total_wchars) == 0) {
			wchars.clear();
		}
	}

	if (_std_out_mutex) {
		_std_out_mutex->lock();
	}
	if (wchars.empty()) {
		// Let's hope it's compatible with UTF-8.
		_std_out += String::utf8(p_bytes, p_size);
	} else {
		_std_out += String(wchars.ptr(), total_wchars);
	}
	if (_std_out_mutex) {
		_std_out_mutex->unlock();
	}
}

void SubProcess::_append_to_std_err(char *p_bytes, int p_size) {
	// Try to convert from default ANSI code page to Unicode.
	LocalVector<wchar_t> wchars;
	int total_wchars = MultiByteToWideChar(CP_ACP, 0, p_bytes, p_size, nullptr, 0);
	if (total_wchars > 0) {
		wchars.resize(total_wchars);
		if (MultiByteToWideChar(CP_ACP, 0, p_bytes, p_size, wchars.ptr(), total_wchars) == 0) {
			wchars.clear();
		}
	}

	if (_std_err_mutex) {
		_std_err_mutex->lock();
	}
	if (wchars.empty()) {
		// Let's hope it's compatible with UTF-8.
		_std_err += String::utf8(p_bytes, p_size);
	} else {
		_std_err += String(wchars.ptr(), total_wchars);
	}
	if (_std_err_mutex) {
		_std_err_mutex->unlock();
	}
}

SubProcess::SubProcess() {
	_data = memnew(SubProcessWindowsData);

	_blocking = false;

	_communication_flags = COMMUNICATION_FLAGS_STDOUT;

	_inherit_environment = true;

	_use_pipe_mutex = false;

	_std_out_mutex = NULL;
	_std_err_mutex = NULL;
	_std_in_mutex = NULL;

	_open_console = false;

	_process_id = ProcessID();
	_exitcode = 0;

	_data->_read_std_handles[0] = NULL;
	_data->_read_std_handles[1] = NULL;

	_data->_read_std_err_handles[0] = NULL;
	_data->_read_std_err_handles[1] = NULL;

	_data->_write_handles[0] = NULL;
	_data->_write_handles[1] = NULL;

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

#ifdef __APPLE__
#define NO_CLEARENV
#endif

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

	_setup_pipe_mutex();

	if (_std_out_mutex) {
		_std_out_mutex->lock();
	}
	_std_out = String();
	if (_std_out_mutex) {
		_std_out_mutex->unlock();
	}

	if (_std_err_mutex) {
		_std_err_mutex->lock();
	}
	_std_err = String();
	if (_std_err_mutex) {
		_std_err_mutex->unlock();
	}

	_bytes.clear();
	_err_bytes.clear();

	if (_communication_flags == COMMUNICATION_FLAGS_NONE) {
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

			// Set up env vars

			bool environment_modified = false;

#ifdef NO_CLEARENV
			extern char **environ;
#endif

			if (!_inherit_environment) {
				environment_modified = true;

#ifndef NO_CLEARENV
				if (!clearenv()) {
					fprintf(stderr, "**ERROR** SubProcess::execute - Could not clear environment!\n");
				}
#else
				// FreeBSD manual: On systems where clearenv() is unavailable, the assignment environ = NULL; will probably do.
				environ = NULL;
#endif
			}

			for (const HashMap<StringName, String>::Element *E = _environment_variables.front(); E; E = E->next) {
				String key = E->key();
				String value = E->value();

				CharString key_cs = key.utf8();
				CharString value_cs = value.utf8();

				if (setenv(key_cs.get_data(), value_cs.get_data(), 1)) {
					fprintf(stderr, "**ERROR** SubProcess::execute - Failed to set environment variable: %s=%s!\n", key_cs.get_data(), value_cs.get_data());
				}

				environment_modified = true;
			}

			if (environment_modified) {
#ifndef NO_CLEARENV
				extern char **environ;
#endif
				execve(_executable_path.utf8().get_data(), &args[0], environ);
			} else {
				execvp(_executable_path.utf8().get_data(), &args[0]);
			}
			// still alive? something failed..
			fprintf(stderr, "**ERROR** SubProcess::execute - Could not create child process while executing: %s\n", _executable_path.utf8().get_data());
			raise(SIGKILL);
			return FAILED;
		}

		_process_id = pid;

		if (_blocking) {
			int status;
			waitpid(pid, &status, 0);

			_exitcode = WIFEXITED(status) ? WEXITSTATUS(status) : status;
		}

		return OK;
	}

	// We run it, and also set up the requested pipes

	// Pipe setup

	if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
		ERR_FAIL_COND_V(pipe(_read_std_pipes) != 0, FAILED);
	}

	if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
		ERR_FAIL_COND_V(pipe(_read_std_err_pipes) != 0, FAILED);
	}

	if ((_communication_flags & COMMUNICATION_FLAGS_STDIN) != 0) {
		ERR_FAIL_COND_V(pipe(_write_pipes) != 0, FAILED);
	}

	// Fork it

	pid_t pid = fork();
	ERR_FAIL_COND_V(pid < 0, ERR_CANT_FORK);

	if (pid == 0) {
		// is child

		// Connect inherited pipes to stdout / err / in

		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
			if (dup2(_read_std_pipes[1], STDOUT_FILENO) != STDOUT_FILENO) {
				fprintf(stderr, "**ERROR** SubProcess::execute - Could not setup std out pipe.\n");
				raise(SIGKILL);
				return FAILED;
			}
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			if (dup2(_read_std_err_pipes[1], STDERR_FILENO) != STDERR_FILENO) {
				fprintf(stderr, "**ERROR** SubProcess::execute - Could not setup std err pipe.\n");
				raise(SIGKILL);
				return FAILED;
			}
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDIN) != 0) {
			if (dup2(_write_pipes[0], STDIN_FILENO) != STDIN_FILENO) {
				fprintf(stderr, "**ERROR** SubProcess::execute - Could not setup std in pipe.\n");
				raise(SIGKILL);
				return FAILED;
			}
		}

		// Close pipes (apparently you need to close all of them in the child, because of dup2)

		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
			close(_read_std_pipes[0]);
			close(_read_std_pipes[1]);
			_read_std_pipes[0] = 0;
			_read_std_pipes[1] = 0;
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			close(_read_std_err_pipes[0]);
			close(_read_std_err_pipes[1]);
			_read_std_err_pipes[0] = 0;
			_read_std_err_pipes[1] = 0;
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDIN) != 0) {
			close(_write_pipes[0]);
			close(_write_pipes[1]);
			_write_pipes[0] = 0;
			_write_pipes[1] = 0;
		}

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

		// Set up env vars

		bool environment_modified = false;

#ifdef NO_CLEARENV
		extern char **environ;
#endif

		if (!_inherit_environment) {
			environment_modified = true;

#ifndef NO_CLEARENV
			if (!clearenv()) {
				fprintf(stderr, "**ERROR** SubProcess::execute - Could not clear environment!\n");
			}
#else
			// FreeBSD manual: On systems where clearenv() is unavailable, the assignment environ = NULL; will probably do.
			environ = NULL;
#endif
		}

		for (const HashMap<StringName, String>::Element *E = _environment_variables.front(); E; E = E->next) {
			String key = E->key();
			String value = E->value();

			CharString key_cs = key.utf8();
			CharString value_cs = value.utf8();

			if (setenv(key_cs.get_data(), value_cs.get_data(), 1)) {
				fprintf(stderr, "**ERROR** SubProcess::execute - Failed to set environment variable: %s=%s!\n", key_cs.get_data(), value_cs.get_data());
			}

			environment_modified = true;
		}

		if (environment_modified) {
#ifndef NO_CLEARENV
			extern char **environ;
#endif

			// Note that execve replaces the current process (us) with the one requested.
			execve(_executable_path.utf8().get_data(), &args[0], environ);
		} else {
			// Note that execvp replaces the current process (us) with the one requested.
			execvp(_executable_path.utf8().get_data(), &args[0]);
		}

		// still alive? something failed..
		fprintf(stderr, "**ERROR** SubProcess::execute - Could not create child process while executing: %s\n", _executable_path.utf8().get_data());
		raise(SIGKILL);
		return FAILED;
	}

	// parent

	_process_id = pid;

	// Close unneeded pipes

	if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
		close(_read_std_pipes[1]);
		_read_std_pipes[1] = 0;
	}

	if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
		close(_read_std_err_pipes[1]);
		_read_std_err_pipes[1] = 0;
	}

	if ((_communication_flags & COMMUNICATION_FLAGS_STDIN) != 0) {
		close(_write_pipes[0]);
		_write_pipes[0] = 0;
	}

	if (_blocking) {
		int bytes_in_buffer = 0;
		int err_bytes_in_buffer = 0;

		for (;;) { // Read StdOut and StdErr from pipe.
			bool had_error = false;

			// First go for stdin
			if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
				if (_read_from_std_out(bytes_in_buffer)) {
					had_error = true;
				}
			}

			// StdErr
			if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
				// We want to read even if stdin errored!
				if (_read_from_std_err(err_bytes_in_buffer)) {
					had_error = true;
				}
			}

			// Note that we don't worry about stdin here, as it can only happen if a thread launches a process in blocking mode, an an another writes to it.

			// This is needed to detect if the subprocess have terminated. even if the stdout and stderr is not connected.
			// Also on linux read() will not fail if the subprocess is not alive anymore.
			if (had_error || !is_process_running()) {
				break;
			}
		}

		// Read remaining

		// StdIn
		if (bytes_in_buffer > 0) {
			_append_to_std_out(_bytes.ptr(), bytes_in_buffer);
		}

		// StdErr
		if (err_bytes_in_buffer > 0) {
			_append_to_std_err(_err_bytes.ptr(), err_bytes_in_buffer);
		}

		// Close all remaining pipes

		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
			close(_read_std_pipes[0]);
			_read_std_pipes[0] = 0;
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			close(_read_std_err_pipes[0]);
			_read_std_err_pipes[0] = 0;
		}

		if ((_communication_flags & COMMUNICATION_FLAGS_STDIN) != 0) {
			close(_write_pipes[1]);
			_write_pipes[1] = 0;
		}

		// Cleanup

		// Grab exit code
		int status;
		// "If a child has already changed state, then these calls return immediately."
		waitpid(pid, &status, 0);
		_exitcode = WIFEXITED(status) ? WEXITSTATUS(status) : status;

		// Not running anymore
		_process_id = 0;
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

	if (!_process_id) {
		return OK;
	}

	if (!_blocking) {
		// Process remaining data when doing a non-blocking call, if there any

		// StdIn
		if ((_communication_flags & COMMUNICATION_FLAGS_STDOUT) != 0) {
			if (_bytes.size() > 0) {
				_append_to_std_out(_bytes.ptr(), _bytes.size());
			}
		}

		// StdErr
		if ((_communication_flags & COMMUNICATION_FLAGS_STDERR) != 0) {
			if (_err_bytes.size() > 0) {
				_append_to_std_err(_err_bytes.ptr(), _err_bytes.size());
			}
		}
	}

	// Cleanup pipe handles.
	for (int i = 0; i < 2; ++i) {
		if (_read_std_pipes[i]) {
			close(_read_std_pipes[i]);
			_read_std_pipes[i] = 0;
		}

		if (_read_std_err_pipes[i]) {
			close(_read_std_err_pipes[i]);
			_read_std_err_pipes[i] = 0;
		}

		if (_write_pipes[i]) {
			close(_write_pipes[i]);
			_write_pipes[i] = 0;
		}
	}

	int ret = ::kill(_process_id, SIGKILL);

	if (!ret) {
		//avoid zombie process
		int st;
		::waitpid(_process_id, &st, 0);
	}

	_process_id = 0;

	return ret ? ERR_INVALID_PARAMETER : OK;

#endif
}

Error SubProcess::poll() {
#ifdef __EMSCRIPTEN__
	// Don't compile this code at all to avoid undefined references.
	// Actual virtual call goes to OS_JavaScript.
	ERR_FAIL_V(ERR_BUG);
#else

	if (_process_id == 0) {
		return ERR_UNAVAILABLE;
	}

	if (_blocking) {
		// If it's blocking, and we want to read output from an another thread, we can just do it without poll
		// Just ignore poll calls

		if (!is_process_running()) {
			return ERR_FILE_EOF;
		}

		return OK;
	}

	if (!_read_std_pipes[0] && !_read_std_err_pipes[0]) {
		return ERR_UNAVAILABLE;
	}

	bool had_error = false;

	if (_read_std_pipes[0]) {
		if (_poll_read_from_std_out()) {
			had_error = true;
		}
	}

	if (_read_std_err_pipes[0]) {
		if (_poll_read_from_std_err()) {
			had_error = true;
		}
	}

	// Need to check, as read will just keep returning 0 if the process has terminated.
	// This should the api more convenient to use.
	if (had_error || !is_process_running()) {
		stop();
		return ERR_FILE_EOF;
	}

	return OK;
#endif
}

Error SubProcess::send_signal(const int p_signal) {
	if (_process_id == 0) {
		return FAILED;
	}

	int err = kill(_process_id, p_signal);

	if (err == EPERM) {
		return ERR_UNAUTHORIZED;
	} else if (err == 0) {
		return OK;
	}

	return FAILED;
}

Error SubProcess::write_to_stdin(const String &p_data) {
	return write_to_stdin_utf8(p_data);
}

Error SubProcess::write_to_stdin_utf8(const String &p_data) {
	if (_process_id == 0) {
		return ERR_UNAVAILABLE;
	}

	if (!_write_pipes[1]) {
		return ERR_UNAVAILABLE;
	}

	if (p_data.length() == 0) {
		return OK;
	}

	ssize_t sent = 0;
	CharString cs = p_data.utf8();

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	// Note, we are using lenght() to skip sending null terminators!
	while (sent < cs.length()) {
		ssize_t wb = write(_write_pipes[1], cs.get_data() + sent, cs.length() - sent);

		// Error
		if (wb < 0) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		sent += wb;
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}

Error SubProcess::write_to_stdin_utf16(const String &p_data) {
	if (_process_id == 0) {
		return ERR_UNAVAILABLE;
	}

	if (!_write_pipes[1]) {
		return ERR_UNAVAILABLE;
	}

	if (p_data.length() == 0) {
		return OK;
	}

	ssize_t sent = 0;
	Char16String cs = p_data.utf16();
	// Note, we are using lenght() to skip sending null terminators!
	int length_bytes = cs.length() * sizeof(char16_t);

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	while (sent < length_bytes) {
		ssize_t wb = write(_write_pipes[1], ((const char *)cs.get_data()) + sent, length_bytes - sent);

		// Error
		if (wb < 0) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		sent += wb;
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}

Error SubProcess::write_to_stdin_utf32(const String &p_data) {
	if (_process_id == 0) {
		return ERR_UNAVAILABLE;
	}

	if (!_write_pipes[1]) {
		return ERR_UNAVAILABLE;
	}

	if (p_data.length() == 0) {
		return OK;
	}

	ssize_t sent = 0;
	const CharType *cs = p_data.get_data();
	// Note, we are using lenght() to skip sending null terminators!
	int length_bytes = p_data.length() * sizeof(CharType);

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	while (sent < length_bytes) {
		ssize_t wb = write(_write_pipes[1], ((const char *)cs + sent), length_bytes - sent);

		// Error
		if (wb < 0) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		sent += wb;
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}

Error SubProcess::write_data_to_stdin(const Vector<uint8_t> &p_data) {
	if (_process_id == 0) {
		return ERR_UNAVAILABLE;
	}

	if (!_write_pipes[1]) {
		return ERR_UNAVAILABLE;
	}

	if (p_data.size() == 0) {
		return OK;
	}

	ssize_t sent = 0;

	if (_std_in_mutex) {
		_std_in_mutex->lock();
	}

	int size = p_data.size();

	while (sent < p_data.size()) {
		ssize_t wb = write(_write_pipes[1], p_data.ptr() + sent, size - sent);

		// Error
		if (wb < 0) {
			if (_std_in_mutex) {
				_std_in_mutex->unlock();
			}

			stop();
			return ERR_FILE_EOF;
		}

		sent += wb;
	}

	if (_std_in_mutex) {
		_std_in_mutex->unlock();
	}

	return OK;
}

bool SubProcess::is_process_running() const {
#ifdef __EMSCRIPTEN__
	// Don't compile this code at all to avoid undefined references.
	// Actual virtual call goes to OS_JavaScript.
	ERR_FAIL_V(false);
#else

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

	_communication_flags = COMMUNICATION_FLAGS_STDOUT;

	_inherit_environment = true;

	_use_pipe_mutex = false;

	_std_out_mutex = NULL;
	_std_err_mutex = NULL;
	_std_in_mutex = NULL;

	_open_console = false;

	_process_id = ProcessID();
	_exitcode = 0;

	_read_std_pipes[0] = 0;
	_read_std_pipes[1] = 0;

	_read_std_err_pipes[0] = 0;
	_read_std_err_pipes[1] = 0;

	_write_pipes[0] = 0;
	_write_pipes[1] = 0;
}
SubProcess::~SubProcess() {
	stop();
}

bool SubProcess::_read_from_std_out(int &bytes_in_buffer) {
	const int CHUNK_SIZE = 4096;

	ssize_t rbytes = 0;
	_bytes.resize(bytes_in_buffer + CHUNK_SIZE);

	rbytes = read(_read_std_pipes[0], _bytes.ptr() + bytes_in_buffer, CHUNK_SIZE);

	if (rbytes < 0) {
		_bytes.resize(bytes_in_buffer);
		//stop();
		return true;
	}

	if (rbytes != 0) {
		// Assume that all possible encodings are ASCII-compatible.
		// Break at newline to allow receiving long output in portions.
		int newline_index = -1;
		for (int i = rbytes - 1; i >= 0; i--) {
			if (_bytes[bytes_in_buffer + i] == '\n') {
				newline_index = i;
				break;
			}
		}

		if (newline_index == -1) {
			bytes_in_buffer += rbytes;
			return false;
		}

		const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
		_append_to_std_out(_bytes.ptr(), bytes_to_convert);

		bytes_in_buffer = rbytes - (newline_index + 1);
		memmove(_bytes.ptr(), _bytes.ptr() + bytes_to_convert, bytes_in_buffer);
	} else {
		// 0 read, remove chunk. Should probably save actual size as a variable eventually.
		_bytes.resize(bytes_in_buffer);
	}

	return false;
}
bool SubProcess::_read_from_std_err(int &err_bytes_in_buffer) {
	const int CHUNK_SIZE = 4096;

	ssize_t erbytes = 0;
	_err_bytes.resize(err_bytes_in_buffer + CHUNK_SIZE);

	erbytes = read(_read_std_err_pipes[0], _err_bytes.ptr() + err_bytes_in_buffer, CHUNK_SIZE);

	if (erbytes < 0) {
		_err_bytes.resize(err_bytes_in_buffer);
		//stop();
		return true;
	}

	if (erbytes != 0) {
		// Assume that all possible encodings are ASCII-compatible.
		// Break at newline to allow receiving long output in portions.
		int newline_index = -1;
		for (int i = erbytes - 1; i >= 0; i--) {
			if (_err_bytes[err_bytes_in_buffer + i] == '\n') {
				newline_index = i;
				break;
			}
		}

		if (newline_index == -1) {
			err_bytes_in_buffer += erbytes;
			return false;
		}

		const int bytes_to_convert = err_bytes_in_buffer + (newline_index + 1);
		_append_to_std_err(_err_bytes.ptr(), bytes_to_convert);

		err_bytes_in_buffer = erbytes - (newline_index + 1);
		memmove(_err_bytes.ptr(), _err_bytes.ptr() + bytes_to_convert, err_bytes_in_buffer);
	} else {
		// 0 read, remove chunk. Should probably save actual size as a variable eventually.
		_err_bytes.resize(err_bytes_in_buffer);
	}

	return false;
}

bool SubProcess::_poll_read_from_std_out() {
	const int CHUNK_SIZE = 4096;

	int bytes_in_buffer = _bytes.size();

	_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
	ssize_t rbytes = read(_read_std_pipes[0], _bytes.ptr() + bytes_in_buffer, CHUNK_SIZE);

	if (rbytes < 0) {
		// Note, stop() will process remaning bytes, we had an error, so get rid of the new chunk, as it's empty.
		_bytes.resize(bytes_in_buffer);
		//stop();
		return true;
	}

	if (rbytes != 0) {
		// Assume that all possible encodings are ASCII-compatible.
		// Break at newline to allow receiving long output in portions.
		int newline_index = -1;
		for (int i = rbytes - 1; i >= 0; i--) {
			if (_bytes[bytes_in_buffer + i] == '\n') {
				newline_index = i;
				break;
			}
		}

		if (newline_index == -1) {
			bytes_in_buffer += rbytes;
		} else {
			const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
			_append_to_std_out(_bytes.ptr(), bytes_to_convert);

			bytes_in_buffer = rbytes - (newline_index + 1);
			memmove(_bytes.ptr(), _bytes.ptr() + bytes_to_convert, bytes_in_buffer);
		}

		_bytes.resize(bytes_in_buffer);
	} else {
		// 0 read, remove chunk. Should probably save actual size as a variable eventually.
		_bytes.resize(bytes_in_buffer);
	}

	return false;
}
bool SubProcess::_poll_read_from_std_err() {
	const int CHUNK_SIZE = 4096;

	int bytes_in_buffer = _err_bytes.size();

	_err_bytes.resize(bytes_in_buffer + CHUNK_SIZE);
	ssize_t rbytes = read(_read_std_err_pipes[0], _err_bytes.ptr() + bytes_in_buffer, CHUNK_SIZE);

	if (rbytes < 0) {
		// Note, stop() will process remaning bytes, we had an error, so get rid of the new chunk, as it's empty.
		_err_bytes.resize(bytes_in_buffer);
		//stop();
		return true;
	}

	if (rbytes != 0) {
		// Assume that all possible encodings are ASCII-compatible.
		// Break at newline to allow receiving long output in portions.
		int newline_index = -1;
		for (int i = rbytes - 1; i >= 0; i--) {
			if (_err_bytes[bytes_in_buffer + i] == '\n') {
				newline_index = i;
				break;
			}
		}

		if (newline_index == -1) {
			bytes_in_buffer += rbytes;
		} else {
			const int bytes_to_convert = bytes_in_buffer + (newline_index + 1);
			_append_to_std_err(_err_bytes.ptr(), bytes_to_convert);

			bytes_in_buffer = rbytes - (newline_index + 1);
			memmove(_err_bytes.ptr(), _err_bytes.ptr() + bytes_to_convert, bytes_in_buffer);
		}

		_err_bytes.resize(bytes_in_buffer);
	} else {
		// 0 read, remove chunk. Should probably save actual size as a variable eventually.
		_err_bytes.resize(bytes_in_buffer);
	}

	return false;
}

void SubProcess::_append_to_std_out(char *p_bytes, int p_size) {
	if (_std_out_mutex) {
		_std_out_mutex->lock();
	}
	_std_out += String::utf8(p_bytes, p_size);
	if (_std_out_mutex) {
		_std_out_mutex->unlock();
	}
}

void SubProcess::_append_to_std_err(char *p_bytes, int p_size) {
	if (_std_err_mutex) {
		_std_err_mutex->lock();
	}
	_std_err += String::utf8(p_bytes, p_size);
	if (_std_err_mutex) {
		_std_err_mutex->unlock();
	}
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

int SubProcess::get_communication_flags() const {
	return _communication_flags;
}
void SubProcess::set_communication_flags(const int p_flags) {
	ERR_FAIL_COND(is_process_running());

	_communication_flags = p_flags;
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

// Environment

bool SubProcess::get_inherit_environment() const {
	return _inherit_environment;
}
void SubProcess::set_inherit_environment(const bool p_value) {
	_inherit_environment = p_value;
}

bool SubProcess::has_environment_variable(const StringName &p_key) {
	return _environment_variables.has(p_key);
}
String SubProcess::get_environment_variable(const StringName &p_key) {
	if (!_environment_variables.has(p_key)) {
		return String();
	}

	return _environment_variables[p_key];
}
void SubProcess::set_environment_variable(const StringName &p_key, const String &p_value) {
	_environment_variables[p_key] = p_value;
}
void SubProcess::unset_environment_variable(const StringName &p_key) {
	_environment_variables.erase(p_key);
}
void SubProcess::clear_environment_variables() {
	_environment_variables.clear();
}

Vector<String> SubProcess::get_environment_variable_keys() {
	Vector<String> r;

	for (const HashMap<StringName, String>::Element *E = _environment_variables.front(); E; E = E->next) {
		r.push_back(E->key());
	}

	return r;
}

// Other getters

String SubProcess::get_std_out() {
	if (_std_out_mutex) {
		_std_out_mutex->lock();
	}

	String data = _std_out;
	_std_out = String();

	if (_std_out_mutex) {
		_std_out_mutex->unlock();
	}

	return data;
}

String SubProcess::get_std_err() {
	if (_std_err_mutex) {
		_std_err_mutex->lock();
	}

	String data = _std_err;
	_std_err = String();

	if (_std_err_mutex) {
		_std_err_mutex->unlock();
	}

	return data;
}

Error SubProcess::run(const String &p_executable_path, const Vector<String> &p_arguments, const int p_communication_flags, bool p_blocking, bool p_use_pipe_mutex, bool p_open_console) {
	if (is_process_running()) {
		return ERR_ALREADY_IN_USE;
	}

	_executable_path = p_executable_path;
	_arguments = p_arguments;

	_communication_flags = p_communication_flags;
	_blocking = p_blocking;

	_use_pipe_mutex = p_use_pipe_mutex;

	_open_console = p_open_console;

	_setup_pipe_mutex();

	return start();
}

/*
SubProcess::SubProcess() {
	_blocking = false;

	_communication_flags = COMMUNICATION_FLAGS_STDOUT;

	_inherit_environment = true;

	_use_pipe_mutex = false;

	_std_out_mutex = NULL;
	_std_err_mutex = NULL;
	_std_in_mutex = NULL;

	_open_console = false;

	_process_id = ProcessID();
	_exitcode = 0;
};
*/

void SubProcess::_setup_pipe_mutex() {
	if (_use_pipe_mutex) {
		if (!_std_out_mutex) {
			_std_out_mutex = memnew(Mutex);
		}
		if (!_std_err_mutex) {
			_std_err_mutex = memnew(Mutex);
		}
		if (!_std_in_mutex) {
			_std_in_mutex = memnew(Mutex);
		}
	} else {
		if (_std_out_mutex) {
			memdelete(_std_out_mutex);
			_std_out_mutex = NULL;
		}
		if (_std_err_mutex) {
			memdelete(_std_err_mutex);
			_std_err_mutex = NULL;
		}
		if (_std_in_mutex) {
			memdelete(_std_in_mutex);
			_std_in_mutex = NULL;
		}
	}
}
