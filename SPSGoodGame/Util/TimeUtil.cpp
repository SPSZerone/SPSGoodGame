#include "TimeUtil.h"
__SPS_GG__NS__U_UTIL;



time_t TimeUtil::get_current_time()
{
	time_t curTime;
	time( &curTime );
	return curTime;
}



tm *TimeUtil::get_current_tm()
{
	const time_t timeTmp = get_current_time();
	return localtime( &timeTmp );
}



time_t TimeUtil::make_time( tm *pTM )
{
	if ( pTM == nullptr )
	{
		return 0;
	}
	return mktime( pTM );
}
