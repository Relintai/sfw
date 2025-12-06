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
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#endif

SFWTime::Date SFWTime::get_date(bool utc) {
#if defined(_WIN64) || defined(_WIN32)
	SYSTEMTIME systemtime;
	if (utc)
		GetSystemTime(&systemtime);
	else
		GetLocalTime(&systemtime);

	// Get DST information from Windows, but only if utc is false.
	TIME_ZONE_INFORMATION info;
	bool daylight = false;
	if (!utc && GetTimeZoneInformation(&info) == TIME_ZONE_ID_DAYLIGHT) {
		daylight = true;
	}

	Date date;
	date.day = systemtime.wDay;
	date.month = Month(systemtime.wMonth);
	date.weekday = Weekday(systemtime.wDayOfWeek);
	date.year = systemtime.wYear;
	date.dst = daylight;
	return date;
#else
	time_t t = time(nullptr);
	struct tm lt;
	if (utc) {
		gmtime_r(&t, &lt);
	} else {
		localtime_r(&t, &lt);
	}
	Date ret;
	ret.year = 1900 + lt.tm_year;
	// Index starting at 1 to match OS_Unix::get_date
	//   and Windows SYSTEMTIME and tm_mon follows the typical structure
	//   of 0-11, noted here: http://www.cplusplus.com/reference/ctime/tm/
	ret.month = (Month)(lt.tm_mon + 1);
	ret.day = lt.tm_mday;
	ret.weekday = (Weekday)lt.tm_wday;
	ret.dst = lt.tm_isdst;

	return ret;
#endif
}

SFWTime::Time SFWTime::get_time(bool utc) {
#if defined(_WIN64) || defined(_WIN32)
	SYSTEMTIME systemtime;
	if (utc)
		GetSystemTime(&systemtime);
	else
		GetLocalTime(&systemtime);

	Time time;
	time.hour = systemtime.wHour;
	time.min = systemtime.wMinute;
	time.sec = systemtime.wSecond;
	return time;
#else
	time_t t = time(nullptr);
	struct tm lt;
	if (utc) {
		gmtime_r(&t, &lt);
	} else {
		localtime_r(&t, &lt);
	}
	Time ret;
	ret.hour = lt.tm_hour;
	ret.min = lt.tm_min;
	ret.sec = lt.tm_sec;
	get_time_zone_info();
	return ret;
#endif
}

SFWTime::TimeZoneInfo SFWTime::get_time_zone_info() {
#if defined(_WIN64) || defined(_WIN32)
	TIME_ZONE_INFORMATION info;
	bool daylight = false;
	if (GetTimeZoneInformation(&info) == TIME_ZONE_ID_DAYLIGHT)
		daylight = true;

	// Daylight Bias needs to be added to the bias if DST is in effect, or else it will not properly update.
	TimeZoneInfo ret;
	if (daylight) {
		ret.name = info.DaylightName;
		ret.bias = info.Bias + info.DaylightBias;
	} else {
		ret.name = info.StandardName;
		ret.bias = info.Bias + info.StandardBias;
	}

	// Bias value returned by GetTimeZoneInformation is inverted of what we expect
	// For example, on GMT-3 GetTimeZoneInformation return a Bias of 180, so invert the value to get -180
	ret.bias = -ret.bias;
	return ret;
#else
	time_t t = time(nullptr);
	struct tm lt;
	localtime_r(&t, &lt);
	char name[16];
	strftime(name, 16, "%Z", &lt);
	name[15] = 0;
	TimeZoneInfo ret;
	ret.name = name;

	char bias_buf[16];
	strftime(bias_buf, 16, "%z", &lt);
	int bias;
	bias_buf[15] = 0;
	sscanf(bias_buf, "%d", &bias);

	// convert from ISO 8601 (1 minute=1, 1 hour=100) to minutes
	int hour = (int)bias / 100;
	int minutes = bias % 100;
	if (bias < 0) {
		ret.bias = hour * 60 - minutes;
	} else {
		ret.bias = hour * 60 + minutes;
	}

	return ret;
#endif
}
String SFWTime::get_iso_date_time(bool local) {
	SFWTime::Date date = get_date(local);
	SFWTime::Time time = get_time(local);

	String timezone;
	if (!local) {
		TimeZoneInfo zone = get_time_zone_info();
		if (zone.bias >= 0) {
			timezone = "+";
		}
		timezone = timezone + itos(zone.bias / 60).pad_zeros(2) + itos(zone.bias % 60).pad_zeros(2);
	} else {
		timezone = "Z";
	}

	return itos(date.year).pad_zeros(2) + "-" +
			itos(date.month).pad_zeros(2) + "-" +
			itos(date.day).pad_zeros(2) + "T" +
			itos(time.hour).pad_zeros(2) + ":" +
			itos(time.min).pad_zeros(2) + ":" +
			itos(time.sec).pad_zeros(2) + timezone;
}
uint64_t SFWTime::get_unix_time() {
#if defined(_WIN64) || defined(_WIN32)
	FILETIME ft;
	SYSTEMTIME st;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);

	SYSTEMTIME ep;
	ep.wYear = 1970;
	ep.wMonth = 1;
	ep.wDayOfWeek = 4;
	ep.wDay = 1;
	ep.wHour = 0;
	ep.wMinute = 0;
	ep.wSecond = 0;
	ep.wMilliseconds = 0;
	FILETIME fep;
	SystemTimeToFileTime(&ep, &fep);

	// Type punning through unions (rather than pointer cast) as per:
	// https://docs.microsoft.com/en-us/windows/desktop/api/minwinbase/ns-minwinbase-filetime#remarks
	ULARGE_INTEGER ft_punning;
	ft_punning.LowPart = ft.dwLowDateTime;
	ft_punning.HighPart = ft.dwHighDateTime;

	ULARGE_INTEGER fep_punning;
	fep_punning.LowPart = fep.dwLowDateTime;
	fep_punning.HighPart = fep.dwHighDateTime;

	return (ft_punning.QuadPart - fep_punning.QuadPart) / 10000000;
#else
	return time(nullptr);
#endif
}
uint64_t SFWTime::get_system_time_secs() {
#if defined(_WIN64) || defined(_WIN32)
	return get_system_time_msecs() / 1000;
#else
	struct timeval tv_now;
	gettimeofday(&tv_now, nullptr);
	return uint64_t(tv_now.tv_sec);
#endif
}
uint64_t SFWTime::get_system_time_msecs() {
#if defined(_WIN64) || defined(_WIN32)
	const uint64_t WINDOWS_TICK = 10000;
	const uint64_t MSEC_TO_UNIX_EPOCH = 11644473600000LL;

	SYSTEMTIME st;
	GetSystemTime(&st);
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);
	uint64_t ret;
	ret = ft.dwHighDateTime;
	ret <<= 32;
	ret |= ft.dwLowDateTime;

	return (uint64_t)(ret / WINDOWS_TICK - MSEC_TO_UNIX_EPOCH);
#else
	struct timeval tv_now;
	gettimeofday(&tv_now, nullptr);
	return uint64_t(tv_now.tv_sec) * 1000 + uint64_t(tv_now.tv_usec) / 1000;
#endif
}

/**
 *  Time constants borrowed from loc_time.h
 */
#define EPOCH_YR 1970 /* EPOCH = Jan 1 1970 00:00:00 */
#define SECS_DAY (24L * 60L * 60L)
#define LEAPYEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year) (LEAPYEAR(year) ? 366 : 365)

/// Table of number of days in each month (for regular year and leap year)
static const unsigned int SFW_TIME_MONTH_DAYS_TABLE[2][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

SFWTime::DateTime SFWTime::get_datetime_from_unix_time(int64_t unix_time_val) {
	DateTime dt;

	long dayclock, dayno;
	int year = EPOCH_YR;

	if (unix_time_val >= 0) {
		dayno = unix_time_val / SECS_DAY;
		dayclock = unix_time_val % SECS_DAY;
		/* day 0 was a thursday */
		dt.date.weekday = static_cast<SFWTime::Weekday>((dayno + 4) % 7);
		while (dayno >= YEARSIZE(year)) {
			dayno -= YEARSIZE(year);
			year++;
		}
	} else {
		dayno = (unix_time_val - SECS_DAY + 1) / SECS_DAY;
		dayclock = unix_time_val - dayno * SECS_DAY;
		dt.date.weekday = static_cast<SFWTime::Weekday>(((dayno % 7) + 11) % 7);
		do {
			year--;
			dayno += YEARSIZE(year);
		} while (dayno < 0);
	}

	dt.time.sec = dayclock % 60;
	dt.time.min = (dayclock % 3600) / 60;
	dt.time.hour = dayclock / 3600;
	dt.date.year = year;

	size_t imonth = 0;

	while ((unsigned long)dayno >= SFW_TIME_MONTH_DAYS_TABLE[LEAPYEAR(year)][imonth]) {
		dayno -= SFW_TIME_MONTH_DAYS_TABLE[LEAPYEAR(year)][imonth];
		imonth++;
	}

	/// Add 1 to month to make sure months are indexed starting at 1
	dt.date.month = static_cast<SFWTime::Month>(imonth + 1);

	dt.date.day = dayno + 1;

	return dt;
}
int64_t SFWTime::get_unix_time_from_datetime(const DateTime &datetime) {
	// Bunch of conversion constants
	static const unsigned int SECONDS_PER_MINUTE = 60;
	static const unsigned int MINUTES_PER_HOUR = 60;
	static const unsigned int HOURS_PER_DAY = 24;
	static const unsigned int SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
	static const unsigned int SECONDS_PER_DAY = SECONDS_PER_HOUR * HOURS_PER_DAY;

	unsigned int second = static_cast<unsigned int>(datetime.time.sec);
	unsigned int minute = static_cast<unsigned int>(datetime.time.min);
	unsigned int hour = static_cast<unsigned int>(datetime.time.hour);
	unsigned int day = static_cast<unsigned int>(datetime.date.day);
	unsigned int month = static_cast<unsigned int>(datetime.date.month);
	unsigned int year = static_cast<unsigned int>(datetime.date.year);

	/// How many days come before each month (0-12)
	static const unsigned short int DAYS_PAST_THIS_YEAR_TABLE[2][13] = {
		/* Normal years.  */
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
		/* Leap years.  */
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
	};

	ERR_FAIL_COND_V_MSG(second > 59, 0, "Invalid second value of: " + itos(second) + ".");
	ERR_FAIL_COND_V_MSG(minute > 59, 0, "Invalid minute value of: " + itos(minute) + ".");
	ERR_FAIL_COND_V_MSG(hour > 23, 0, "Invalid hour value of: " + itos(hour) + ".");
	ERR_FAIL_COND_V_MSG(year == 0, 0, "Years before 1 AD are not supported. Value passed: " + itos(year) + ".");
	ERR_FAIL_COND_V_MSG(month > 12 || month == 0, 0, "Invalid month value of: " + itos(month) + ".");
	// Do this check after month is tested as valid
	unsigned int days_in_month = SFW_TIME_MONTH_DAYS_TABLE[LEAPYEAR(year)][month - 1];
	ERR_FAIL_COND_V_MSG(day == 0 || day > days_in_month, 0, "Invalid day value of: " + itos(day) + ". It should be comprised between 1 and " + itos(days_in_month) + " for month " + itos(month) + ".");

	// Calculate all the seconds from months past in this year
	uint64_t SECONDS_FROM_MONTHS_PAST_THIS_YEAR = DAYS_PAST_THIS_YEAR_TABLE[LEAPYEAR(year)][month - 1] * SECONDS_PER_DAY;

	int64_t SECONDS_FROM_YEARS_PAST = 0;
	if (year >= EPOCH_YR) {
		for (unsigned int iyear = EPOCH_YR; iyear < year; iyear++) {
			SECONDS_FROM_YEARS_PAST += YEARSIZE(iyear) * SECONDS_PER_DAY;
		}
	} else {
		for (unsigned int iyear = EPOCH_YR - 1; iyear >= year; iyear--) {
			SECONDS_FROM_YEARS_PAST -= YEARSIZE(iyear) * SECONDS_PER_DAY;
		}
	}

	int64_t epoch =
			second +
			minute * SECONDS_PER_MINUTE +
			hour * SECONDS_PER_HOUR +
			// Subtract 1 from day, since the current day isn't over yet
			//   and we cannot count all 24 hours.
			(day - 1) * SECONDS_PER_DAY +
			SECONDS_FROM_MONTHS_PAST_THIS_YEAR +
			SECONDS_FROM_YEARS_PAST;

	return epoch;
}

#undef EPOCH_YR
#undef SECS_DAY
#undef LEAPYEAR
#undef YEARSIZE

uint64_t SFWTime::date() {
	return get_unix_time();
}
String SFWTime::date_string() {
	return get_iso_date_time();
}

uint64_t SFWTime::date_epoch() {
	return get_unix_time();
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
