#ifndef __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_UTIL__FTH_UTIL_H__
#define __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_UTIL__FTH_UTIL_H__

#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Common.h"



__SPS_GG__NS__B_EXTEND_FREETYPE

class FTH_Util
{
public:
	// 大于等于当前数的最小的2的整数次幂
	static unsigned long next_power_of_2( const unsigned long nValue );

	// 获取像素模式单个像素需要的字节数
	static FTH_UByte get_pixed_mode_need_byte_count( PixelMode ePixelMode );
}; // end class FTH_Util

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_FREETYPE



#endif // #if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_UTIL__FTH_UTIL_H__
