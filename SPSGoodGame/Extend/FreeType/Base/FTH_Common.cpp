#include "SPSGoodGame/Extend/FreeType/Base/FTH_Common.h"
#if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/FreeType/Util/FTH_Util.h"
__SPS_GG__NS__U_EXTEND_FREETYPE;



// ========== FTH_Color [ begin ] ==========
FTH_Color::FTH_Color()
	: red( 255 ), green( 255 ), blue( 255 ) {}

FTH_Color::FTH_Color( FTH_UByte r, FTH_UByte g, FTH_UByte b )
	: red( r ), green( g ), blue( b ) {}

bool FTH_Color::operator == ( const FTH_Color& right ) const
{
	return ( red == right.red && green == right.green && blue == right.blue );
}

bool FTH_Color::operator != ( const FTH_Color& right ) const
{
	return !( *this == right );
}

bool FTH_Color::Equals( const FTH_Color& other ) const
{
	return ( *this == other );
}
// ========== FTH_Color [ end ] ==========


	
// ========== FTH_TextDefine [ begin ] ==========
FTH_TextDefine::FTH_TextDefine()
{
	text_buffer_ucs4 = nullptr;
	text_buffer_ucs2 = nullptr;
	text_buffer_size = 0;

	ePixelMode = PixelMode::RGB888;
	eTextAlignHorizontal = TextAlignHorizontal::LEFT;

	nFontSize = 32;
	textColor.red = 255;
	textColor.green = 255;
	textColor.blue = 255;
	nTextAlpha = 255;

	nLineGap = 0;
	nLineMaxWidth = 0;
	nLineMaxRows = 0;

	bgColor.red = 0;
	bgColor.green = 0;
	bgColor.blue = 0;
	nBGAlpha = 0;

	eIndentationType = IndentationType::WORD;
	nIndentationValue = 0;
}

FTH_TextDefine::~FTH_TextDefine() {}

int FTH_TextDefine::GetWordCount( unsigned long &_word_count, unsigned long &_word_real_count )
{
	_word_count = 0;
	_word_real_count = 0;

	if ( text_buffer_ucs4 )
	{
		for( unsigned long i = 0; i < text_buffer_size; i++ )
		{
			if ( text_buffer_ucs4[ i ] == 0x0 )
			{
				break;
			}

			_word_count++;

			if ( __GG__FTH__IS_ESCAPE( text_buffer_ucs4[ i ] ) )
			{
				continue;
			}

			_word_real_count++;
		}

		return 0;
	}
	else if ( text_buffer_ucs2 )
	{
		for( unsigned long i = 0; i < text_buffer_size; i++ )
		{
			if ( text_buffer_ucs2[ i ] == 0x0 )
			{
				break;
			}

			_word_count++;

			if ( __GG__FTH__IS_ESCAPE( text_buffer_ucs2[ i ] ) )
			{
				continue;
			}

			_word_real_count++;
		}

		return 0;
	}

	return -1;
}

int FTH_TextDefine::GetLineBreakCount( unsigned long &_line_break_count )
{
	_line_break_count = 0;

	if ( text_buffer_ucs4 )
	{
		for( unsigned long i = 0; i < text_buffer_size; i++ )
		{
			if ( text_buffer_ucs4[ i ] == 0x0 )
			{
				break;
			}
			
			if ( __GG__FTH__IS_LINE_BREAK( text_buffer_ucs4[ i ] ) )
			{
				_line_break_count++;
			}
		}

		return 0;
	}
	else if ( text_buffer_ucs2 )
	{
		for( unsigned long i = 0; i < text_buffer_size; i++ )
		{
			if ( text_buffer_ucs2[ i ] == 0x0 )
			{
				break;
			}

			if ( __GG__FTH__IS_LINE_BREAK( text_buffer_ucs2[ i ] ) )
			{
				_line_break_count++;
			}
		}

		return 0;
	}

	return -1;
}
// ========== FTH_TextDefine [ end ] ==========



// ========== FTH_StrokeDefine [ begin ] ==========
FTH_StrokeDefine::FTH_StrokeDefine()
{
	nStrokeSize = 2;
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	nAlpha = 255;
}

FTH_StrokeDefine::~FTH_StrokeDefine() {}
// ========== FTH_StrokeDefine [ end ] ==========



// ========== FTH_UnderLineDefine [ begin ] ==========
FTH_UnderLineDefine::FTH_UnderLineDefine()
{
	nThick = 2;
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	nAlpha = 255;
}

FTH_UnderLineDefine::~FTH_UnderLineDefine()
{

}
// ========== FTH_UnderLineDefine [ end ] ==========



// ========== FTH_DeleteLineDefine [ begin ] ==========
FTH_DeleteLineDefine::FTH_DeleteLineDefine()
{
	nThick = 2;
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	nAlpha = 255;
	fAnchor = 0.0f;
}

FTH_DeleteLineDefine::~FTH_DeleteLineDefine()
{

}

int FTH_DeleteLineDefine::FixAnchor()
{
	if ( fAnchor < -1.0f )
	{
		fAnchor = -1.0f;
		return -1;
	}

	if ( fAnchor > 1.0f )
	{
		fAnchor = 1.0f;
		return 1;
	}

	return 0;
}
// ========== FTH_DeleteLineDefine [ end ] ==========



// ========== FTH_TextTexture [ begin ] ==========
FTH_TextTexture::FTH_TextTexture()
{
	Reset();
}

FTH_TextTexture::~FTH_TextTexture() {}

void FTH_TextTexture::Reset()
{
	buffer = nullptr;
	nBufferSize = 0;
	nBufferPixelWidth = 0;
	nBufferPixelHeight = 0;
	nByteCountPerPixel = 0;
	nByteCountPerLine = 0;


	nRealPixelWidth = 0;
	nRealPixelHeight = 0;
	nEstimatePixelWidth = 0;
	nEstimatePixelHeight = 0;


	nWordCount = 0;
	nWordRealCount = 0;
	nWordPixelAscenderHeight = 0;
	nWordPixelDescenderHeight = 0;
	nWordPixelHeight = 0;
	nWordMaxAdvance = 0;


	nTextEstimatePixelTotalWidth = 0;
	nTextRowCount = 0;


	nIndentationStartPos = 0;


	nTextEndPosX = 0;
	nTextEndPosY = 0;


	nTextBlankHalfWidth = 0;
}



int FTH_TextTexture::DestroyBuffer()
{
	if ( buffer )
	{
		delete [] buffer;
		buffer = nullptr;
		return 0;
	}

	return 1;
}



int FTH_TextTexture::FixBlankWidth()
{
	if ( nTextBlankHalfWidth > nWordMaxAdvance )
	{
		nTextBlankHalfWidth = ( nWordMaxAdvance >> 1 );
	}

	return 0;
}



int FTH_TextTexture::PreCalculateTextPixelTotalWidth( FT_Face _ftFace, FTH_TextDefine *_pTextDefine, FTH_StrokeDefine *_pStrokeDefine )
{
	const unsigned int nStrokeTotalSize = _pStrokeDefine ? ( _pStrokeDefine->nStrokeSize << 1 ) : 0;
	
	nTextEstimatePixelTotalWidth = 0;
	int bitmap_left = 0;

	for ( unsigned long nTextIndex = 0; nTextIndex < nWordCount; nTextIndex++ )
	{
		// 忽略转义字符
		if ( ( _pTextDefine->text_buffer_ucs4 && __GG__FTH__IS_ESCAPE( _pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
				|| ( _pTextDefine->text_buffer_ucs2 && __GG__FTH__IS_ESCAPE( _pTextDefine->text_buffer_ucs2[ nTextIndex ] ) ) )
		{
			continue;
		}


		if ( _pTextDefine->text_buffer_ucs4 )
		{
			FT_Error ftError = FT_Load_Char( _ftFace, _pTextDefine->text_buffer_ucs4[ nTextIndex ], FT_LOAD_RENDER );
			if ( ftError )
			{
				continue;
			}
		}
		else if ( _pTextDefine->text_buffer_ucs2 )
		{
			FT_Error ftError = FT_Load_Char( _ftFace, _pTextDefine->text_buffer_ucs2[ nTextIndex ], FT_LOAD_RENDER );
			if ( ftError )
			{
				continue;
			}
		}

		
		const signed long nAdvanceX = __GG__FTH__NUM_FT_TO_NORMAL( _ftFace->glyph->advance.x );
		nTextEstimatePixelTotalWidth += nAdvanceX;
		nTextEstimatePixelTotalWidth += nStrokeTotalSize;


		bitmap_left = _ftFace->glyph->bitmap_left;
	}

	
	nTextEstimatePixelTotalWidth += bitmap_left;


	return 0;
}



int FTH_TextTexture::Init( FT_Face _ftFace, FTH_TextDefine *_pTextDefine, FTH_StrokeDefine *_pStrokeDefine, FTH_UnderLineDefine *_pUnderLineDefine )
{
	DestroyBuffer();
	Reset();


	if ( _ftFace == nullptr )
	{
		return -1;
	}
	if ( _pTextDefine == nullptr )
	{
		return -2;
	}


	const int _tmp_nResult_GWC = _pTextDefine->GetWordCount( nWordCount, nWordRealCount );
	if ( _tmp_nResult_GWC != 0 || nWordCount <= 0 || nWordRealCount <= 0 )
	{
		return -10;
	}

	
	nWordPixelAscenderHeight = __GG__FTH__NUM_FT_TO_NORMAL( _ftFace->size->metrics.ascender );
	nWordPixelDescenderHeight = -__GG__FTH__NUM_FT_TO_NORMAL( _ftFace->size->metrics.descender );


	const unsigned int nStrokeTotalSize = _pStrokeDefine ? ( _pStrokeDefine->nStrokeSize << 1 ) : 0;


	nWordPixelHeight = __GG__FTH__NUM_FT_TO_NORMAL( _ftFace->size->metrics.ascender - _ftFace->size->metrics.descender )
		+ nStrokeTotalSize + ( _pUnderLineDefine ? _pUnderLineDefine->nThick : 0 );
	nWordMaxAdvance = __GG__FTH__NUM_FT_TO_NORMAL( _ftFace->size->metrics.max_advance ) + nStrokeTotalSize;


	if ( nWordMaxAdvance <= 0 )
	{
		return -11;
	}


	//计算nTextEstimatePixelTotalWidth
	PreCalculateTextPixelTotalWidth( _ftFace, _pTextDefine, _pStrokeDefine );
	

	// 首行缩进
	if ( _pTextDefine->eIndentationType == IndentationType::PIXEL )
	{
		nIndentationStartPos = _pTextDefine->nIndentationValue;
	}
	else if ( _pTextDefine->eIndentationType == IndentationType::WORD )
	{
		nIndentationStartPos = _pTextDefine->nIndentationValue * nWordMaxAdvance;
	}
	else
	{
		nIndentationStartPos = 0;
	}


	// 至少保证缩进行显示1个字
	if ( nIndentationStartPos + nWordMaxAdvance > nTextEstimatePixelTotalWidth )
	{
		nIndentationStartPos = 0;
	}
	nTextEstimatePixelTotalWidth += nIndentationStartPos;

	
	if ( _pTextDefine->nLineMaxWidth == 0 )
	{
		nEstimatePixelWidth = nTextEstimatePixelTotalWidth;
		nBufferPixelWidth = FTH_Util::next_power_of_2( nEstimatePixelWidth );
		nTextRowCount = 1;
	}
	else
	{
		nEstimatePixelWidth = __GG__FTH__MIN( _pTextDefine->nLineMaxWidth, nTextEstimatePixelTotalWidth );
		nBufferPixelWidth = FTH_Util::next_power_of_2( nEstimatePixelWidth );

		const unsigned long _tmp_nMinWordCountPerLine = _pTextDefine->nLineMaxWidth / nWordMaxAdvance;
		if ( _tmp_nMinWordCountPerLine <= 0 )
		{
			return -31;
		}
		const unsigned long _tmp_nTextEstimateRowCount = ( nWordRealCount - 1 ) / _tmp_nMinWordCountPerLine + 1;

		nTextRowCount = _pTextDefine->nLineMaxRows == 0 ? _tmp_nTextEstimateRowCount : __GG__FTH__MIN( _tmp_nTextEstimateRowCount, _pTextDefine->nLineMaxRows );
	}
	if ( nTextRowCount <= 0 )
	{
		return -40;
	}


	unsigned long _tmp_nLineBreakCount = 0;
	const int _tmp_nResult_GLBC = _pTextDefine->GetLineBreakCount( _tmp_nLineBreakCount );
	if ( _tmp_nResult_GLBC == 0 )
	{
		if ( _pTextDefine->nLineMaxWidth == 0 || _pTextDefine->nLineMaxRows == 0 )
		{
			nTextRowCount += _tmp_nLineBreakCount;
		}
		else if ( _pTextDefine->nLineMaxRows > 0 )
		{
			nTextRowCount += _tmp_nLineBreakCount;
			nTextRowCount = __GG__FTH__MIN( nTextRowCount, _pTextDefine->nLineMaxRows );
		}
	}


	if ( nTextRowCount == 1 )
	{
		nBufferPixelHeight = FTH_Util::next_power_of_2( nWordPixelHeight );
	}
	else
	{
		nBufferPixelHeight = FTH_Util::next_power_of_2( nTextRowCount * ( nWordPixelHeight + _pTextDefine->nLineGap ) - _pTextDefine->nLineGap );
	}


	// 一个像素的字节数
	nByteCountPerPixel = FTH_Util::get_pixed_mode_need_byte_count( _pTextDefine->ePixelMode );	
	if ( nByteCountPerPixel <= 0 )
	{
		return -100;
	}


	nByteCountPerLine = nBufferPixelWidth * nByteCountPerPixel;
	nBufferSize = nByteCountPerLine * nBufferPixelHeight;
	buffer = new unsigned char[ nBufferSize ];
#if ( defined( __GG__FTH__MAKE_DEBUG ) && ( __GG__FTH__MAKE_DEBUG ) )
	memset( buffer, 255, nBufferSize );
#else
	memset( buffer, 0, nBufferSize );
#endif


	return 0;
}
// ========== FTH_TextTexture [ end ] ==========

#endif // #if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
