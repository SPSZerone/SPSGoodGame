#include "TextViewFT.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Encoding/Encoding.h"
__SPS_GG__NS__U_EXTEND_COCOS;
__SPS_GG__NS__U_ENCODING;



TextViewFT::TextViewFT()
{
	_gg_pFTH_Maker = nullptr;

	_gg_fthTextDefine.ePixelMode = __SPS_GG__NS__N_EXTEND_FREETYPE::PixelMode::RGBA8888;
	_gg_fthTextDefine.eTextAlignHorizontal = __SPS_GG__NS__N_EXTEND_FREETYPE::TextAlignHorizontal::LEFT;

	_gg_fthTextDefine.text_buffer_ucs4 = nullptr;
	_gg_fthTextDefine.text_buffer_ucs2 = nullptr;
	_gg_fthTextDefine.nFontSize = 20;
	_gg_fthTextDefine.textColor.red = 255;
	_gg_fthTextDefine.textColor.green = 255;
	_gg_fthTextDefine.textColor.blue = 255;
	_gg_fthTextDefine.nTextAlpha = 255;

	_gg_fthTextDefine.nLineGap = 2;
	_gg_fthTextDefine.nLineMaxWidth = 0;
	_gg_fthTextDefine.nLineMaxRows = 0;

	_gg_fthTextDefine.bgColor.red = 0;
	_gg_fthTextDefine.bgColor.green = 0;
	_gg_fthTextDefine.bgColor.blue = 0;
	_gg_fthTextDefine.nBGAlpha = 0;

	_gg_fthTextDefine.eIndentationType = __SPS_GG__NS__N_EXTEND_FREETYPE::IndentationType::WORD;
	_gg_fthTextDefine.nIndentationValue = 0;


	_gg_fthStrokeDefine.nStrokeSize = 2;
	_gg_fthStrokeDefine.color.red = 255;
	_gg_fthStrokeDefine.color.green = 255;
	_gg_fthStrokeDefine.color.blue = 255;
	_gg_fthStrokeDefine.nAlpha = 255;


	_gg_fthUnderLineDefine.nThick = 2;
	_gg_fthUnderLineDefine.color.red = 255;
	_gg_fthUnderLineDefine.color.green = 255;
	_gg_fthUnderLineDefine.color.blue = 255;
	_gg_fthUnderLineDefine.nAlpha = 255;


	_gg_fthDeleteLineDefine.nThick = 2;
	_gg_fthDeleteLineDefine.color.red = 255;
	_gg_fthDeleteLineDefine.color.green = 255;
	_gg_fthDeleteLineDefine.color.blue = 255;
	_gg_fthDeleteLineDefine.nAlpha = 255;
	_gg_fthDeleteLineDefine.fAnchor = 0.2f;


	_gg_fthTextTexture.Reset();


	_gg_strText = "";
	_gg_textAnchor = Point::ANCHOR_MIDDLE;


	_gg_isStrokeEnable = false;
	_gg_isUnderLineEnable = false;
	_gg_isDeleteLineEnable = false;
}



TextViewFT::~TextViewFT()
{
}



bool TextViewFT::init()
{
	setContentSize( Size::ZERO );
	return true;
}



void TextViewFT::setAnchorPoint( const Point &anchor )
{
	_gg_textAnchor = anchor;
	RenderSprite_FixPosition();
}



const FTH_TextTexture &TextViewFT::GetTextTexture() const
{
	return _gg_fthTextTexture;
}



Point TextViewFT::GetOriginPosition() const
{
	return GetAnchorPosition( Point::ZERO );
}



Point TextViewFT::GetAnchorPosition( const Point &anchor ) const
{
	Point position;

	Size contentSize = getContentSize();

	if ( ( contentSize.width <= 0 ) || ( _gg_fthTextDefine.nLineMaxWidth > 0 && _gg_fthTextDefine.nLineMaxWidth < contentSize.width ) )
	{
		contentSize.width = _gg_fthTextDefine.nLineMaxWidth;
	}

	if ( contentSize.height <= 0 )
	{
		contentSize.height = _gg_fthTextDefine.nFontSize + ( _gg_fthStrokeDefine.nStrokeSize << 1 ) + _gg_fthUnderLineDefine.nThick;
	}

	position.x = contentSize.width * ( anchor.x - _gg_textAnchor.x );
	position.y = contentSize.height * ( anchor.y - _gg_textAnchor.y );

	return position;
}



Point TextViewFT::GetWorldPosition() const
{
	const Point position = getPosition();
	const Node *pParentNode = getParent();
	if ( pParentNode == nullptr )
	{
		return position;
	}
	return pParentNode->convertToWorldSpace( position );
}



Point TextViewFT::GetTextEndWorldPosition() const
{
	const Point leftTopPositon = GetAnchorPosition( Point::ANCHOR_TOP_LEFT );
	Point position;

	if ( IsTextEmpty() )
	{
		position = GetAnchorPosition( Point::ZERO );
	}
	else
	{
		position.x = leftTopPositon.x + _gg_fthTextTexture.nTextEndPosX;
		position.y = leftTopPositon.y - _gg_fthTextTexture.nTextEndPosY;

		if ( _gg_isStrokeEnable && _gg_fthStrokeDefine.nStrokeSize > 0 )
		{
			position.y -= _gg_fthStrokeDefine.nStrokeSize;
		}
	}

	return convertToWorldSpace( position );
}



float TextViewFT::GetTextBaseLineAnchor() const
{
	const unsigned long nAscHeight = _gg_fthTextTexture.nWordPixelAscenderHeight;
	const unsigned long nDesHeight = _gg_fthTextTexture.nWordPixelDescenderHeight;
	float fAnchor = 1.0 * nDesHeight / ( nAscHeight + nDesHeight );
	if ( fAnchor < 0.0f )
	{
		fAnchor = 0.0f;
	}
	if ( fAnchor > 1.0f )
	{
		fAnchor = 1.0f;
	}
	return fAnchor;
}



const std::string &TextViewFT::GetText() const
{
	return _gg_strText;
}



bool TextViewFT::IsTextEmpty() const
{
	return _gg_strText.empty();
}



int TextViewFT::Prepare_PixelMode( TextViewFT::PixelMode ePixelMode )
{
	switch ( ePixelMode )
	{
	case TextViewFT::PixelMode::RGBA8888:		_gg_fthTextDefine.ePixelMode = __SPS_GG__NS__N_EXTEND_FREETYPE::PixelMode::RGBA8888;		break;
	case TextViewFT::PixelMode::RGB888:			_gg_fthTextDefine.ePixelMode = __SPS_GG__NS__N_EXTEND_FREETYPE::PixelMode::RGB888;			break;
	}

	return 0;
}



int TextViewFT::Prepare_TextAlignHorizontal( TextViewFT::TextAlignHorizontal eTextAlignHorizontal )
{
	switch ( eTextAlignHorizontal )
	{
	case TextViewFT::TextAlignHorizontal::LEFT:			_gg_fthTextDefine.eTextAlignHorizontal = __SPS_GG__NS__N_EXTEND_FREETYPE::TextAlignHorizontal::LEFT;			break;
	case TextViewFT::TextAlignHorizontal::CENTER:		_gg_fthTextDefine.eTextAlignHorizontal = __SPS_GG__NS__N_EXTEND_FREETYPE::TextAlignHorizontal::CENTER;		break;
	case TextViewFT::TextAlignHorizontal::RIGHT:			_gg_fthTextDefine.eTextAlignHorizontal = __SPS_GG__NS__N_EXTEND_FREETYPE::TextAlignHorizontal::RIGHT;			break;
	}

	return 0;
}



int TextViewFT::Prepare_Text( const char *text, unsigned int nFontSize, const Color3B &color, unsigned char nAlpha )
{
	_gg_strText.clear();
	if ( text )
	{
		_gg_strText.append( text );
	}

	_gg_fthTextDefine.nFontSize = nFontSize;

	_gg_fthTextDefine.textColor.red = color.r;
	_gg_fthTextDefine.textColor.green = color.g;
	_gg_fthTextDefine.textColor.blue = color.b;

	_gg_fthTextDefine.nTextAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_Text( const char *text )
{
	if( text == nullptr )
	{
		return -1;
	}

	if ( _gg_strText.compare( text ) == 0 )
	{
		return 1;
	}

	_gg_strText.clear();
	_gg_strText.append( text );

	return 0;
}



int TextViewFT::Prepare_FontSize( unsigned int nFontSize )
{
	if ( _gg_fthTextDefine.nFontSize == nFontSize )
	{
		return 1;
	}

	_gg_fthTextDefine.nFontSize = nFontSize;

	return 0;
}



int TextViewFT::Prepare_TextColor( const Color3B &color )
{
	FTH_Color fthColor( color.r, color.g, color.b );

	if ( _gg_fthTextDefine.textColor == fthColor )
	{
		return 1;
	}

	_gg_fthTextDefine.textColor = fthColor;

	return 0;
}



int TextViewFT::Prepare_TextAlpha( unsigned char nAlpha )
{
	if( _gg_fthTextDefine.nTextAlpha == nAlpha )
	{
		return 1;
	}

	_gg_fthTextDefine.nTextAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_Line( unsigned short nLineGap, unsigned long nLineMaxWidth, unsigned int nLineMaxRows )
{
	_gg_fthTextDefine.nLineGap = nLineGap;
	_gg_fthTextDefine.nLineMaxWidth = nLineMaxWidth;
	_gg_fthTextDefine.nLineMaxRows = nLineMaxRows;

	return 0;
}



int TextViewFT::Prepare_LineGap( unsigned short nLineGap )
{
	if ( _gg_fthTextDefine.nLineGap == nLineGap )
	{
		return 1;
	}

	_gg_fthTextDefine.nLineGap = nLineGap;

	return 0;
}



int TextViewFT::Prepare_LineMaxWidth( unsigned long nLineMaxWidth )
{
	if ( _gg_fthTextDefine.nLineMaxWidth == nLineMaxWidth )
	{
		return 1;
	}

	_gg_fthTextDefine.nLineMaxWidth = nLineMaxWidth;

	return 0;
}



int TextViewFT::Prepare_LineMaxRows( unsigned int nLineMaxRows )
{
	if ( _gg_fthTextDefine.nLineMaxRows == nLineMaxRows )
	{
		return 1;
	}

	_gg_fthTextDefine.nLineMaxRows = nLineMaxRows;

	return 0;
}


	
int TextViewFT::Prepare_BG( const Color3B &color, unsigned char nAlpha )
{
	_gg_fthTextDefine.bgColor.red = color.r;
	_gg_fthTextDefine.bgColor.green = color.g;
	_gg_fthTextDefine.bgColor.blue = color.b;

	_gg_fthTextDefine.nBGAlpha = nAlpha;
	return 0;
}


	
int TextViewFT::Prepare_BGColor( const Color3B &color )
{
	FTH_Color fthColor( color.r, color.g, color.b );

	if ( _gg_fthTextDefine.bgColor == fthColor )
	{
		return 1;
	}

	_gg_fthTextDefine.bgColor = fthColor;

	return 0;
}



int TextViewFT::Prepare_BGAlpha( unsigned char nAlpha )
{
	if ( _gg_fthTextDefine.nBGAlpha == nAlpha )
	{
		return 1;
	}

	_gg_fthTextDefine.nBGAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_StrokeEnable( bool isEnable )
{
	if ( _gg_isStrokeEnable == isEnable )
	{
		return 1;
	}

	_gg_isStrokeEnable = isEnable;

	return 0;
}



int TextViewFT::Prepare_Stroke( unsigned int nStrokeSize, const Color3B &color, unsigned char nAlpha )
{
	Prepare_StrokeEnable( nStrokeSize != 0 );

	_gg_fthStrokeDefine.nStrokeSize = nStrokeSize;

	_gg_fthStrokeDefine.color.red = color.r;
	_gg_fthStrokeDefine.color.green = color.g;
	_gg_fthStrokeDefine.color.blue = color.b;

	_gg_fthStrokeDefine.nAlpha = nAlpha;
	return 0;
}



int TextViewFT::Prepare_StrokeSize( unsigned int nStrokeSize )
{
	if ( _gg_fthStrokeDefine.nStrokeSize == nStrokeSize )
	{
		return 1;
	}

	Prepare_StrokeEnable( nStrokeSize != 0 );
	_gg_fthStrokeDefine.nStrokeSize = nStrokeSize;

	return 0;
}



int TextViewFT::Prepare_StrokeColor( const Color3B &color )
{
	FTH_Color fthColor( color.r, color.g, color.b );

	if ( _gg_fthStrokeDefine.color == fthColor )
	{
		return 1;
	}

	_gg_fthStrokeDefine.color = fthColor;

	return 0;
}



int TextViewFT::Prepare_StrokeAlpha( unsigned char nAlpha )
{
	if ( _gg_fthStrokeDefine.nAlpha == nAlpha )
	{
		return 1;
	}

	_gg_fthStrokeDefine.nAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_DeleteLineEnable( bool isEnable )
{
	if ( _gg_isDeleteLineEnable == isEnable )
	{
		return 1;
	}

	_gg_isDeleteLineEnable = isEnable;

	return 0;
}



int TextViewFT::Prepare_DeleteLine( unsigned int nThick, const Color3B &color, unsigned char nAlpha, float fAnchor )
{
	Prepare_DeleteLineEnable( nThick != 0 );

	_gg_fthDeleteLineDefine.nThick = nThick;

	_gg_fthDeleteLineDefine.color.red = color.r;
	_gg_fthDeleteLineDefine.color.green = color.g;
	_gg_fthDeleteLineDefine.color.blue = color.b;

	_gg_fthDeleteLineDefine.nAlpha = nAlpha;

	_gg_fthDeleteLineDefine.fAnchor = fAnchor;
	_gg_fthDeleteLineDefine.FixAnchor();

	return 0;
}



int TextViewFT::Prepare_DeleteLineThick( unsigned int nThick )
{
	if ( _gg_fthDeleteLineDefine.nThick == nThick )
	{
		return 1;
	}

	Prepare_DeleteLineEnable( nThick != 0 );
	_gg_fthDeleteLineDefine.nThick = nThick;

	return 0;
}



int TextViewFT::Prepare_DeleteLineColor( const Color3B &color )
{
	FTH_Color fthColor( color.r, color.g, color.b );

	if ( _gg_fthDeleteLineDefine.color == fthColor )
	{
		return 1;
	}

	_gg_fthDeleteLineDefine.color = fthColor;

	return 0;
}



int TextViewFT::Prepare_DeleteLineAlpha( unsigned char nAlpha )
{
	if ( _gg_fthDeleteLineDefine.nAlpha == nAlpha )
	{
		return 1;
	}

	_gg_fthDeleteLineDefine.nAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_DeleteLineAnchor( float fAnchor )
{
	if ( _gg_fthDeleteLineDefine.fAnchor == fAnchor )
	{
		_gg_fthDeleteLineDefine.FixAnchor();
		return 1;
	}

	_gg_fthDeleteLineDefine.fAnchor = fAnchor;
	_gg_fthDeleteLineDefine.FixAnchor();

	return 0;
}



int TextViewFT::Prepare_UnderLineEnable( bool isEnable )
{
	if ( _gg_isUnderLineEnable == isEnable )
	{
		return 1;
	}

	_gg_isUnderLineEnable = isEnable;

	return 0;
}



int TextViewFT::Prepare_UnderLine( unsigned int nThick, const Color3B &color, unsigned char nAlpha )
{
	Prepare_UnderLineEnable( nThick != 0 );

	_gg_fthUnderLineDefine.nThick = nThick;

	_gg_fthUnderLineDefine.color.red = color.r;
	_gg_fthUnderLineDefine.color.green = color.g;
	_gg_fthUnderLineDefine.color.blue = color.b;

	_gg_fthUnderLineDefine.nAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_UnderLineThick( unsigned int nThick )
{
	if ( _gg_fthUnderLineDefine.nThick == nThick )
	{
		return 1;
	}

	Prepare_UnderLineEnable( nThick != 0 );
	_gg_fthUnderLineDefine.nThick = nThick;

	return 0;
}



int TextViewFT::Prepare_UnderLineColor( const Color3B &color )
{
	FTH_Color fthColor( color.r, color.g, color.b );

	if ( _gg_fthUnderLineDefine.color == fthColor )
	{
		return 1;
	}

	_gg_fthUnderLineDefine.color = fthColor;

	return 0;
}



int TextViewFT::Prepare_UnderLineAlpha( unsigned char nAlpha )
{
	if ( _gg_fthUnderLineDefine.nAlpha == nAlpha )
	{
		return 1;
	}

	_gg_fthUnderLineDefine.nAlpha = nAlpha;

	return 0;
}



int TextViewFT::Prepare_Indentation( TextViewFT::IndentationType eType, unsigned int nValue )
{
	_gg_fthTextDefine.eIndentationType = ( eType == TextViewFT::IndentationType::PIXEL )
		? __SPS_GG__NS__N_EXTEND_FREETYPE::IndentationType::PIXEL
		: __SPS_GG__NS__N_EXTEND_FREETYPE::IndentationType::WORD;
	_gg_fthTextDefine.nIndentationValue = nValue;

	return 0;
}



int TextViewFT::Make()
{
	if (_gg_pFTH_Maker == nullptr)
	{
		return -1;
	}


	if( _gg_strText.empty() )
	{
		//LOG_E( "TextViewFT_Make", "text is empty" );
		RenderSprite_UpdateTexture( nullptr );
		return -2;
	}

	

	// 1、计算字数
	Utf8StrInfor utf8StrInfor;
	const unsigned long nTextLength = _gg_strText.length();
	const int nGetWordCountResult = Encoding::get_utf8_str_infor( ( const unsigned char * )_gg_strText.c_str(), nTextLength, &utf8StrInfor );
	if ( nGetWordCountResult != 0 )
	{
		return -10;
	}



	// 2、转成UNICODE
	_gg_fthTextDefine.text_buffer_size = utf8StrInfor.nWordCount + 1;
	_gg_fthTextDefine.text_buffer_ucs4 = nullptr;
	_gg_fthTextDefine.text_buffer_ucs2 = nullptr;


	if ( utf8StrInfor.isUCS2 )
	{
		unsigned short *unicode_buffer_ucs2 = new unsigned short[ _gg_fthTextDefine.text_buffer_size ];
		const EncodingResult eEncodingResultUCS2 = Encoding::utf8_to_unicode( _gg_strText.c_str(), nTextLength, unicode_buffer_ucs2, _gg_fthTextDefine.text_buffer_size );
		if( eEncodingResultUCS2 != EncodingResult::OK && eEncodingResultUCS2 != EncodingResult::WARN_HaveNotEndSymbol )
		{
			delete [] unicode_buffer_ucs2;
			unicode_buffer_ucs2 = nullptr;

			return -11;
		}

		_gg_fthTextDefine.text_buffer_ucs2 = unicode_buffer_ucs2;
	}
	else
	{
		unsigned long *unicode_buffer_ucs4 = new unsigned long[ _gg_fthTextDefine.text_buffer_size ];
		const EncodingResult eEncodingResultUCS4 = Encoding::utf8_to_unicode( _gg_strText.c_str(), nTextLength, unicode_buffer_ucs4, _gg_fthTextDefine.text_buffer_size );
		if( eEncodingResultUCS4 != EncodingResult::OK && eEncodingResultUCS4 != EncodingResult::WARN_HaveNotEndSymbol )
		{
			delete [] unicode_buffer_ucs4;
			unicode_buffer_ucs4 = nullptr;

			return -12;
		}

		_gg_fthTextDefine.text_buffer_ucs4 = unicode_buffer_ucs4;
	}



	// 3、创建texture buffer
	int nResult = -1;
	if ( _gg_isStrokeEnable && _gg_fthStrokeDefine.nStrokeSize > 0 )
	{
		nResult = _gg_pFTH_Maker->CreateTextureBuffer( &_gg_fthTextTexture, &_gg_fthTextDefine, &_gg_fthStrokeDefine,
			_gg_isUnderLineEnable ? ( &_gg_fthUnderLineDefine ) : nullptr,
			_gg_isDeleteLineEnable ? ( &_gg_fthDeleteLineDefine ) : nullptr );
	}
	else
	{
		nResult = _gg_pFTH_Maker->CreateTextureBuffer( &_gg_fthTextTexture, &_gg_fthTextDefine,
			_gg_isUnderLineEnable ? ( &_gg_fthUnderLineDefine ) : nullptr,
			_gg_isDeleteLineEnable ? ( &_gg_fthDeleteLineDefine ) : nullptr );
	}


	if ( nResult != 0 )
	{

	}


	// !!! create texture finish, now delete text_buffer_ucsX
	if( _gg_fthTextDefine.text_buffer_ucs4 )
	{
		delete [] ( _gg_fthTextDefine.text_buffer_ucs4 );
		_gg_fthTextDefine.text_buffer_ucs4 = nullptr;
	}

	if( _gg_fthTextDefine.text_buffer_ucs2 )
	{
		delete [] ( _gg_fthTextDefine.text_buffer_ucs2 );
		_gg_fthTextDefine.text_buffer_ucs2 = nullptr;
	}



	// 4、创建精灵
	if ( _gg_fthTextTexture.buffer == nullptr )
	{
		return -20;
	}

	Texture2D *pTexture2D = new Texture2D();
	pTexture2D->autorelease();

	Texture2D::PixelFormat ePixelFormat = Texture2D::PixelFormat::RGBA8888;
	if ( _gg_fthTextDefine.ePixelMode == __SPS_GG__NS__N_EXTEND_FREETYPE::PixelMode::RGBA8888 )
	{
		ePixelFormat = Texture2D::PixelFormat::RGBA8888;
	}
	else if ( _gg_fthTextDefine.ePixelMode == __SPS_GG__NS__N_EXTEND_FREETYPE::PixelMode::RGB888 )
	{
		ePixelFormat = Texture2D::PixelFormat::RGB888;
	}
	pTexture2D->initWithData( _gg_fthTextTexture.buffer, _gg_fthTextTexture.nBufferSize, ePixelFormat,
		_gg_fthTextTexture.nBufferPixelWidth, _gg_fthTextTexture.nBufferPixelHeight,
		Size( _gg_fthTextTexture.nRealPixelWidth, _gg_fthTextTexture.nRealPixelHeight ) );


	_gg_fthTextTexture.DestroyBuffer();

		
	setContentSize( Size( _gg_fthTextTexture.nRealPixelWidth, _gg_fthTextTexture.nRealPixelHeight ) );

	RenderSprite_UpdateTexture( pTexture2D );
	RenderSprite_FixPosition();


	return 0;
}



int TextViewFT::ChangeText( const char *text, bool isForceRefresh )
{
	const int nResult = Prepare_Text( text );
	
	if ( nResult == 0 || isForceRefresh || GetRenderSprite() == nullptr )
	{
		Make();
		return 0;
	}

	return -1;
}



int TextViewFT::ChangeTextWithBlink( const char *text, float fBlinkDurationTime, unsigned int nBlinkCount )
{
	const int nResult = Prepare_Text( text );
	if ( nResult == 0 || GetRenderSprite() == nullptr )
	{
		Make();
	}

	Sprite *pRender = GetRenderSprite();
	if ( pRender )
	{
		pRender->runAction( Blink::create( fBlinkDurationTime, nBlinkCount ) );
	}

	return 0;
}



int TextViewFT::ChangeTextWithBlinkIfDiff( const char *text, float fBlinkDurationTime, unsigned int nBlinkCount )
{
	const int nResult = Prepare_Text( text );
	if ( nResult != 0 && GetRenderSprite() )
	{
		return nResult;
	}
	
	Make();

	Sprite *pRender = GetRenderSprite();
	if ( pRender )
	{
		pRender->runAction( Blink::create( fBlinkDurationTime, nBlinkCount ) );
	}

	return 0;
}



int TextViewFT::ChangeTextColor( const Color3B &textColor, unsigned char nAlpha, bool isForceRefresh )
{
	const int nColorResult = Prepare_TextColor( textColor );
	const int nAlphaResult = Prepare_TextAlpha( nAlpha );
	if ( nColorResult == 0 || nAlphaResult == 0 || isForceRefresh || GetRenderSprite() == nullptr )
	{
		Make();
		return 0;
	}

	return -1;
}



Sprite *TextViewFT::GetRenderSprite()
{
	return dynamic_cast<Sprite *>( getChildByTag( TextViewFT::kTextViewFT_UITag_RENDER ) );
}



Texture2D *TextViewFT::GetTexture()
{
	auto pRenderSprite = GetRenderSprite();
	if ( pRenderSprite == nullptr )
	{
		return nullptr;
	}
	return pRenderSprite->getTexture();
}



int TextViewFT::RenderSprite_UpdateTexture( Texture2D *pTexture )
{
	Sprite *pRenderSprite = GetRenderSprite();
	if ( pRenderSprite )
	{
		removeChild( pRenderSprite, true );
	}

	if ( pTexture == nullptr )
	{
		return -1;
	}
	
	pRenderSprite = Sprite::createWithTexture( pTexture );
	if ( pRenderSprite == nullptr )
	{
		return -2;
	}

	addChild( pRenderSprite, 0, TextViewFT::kTextViewFT_UITag_RENDER );
	pRenderSprite->setAnchorPoint( Point::ANCHOR_TOP_LEFT );

	return 0;
}



int TextViewFT::RenderSprite_FixPosition()
{
	Sprite *pRenderSprite = GetRenderSprite();
	if ( pRenderSprite == nullptr )
	{
		return -1;
	}
	pRenderSprite->setAnchorPoint( Point::ANCHOR_TOP_LEFT );

	const Size contentSize = getContentSize();
	
	pRenderSprite->setPosition( Point( - contentSize.width * _gg_textAnchor.x, contentSize.height * ( 1.0f - _gg_textAnchor.y ) ) );

	return 0;
}



int TextViewFT::StartActionOnRenderSprite( Action *pAction )
{
	if ( pAction == nullptr )
	{
		return -1;
	}

	Sprite *pRenderSprite = GetRenderSprite();
	if ( pRenderSprite == nullptr )
	{
		return -2;
	}
	
	pRenderSprite->runAction( pAction );

	return 0;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
