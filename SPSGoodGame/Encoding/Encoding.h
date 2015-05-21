#ifndef __SPS__GOOD_GAME__ENCODING__ENCODING_H__
#define __SPS__GOOD_GAME__ENCODING__ENCODING_H__

#include "Common.h"
#include "SPSGoodGame/Base/Config.h"
#include <string>
#include <cstring>



__SPS_GG__NS__B_ENCODING

class Encoding
{
public:
	// 转换到 %HH 格式
	static int format_to_hexdig_hexdig( const char *src_buffer, std::string &desStr );


	/* utf8字符串中字的个数
		return 0：成功
	*/
	static int get_utf8_str_infor( const unsigned char *utf8_buffer, const unsigned long utf8_buffer_size, Utf8StrInfor *pUtf8StrInfor );
	

	/* UTF8字符串中，获取第X个字的索引（可显示的字，即不包括转义字符）
		X：nRealWordCount：从1开始
		return 0：成功
	*/
	static int get_real_word_index_in_utf8_str( const unsigned char *utf8_buffer, const unsigned long utf8_buffer_size,
		const unsigned long nRealWordCount, const unsigned short nRatioOfMBWord, unsigned long &nStartIndex, unsigned long &nEndIndex );


	// ========== SUPPORT_ICON [ begin ]==========
#if ( ( defined( __SPS_GG__SUPPORT__ICONV ) ) && ( __SPS_GG__SUPPORT__ICONV ) )
	static int iconv_encoding( const char *from_encoding, const char *to_encoding, const char *src_buffer, const unsigned long n_src_size, char *des_buffer, const unsigned long n_des_size );
	static int iconv_encoding_gbk_to_utf8( const char *src_buffer, const unsigned long n_src_size, char *des_buffer, const unsigned long n_des_size );
#endif // end #if ( ( defined( __SPS_GG__SUPPORT__ICONV ) ) && ( __SPS_GG__SUPPORT__ICONV ) )
	// ========== SUPPORT_ICON [ end ]==========


	// ============================================================
	// SEE enum class EncodingResult
	template<typename UT>
	static EncodingResult unicode_to_utf8( const UT *unicode_buffer, const unsigned long unicode_buffer_size, char *utf8_buffer, const unsigned long utf8_buffer_size )
	{
		return unicode_to_utf8( unicode_buffer, unicode_buffer_size, ( unsigned char * )utf8_buffer, utf8_buffer_size );
	}
	template<typename UT>
	static EncodingResult unicode_to_utf8( const UT *unicode_buffer, const unsigned long unicode_buffer_size, unsigned char *utf8_buffer, const unsigned long utf8_buffer_size )
	{
		if( unicode_buffer == nullptr )
		{
			return EncodingResult::FAIL_UnicodeBuffer_NULL;
		}

		if( utf8_buffer == nullptr )
		{
			return EncodingResult::FAIL_UTF8Buffer_NULL;
		}

		const size_t nUnicodeTypeSize = sizeof( UT );
		if ( nUnicodeTypeSize < 2 )
		{
			return EncodingResult::FAIL_UnicodeTypeSizeNotEnough;
		}

		if ( nUnicodeTypeSize % 2 != 0 )
		{
			return EncodingResult::FAIL_UnsupportUnicodeType;
		}

		unsigned long unicode_word_count = 0;
		for( unsigned long i = 0; i < unicode_buffer_size; i++ )
		{
			if ( unicode_buffer[ i ] == 0x0 )
			{
				break;
			}
			unicode_word_count++;
		}

		memset( utf8_buffer, 0, utf8_buffer_size );

		unsigned long nUtf8Index = 0;

		for( unsigned long i = 0; i < unicode_word_count; i++ )
		{
			// 1 byte >> 0x00000000 ~ 0x0000007F >> 0XXXXXXX
			if( unicode_buffer[ i ] <= __GG__ENCODING__UNICODE__1BYTE_MAX )
			{
				if( nUtf8Index >= utf8_buffer_size )
				{
					return EncodingResult::FAIL_UTF8Buffer_NotEnoughSpace_1byte;
				}

				utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_HEAD__1BYTE__M0_X1 & unicode_buffer[ i ];

				continue;
			}

			// 2 byte >> 0x00000080 ~ 0x000007FF >> 110XXXXX 10XXXXXX
			if( unicode_buffer[ i ] <= __GG__ENCODING__UNICODE__2BYTE_MAX )
			{
				if( nUtf8Index + 1 >= utf8_buffer_size )
				{
					return EncodingResult::FAIL_UTF8Buffer_NotEnoughSpace_2bytes;
				}

				utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_HEAD__2BYTE__MARK | ( __GG__ENCODING__UTF8_HEAD__2BYTE__M0_X1 & ( unicode_buffer[ i ] >> 6 ) );
				utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & unicode_buffer[ i ] );

				continue;
			}

			// 3 byte >> 0x00000800 ~ 0x0000FFFF >> 1110XXXX 10XXXXXX 10XXXXXX
			if( unicode_buffer[ i ] <= __GG__ENCODING__UNICODE__3BYTE_MAX )
			{
				if( nUtf8Index + 2 >= utf8_buffer_size )
				{
					return EncodingResult::FAIL_UTF8Buffer_NotEnoughSpace_3bytes;
				}

				utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_HEAD__3BYTE__MARK | ( __GG__ENCODING__UTF8_HEAD__3BYTE__M0_X1 & ( unicode_buffer[ i ] >> 12 ) );
				utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 6 ) );
				utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & unicode_buffer[ i ] );

				continue;
			}

			if ( nUnicodeTypeSize >= 4 )
			{
				// 4 byte >> 0x00010000 ~ 0x001FFFFF >> 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
				if( unicode_buffer[ i ] <= __GG__ENCODING__UNICODE__4BYTE_MAX )
				{
					if( nUtf8Index + 3 >= utf8_buffer_size )
					{
						return EncodingResult::FAIL_UTF8Buffer_NotEnoughSpace_4bytes;
					}

					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_HEAD__4BYTE__MARK | ( __GG__ENCODING__UTF8_HEAD__4BYTE__M0_X1 & ( unicode_buffer[ i ] >> 18 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 12 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 6 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & unicode_buffer[ i ] );

					continue;
				}

				// 5 byte >> 0x00200000 ~ 0x03FFFFFF >> 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
				if( unicode_buffer[ i ] <= __GG__ENCODING__UNICODE__5BYTE_MAX )
				{
					if( nUtf8Index + 4 >= utf8_buffer_size )
					{
						return EncodingResult::FAIL_UTF8Buffer_NotEnoughSpace_5bytes;
					}

					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_HEAD__5BYTE__MARK | ( __GG__ENCODING__UTF8_HEAD__5BYTE__M0_X1 & ( unicode_buffer[ i ] >> 24 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 18 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 12 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 6 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & unicode_buffer[ i ] );

					continue;
				}

				// 6 byte >> 0x04000000 ~ 0x7FFFFFFF >> 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
				if( unicode_buffer[ i ] <= __GG__ENCODING__UNICODE__6BYTE_MAX )
				{
					if( nUtf8Index + 5 >= utf8_buffer_size )
					{
						return EncodingResult::FAIL_UTF8Buffer_NotEnoughSpace_6bytes;
					}

					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_HEAD__6BYTE__MARK | ( __GG__ENCODING__UTF8_HEAD__6BYTE__M0_X1 & ( unicode_buffer[ i ] >> 30 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 24 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 18 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 12 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & ( unicode_buffer[ i ] >> 6 ) );
					utf8_buffer[ nUtf8Index++ ] = __GG__ENCODING__UTF8_TAIL__HEAD | ( __GG__ENCODING__UTF8_TAIL__H0_X1 & unicode_buffer[ i ] );

					continue;
				}

				return EncodingResult::FAIL_OutOfRangeUCS4;
			}
			else
			{
				return EncodingResult::FAIL_OutOfRangeUCS2;
			}
		} // end for

		if( nUtf8Index >= utf8_buffer_size )
		{
			return EncodingResult::WARN_HaveNotEndSymbol;
		}

		return EncodingResult::OK;
	} // end static EncodingResult unicode_to_utf8


	template<typename UT>
	static EncodingResult utf8_to_unicode( const char *utf8_buffer, const unsigned long utf8_buffer_size, UT *unicode_buffer, const unsigned long unicode_buffer_size )
	{
		return utf8_to_unicode( ( unsigned char * )utf8_buffer, utf8_buffer_size, unicode_buffer, unicode_buffer_size );
	}
	// SEE enum class EncodingResult
	template<typename UT>
	static EncodingResult utf8_to_unicode( const unsigned char *utf8_buffer, const unsigned long utf8_buffer_size, UT *unicode_buffer, const unsigned long unicode_buffer_size )
	{
		if( utf8_buffer == nullptr )
		{
			return EncodingResult::FAIL_UTF8Buffer_NULL;
		}

		if( unicode_buffer == nullptr )
		{
			return EncodingResult::FAIL_UnicodeBuffer_NULL;
		}

		const size_t nUnicodeTypeSize = sizeof( UT );
		if ( nUnicodeTypeSize < 2 )
		{
			return EncodingResult::FAIL_UnicodeTypeSizeNotEnough;
		}

		if ( nUnicodeTypeSize % 2 != 0 )
		{
			return EncodingResult::FAIL_UnsupportUnicodeType;
		}

		unsigned long utf8_buffer_length = 0;
		for( unsigned long i = 0; i < utf8_buffer_size; i++ )
		{
			if ( utf8_buffer[ i ] == 0x0 )
			{
				break;
			}
			utf8_buffer_length++;
		}

		memset( unicode_buffer, 0, unicode_buffer_size * nUnicodeTypeSize );

		unsigned long nUtf8Index = 0;
		unsigned long nUnicodeIndex = 0;

		while ( nUtf8Index < utf8_buffer_length )
		{
			if( nUnicodeIndex >= unicode_buffer_size )
			{
				return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_1byte;
			}

			// 1 byte >> 0x00000000 ~ 0x0000007F >> 0XXXXXXX
			if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__1BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__1BYTE__MARK )
			{
				if ( nUtf8Index >= utf8_buffer_length )
				{
					return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_1byte;
				}

				unicode_buffer[ nUnicodeIndex ] = __GG__ENCODING__UTF8_HEAD__1BYTE__M0_X1 & utf8_buffer[ nUtf8Index++ ];
			} 
			// 2 byte >> 0x00000080 ~ 0x000007FF >> 110XXXXX 10XXXXXX
			else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__2BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__2BYTE__MARK )
			{
				if ( nUtf8Index + 1 >= utf8_buffer_length )
				{
					return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_2bytes;
				}

				unicode_buffer[ nUnicodeIndex ] = ( ( __GG__ENCODING__UTF8_HEAD__2BYTE__M0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 6 );
				unicode_buffer[ nUnicodeIndex ] |= ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] );
			}
			// 3 byte >> 0x00000800 ~ 0x0000FFFF >> 1110XXXX 10XXXXXX 10XXXXXX
			else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__3BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__3BYTE__MARK )
			{
				if ( nUtf8Index + 2 >= utf8_buffer_length )
				{
					return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_3bytes;
				}

				unicode_buffer[ nUnicodeIndex ] = ( ( __GG__ENCODING__UTF8_HEAD__3BYTE__M0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 12 );
				unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 6 );
				unicode_buffer[ nUnicodeIndex ] |= ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] );
			}
			else if ( nUnicodeTypeSize >= 4 )
			{
				// 4 byte >> 0x00010000 ~ 0x001FFFFF >> 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
				if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__4BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__4BYTE__MARK )
				{
					if ( nUtf8Index + 3 >= utf8_buffer_length )
					{
						return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_4bytes;
					}

					unicode_buffer[ nUnicodeIndex ] = ( ( __GG__ENCODING__UTF8_HEAD__4BYTE__M0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 18 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 12 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 6 );
					unicode_buffer[ nUnicodeIndex ] |= ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] );
				}
				// 5 byte >> 0x00200000 ~ 0x03FFFFFF >> 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
				else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__5BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__5BYTE__MARK )
				{
					if ( nUtf8Index + 4 >= utf8_buffer_length )
					{
						return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_5bytes;
					}

					unicode_buffer[ nUnicodeIndex ] = ( ( __GG__ENCODING__UTF8_HEAD__5BYTE__M0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 24 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 18 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 12 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 6 );
					unicode_buffer[ nUnicodeIndex ] |= ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] );
				}
				// 6 byte >> 0x04000000 ~ 0x7FFFFFFF >> 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
				else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__6BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__6BYTE__MARK )
				{
					if ( nUtf8Index + 5 >= utf8_buffer_length )
					{
						return EncodingResult::FAIL_UnicodeBuffer_NotEnoughSpace_6bytes;
					}

					unicode_buffer[ nUnicodeIndex ] = ( ( __GG__ENCODING__UTF8_HEAD__6BYTE__M0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 30 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 24 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 18 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 12 );
					unicode_buffer[ nUnicodeIndex ] |= ( ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] ) << 6 );
					unicode_buffer[ nUnicodeIndex ] |= ( __GG__ENCODING__UTF8_TAIL__H0_X1 & utf8_buffer[ nUtf8Index++ ] );
				}
				else
				{
					return EncodingResult::FAIL_OutOfRangeUCS4;
				}
			}
			else
			{
				return EncodingResult::FAIL_OutOfRangeUCS2;
			}

			nUnicodeIndex++;
		} // end while

		if ( nUnicodeIndex >= unicode_buffer_size )
		{
			return EncodingResult::WARN_HaveNotEndSymbol;
		}

		return EncodingResult::OK;
	} // end static EncodingResult utf8_to_unicode


	// unicode 转 utf8时，最小char size
	template<typename UT>
	static int get_min_size_of_utf8_buffer_from_unicode( const UT *unicode_buffer, const unsigned long unicode_buffer_size, unsigned long &utf8_buffer_size )
	{
		utf8_buffer_size = 0;

		if ( unicode_buffer == nullptr )
		{
			return -1;
		}

		const size_t nUnicodeTypeSize = sizeof( UT );
		if ( nUnicodeTypeSize < 2 )
		{
			return -2;
		}

		if ( nUnicodeTypeSize % 2 != 0 )
		{
			return -3;
		}

		unsigned long nUnicodeIndex = 0;

		while( nUnicodeIndex < unicode_buffer_size )
		{
			if ( unicode_buffer[ nUnicodeIndex ] == 0 )
			{
				break;
			}
			// 1 byte >> 0x00000000 ~ 0x0000007F >> 0XXXXXXX
			else if( unicode_buffer[ nUnicodeIndex ] <= __GG__ENCODING__UNICODE__1BYTE_MAX )
			{
				utf8_buffer_size++;
			}
			// 2 byte >> 0x00000080 ~ 0x000007FF >> 110XXXXX 10XXXXXX
			else if( unicode_buffer[ nUnicodeIndex ] <= __GG__ENCODING__UNICODE__2BYTE_MAX )
			{
				utf8_buffer_size += 2;
			}
			// 3 byte >> 0x00000800 ~ 0x0000FFFF >> 1110XXXX 10XXXXXX 10XXXXXX
			else if( unicode_buffer[ nUnicodeIndex ] <= __GG__ENCODING__UNICODE__3BYTE_MAX )
			{
				utf8_buffer_size += 3;
			}
			else if ( nUnicodeTypeSize >= 4 )
			{
				// 4 byte >> 0x00010000 ~ 0x001FFFFF >> 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
				if( unicode_buffer[ nUnicodeIndex ] <= __GG__ENCODING__UNICODE__4BYTE_MAX )
				{
					utf8_buffer_size += 4;
				}
				// 5 byte >> 0x00200000 ~ 0x03FFFFFF >> 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
				else if( unicode_buffer[ nUnicodeIndex ] <= __GG__ENCODING__UNICODE__5BYTE_MAX )
				{
					utf8_buffer_size += 5;
				}
				// 6 byte >> 0x04000000 ~ 0x7FFFFFFF >> 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
				else if( unicode_buffer[ nUnicodeIndex ] <= __GG__ENCODING__UNICODE__6BYTE_MAX )
				{
					utf8_buffer_size += 6;
				}
				else
				{
					return -10;
				}
			}
			else
			{
				return -11;
			}

			nUnicodeIndex++;
		}

		utf8_buffer_size++;

		return 0;
	} // end static int get_min_size_of_utf8_buffer_from_unicode


}; // end class Encoding

__SPS_GG__NS__END // end __SPS_GG__NS__B_ENCODING



#endif // #ifndef __SPS__GOOD_GAME__ENCODING__ENCODING_H__
