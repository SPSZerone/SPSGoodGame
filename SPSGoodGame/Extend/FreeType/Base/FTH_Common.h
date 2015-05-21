#ifndef __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_BASE__FTH_COMMON_H__
#define __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_BASE__FTH_COMMON_H__

#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Base.h"
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Config.h"



#define __GG__FTH__NUM_FT_TO_NORMAL( ___FTHN_FT_to_NOR___ )				( ( ( ___FTHN_FT_to_NOR___ ) >> 6 ) )
#define __GG__FTH__NUM_NORMAL_TO_FT( ___FTHN_NOR_to_FT___ )				( ( ( ___FTHN_NOR_to_FT___ ) << 6 ) )


#define __GG__FTH__MIN( ___FTHMIN_X___, ___FTHMIN_Y___ )				( ( ( ___FTHMIN_X___ ) < ( ___FTHMIN_Y___ ) ) ? ( ___FTHMIN_X___ ) : ( ___FTHMIN_Y___ ) )
#define __GG__FTH__MAX( ___FTHMAX_X___, ___FTHMAX_Y___ )				( ( ( ___FTHMAX_X___ ) > ( ___FTHMAX_Y___ ) ) ? ( ___FTHMAX_X___ ) : ( ___FTHMAX_Y___ ) )


// 是否为换行符
#define __GG__FTH__IS_LINE_BREAK( __FTH_UNICODE__ )          ( ( __FTH_UNICODE__ ) == '\n' || ( __FTH_UNICODE__ ) == '\r' )

// 是否为转义字符
#define __GG__FTH__IS_ESCAPE( __FTH_UNICODE__ )          ( ( __FTH_UNICODE__ ) <= 31 || ( __FTH_UNICODE__ ) == 127 )

// 是否为空格（半角）
#define __GG__FTH__IS_BLANK_HW( __FTH_UNICODE__ )          ( ( __FTH_UNICODE__ ) == 32 )

// 是否为空格（全角）
#define __GG__FTH__IS_BLANK_FW( __FTH_UNICODE__ )          ( ( __FTH_UNICODE__ ) == 0x3000 )



__SPS_GG__NS__B_EXTEND_FREETYPE

enum class PixelMode
{
	RGBA8888,
	RGB888,
}; // end enum class PixelMode


enum class TextAlignHorizontal
{
	LEFT,
	CENTER,
	RIGHT,
}; // end enum class TextAlignHorizontal


enum class IndentationType
{
	WORD,			// 缩进几个字
	PIXEL,				// 缩进像素宽度
}; // end enum class IndentationType


class FTH_Color
{
public:
	FTH_UByte red;
	FTH_UByte green;
	FTH_UByte blue;


	FTH_Color();
	FTH_Color( FTH_UByte r, FTH_UByte g, FTH_UByte b );

	bool operator == ( const FTH_Color& right ) const;
	bool operator != ( const FTH_Color& right ) const;
	bool Equals( const FTH_Color& other ) const;
}; // end class FTH_Color


	
class FTH_TextDefine
{
public:
	/* 文本buffer(UCS4)
	*/
	const unsigned long *text_buffer_ucs4;
	/* 文本buffer(UCS2)
	*/
	const unsigned short *text_buffer_ucs2;
		
	/* 文本buffer_size
	*/
	unsigned long text_buffer_size;

	/* 像素模式
	*/
	PixelMode ePixelMode;

	/* 水平对齐方式
	*/
	TextAlignHorizontal eTextAlignHorizontal;

	/* 字体大小
	*/
	unsigned int nFontSize;

	/* 文本颜色（0~255）
	*/
	FTH_Color textColor;

	/* 文本Alpha（0~255）
	*/
	FTH_UByte nTextAlpha;

	/* 行间距
	*/
	unsigned short nLineGap;

	/* 行宽
		如果为0则不进行换行
	*/
	unsigned long nLineMaxWidth;

	/* 最大行数
		如果为0则全部绘制
	*/
	unsigned long nLineMaxRows;
		
	/* 背景颜色（0~255）
	*/
	FTH_Color bgColor;

	/* 背景Alpha（0~255）
	*/
	FTH_UByte nBGAlpha;
	
	/* 首行缩进方式 SEE @ IndentationType
	*/
	IndentationType eIndentationType;
	/* 首行缩进的值
		像素缩进：像素宽度
		字缩进：字数
	*/
	unsigned int nIndentationValue;


	FTH_TextDefine();
	virtual ~FTH_TextDefine();
	virtual int GetWordCount( unsigned long &_word_count, unsigned long &_word_real_count );
	virtual int GetLineBreakCount( unsigned long &_line_break_count );
}; // end class FTH_TextDefine


	
class FTH_StrokeDefine
{
public:
	/* 描边尺寸
	*/
	unsigned int nStrokeSize;

	/* 描边颜色（0~255）
	*/
	FTH_Color color;

	/* 描边Alpha（0~255）
	*/
	FTH_UByte nAlpha;


	FTH_StrokeDefine();
	virtual ~FTH_StrokeDefine();
}; // end class FTH_StrokeDefine


	
class FTH_UnderLineDefine
{
public:
	/* 厚度
	*/
	unsigned int nThick;

	/* 颜色（0~255）
	*/
	FTH_Color color;

	/* Alpha（0~255）
	*/
	FTH_UByte nAlpha;


	FTH_UnderLineDefine();
	virtual ~FTH_UnderLineDefine();
}; // end class FTH_UnderLineDefine


	
class FTH_DeleteLineDefine
{
public:
	/* 厚度
	*/
	unsigned int nThick;

	/* 颜色（0~255）
	*/
	FTH_Color color;

	/* Alpha（0~255）
	*/
	FTH_UByte nAlpha;

	/* 删除线位置（基于基线位置）
		= 0 在基线位置
		> 0 ( 0 ~ 1 ] 基线到上行高度之间
		< 0 [ -1 ~ 0 ) 基线到下行高度之间
	*/
	float fAnchor;


	FTH_DeleteLineDefine();
	virtual ~FTH_DeleteLineDefine();
	virtual int FixAnchor();
}; // end class FTH_DeleteLineDefine


	
class FTH_TextTexture
{
public:
	/* texture buffer
	*/
	unsigned char *buffer;
	/* buffer size
	*/
	unsigned long nBufferSize;
	/* 像素宽（2^n）
	*/
	unsigned long nBufferPixelWidth;
	/* 像素高（2^n）
	*/
	unsigned long nBufferPixelHeight;
	/* 每像素需要的字节数
	*/
	FTH_UByte nByteCountPerPixel;
	/* 每行的字节数
	*/
	unsigned long nByteCountPerLine;


	/* 实际宽度
	*/
	unsigned long nRealPixelWidth;
	/* 实际高度
	*/
	unsigned long nRealPixelHeight;
	/* 预估宽度
	*/
	unsigned long nEstimatePixelWidth;
	/* 预估高度
	*/
	unsigned long nEstimatePixelHeight;


	/* 字数（包括转义字符）
	*/
	unsigned long nWordCount;
	/* 实际可显示的字数
	*/
	unsigned long nWordRealCount;
	/* "字"的上行高度（相对基线）
	*/
	unsigned long nWordPixelAscenderHeight;
	/* "字"的下行高度（相对基线）
	*/
	unsigned long nWordPixelDescenderHeight;
	/* "字"的高度（包括描边和下划线）
	*/
	unsigned long nWordPixelHeight;
	/* 单个"字"的最大步进（包括描边）
	*/
	unsigned long nWordMaxAdvance;


	/* 单行显示预计的总宽度（包括首行缩进的宽度）
	*/
	unsigned long nTextEstimatePixelTotalWidth;
	/* 实际文本行数
	*/
	unsigned long nTextRowCount;


	/* 首行缩进开始位置
	*/
	unsigned long nIndentationStartPos;


	unsigned long nTextEndPosX;
	unsigned long nTextEndPosY;


	/* 空格宽度（半角）
	*/
	unsigned int nTextBlankHalfWidth;


	FTH_TextTexture();
	virtual ~FTH_TextTexture();

	virtual void Reset();
	virtual int DestroyBuffer();
	virtual int FixBlankWidth();
	virtual int PreCalculateTextPixelTotalWidth( FT_Face _ftFace, FTH_TextDefine *_pTextDefine, FTH_StrokeDefine *_pStrokeDefine );
	virtual int Init( FT_Face _ftFace, FTH_TextDefine *_pTextDefine, FTH_StrokeDefine *_pStrokeDefine, FTH_UnderLineDefine *_pUnderLineDefine );
}; // end class FTH_TextTexture

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_FREETYPE



#endif // #if ( ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_FREE_TYPE_HELPER_BASE__FTH_COMMON_H__
