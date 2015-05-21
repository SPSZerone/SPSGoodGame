#include "CPUUtil.h"
__SPS_GG__NS__U_UTIL;



CPUUtil::Endian CPUUtil::check_endian()
{
	union EndianCheck
	{  
		unsigned short num;
		unsigned char chr;
	};

	EndianCheck unEndian;
	unEndian.num = 0xBB11;

	if( unEndian.chr == 0xBB )
	{
		return Endian::BIG;
	}

	return Endian::LITTLE;
}
