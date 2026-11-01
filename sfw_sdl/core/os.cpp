
//--STRIP
#include "os.h"
//--STRIP

#if defined(_WIN64) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winnt.h>
#else
#include <unistd.h>
#endif

#if defined(_WIN64) || defined(_WIN32)
// From the Pandemonium Engine.

// We need this because GetSystemInfo() is unreliable on WOW64
// see https://msdn.microsoft.com/en-us/library/windows/desktop/ms724381(v=vs.85).aspx
// Taken from MSDN
typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL is_wow64() {
	BOOL wow64 = FALSE;

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (fnIsWow64Process) {
		if (!fnIsWow64Process(GetCurrentProcess(), &wow64)) {
			wow64 = FALSE;
		}
	}

	return wow64;
}
#endif

// From the Pandemonium Engine.
int OS::get_processor_count() {
#if defined(_WIN64) || defined(_WIN32)
	SYSTEM_INFO sysinfo;
	if (is_wow64())
		GetNativeSystemInfo(&sysinfo);
	else
		GetSystemInfo(&sysinfo);

	return sysinfo.dwNumberOfProcessors;
#else
	return sysconf(_SC_NPROCESSORS_CONF);
#endif
}
