#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__TEXT_VIEW_FT_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__TEXT_VIEW_FT_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/FreeType/Helper/FTH_Maker.h"
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_EXTEND_FREETYPE;



__SPS_GG__NS__B_EXTEND_COCOS
	
class EditTextFT;
class TextViewFT : public Node
{
protected:
	friend class EditTextFT;


public:
	enum class PixelMode
	{
		RGBA8888,
		RGB888
	};

	enum class TextAlignHorizontal
	{
		LEFT,
		CENTER,
		RIGHT,
	};

	enum class IndentationType
	{
		WORD,			// 缩进几个字
		PIXEL,				// 缩进像素宽度
	};

	enum UITag
	{
		kTextViewFT_UITag_RENDER,
	};
	

protected:
	FTH_Maker *_gg_pFTH_Maker;

	FTH_TextDefine _gg_fthTextDefine;
	FTH_StrokeDefine _gg_fthStrokeDefine;
	FTH_UnderLineDefine _gg_fthUnderLineDefine;
	FTH_DeleteLineDefine _gg_fthDeleteLineDefine;

	FTH_TextTexture _gg_fthTextTexture;

	std::string _gg_strText;
	Point _gg_textAnchor;


	bool _gg_isStrokeEnable;
	bool _gg_isUnderLineEnable;
	bool _gg_isDeleteLineEnable;

	
public:
	CREATE_FUNC( TextViewFT );
	TextViewFT();
	virtual ~TextViewFT();
	virtual bool init() override;


	virtual void setAnchorPoint( const Point &anchor ) override;
	

	virtual void SetFTH_Maker( FTH_Maker *pFTH_Maker ) { _gg_pFTH_Maker = pFTH_Maker; }
	virtual FTH_Maker * GetFTH_Maker() { return _gg_pFTH_Maker; }
	virtual const FTH_TextTexture &GetTextTexture() const;

	
	/* 坐标系EditTextFT
		以左下角为起点
	*/
	virtual Point GetOriginPosition() const;
	// 相对坐标：0~1 e.g. 左下角、右下角、中心
	virtual Point GetAnchorPosition( const Point &anchor ) const;

	
	virtual Point GetWorldPosition() const;
	// 文本最后一行右下角的世界坐标（Y轴为base line）
	virtual Point GetTextEndWorldPosition() const;


	// 文本base line在整个字BOX区域中的描点，从下到上范围[ 0, 1 ]
	virtual float GetTextBaseLineAnchor() const;


	virtual const std::string &GetText() const;
	virtual bool IsTextEmpty() const;

	
	/* 默认RGBA8888
		如果文本的背景为纯色（如黑色或白色），建议采用RGB888，节省内存
		调用Prepare_BG将 "字的背景" 设置为与 "文本的背景" 相同的颜色
	*/
	virtual int Prepare_PixelMode( TextViewFT::PixelMode ePixelMode );
	virtual int Prepare_TextAlignHorizontal( TextViewFT::TextAlignHorizontal eTextAlignHorizontal );

	virtual int Prepare_Text( const char *text, unsigned int nFontSize, const Color3B &textColor, unsigned char nAlpha = 255 );
	virtual int Prepare_Text( const char *text );
	virtual int Prepare_FontSize( unsigned int nFontSize );
	virtual int Prepare_TextColor( const Color3B &textColor );
	virtual int Prepare_TextAlpha( unsigned char nAlpha );

	/*
		nLineGap：行间距
		nLineMaxWidth：每行最大宽度（为0，则显示一行）
		nLineMaxRows：最多显示几行（nLineMaxWidth > 0时有效）
	*/
	virtual int Prepare_Line( unsigned short nLineGap, unsigned long nLineMaxWidth, unsigned int nLineMaxRows );
	virtual int Prepare_LineGap( unsigned short nLineGap );
	virtual int Prepare_LineMaxWidth( unsigned long nLineMaxWidth );
	virtual int Prepare_LineMaxRows( unsigned int nLineMaxRows );
	
	/* 字的背景（通常不会用到）
	*/
	virtual int Prepare_BG( const Color3B &color, unsigned char nAlpha );
	virtual int Prepare_BGColor( const Color3B &color );
	virtual int Prepare_BGAlpha( unsigned char nAlpha );

	virtual int Prepare_StrokeEnable( bool isEnable );
	virtual int Prepare_Stroke( unsigned int nStrokeSize, const Color3B &color, unsigned char nAlpha = 255 );
	virtual int Prepare_StrokeSize( unsigned int nStrokeSize );
	virtual int Prepare_StrokeColor( const Color3B &color );
	virtual int Prepare_StrokeAlpha( unsigned char nAlpha );

	virtual int Prepare_DeleteLineEnable( bool isEnable );
	virtual int Prepare_DeleteLine( unsigned int nThick, const Color3B &color, unsigned char nAlpha = 255, float fAnchor = 0.5f );
	virtual int Prepare_DeleteLineThick( unsigned int nThick );
	virtual int Prepare_DeleteLineColor( const Color3B &color );
	virtual int Prepare_DeleteLineAlpha( unsigned char nAlpha );
	virtual int Prepare_DeleteLineAnchor( float fAnchor );

	virtual int Prepare_UnderLineEnable( bool isEnable );
	virtual int Prepare_UnderLine( unsigned int nThick, const Color3B &color, unsigned char nAlpha = 255 );
	virtual int Prepare_UnderLineThick( unsigned int nThick );
	virtual int Prepare_UnderLineColor( const Color3B &color );
	virtual int Prepare_UnderLineAlpha( unsigned char nAlpha );

	virtual int Prepare_Indentation( TextViewFT::IndentationType eType, unsigned int nValue );

	virtual int Make();


	virtual int ChangeText( const char *text, bool isForceRefresh = false );
	virtual int ChangeTextWithBlink( const char *text, float fBlinkDurationTime, unsigned int nBlinkCount );
	virtual int ChangeTextWithBlinkIfDiff( const char *text, float fBlinkDurationTime, unsigned int nBlinkCount );
	virtual int ChangeTextColor( const Color3B &textColor, unsigned char nAlpha = 255, bool isForceRefresh = false );


	virtual Sprite *GetRenderSprite();
	virtual Texture2D *GetTexture();
protected:
	virtual int RenderSprite_UpdateTexture( Texture2D *pTexture );
	virtual int RenderSprite_FixPosition();


public:
	virtual int StartActionOnRenderSprite( Action *pAction );
}; // end class TextViewFT

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__TEXT_VIEW_FT_H__
