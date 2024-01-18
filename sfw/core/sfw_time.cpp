// ----------------------------------------------------------------------------
// time

//--STRIP
#include "core/sfw_time.h"

#include <time.h>
#include <ctime>
//--STRIP

#if defined(_WIN64) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winnt.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#if 0
uint64_t SFWTime::time_gpu() {
    GLint64 t = 123456789;
    glGetInteger64v(GL_TIMESTAMP, &t);
    return (uint64_t)t;
}
#endif
uint64_t SFWTime::date() {
	//time_t epoch = time(0);
	//struct tm *ti = localtime(&epoch);
	//return atoi64(va("%04d%02d%02d%02d%02d%02d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec));
	return 0;
}
char *SFWTime::date_string() {
	//time_t epoch = time(0);
	//struct tm *ti = localtime(&epoch);
	//return va("%04d-%02d-%02d %02d:%02d:%02d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
	return 0;
}
uint64_t SFWTime::date_epoch() {
	time_t epoch = time(0);
	return epoch;
}
#if 0
double SFWTime::time_ss() {
    return glfwGetTime();
}
double SFWTime::time_ms() {
    return glfwGetTime() * 1000.0;
}
uint64_t SFWTime::time_us() {
    return (uint64_t)(glfwGetTime() * 1000000.0); // @fixme: use a high resolution timer instead, or time_gpu below
}
uint64_t SFWTime::sleep_us(uint64_t us) { // @fixme: use a high resolution sleeper instead
    return sleep_ms( us / 1000.0 );
}
double SFWTime::sleep_ms(double ms) {
    double now = time_ms();
    if( ms <= 0 ) {
#if defined(_WIN64) || defined(_WIN32)
        Sleep(0); // yield
#else
        usleep(0);
#endif
    } else {
#if defined(_WIN64) || defined(_WIN32)
        Sleep(ms);
#else
        usleep(ms * 1000);
#endif
    }
    return time_ms() - now;
}
double sleep_ss(double ss) {
    return sleep_ms( ss * 1000 ) / 1000.0;
}
#endif

// high-perf functions

#define TIMER_E3 1000ULL
#define TIMER_E6 1000000ULL
#define TIMER_E9 1000000000ULL

#ifdef CLOCK_MONOTONIC_RAW
#define TIME_MONOTONIC CLOCK_MONOTONIC_RAW
#elif defined CLOCK_MONOTONIC
#define TIME_MONOTONIC CLOCK_MONOTONIC
#else
// #define TIME_MONOTONIC CLOCK_REALTIME // untested
#endif

static uint64_t nanotimer(uint64_t *out_freq) {
	if (out_freq) {
#if defined(_WIN64) || defined(_WIN32)
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		*out_freq = li.QuadPart;
//#elif is(ANDROID)
//      *out_freq = CLOCKS_PER_SEC;
#elif defined TIME_MONOTONIC
		*out_freq = TIMER_E9;
#else
		*out_freq = TIMER_E6;
#endif
	}
#if defined(_WIN64) || defined(_WIN32)
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (uint64_t)li.QuadPart;
//#elif is(ANDROID)
//    return (uint64_t)clock();
#elif defined TIME_MONOTONIC
	struct timespec ts;
	clock_gettime(TIME_MONOTONIC, &ts);
	return (TIMER_E9 * (uint64_t)ts.tv_sec) + ts.tv_nsec;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (TIMER_E6 * (uint64_t)tv.tv_sec) + tv.tv_usec;
#endif
}

uint64_t SFWTime::time_ns() {
	static thread_local uint64_t epoch = 0;
	static thread_local uint64_t freq = 0;
	if (!freq) {
		epoch = nanotimer(&freq);
	}

	uint64_t a = nanotimer(NULL) - epoch;
	uint64_t b = TIMER_E9;
	uint64_t c = freq;

	// Computes (a*b)/c without overflow, as long as both (a*b) and the overall result fit into 64-bits.
	// [ref] https://github.com/rust-lang/rust/blob/3809bbf47c8557bd149b3e52ceb47434ca8378d5/src/libstd/sys_common/mod.rs#L124
	uint64_t q = a / c;
	uint64_t r = a % c;
	return q * b + r * b / c;
}
uint64_t SFWTime::time_us() {
	return time_ns() / TIMER_E3;
}
uint64_t SFWTime::time_ms() {
	return time_ns() / TIMER_E6;
}
double SFWTime::time_ss() {
	return time_ns() / 1e9; // TIMER_E9;
}
double SFWTime::time_mm() {
	return time_ss() / 60;
}
double SFWTime::time_hh() {
	return time_mm() / 60;
}

void SFWTime::sleep_ns(double ns) {
#if defined(_WIN64) || defined(_WIN32)
	if (ns >= 100) {
		LARGE_INTEGER li; // Windows sleep in 100ns units
		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
		li.QuadPart = (LONGLONG)(__int64)(-ns / 100); // Negative for relative time
		SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE);
		WaitForSingleObject(timer, INFINITE);
		CloseHandle(timer);
#else
	if (ns > 0) {
		struct timespec wait = { 0 };
		wait.tv_sec = ns / 1e9;
		wait.tv_nsec = ns - wait.tv_sec * 1e9;
		nanosleep(&wait, NULL);
#endif
	} else {
#if defined(_WIN64) || defined(_WIN32)
		Sleep(0); // yield, Sleep(0), SwitchToThread
#else
		usleep(0);
#endif
	}
}
void SFWTime::sleep_us(double us) {
	sleep_ns(us * 1e3);
}
void SFWTime::sleep_ms(double ms) {
	sleep_ns(ms * 1e6);
}
void SFWTime::sleep_ss(double ss) {
	sleep_ns(ss * 1e9);
}
