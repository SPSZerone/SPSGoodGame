#include "Encoding.h"
#if ( ( defined( __SPS_GG__SUPPORT__ICONV ) ) && ( __SPS_GG__SUPPORT__ICONV ) )
#include "iconv.h"
#endif // end #if ( ( defined( __SPS_GG__SUPPORT__ICONV ) ) && ( __SPS_GG__SUPPORT__ICONV ) )

__SPS_GG__NS__U_ENCODING;



int Encoding::format_to_hexdig_hexdig( const char *src_buffer, std::string &desStr )
{
	if ( src_buffer == nullptr )
	{
		return -1;
	}

	desStr.clear();

	char format_txt[ 10 ] = { 0 };
	const unsigned int nSrcLength = strlen( src_buffer );
	for ( unsigned int i = 0; i < nSrcLength; i++ )
	{
		sprintf( format_txt, "%%%X", ( (unsigned char)(src_buffer[ i ]) ) );
		desStr.append( format_txt );
	}

	return 0;
}



int Encoding::get_utf8_str_infor( const unsigned char *utf8_buffer, const unsigned long utf8_buffer_size, Utf8StrInfor *pUtf8StrInfor )
{
	if ( utf8_buffer == nullptr )
	{
		return -1;
	}
	if ( pUtf8StrInfor == nullptr )
	{
		return -2;
	}
	pUtf8StrInfor->Reset();

	unsigned long nUtf8Index = 0;

	while ( nUtf8Index < utf8_buffer_size )
	{
		if ( utf8_buffer[ nUtf8Index ] == 0 )
		{
			break;
		}
		// 1 byte >> 0x00000000 ~ 0x0000007F >> 0XXXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__1BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__1BYTE__MARK ) 
		{
			pUtf8StrInfor->nWordCountOf1Byte++;
			if ( __GG__ENCODING__IS_ESCAPE( utf8_buffer[ nUtf8Index ] ) == false )
			{
				pUtf8StrInfor->nWordRealCount++;
				pUtf8StrInfor->nWordRealCountOf1Byte++;
			}

			nUtf8Index++;
		}
		// 2 byte >> 0x00000080 ~ 0x000007FF >> 110XXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__2BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__2BYTE__MARK )
		{
			pUtf8StrInfor->nWordRealCount++;

			nUtf8Index += 2;
		}
		// 3 byte >> 0x00000800 ~ 0x0000FFFF >> 1110XXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__3BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__3BYTE__MARK )
		{
			pUtf8StrInfor->nWordRealCount++;

			nUtf8Index += 3;
		}
		// 4 byte >> 0x00010000 ~ 0x001FFFFF >> 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__4BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__4BYTE__MARK )
		{
			pUtf8StrInfor->nWordRealCount++;
			pUtf8StrInfor->isUCS2 = false;

			nUtf8Index += 4;
		}
		// 5 byte >> 0x00200000 ~ 0x03FFFFFF >> 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__5BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__5BYTE__MARK )
		{
			pUtf8StrInfor->nWordRealCount++;
			pUtf8StrInfor->isUCS2 = false;

			nUtf8Index += 5;
		}
		// 6 byte >> 0x04000000 ~ 0x7FFFFFFF >> 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__6BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__6BYTE__MARK )
		{
			pUtf8StrInfor->nWordRealCount++;
			pUtf8StrInfor->isUCS2 = false;

			nUtf8Index += 6;
		}
		else
		{
			return -10;
		}

		pUtf8StrInfor->nWordCount++;
	} // end while

	return 0;
}



int Encoding::get_real_word_index_in_utf8_str( const unsigned char *utf8_buffer, const unsigned long utf8_buffer_size,
	const unsigned long nRealWordCount, const unsigned short nRatioOfMBWord, unsigned long &nStartIndex, unsigned long &nEndIndex )
{
	nStartIndex = 0xFFFFFFFF;
	nEndIndex = 0xFFFFFFFF;

	if ( utf8_buffer == nullptr )
	{
		return -1;
	}

	if ( nRealWordCount < 1 )
	{
		return -2;
	}

	unsigned long nUtf8Index = 0;
	unsigned long nCurRealWordCountOf1B = 0;
	unsigned long nCurRealWordCountOfMB = 0;

	while ( nUtf8Index < utf8_buffer_size )
	{
		if ( utf8_buffer[ nUtf8Index ] == 0 )
		{
			break;
		}
		// 1 byte >> 0x00000000 ~ 0x0000007F >> 0XXXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__1BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__1BYTE__MARK ) 
		{
			if ( __GG__ENCODING__IS_ESCAPE( utf8_buffer[ nUtf8Index ] ) == false )
			{
				if ( nCurRealWordCountOf1B + nCurRealWordCountOfMB * nRatioOfMBWord + 1 > nRealWordCount )
				{
					break;
				}

				nCurRealWordCountOf1B++;

				nStartIndex = nUtf8Index;
				nEndIndex = nUtf8Index;
			}

			nUtf8Index++;
		}
		// 2 byte >> 0x00000080 ~ 0x000007FF >> 110XXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__2BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__2BYTE__MARK )
		{
			if ( nCurRealWordCountOf1B + nCurRealWordCountOfMB * nRatioOfMBWord + 2 > nRealWordCount )
			{
				break;
			}

			nCurRealWordCountOfMB++;

			nStartIndex = nUtf8Index;
			nEndIndex = nUtf8Index + 1;

			nUtf8Index += 2;
		}
		// 3 byte >> 0x00000800 ~ 0x0000FFFF >> 1110XXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__3BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__3BYTE__MARK )
		{
			if ( nCurRealWordCountOf1B + nCurRealWordCountOfMB * nRatioOfMBWord + 3 > nRealWordCount )
			{
				break;
			}

			nCurRealWordCountOfMB++;

			nStartIndex = nUtf8Index;
			nEndIndex = nUtf8Index + 2;

			nUtf8Index += 3;
		}
		// 4 byte >> 0x00010000 ~ 0x001FFFFF >> 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__4BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__4BYTE__MARK )
		{
			if ( nCurRealWordCountOf1B + nCurRealWordCountOfMB * nRatioOfMBWord + 4 > nRealWordCount )
			{
				break;
			}

			nCurRealWordCountOfMB++;

			nStartIndex = nUtf8Index;
			nEndIndex = nUtf8Index + 3;

			nUtf8Index += 4;
		}
		// 5 byte >> 0x00200000 ~ 0x03FFFFFF >> 111110XX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__5BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__5BYTE__MARK )
		{
			if ( nCurRealWordCountOf1B + nCurRealWordCountOfMB * nRatioOfMBWord + 5 > nRealWordCount )
			{
				break;
			}

			nCurRealWordCountOfMB++;

			nStartIndex = nUtf8Index;
			nEndIndex = nUtf8Index + 4;

			nUtf8Index += 5;
		}
		// 6 byte >> 0x04000000 ~ 0x7FFFFFFF >> 1111110X 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX 10XXXXXX
		else if ( ( utf8_buffer[ nUtf8Index ] & __GG__ENCODING__UTF8_HEAD__6BYTE__M1_X0 ) == __GG__ENCODING__UTF8_HEAD__6BYTE__MARK )
		{
			if ( nCurRealWordCountOf1B + nCurRealWordCountOfMB * nRatioOfMBWord + 6 > nRealWordCount )
			{
				break;
			}

			nCurRealWordCountOfMB++;

			nStartIndex = nUtf8Index;
			nEndIndex = nUtf8Index + 5;

			nUtf8Index += 6;
		}
		else
		{
			return -10;
		}
	} // end while

	if ( nStartIndex == 0xFFFFFFFF || nEndIndex == 0xFFFFFFFF )
	{
		return -20;
	}

	return 0;
}



#if ( ( defined( __SPS_GG__SUPPORT__ICONV ) ) && ( __SPS_GG__SUPPORT__ICONV ) )

int Encoding::iconv_encoding( const char *from_encoding, const char *to_encoding, const char *src_buffer, const unsigned long n_src_size, char *des_buffer, const unsigned long n_des_size )
{
	if ( from_encoding == nullptr )
	{
		return -1;
	}

	if ( to_encoding == nullptr )
	{
		return -2;
	}

	if ( src_buffer == nullptr )
	{
		return -3;
	}

	if ( des_buffer == nullptr )
	{
		return -4;
	}

	const char *pSrcBuffer = src_buffer;
	size_t nSrcSize = n_src_size;
	char *pDesBuffer = des_buffer;
	size_t nDesSize = n_des_size;

	memset( pDesBuffer, 0, nDesSize );

	iconv_t iconvH;
	iconvH = iconv_open( to_encoding, from_encoding );
	if ( iconvH == 0 )
	{
		return -10;
	}

	if ( -1 == iconv( iconvH, &pSrcBuffer, &nSrcSize, &pDesBuffer, &nDesSize ) )
	{
		iconv_close( iconvH );
		return -11;
	}
	
	iconv_close( iconvH );

	return 0;
}



int Encoding::iconv_encoding_gbk_to_utf8( const char *src_buffer, const unsigned long n_src_size, char *des_buffer, const unsigned long n_des_size )
{
	return iconv_encoding( "GBK", "UTF-8", src_buffer, n_src_size, des_buffer, n_des_size );
}

#endif // end #if ( ( defined( __SPS_GG__SUPPORT__ICONV ) ) && ( __SPS_GG__SUPPORT__ICONV ) )
