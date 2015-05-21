#ifndef __SPS__GOOD_GAME__UTIL__CPU_UTIL_H__
#define __SPS__GOOD_GAME__UTIL__CPU_UTIL_H__

#include "SPSGoodGame/Base/Base.h"



__SPS_GG__NS__B_UTIL

class CPUUtil
{
public:
	enum class Endian
	{
		LITTLE,
		BIG
	};
	/* 大小端判断
	*/
	static Endian check_endian();
}; // end class CPUUtil

__SPS_GG__NS__END



#endif // #ifndef __SPS__GOOD_GAME__UTIL__CPU_UTIL_H__
