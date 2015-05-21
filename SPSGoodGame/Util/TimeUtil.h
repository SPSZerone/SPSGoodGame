#ifndef __SPS__GOOD_GAME__UTIL__TIME_UTIL_H__
#define __SPS__GOOD_GAME__UTIL__TIME_UTIL_H__

#include "SPSGoodGame/Base/Base.h"
#include <time.h>



/* tm
	tm_year			// 年：其值等于实际年份减去1900

	tm_mon			// 月 - 范围 [ 0, 11 ]：从一月开始，0代表一月

	tm_mday			// 日（一个月中的日期） - 范围 [ 1, 31 ]
	tm_wday			// 星期 - 范围 [ 0, 6 ]：0代表星期天，1代表星期一，以此类推
	tm_yday			// 从每年的1月1日开始的天数 - 范围 [ 0, 365 ]：0代表1月1日，1代表1月2日，以此类推

	tm_hour			// 时 - 范围 [ 0, 23 ]
	tm_min				// 分 - 范围 [ 0, 59 ]
	tm_sec				// 秒 - 范围 [ 0, 59 ]

	tm_isdst			// 夏令时标识符：> 0 实行夏令时；0 不实行夏令时；< 0 不了解情况时
*/
__SPS_GG__NS__B_UTIL

class TimeUtil
{
public:
	static time_t get_current_time();
	static tm *get_current_tm();
	static time_t make_time( tm *pTM );
}; // end class TimeUtil

__SPS_GG__NS__END



#endif // #ifndef __SPS__GOOD_GAME__UTIL__TIME_UTIL_H__
