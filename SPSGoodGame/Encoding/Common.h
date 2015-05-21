#ifndef __SPS__GOOD_GAME__ENCODING__COMMON_H__
#define __SPS__GOOD_GAME__ENCODING__COMMON_H__

#include "SPSGoodGame/Base/Base.h"



// 是否为换行符
#define __GG__ENCODING__IS_LINE_BREAK( __UNICODE__ )          ( ( __UNICODE__ ) == '\n' || ( __UNICODE__ ) == '\r' )
// 是否为转义字符
#define __GG__ENCODING__IS_ESCAPE( __UNICODE__ )          ( ( __UNICODE__ ) <= 31 || ( __UNICODE__ ) == 127 )



// 1 byte >> 0x00000000 ~ 0x0000007F >> 0XXXXXXX
// 2 byte >> 0x00000080 ~ 0x000007FF >> 110XXXXX 10XXXXXX
// 3 byte >> 0x00000800 ~ 0x0000FFFF >> 1110XXXX 10XXXXXX 10XXXXXX
// 4 byte >> 0x00010000 ~ 0x001FFFFF >> 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
// 5 byte >> 0x00200000 ~ 0x03FFFFFF >> 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
// 6 byte >> 0x04000000 ~ 0x7FFFFFFF >> 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
// >>>>>>>>>> UNICODE range [ begin ]<<<<<<<<<<
#define __GG__ENCODING__UNICODE__1BYTE_MIN			0x00000000
#define __GG__ENCODING__UNICODE__1BYTE_MAX			0x0000007F

#define __GG__ENCODING__UNICODE__2BYTE_MIN			0x00000080
#define __GG__ENCODING__UNICODE__2BYTE_MAX			0x000007FF

#define __GG__ENCODING__UNICODE__3BYTE_MIN			0x00000800
#define __GG__ENCODING__UNICODE__3BYTE_MAX			0x0000FFFF

#define __GG__ENCODING__UNICODE__4BYTE_MIN			0x00010000
#define __GG__ENCODING__UNICODE__4BYTE_MAX			0x001FFFFF

#define __GG__ENCODING__UNICODE__5BYTE_MIN			0x00200000
#define __GG__ENCODING__UNICODE__5BYTE_MAX			0x03FFFFFF

#define __GG__ENCODING__UNICODE__6BYTE_MIN			0x04000000
#define __GG__ENCODING__UNICODE__6BYTE_MAX			0x7FFFFFFF
// >>>>>>>>>> UNICODE range [ end ]<<<<<<<<<<



/* NOTES
	MARK：UTF8字节数标记的值，如：2字节的，110XXXXX：11000000 
	M0_X1：UTF8每个字节中，M0:开始几位全为0，X1:后面的X全为1，如：110XXXXX：000_11111
	M1_X0：UTF8每个字节中，M1:开始几位全为1，X0:后面的X全为0，如：110XXXXX：111_00000
*/
#define __GG__ENCODING__UTF8_HEAD__1BYTE__MARK				0x0 // 0XXXXXXX >> 0_0000000
#define __GG__ENCODING__UTF8_HEAD__1BYTE__M0_X1				0x7F // 0XXXXXXX >> 0_1111111
#define __GG__ENCODING__UTF8_HEAD__1BYTE__M1_X0				0x80 // 0XXXXXXX >> 1_0000000

#define __GG__ENCODING__UTF8_HEAD__2BYTE__MARK				0xC0 // 110XXXXX >> 110_00000
#define __GG__ENCODING__UTF8_HEAD__2BYTE__M0_X1				0x1F // 110XXXXX >> 000_11111
#define __GG__ENCODING__UTF8_HEAD__2BYTE__M1_X0				0xE0 // 110XXXXX >> 111_00000

#define __GG__ENCODING__UTF8_HEAD__3BYTE__MARK				0xE0 // 1110XXXX >> 1110_0000
#define __GG__ENCODING__UTF8_HEAD__3BYTE__M0_X1				0x0F // 1110XXXX >> 0000_1111
#define __GG__ENCODING__UTF8_HEAD__3BYTE__M1_X0				0xF0 // 1110XXXX >> 1111_0000

#define __GG__ENCODING__UTF8_HEAD__4BYTE__MARK				0xF0 // 11110XXX >> 11110_000
#define __GG__ENCODING__UTF8_HEAD__4BYTE__M0_X1				0x07 // 11110XXX >> 00000_111
#define __GG__ENCODING__UTF8_HEAD__4BYTE__M1_X0				0xF8 // 11110XXX >> 11111_000

#define __GG__ENCODING__UTF8_HEAD__5BYTE__MARK				0xF8 // 111110XX >> 111110_00
#define __GG__ENCODING__UTF8_HEAD__5BYTE__M0_X1				0x03 // 111110XX >> 000000_11
#define __GG__ENCODING__UTF8_HEAD__5BYTE__M1_X0				0xFC // 111110XX >> 111111_00

#define __GG__ENCODING__UTF8_HEAD__6BYTE__MARK				0xFC // 1111110X >> 1111110_0
#define __GG__ENCODING__UTF8_HEAD__6BYTE__M0_X1				0x01 // 1111110X >> 0000000_1
#define __GG__ENCODING__UTF8_HEAD__6BYTE__M1_X0				0xFE // 1111110X >> 1111111_0



#define __GG__ENCODING__UTF8_TAIL__HEAD				0x80 // 10XXXXXX >> 10_000000
#define __GG__ENCODING__UTF8_TAIL__H0_X1				0x3F // 10XXXXXX >> 00_111111



__SPS_GG__NS__B_ENCODING

enum class EncodingResult
{
	OK,

	WARN_HaveNotEndSymbol,

	FAIL_UnicodeBuffer_NULL,
	FAIL_UTF8Buffer_NULL,
	
	FAIL_OutOfRangeUCS2,
	FAIL_OutOfRangeUCS4,
	
	FAIL_UnicodeTypeSizeNotEnough,
	FAIL_UnsupportUnicodeType,

	FAIL_UTF8Buffer_NotEnoughSpace_1byte,
	FAIL_UTF8Buffer_NotEnoughSpace_2bytes,
	FAIL_UTF8Buffer_NotEnoughSpace_3bytes,
	FAIL_UTF8Buffer_NotEnoughSpace_4bytes,
	FAIL_UTF8Buffer_NotEnoughSpace_5bytes,
	FAIL_UTF8Buffer_NotEnoughSpace_6bytes,

	FAIL_UnicodeBuffer_NotEnoughSpace_1byte,
	FAIL_UnicodeBuffer_NotEnoughSpace_2bytes,
	FAIL_UnicodeBuffer_NotEnoughSpace_3bytes,
	FAIL_UnicodeBuffer_NotEnoughSpace_4bytes,
	FAIL_UnicodeBuffer_NotEnoughSpace_5bytes,
	FAIL_UnicodeBuffer_NotEnoughSpace_6bytes,

}; // end enum class EncodingResult


class Utf8StrInfor
{
public:
	// 总字数（包括转义字符）
	unsigned long nWordCount;
	// 总字数（包括转义字符）（仅1字节表示的）
	unsigned long nWordCountOf1Byte;

	// 实际可显示的字数
	unsigned long nWordRealCount;
	// 实际可显示的字数（仅1字节表示的）
	unsigned long nWordRealCountOf1Byte;

	bool isUCS2;


	Utf8StrInfor()
	{
		Reset();
	}

	void Reset()
	{
		nWordCount = 0;
		nWordCountOf1Byte = 0;

		nWordRealCount = 0;
		nWordRealCountOf1Byte = 0;

		isUCS2 = true;
	}
}; // end class Utf8StrInfor

__SPS_GG__NS__END // end __SPS_GG__NS__B_ENCODING


#endif // #ifndef __SPS__GOOD_GAME__ENCODING__COMMON_H__
