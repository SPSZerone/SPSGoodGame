#include "FTH_Maker.h"
#if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/FreeType/Util/FTH_Util.h"
__SPS_GG__NS__U_EXTEND_FREETYPE;



FT_Library FTH_Maker::_gg_s_ftLibrary = nullptr;



int FTH_Maker::destroy_ft_library()
{
	if ( _gg_s_ftLibrary )
	{
		FT_Done_FreeType( _gg_s_ftLibrary );
		_gg_s_ftLibrary = nullptr;
		return 0;
	}

	return 1;
}



FTH_Maker::FTH_Maker()
{
	_gg_ftFace = nullptr;
	_gg_ftStroker = nullptr;
}



FTH_Maker::~FTH_Maker()
{
	if ( _gg_ftStroker )
	{
		FT_Stroker_Done( _gg_ftStroker );
		_gg_ftStroker = nullptr;
	}

	if ( _gg_ftFace )
	{
		FT_Done_Face( _gg_ftFace );
		_gg_ftFace = nullptr;
	}
}



int FTH_Maker::Init_FT_Library()
{
	if ( _gg_s_ftLibrary )
	{
		return 1;
	}
	
	FT_Error ftError = FT_Init_FreeType( &_gg_s_ftLibrary );
	if ( ftError )
	{
		_gg_s_ftLibrary = nullptr;
		return -1;
	}

	return 0;
}


FT_Library FTH_Maker::Get_FT_Library()
{
	Init_FT_Library();
	return _gg_s_ftLibrary;
}



int FTH_Maker::Destroy_FT_Face()
{
	if ( _gg_ftFace == nullptr )
	{
		return 1;
	}

	FT_Done_Face( _gg_ftFace );
	_gg_ftFace = nullptr;

	return 0;
}



int FTH_Maker::New_FT_Face_FromFile( const char *fontFile )
{
	if ( fontFile == nullptr )
	{
		return -1;
	}
	
	if ( Get_FT_Library() == nullptr )
	{
		return -2;
	}
	
	Destroy_FT_Face();

	FT_Error ftError = FT_New_Face( Get_FT_Library(), fontFile, 0, &_gg_ftFace );
	if ( ftError )
	{
		_gg_ftFace = nullptr;
		return -3;
	}
	
	ftError = FT_Select_Charmap( _gg_ftFace, FT_ENCODING_UNICODE );
	if ( ftError )
	{
		Destroy_FT_Face();
		return -4;
	}

	return 0;
}



int FTH_Maker::New_FT_Face_FromMemory( const unsigned char *fontBuffer, const unsigned long &nFontBufferSize )
{
	if ( fontBuffer == nullptr )
	{
		return -1;
	}

	if ( Get_FT_Library() == nullptr )
	{
		return -2;
	}

	Destroy_FT_Face();

	FT_Error ftError = FT_New_Memory_Face( Get_FT_Library(), fontBuffer, nFontBufferSize, 0, &_gg_ftFace );
	if ( ftError )
	{
		_gg_ftFace = nullptr;
		return -3;
	}

	ftError = FT_Select_Charmap( _gg_ftFace, FT_ENCODING_UNICODE );
	if ( ftError )
	{
		Destroy_FT_Face();
		return -4;
	}

	return 0;
}



int FTH_Maker::New_FT_Stroker()
{
	if ( Get_FT_Library() == nullptr )
	{
		return -1;
	}

	if ( _gg_ftStroker )
	{
		return 1;
	}	

	FT_Error ftError = FT_Stroker_New( Get_FT_Library(), &_gg_ftStroker );
	if ( ftError )
	{
		_gg_ftStroker = nullptr;
		return -2;
	}

	return 0;
}



int FTH_Maker::CreateTextureBuffer( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FTH_UnderLineDefine *pUnderLineDefine, FTH_DeleteLineDefine *pDeleteLineDefine )
{
	if ( Get_FT_Library() == nullptr )
	{
		return -1;
	}


	if ( _gg_ftFace == nullptr )
	{
		return -2;
	}


	if ( pTextTexture == nullptr )
	{
		return -10;
	}


	if ( pTextDefine == nullptr )
	{
		return -20;
	}


	if ( pTextDefine->text_buffer_ucs4 == nullptr && pTextDefine->text_buffer_ucs2 == nullptr )
	{
		return -21;
	}


	//FT_Error ftError = FT_Set_Char_Size( _gg_ftFace, FTH_NUM_NORMAL_TO_FT( pTextDefine->nFontSize ), 0, 96, 0 );
	FT_Error ftError = FT_Set_Pixel_Sizes( _gg_ftFace, pTextDefine->nFontSize, 0 );
	if ( ftError )
	{
		return -100;
	}


	const int nResult = pTextTexture->Init( _gg_ftFace, pTextDefine, nullptr, pUnderLineDefine );
	if ( nResult != 0 )
	{
		return -101;
	}


#if ( defined( __GG__FTH__MAKER_USE_TRANSFORM ) && ( __GG__FTH__MAKER_USE_TRANSFORM ) )

	//const double			angle = ( 0.0 / 360 ) * 3.14159 * 2;
	FT_Matrix				ftMatrix;
	FT_Vector				ftVectorPen;
	
	
	ftMatrix.xx = 0x10000L;
	ftMatrix.xy = 0;
	ftMatrix.yx = 0;
	ftMatrix.yy = 0x10000L;
	/*
	ftMatrix.xx = ( FT_Fixed )( cos( angle ) * 0x10000L );
	ftMatrix.xy = ( FT_Fixed )( -sin( angle ) * 0x10000L );
	ftMatrix.yx = ( FT_Fixed )( sin( angle ) * 0x10000L );
	ftMatrix.yy = ( FT_Fixed )( cos( angle ) * 0x10000L );*/

	ftVectorPen.x = 0;
	ftVectorPen.y = 0;

#else
	
	unsigned long nBufferAdvanceX = 0;

#endif


	unsigned long nBufferBaseY = pTextTexture->nWordPixelAscenderHeight;
	unsigned long nBufferStartX = 0;
	unsigned long nBufferStartY = 0;
	unsigned long nCurTextDrawRow = 0;
	unsigned long nCurLineDrawWidth = 0; // 当前行绘制的宽度


	pTextTexture->nEstimatePixelHeight = pTextTexture->nWordPixelHeight;


	for ( unsigned long nTextIndex = 0; nTextIndex < pTextTexture->nWordCount; nTextIndex++ )
	{
		if ( ( pTextDefine->text_buffer_ucs4 && __GG__FTH__IS_LINE_BREAK( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
				|| ( pTextDefine->text_buffer_ucs2 && __GG__FTH__IS_LINE_BREAK( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) ) )
		{
			DrawUnderDeleteLine( pTextTexture, pTextDefine, nullptr, pUnderLineDefine, pDeleteLineDefine, nBufferBaseY, 0, nCurLineDrawWidth );

			nCurLineDrawWidth = 0;

			nCurTextDrawRow++;
			if ( nCurTextDrawRow >= pTextTexture->nTextRowCount )
			{
				break;
			}


			const unsigned long nOffsetY = pTextTexture->nWordPixelHeight + pTextDefine->nLineGap;


#if ( defined( __GG__FTH__MAKER_USE_TRANSFORM ) && ( __GG__FTH__MAKER_USE_TRANSFORM ) )
			ftVectorPen.x = 0;
			ftVectorPen.y -= nOffsetY;
#else
			nBufferAdvanceX = 0;
#endif


			nBufferBaseY += nOffsetY;
			pTextTexture->nEstimatePixelHeight +=  nOffsetY;


			continue;
		}
		else if ( ( pTextDefine->text_buffer_ucs4 && __GG__FTH__IS_ESCAPE( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
						|| ( pTextDefine->text_buffer_ucs2 && __GG__FTH__IS_ESCAPE( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) ) )
		{
			continue;
		}


#if ( defined( __GG__FTH__MAKER_USE_TRANSFORM ) && ( __GG__FTH__MAKER_USE_TRANSFORM ) )
		FT_Set_Transform( _gg_ftFace, &ftMatrix, &ftVectorPen );
#endif


		//ftError = FT_Load_Char( _gg_ftFace, 0x4E00 + nTextIndex, FT_LOAD_RENDER ); // 中文TEST
		if ( pTextDefine->text_buffer_ucs4 )
		{
			ftError = FT_Load_Char( _gg_ftFace, pTextDefine->text_buffer_ucs4[ nTextIndex ], FT_LOAD_RENDER );
			if ( ftError )
			{
				continue;
			}
		}
		else if ( pTextDefine->text_buffer_ucs2 )
		{
			ftError = FT_Load_Char( _gg_ftFace, pTextDefine->text_buffer_ucs2[ nTextIndex ], FT_LOAD_RENDER );
			if ( ftError )
			{
				continue;
			}
		}
		else
		{
			return -1000;
		}


		/*
		// retrieve glyph index from character code
		//FT_Int glyph_index = FT_Get_Char_Index( _gg_ftFace, 0x4E00 + nTextIndex );
		FT_Int glyph_index = FT_Get_Char_Index( _gg_ftFace, pTextDefine->text_buffer_ucsX[ nTextIndex ] );

		// load glyph image into the slot (erase previous one)
		ftError = FT_Load_Glyph( _gg_ftFace, glyph_index, FT_LOAD_DEFAULT );
		if ( ftError )
		{
			continue;  // ignore errors
		}

		// convert to an anti-aliased bitmap
		ftError = FT_Render_Glyph( _gg_ftFace->glyph, FT_RENDER_MODE_NORMAL );
		if ( ftError )
		{
			continue;
		}//*/


		FT_Bitmap *					pFTBitmap		= &( _gg_ftFace->glyph->bitmap );
		const unsigned int		nItemWidth		= pFTBitmap->width;
		const signed long			nAdvanceX		= __GG__FTH__NUM_FT_TO_NORMAL( _gg_ftFace->glyph->advance.x );


		if ( pTextDefine->text_buffer_ucs4 )
		{
			if ( __GG__FTH__IS_BLANK_HW( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = nAdvanceX;
				pTextTexture->FixBlankWidth();
			}
			else if ( __GG__FTH__IS_BLANK_FW( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = ( nAdvanceX >> 1 );
				pTextTexture->FixBlankWidth();
			}
		}
		else if ( pTextDefine->text_buffer_ucs2 )
		{
			if ( __GG__FTH__IS_BLANK_HW( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = nAdvanceX;
				pTextTexture->FixBlankWidth();
			}
			else if ( __GG__FTH__IS_BLANK_FW( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = ( nAdvanceX >> 1 );
				pTextTexture->FixBlankWidth();
			}
		}


#if ( defined( __GG__FTH__MAKER_USE_TRANSFORM ) && ( __GG__FTH__MAKER_USE_TRANSFORM ) )
		nBufferStartX = _gg_ftFace->glyph->bitmap_left;
		nBufferStartY = nBufferBaseY - _gg_ftFace->glyph->bitmap_top;
#else
		nBufferStartX = _gg_ftFace->glyph->bitmap_left + nBufferAdvanceX;
		nBufferStartY = nBufferBaseY - _gg_ftFace->glyph->bitmap_top;
#endif
		if ( nCurTextDrawRow == 0 )
		{
			nBufferStartX += pTextTexture->nIndentationStartPos;
		}


		if ( pTextTexture->nTextRowCount > 1 )
		{
			if ( nBufferStartX + nAdvanceX > pTextTexture->nEstimatePixelWidth )
			{
				DrawUnderDeleteLine( pTextTexture, pTextDefine, nullptr, pUnderLineDefine, pDeleteLineDefine, nBufferBaseY, 0, nCurLineDrawWidth );
				
				nCurLineDrawWidth = 0;

				nCurTextDrawRow++;
				if ( nCurTextDrawRow >= pTextTexture->nTextRowCount )
				{
					break;
				}


				const unsigned long nOffsetY = pTextTexture->nWordPixelHeight + pTextDefine->nLineGap;


	#if ( defined( __GG__FTH__MAKER_USE_TRANSFORM ) && ( __GG__FTH__MAKER_USE_TRANSFORM ) )
				ftVectorPen.x = 0;
				ftVectorPen.y -= nOffsetY;
	#else
				nBufferAdvanceX = 0;
	#endif


				nBufferBaseY += nOffsetY;
				pTextTexture->nEstimatePixelHeight +=  nOffsetY;


				nTextIndex--;

				continue;
			}
		} // end if ( nTextMaxRowCount > 1 )
		else if ( ( nBufferStartX + nAdvanceX > pTextTexture->nEstimatePixelWidth ) && ( nTextIndex < pTextTexture->nWordCount - 1 ) )
		{
			break;
		}


		DrawWord( pTextTexture, pTextDefine, pFTBitmap, nBufferStartX, nBufferStartY );


#if ( defined( __GG__FTH__MAKER_USE_TRANSFORM ) && ( __GG__FTH__MAKER_USE_TRANSFORM ) )
		ftVectorPen.x += _gg_ftFace->glyph->advance.x;
#else
		nBufferAdvanceX += nAdvanceX;
#endif
		

		const unsigned long nBufferCurEndX = nBufferStartX + ( nItemWidth > 0 ? nItemWidth : nAdvanceX );
		if( nBufferCurEndX > pTextTexture->nRealPixelWidth )
		{
			pTextTexture->nRealPixelWidth = nBufferCurEndX;
		}


		nCurLineDrawWidth = nBufferCurEndX;
	} // end for


	pTextTexture->nTextEndPosX = nCurLineDrawWidth;
	pTextTexture->nTextEndPosY = nBufferBaseY;


	DrawUnderDeleteLine( pTextTexture, pTextDefine, nullptr, pUnderLineDefine, pDeleteLineDefine, nBufferBaseY, 0, nCurLineDrawWidth );


	pTextTexture->nRealPixelHeight = pTextTexture->nEstimatePixelHeight;


	return 0;
}



int FTH_Maker::CreateTextureBuffer( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FTH_StrokeDefine *pStrokeDefine, FTH_UnderLineDefine *pUnderLineDefine, FTH_DeleteLineDefine *pDeleteLineDefine )
{
	if ( Get_FT_Library() == nullptr )
	{
		return -1;
	}


	if ( _gg_ftFace == nullptr )
	{
		return -2;
	}


	if ( _gg_ftStroker == nullptr )
	{
		New_FT_Stroker();
		if ( _gg_ftStroker == nullptr )
		{
			return -3;
		}
	}


	if ( pTextTexture == nullptr )
	{
		return -10;
	}


	if ( pTextDefine == nullptr )
	{
		return -20;
	}


	if ( pTextDefine->text_buffer_ucs4 == nullptr && pTextDefine->text_buffer_ucs2 == nullptr )
	{
		return -21;
	}


	if ( pStrokeDefine == nullptr )
	{
		return CreateTextureBuffer( pTextTexture, pTextDefine, pUnderLineDefine, pDeleteLineDefine );
	}
	if ( pStrokeDefine->nStrokeSize <= 0 )
	{
		return CreateTextureBuffer( pTextTexture, pTextDefine, pUnderLineDefine, pDeleteLineDefine );
	}


	//FT_Error ftError = FT_Set_Char_Size( _gg_ftFace, FTH_NUM_NORMAL_TO_FT( pTextDefine->nFontSize ), 0, 96, 0 );
	FT_Error ftError = FT_Set_Pixel_Sizes( _gg_ftFace, pTextDefine->nFontSize, 0 );
	if ( ftError )
	{
		return -100;
	}


	FT_Stroker_Set( _gg_ftStroker, __GG__FTH__NUM_NORMAL_TO_FT( pStrokeDefine->nStrokeSize ), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0 );


	const int nResult = pTextTexture->Init( _gg_ftFace, pTextDefine, pStrokeDefine, pUnderLineDefine );
	if ( nResult != 0 )
	{
		return -101;
	}


	unsigned long nBufferBaseY = pTextTexture->nWordPixelAscenderHeight;;
	unsigned long nBufferAdvanceX = 0;
	unsigned long nBufferStartX = 0;
	unsigned long nBufferStartY = 0;
	unsigned long nCurTextDrawRow = 0;
	unsigned long nCurLineDrawWidth = 0; // 当前行绘制的宽度


	pTextTexture->nEstimatePixelHeight = pTextTexture->nWordPixelHeight;


	for ( unsigned long nTextIndex = 0; nTextIndex < pTextTexture->nWordCount; nTextIndex++ )
	{
		if ( ( pTextDefine->text_buffer_ucs4 && __GG__FTH__IS_LINE_BREAK( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
				|| ( pTextDefine->text_buffer_ucs2 && __GG__FTH__IS_LINE_BREAK( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) ) )
		{
			DrawUnderDeleteLine( pTextTexture, pTextDefine, pStrokeDefine, pUnderLineDefine, pDeleteLineDefine, nBufferBaseY, 0, nCurLineDrawWidth );

			nCurLineDrawWidth = 0;

			nCurTextDrawRow++;
			if ( nCurTextDrawRow >= pTextTexture->nTextRowCount )
			{
				break;
			}

			const unsigned long nOffsetY = pTextTexture->nWordPixelHeight + pTextDefine->nLineGap;

			nBufferAdvanceX = 0;
			nBufferBaseY += nOffsetY;
			pTextTexture->nEstimatePixelHeight +=  nOffsetY;


			continue;
		}
		else if ( ( pTextDefine->text_buffer_ucs4 && __GG__FTH__IS_ESCAPE( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
						|| ( pTextDefine->text_buffer_ucs2 && __GG__FTH__IS_ESCAPE( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) ) )
		{
			continue;
		}


		// retrieve glyph index from character code
		//FT_Int glyph_index = FT_Get_Char_Index( _gg_ftFace, 0x4E00 + nTextIndex ); // 中文TEST
		FT_Int glyph_index = 0;
		if ( pTextDefine->text_buffer_ucs4 )
		{
			glyph_index = FT_Get_Char_Index( _gg_ftFace, pTextDefine->text_buffer_ucs4[ nTextIndex ] );
		}
		else if ( pTextDefine->text_buffer_ucs2 )
		{
			glyph_index = FT_Get_Char_Index( _gg_ftFace, pTextDefine->text_buffer_ucs2[ nTextIndex ] );
		}
		else
		{
			return -1000;
		}


		if ( glyph_index == 0 )
		{
			continue;
		}


		// load glyph image into the slot (erase previous one)
		ftError = FT_Load_Glyph( _gg_ftFace, glyph_index, FT_LOAD_DEFAULT );
		if ( ftError )
		{
			continue;  // ignore errors
		}


		// !!release
		FT_Glyph ftGlyphFull;
		ftError = FT_Get_Glyph( _gg_ftFace->glyph, &ftGlyphFull );
		if ( ftError )
		{
			continue;
		}


		ftError = FT_Glyph_StrokeBorder( &ftGlyphFull, _gg_ftStroker, 0, 1 );
		if ( ftError )
		{
			FT_Done_Glyph( ftGlyphFull );
			continue;
		}


		if ( ftGlyphFull->format != FT_GLYPH_FORMAT_OUTLINE )
		{
			FT_Done_Glyph( ftGlyphFull );
			continue;
		}


		FT_Outline *ftOutline = &( reinterpret_cast<FT_OutlineGlyph>( ftGlyphFull )->outline );


		FT_BBox ftBBoxFull;
		FT_Glyph_Get_CBox( ftGlyphFull, FT_GLYPH_BBOX_GRIDFIT, &ftBBoxFull );


		const unsigned int nItemWidth		= __GG__FTH__NUM_FT_TO_NORMAL( ftBBoxFull.xMax - ftBBoxFull.xMin );
		const unsigned int nItemHeight	= __GG__FTH__NUM_FT_TO_NORMAL( ftBBoxFull.yMax - ftBBoxFull.yMin );
		const signed long nAdvanceX		= __GG__FTH__NUM_FT_TO_NORMAL( _gg_ftFace->glyph->advance.x );
		const unsigned long nItemSize		= nItemWidth * nItemHeight;


		if ( pTextDefine->text_buffer_ucs4 )
		{
			if ( __GG__FTH__IS_BLANK_HW( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = nAdvanceX;
				pTextTexture->FixBlankWidth();
			}
			else if ( __GG__FTH__IS_BLANK_FW( pTextDefine->text_buffer_ucs4[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = ( nAdvanceX >> 1 );
				pTextTexture->FixBlankWidth();
			}
		}
		else if ( pTextDefine->text_buffer_ucs2 )
		{
			if ( __GG__FTH__IS_BLANK_HW( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = nAdvanceX;
				pTextTexture->FixBlankWidth();
			}
			else if ( __GG__FTH__IS_BLANK_FW( pTextDefine->text_buffer_ucs2[ nTextIndex ] ) )
			{
				pTextTexture->nTextBlankHalfWidth = ( nAdvanceX >> 1 );
				pTextTexture->FixBlankWidth();
			}
		}


		nBufferStartX = __GG__FTH__NUM_FT_TO_NORMAL( _gg_ftFace->glyph->metrics.horiBearingX ) + nBufferAdvanceX;
		nBufferStartY = nBufferBaseY - __GG__FTH__NUM_FT_TO_NORMAL( _gg_ftFace->glyph->metrics.horiBearingY );
		if ( nCurTextDrawRow == 0 )
		{
			nBufferStartX += pTextTexture->nIndentationStartPos;
		}


		if( pTextTexture->nTextRowCount > 1 )
		{
			if ( nBufferStartX + nAdvanceX + ( pStrokeDefine->nStrokeSize << 1 ) > pTextTexture->nEstimatePixelWidth )
			{
				DrawUnderDeleteLine( pTextTexture, pTextDefine, pStrokeDefine, pUnderLineDefine, pDeleteLineDefine, nBufferBaseY, 0, nCurLineDrawWidth );

				FT_Done_Glyph( ftGlyphFull );

				nCurLineDrawWidth = 0;

				nCurTextDrawRow++;
				if ( nCurTextDrawRow >= pTextTexture->nTextRowCount )
				{
					break;
				}

				const unsigned long nOffsetY = pTextTexture->nWordPixelHeight + pTextDefine->nLineGap;

				nBufferAdvanceX = 0;
				nBufferBaseY += nOffsetY;
				pTextTexture->nEstimatePixelHeight +=  nOffsetY;

				nTextIndex--;

				continue;
			}
		} // if( nTextMaxRowCount > 1 )
		else if ( ( nBufferStartX + nAdvanceX + ( pStrokeDefine->nStrokeSize << 1 ) > pTextTexture->nEstimatePixelWidth )
						&& ( nTextIndex < pTextTexture->nWordCount - 1 ) )
		{
			break;
		}


		// ========== 字形和描边 [ begin ] ==========
		// !!release
		unsigned char *buffer_full = new unsigned char[ nItemSize ];
		memset( buffer_full, 0, nItemSize );


		FT_Bitmap ftBitmap;
		ftBitmap.buffer				= buffer_full;
		ftBitmap.width				= nItemWidth;
		ftBitmap.rows				= nItemHeight;
		ftBitmap.pitch				= nItemWidth;
		ftBitmap.pixel_mode		= FT_PIXEL_MODE_GRAY;
		ftBitmap.num_grays		= 256;


		FT_Raster_Params ftRasterParams;
		memset( &ftRasterParams, 0, sizeof ( ftRasterParams ) );
		ftRasterParams.source	= ftOutline;
		ftRasterParams.target	= &ftBitmap;
		ftRasterParams.flags	= FT_RASTER_FLAG_AA;
		FT_Outline_Translate( ftOutline, -ftBBoxFull.xMin, -ftBBoxFull.yMin );
		ftError = FT_Outline_Render( Get_FT_Library(), ftOutline, &ftRasterParams );
		if ( ftError )
		{
			FT_Done_Glyph( ftGlyphFull );

			delete [] buffer_full;
			buffer_full = nullptr;

			continue;
		}
		// ========== 字形和描边 [ end ] ==========


		// ========== 字形 [ begin ] ==========
		FT_BBox ftBBoxFont;
		// !!release
		FT_Glyph ftGlyphFontGlyph;
		ftError = FT_Get_Glyph( _gg_ftFace->glyph, &ftGlyphFontGlyph );
		if ( ftError )
		{
			FT_Done_Glyph( ftGlyphFull );

			delete [] buffer_full;
			buffer_full = nullptr;

			continue;
		}
		FT_Glyph_Get_CBox( ftGlyphFontGlyph, FT_GLYPH_BBOX_GRIDFIT, &ftBBoxFont );


		// !!release
		unsigned char *buffer_word = new unsigned char[ nItemSize ];
		memset( buffer_word, 0, nItemSize );


		ftBitmap.buffer				= buffer_word;
		ftBitmap.width				= nItemWidth;
		ftBitmap.rows				= nItemHeight;
		ftBitmap.pitch				= nItemWidth;
		ftBitmap.pixel_mode		= FT_PIXEL_MODE_GRAY;
		ftBitmap.num_grays		= 256;
		
		
		ftOutline = &( reinterpret_cast<FT_OutlineGlyph>( ftGlyphFontGlyph )->outline );
		memset( &ftRasterParams, 0, sizeof ( ftRasterParams ) );
		ftRasterParams.source	= ftOutline;
		ftRasterParams.target	= &ftBitmap;
		ftRasterParams.flags		= FT_RASTER_FLAG_AA;
		FT_Outline_Translate( ftOutline, -ftBBoxFull.xMin, -ftBBoxFull.yMin );
		ftError = FT_Outline_Render( Get_FT_Library(), ftOutline, &ftRasterParams );
		if ( ftError )
		{
			FT_Done_Glyph( ftGlyphFull );

			delete [] buffer_full;
			buffer_full = nullptr;

			FT_Done_Glyph( ftGlyphFontGlyph );

			delete [] buffer_word;
			buffer_word = nullptr;

			continue;
		}
		// ========== 字形 [ end ] ==========

		
		DrawWord( pTextTexture, pTextDefine, pStrokeDefine, buffer_full, buffer_word, nItemWidth, nItemHeight, nItemSize, nBufferStartX, nBufferStartY );


		nBufferAdvanceX += ( nAdvanceX + ( pStrokeDefine->nStrokeSize << 1 ) );
		

		const unsigned long nBufferCurEndX = nBufferStartX + ( nItemWidth > 0 ? nItemWidth : nAdvanceX );
		if( nBufferCurEndX > pTextTexture->nRealPixelWidth )
		{
			pTextTexture->nRealPixelWidth = nBufferCurEndX;
		}


		nCurLineDrawWidth = nBufferCurEndX;



		FT_Done_Glyph( ftGlyphFull );
		FT_Done_Glyph( ftGlyphFontGlyph );

		delete [] buffer_full;
		delete [] buffer_word;
	} // end for


	pTextTexture->nTextEndPosX = nCurLineDrawWidth;
	pTextTexture->nTextEndPosY = nBufferBaseY;


	DrawUnderDeleteLine( pTextTexture, pTextDefine, pStrokeDefine, pUnderLineDefine, pDeleteLineDefine, nBufferBaseY, 0, nCurLineDrawWidth );


	pTextTexture->nRealPixelHeight = pTextTexture->nEstimatePixelHeight;


	return 0;
}



int FTH_Maker::DrawWord( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FT_Bitmap *pFTBitmap,
	const unsigned long nBufferStartX, const unsigned long nBufferStartY )
{
	if ( pTextTexture == nullptr )
	{
		return -1;
	}

	if ( pTextDefine == nullptr )
	{
		return -2;
	}

	if ( pFTBitmap == nullptr )
	{
		return -3;
	}


	const unsigned int		nItemWidth							= pFTBitmap->width;
	const unsigned int		nItemHeight							= pFTBitmap->rows;
	const unsigned long		nItemSize								= nItemWidth * nItemHeight;
	const FTH_UByte			nMaxOffsetIndexOfBuffer		= ( pTextTexture->nByteCountPerPixel > 1 ) ? ( pTextTexture->nByteCountPerPixel - 1 ) : pTextTexture->nByteCountPerPixel;


	// 拷贝字符图像内存到 texture buffer, 从左到右，从上到下
	for ( unsigned int nItemY = 0; nItemY < nItemHeight; nItemY++ )
	{
		const unsigned long nItemStartIndex = nItemY * nItemWidth;

		for ( unsigned int nItemX = 0; nItemX < nItemWidth; nItemX++ )
		{
			const unsigned long nItemIndex = nItemStartIndex + nItemX;
			const unsigned long nTextureBufferIndex = ( nBufferStartY + nItemY ) * pTextTexture->nByteCountPerLine
				+ ( ( nBufferStartX + nItemX ) * pTextTexture->nByteCountPerPixel );


			if ( nTextureBufferIndex + nMaxOffsetIndexOfBuffer >= pTextTexture->nBufferSize
					|| nItemIndex >= nItemSize )
			{
				continue;
			}


			unsigned char bmpBufferValue = ( pFTBitmap->buffer[ nItemIndex ] );


			if ( pTextDefine->ePixelMode == PixelMode::RGBA8888 )
			{
				if ( bmpBufferValue > 0 )
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = pTextDefine->textColor.red;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pTextDefine->textColor.green;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pTextDefine->textColor.blue;
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = ( pTextDefine->nTextAlpha * bmpBufferValue ) >> 8;
				}
				else
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = pTextDefine->bgColor.red;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pTextDefine->bgColor.green;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pTextDefine->bgColor.blue;
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = pTextDefine->nBGAlpha;
				}
			}
			else if ( pTextDefine->ePixelMode == PixelMode::RGB888 )
			{
				if ( bmpBufferValue > 0 )
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = ( pTextDefine->textColor.red * bmpBufferValue ) >> 8;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = ( pTextDefine->textColor.green * bmpBufferValue ) >> 8;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = ( pTextDefine->textColor.blue * bmpBufferValue ) >> 8;
				}
				else
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = pTextDefine->bgColor.red;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pTextDefine->bgColor.green;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pTextDefine->bgColor.blue;
				}
			}
		} // end for X
	} // end for Y


	return 0;
}



int FTH_Maker::DrawWord( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FTH_StrokeDefine *pStrokeDefine,
		const unsigned char *buffer_full, const unsigned char *buffer_word,
		const unsigned int nItemWidth, const unsigned int nItemHeight, const unsigned long nItemSize,
		const unsigned long nBufferStartX, const unsigned long nBufferStartY )
{
	if ( pTextTexture == nullptr )
	{
		return -1;
	}

	if ( pTextDefine == nullptr )
	{
		return -2;
	}

	if ( pStrokeDefine == nullptr )
	{
		return -3;
	}

	if ( buffer_full == nullptr )
	{
		return -4;
	}
	if ( buffer_word == nullptr )
	{
		return -5;
	}

	
	const FTH_UByte			nMaxOffsetIndexOfBuffer		= ( pTextTexture->nByteCountPerPixel > 1 ) ? ( pTextTexture->nByteCountPerPixel - 1 ) : pTextTexture->nByteCountPerPixel;


	for ( unsigned int nItemY = 0; nItemY < nItemHeight; nItemY++ )
	{
		const unsigned long nItemStartIndex = nItemY * nItemWidth;

		for ( unsigned int nItemX = 0; nItemX < nItemWidth; nItemX++ )
		{
			const unsigned long nItemIndex = nItemStartIndex + nItemX;
			const unsigned long nTextureBufferIndex = ( nBufferStartY + nItemY ) * pTextTexture->nByteCountPerLine
				+ ( ( nBufferStartX + nItemX ) * pTextTexture->nByteCountPerPixel );


			if ( nTextureBufferIndex + nMaxOffsetIndexOfBuffer >= pTextTexture->nBufferSize
					|| nItemIndex >= nItemSize )
			{
				continue;
			}


			const unsigned char itemValueFull = buffer_full[ nItemIndex ];
			const unsigned char itemValueWord = buffer_word[ nItemIndex ];


			if ( pTextDefine->ePixelMode == PixelMode::RGBA8888 )
			{
				if ( itemValueFull )
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex + 0 ] = pStrokeDefine->color.red;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pStrokeDefine->color.green;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pStrokeDefine->color.blue;
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = ( pStrokeDefine->nAlpha * itemValueFull ) >> 8;
				}
				else
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = pTextDefine->bgColor.red;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pTextDefine->bgColor.green;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pTextDefine->bgColor.blue;
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = pTextDefine->nBGAlpha;
				}


				if ( itemValueWord )
				{
					// 抗锯齿
					unsigned short nItemValueTotalR = pStrokeDefine->color.red + ( ( ( pTextDefine->textColor.red - pStrokeDefine->color.red ) * itemValueWord ) >> 8 );
					unsigned short nItemValueTotalG = pStrokeDefine->color.green + ( ( ( pTextDefine->textColor.green - pStrokeDefine->color.green ) * itemValueWord ) >> 8 );
					unsigned short nItemValueTotalB = pStrokeDefine->color.blue + ( ( ( pTextDefine->textColor.blue - pStrokeDefine->color.blue ) * itemValueWord ) >> 8 );
					unsigned short nItemValueTotalA = ( ( pTextDefine->nTextAlpha * itemValueWord ) >> 8 ) + ( ( pStrokeDefine->nAlpha * itemValueFull ) >> 8 );
					if ( nItemValueTotalR > 255 )
					{
						nItemValueTotalR = 255;
					}
					if ( nItemValueTotalG > 255 )
					{
						nItemValueTotalG = 255;
					}
					if ( nItemValueTotalB > 255 )
					{
						nItemValueTotalB = 255;
					}
					if ( nItemValueTotalA > 255 )
					{
						nItemValueTotalA = 255;
					}

					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = nItemValueTotalR;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = nItemValueTotalG;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = nItemValueTotalB;
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = nItemValueTotalA;
				}
			}
			else if ( pTextDefine->ePixelMode == PixelMode::RGB888 )
			{
				if ( itemValueFull )
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex + 0 ] = ( pStrokeDefine->color.red * itemValueFull ) >> 8;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = ( pStrokeDefine->color.green * itemValueFull ) >> 8;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = ( pStrokeDefine->color.blue * itemValueFull ) >> 8;
				}
				else
				{
					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = pTextDefine->bgColor.red;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pTextDefine->bgColor.green;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pTextDefine->bgColor.blue;
				}


				if ( itemValueWord )
				{
					// 抗锯齿
					unsigned short nItemValueTotalR = pStrokeDefine->color.red + ( ( ( pTextDefine->textColor.red - pStrokeDefine->color.red ) * itemValueWord ) >> 8 );
					unsigned short nItemValueTotalG = pStrokeDefine->color.green + ( ( ( pTextDefine->textColor.green - pStrokeDefine->color.green ) * itemValueWord ) >> 8 );
					unsigned short nItemValueTotalB = pStrokeDefine->color.blue + ( ( ( pTextDefine->textColor.blue - pStrokeDefine->color.blue ) * itemValueWord ) >> 8 );
					if ( nItemValueTotalR > 255 )
					{
						nItemValueTotalR = 255;
					}
					if ( nItemValueTotalG > 255 )
					{
						nItemValueTotalG = 255;
					}
					if ( nItemValueTotalB > 255 )
					{
						nItemValueTotalB = 255;
					}

					// R
					pTextTexture->buffer[ nTextureBufferIndex ] = nItemValueTotalR;
					// G
					pTextTexture->buffer[ nTextureBufferIndex + 1 ] = nItemValueTotalG;
					// B
					pTextTexture->buffer[ nTextureBufferIndex + 2 ] = nItemValueTotalB;
				}
			}
		} // end for X
	} // end for Y


	return 0;
}



int FTH_Maker::DrawUnderDeleteLine( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FTH_StrokeDefine *pStrokeDefine,
	FTH_UnderLineDefine *pUnderLineDefine, FTH_DeleteLineDefine *pDeleteLineDefine,
	const unsigned long nLineBaseY, const unsigned long nLineStartX, const unsigned long nLineWidth )
{
	if ( pTextTexture == nullptr )
	{
		return -1;
	}

	if ( pTextDefine == nullptr )
	{
		return -2;
	}

	if ( nLineWidth <= 0 )
	{
		return -10;
	}


	const unsigned long nDeleteLineOriginY = nLineBaseY - pTextTexture->nWordPixelAscenderHeight;
	unsigned long nDeleteLineStartY = 0;
	if ( pDeleteLineDefine )
	{
		if ( pTextTexture->nWordPixelAscenderHeight + pTextTexture->nWordPixelDescenderHeight < pDeleteLineDefine->nThick )
		{
			pDeleteLineDefine->nThick = 2;
		}

		pDeleteLineDefine->FixAnchor();

		const unsigned long nDeleteLineMinStartY = nDeleteLineOriginY + ( pDeleteLineDefine->nThick >> 1 );
		const unsigned long nDeleteLineMaxStartY = nDeleteLineOriginY + pTextTexture->nWordPixelAscenderHeight + pTextTexture->nWordPixelDescenderHeight - ( pDeleteLineDefine->nThick >> 1 );

		unsigned long nDeleteLineAnchorY = nLineBaseY;
		if ( pDeleteLineDefine->fAnchor == 0.0f )
		{
			nDeleteLineAnchorY = nLineBaseY;
		}
		else if ( pDeleteLineDefine->fAnchor > 0.0f )
		{
			nDeleteLineAnchorY = nLineBaseY - pTextTexture->nWordPixelAscenderHeight * pDeleteLineDefine->fAnchor;
		}
		else
		{
			nDeleteLineAnchorY = nLineBaseY + pTextTexture->nWordPixelDescenderHeight * ( -pDeleteLineDefine->fAnchor );
		}

		if ( nDeleteLineAnchorY < nDeleteLineMinStartY )
		{
			nDeleteLineStartY = nDeleteLineMinStartY;
		}
		else if ( nDeleteLineAnchorY > nDeleteLineMaxStartY )
		{
			nDeleteLineStartY = nDeleteLineMaxStartY;
		}
		else
		{
			nDeleteLineStartY = nDeleteLineAnchorY - ( pDeleteLineDefine->nThick >> 1 );
		}
	}


	const unsigned long nUnderLineStartY = nLineBaseY + pTextTexture->nWordPixelDescenderHeight
		+ ( pStrokeDefine ? pStrokeDefine->nStrokeSize * 2 : 0 );

	
	const FTH_UByte			nMaxOffsetIndexOfBuffer		= ( pTextTexture->nByteCountPerPixel > 1 ) ? ( pTextTexture->nByteCountPerPixel - 1 ) : pTextTexture->nByteCountPerPixel;


	for ( unsigned long nLineX = nLineStartX; nLineX <= nLineWidth; nLineX++ )
	{
		const unsigned long nCurLineX = nLineX * pTextTexture->nByteCountPerPixel;



		if ( pDeleteLineDefine )
		{
			for ( unsigned int nDeleteLineThickY = 0; nDeleteLineThickY < pDeleteLineDefine->nThick; nDeleteLineThickY++ )
			{
				const unsigned long nTextureBufferIndex = ( nDeleteLineStartY + nDeleteLineThickY ) * pTextTexture->nByteCountPerLine + nCurLineX;


				if ( nTextureBufferIndex + nMaxOffsetIndexOfBuffer >= pTextTexture->nBufferSize )
				{
					continue;
				}


				// R
				pTextTexture->buffer[ nTextureBufferIndex ] = pDeleteLineDefine->color.red;
				// G
				pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pDeleteLineDefine->color.green;
				// B
				pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pDeleteLineDefine->color.blue;

				if ( pTextDefine->ePixelMode == PixelMode::RGBA8888 )
				{
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = pDeleteLineDefine->nAlpha;
				}

			} // end for DeleteLine Y
		} // end if ( pDeleteLineDefine )



		if ( pUnderLineDefine )
		{
			for ( unsigned int nUnderLineThickY = 0; nUnderLineThickY < pUnderLineDefine->nThick; nUnderLineThickY++ )
			{
				const unsigned long nTextureBufferIndex = ( nUnderLineStartY + nUnderLineThickY ) * pTextTexture->nByteCountPerLine + nCurLineX;


				if ( nTextureBufferIndex + pTextTexture->nByteCountPerLine - 1 >= pTextTexture->nBufferSize )
				{
					continue;
				}


				// R
				pTextTexture->buffer[ nTextureBufferIndex ] = pUnderLineDefine->color.red;
				// G
				pTextTexture->buffer[ nTextureBufferIndex + 1 ] = pUnderLineDefine->color.green;
				// B
				pTextTexture->buffer[ nTextureBufferIndex + 2 ] = pUnderLineDefine->color.blue;

				if ( pTextDefine->ePixelMode == PixelMode::RGBA8888 )
				{
					// A
					pTextTexture->buffer[ nTextureBufferIndex + 3 ] = pUnderLineDefine->nAlpha;
				}

			} // end for DeleteLine Y
		} // end if ( pUnderLineDefine )


	} // end for X


	return 0;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
