#include "FTH_Util.h"
#if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
__SPS_GG__NS__U_EXTEND_FREETYPE;



unsigned long FTH_Util::next_power_of_2( const unsigned long nValue )
{
	unsigned int nBitOffset = 0;
	unsigned long nPowerOf2 = 0;

	while ( nBitOffset < 32 )
	{
		nPowerOf2 = 1 << nBitOffset;
		nBitOffset++;

		if ( nPowerOf2 >= nValue )
		{
			return nPowerOf2;
		}
	}

	return 0xFFFFFFFF;
}



FTH_UByte FTH_Util::get_pixed_mode_need_byte_count( PixelMode ePixelMode )
{
	switch( ePixelMode )
	{
	case PixelMode::RGBA8888:		return 4;
	case PixelMode::RGB888:			return 3;
	}

	return 0;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
