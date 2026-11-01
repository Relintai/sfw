//--STRIP
#ifndef SFW_TIME_H
#define SFW_TIME_H
//--STRIP

// -----------------------------------------------------------------------------
// time framework utils
// - originally by rlyeh, public domain.

/*************************************************************************/
/*  Som methods are                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/int_types.h"
#include "core/ustring.h"
//--STRIP

class SFWTime {
public:
	enum Weekday {
		DAY_SUNDAY,
		DAY_MONDAY,
		DAY_TUESDAY,
		DAY_WEDNESDAY,
		DAY_THURSDAY,
		DAY_FRIDAY,
		DAY_SATURDAY
	};

	enum Month {
		/// Start at 1 to follow Windows SYSTEMTIME structure
		/// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx
		MONTH_JANUARY = 1,
		MONTH_FEBRUARY,
		MONTH_MARCH,
		MONTH_APRIL,
		MONTH_MAY,
		MONTH_JUNE,
		MONTH_JULY,
		MONTH_AUGUST,
		MONTH_SEPTEMBER,
		MONTH_OCTOBER,
		MONTH_NOVEMBER,
		MONTH_DECEMBER
	};

	struct Date {
		int year;
		Month month;
		int day;
		Weekday weekday;
		bool dst;
	};

	struct Time {
		int hour;
		int min;
		int sec;
	};

	struct DateTime {
		Date date;
		Time time;
	};

	struct TimeZoneInfo {
		int bias;
		String name;
	};

	static Date get_date(bool local = false);
	static Time get_time(bool local = false);
	static TimeZoneInfo get_time_zone_info();
	static String get_iso_date_time(bool local = false);
	static uint64_t get_unix_time();
	static uint64_t get_system_time_secs();
	static uint64_t get_system_time_msecs();
	static DateTime get_datetime_from_unix_time(int64_t unix_time_val);
	static int64_t get_unix_time_from_datetime(const DateTime &datetime);

	// Deprecated:
	static uint64_t date(); // == get_unix_time();
	static uint64_t date_epoch(); // == get_unix_time();
	static String date_string(); // == get_iso_date_time();

	static double time_hh();
	static double time_mm();
	static double time_ss();

	static uint64_t time_ms();
	static uint64_t time_us();
	static uint64_t time_ns();

	static void sleep_ss(double ss);
	static void sleep_ms(double ms);
	static void sleep_us(double us);
	static void sleep_ns(double us);
};

//--STRIP
#endif
//--STRIP
