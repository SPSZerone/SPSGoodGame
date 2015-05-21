#ifndef __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_HELPER__FTH_MAKER_H__
#define __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_HELPER__FTH_MAKER_H__

#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Common.h"
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Config.h"



#define __GG__FTH__MAKER_USE_TRANSFORM        0



__SPS_GG__NS__B_EXTEND_FREETYPE

/* texture buffer 坐标系
	X轴从左到右，增长
	Y轴从上到下，增长
*/
class FTH_Maker
{
protected:
	static FT_Library	_gg_s_ftLibrary;

	FT_Face				_gg_ftFace;
	FT_Stroker			_gg_ftStroker;



public:
	static int destroy_ft_library();

	FTH_Maker();
	virtual ~FTH_Maker();

	FT_Library Get_FT_Library();
	
	int New_FT_Face_FromFile(  const char *fontFile  );
	/* !!! attention !!!
	fontBuffer由调用者释放
	*/
	int New_FT_Face_FromMemory( const unsigned char *fontBuffer, const unsigned long &nFontBufferSize );
	int New_FT_Stroker();


	/* 由调用者释放内存
		pTextTexture->DestroyBuffer();
	*/
	int CreateTextureBuffer( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine,
		FTH_UnderLineDefine *pUnderLineDefine, FTH_DeleteLineDefine *pDeleteLineDefine );

	/* 由调用者释放内存
		pTextTexture->DestroyBuffer();
	*/
	int CreateTextureBuffer( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine,
		FTH_StrokeDefine *pStrokeDefine, FTH_UnderLineDefine *pUnderLineDefine, FTH_DeleteLineDefine *pDeleteLineDefine );


protected:
	int Init_FT_Library();
	int Destroy_FT_Face();


	int DrawWord( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FT_Bitmap *pFTBitmap,
		const unsigned long nBufferStartX, const unsigned long nBufferStartY );

	int DrawWord( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FTH_StrokeDefine *pStrokeDefine,
		const unsigned char *buffer_full, const unsigned char *buffer_word,
		const unsigned int nItemWidth, const unsigned int nItemHeight, const unsigned long nItemSize,
		const unsigned long nBufferStartX, const unsigned long nBufferStartY );
	
	int DrawUnderDeleteLine( FTH_TextTexture *pTextTexture, FTH_TextDefine *pTextDefine, FTH_StrokeDefine *pStrokeDefine,
		FTH_UnderLineDefine *pUnderLineDefine, FTH_DeleteLineDefine *pDeleteLineDefine,
		const unsigned long nLineBaseY, const unsigned long nLineStartX, const unsigned long nLineWidth );

}; // end class FTH_Maker

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_FREETYPE



#endif // #if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_HELPER__FTH_MAKER_H__
