
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
