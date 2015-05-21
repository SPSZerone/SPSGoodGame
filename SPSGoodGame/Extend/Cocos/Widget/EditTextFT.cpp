#include "EditTextFT.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Encoding/Encoding.h"
#include "SPSGoodGame/Extend/FreeType/Util/FTH_Util.h"
__SPS_GG__NS__U_EXTEND_COCOS;
__SPS_GG__NS__U_EXTEND_FREETYPE;
__SPS_GG__NS__U_ENCODING;



EditTextFT::EditTextFT()
{
	_gg_eInputMode = InputMode::ANY;
	_gg_eLineMode = LineMode::SINGLE;
	_gg_editTextAnchor = Point::ANCHOR_MIDDLE;

	_gg_pSingleTouchNode = nullptr;

	_gg_pListener = nullptr;

	_gg_isAttachedIME = false;

	_gg_nMaxWordCount = 0;
	_gg_nRatioOfMBWord = 2;

	_gg_nCursorThick = 3;
	_gg_padding = Point::ZERO;

	_gg_isKeyboardShow = false;
	_gg_InputOrgPos = Point::ZERO;
	_gg_nInputOrgZorder = 0;
}



EditTextFT::~EditTextFT()
{

}



bool EditTextFT::init()
{
	setContentSize( Size::ZERO );

	if ( _gg_pSingleTouchNode == nullptr )
	{
		_gg_pSingleTouchNode = SingleTouchNode::create();
		if ( _gg_pSingleTouchNode )
		{
			addChild( _gg_pSingleTouchNode, kEditTextFT_UITag_TOUCH, kEditTextFT_UITag_TOUCH );
			_gg_pSingleTouchNode->SetListener( this );
		}
	}

	return true;
}



void EditTextFT::onEnter()
{
	Node::onEnter();

	if ( GetCursorNode() == nullptr )
	{
		SetCursor( 3, Color3B( 100, 100, 100 ) );
	}
	
	FixPosition_All();
}



void EditTextFT::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
}



void EditTextFT::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}



void EditTextFT::onExit()
{
	Node::onExit();
}



void EditTextFT::setAnchorPoint( const Point &anchor )
{
	_gg_editTextAnchor = anchor;

	ClipNode *pTextClipNode = GetTextClipNode();
	if ( pTextClipNode )
	{
		pTextClipNode->SetClipAnchor( _gg_editTextAnchor );
	}

	FixPosition_All();
}



void EditTextFT::setContentSize( const Size &contentSize )
{
	Node::setContentSize( contentSize );

	if ( _gg_pSingleTouchNode )
	{
		_gg_pSingleTouchNode->SetTouchSize( contentSize );
	}

	FixPosition_Touch();
	FixPosition_ClipNode();

	UpdateInputWidth();
	UpdateClipSize();
}



void EditTextFT::SetListener( EditTextFTListener *pListener )
{
	_gg_pListener = pListener;
}



const EditTextFTListener *EditTextFT::GetListener() const
{
	return _gg_pListener;
}



bool EditTextFT::IsAttachedIME() const
{
	return _gg_isAttachedIME;
}



const Point EditTextFT::GetOriginPosition() const
{
	return GetAnchorPosition( Point::ZERO );
}



const Point EditTextFT::GetAnchorPosition( const Point &anchor ) const
{
	Point position;

	const Size contentSize = getContentSize();

	position.x = contentSize.width * ( anchor.x - _gg_editTextAnchor.x );
	position.y = contentSize.height * ( anchor.y - _gg_editTextAnchor.y );

	return position;
}



const Point EditTextFT::GetClipOriginPosition()
{
	return GetClipAnchorPosition( Point::ZERO );
}



const Point EditTextFT::GetClipAnchorPosition( const Point &anchor )
{
	ClipNode *pClipNode = GetTextClipNode();
	if ( pClipNode == nullptr )
	{
		return Point::ZERO;
	}
	pClipNode->SetClipAnchor( Point::ANCHOR_MIDDLE );
	return pClipNode->GetAnchorPosition( anchor );
}



const Size EditTextFT::GetClipVisibleSize()
{
	ClipNode *pClipNode = GetTextClipNode();
	if ( pClipNode )
	{
		return pClipNode->GetClipSize();
	}

	Size clipSize = getContentSize();
	clipSize.width -= ( _gg_padding.x * 2 );
	clipSize.height -= ( _gg_padding.y * 2 );

	return clipSize;
}



void EditTextFT::SetInputMode( InputMode eInputMode )
{
	_gg_eInputMode = eInputMode;
}



const EditTextFT::InputMode EditTextFT::GetInputMode() const
{
	return _gg_eInputMode;
}



void EditTextFT::SetLineMode( LineMode eLineMode )
{
	_gg_eLineMode = eLineMode;
}



const EditTextFT::LineMode EditTextFT::GetLineMode() const
{
	return _gg_eLineMode;
}



void EditTextFT::SetMaxWordCount( unsigned long nMaxCount )
{
	_gg_nMaxWordCount = nMaxCount;
}



const unsigned long EditTextFT::GetMaxWordCount() const
{
	return _gg_nMaxWordCount;
}



void EditTextFT::SetRatioOfMBWord( unsigned short nRatio )
{
	if ( nRatio > 0 )
	{
		_gg_nRatioOfMBWord = nRatio;
	}
}



const unsigned short EditTextFT::GetRatioOfMBWord() const
{
	return _gg_nRatioOfMBWord;
}



void EditTextFT::SetPadding( const Point &padding )
{
	_gg_padding = padding;
	
	if ( _gg_padding.x < 0 )
	{
		_gg_padding.x = 0.0f;
	}
	
	if ( _gg_padding.y < 0 )
	{
		_gg_padding.y = 0.0f;
	}

	UpdateClipSize();
}



const Point &EditTextFT::GetPadding() const
{
	return _gg_padding;
}



int EditTextFT::SetBGNode( Node *pBGNode )
{
	Node *pCurBGNode = GetBGNode();
	if ( pCurBGNode )
	{
		if ( pCurBGNode == pBGNode )
		{
			return 1;
		}

		pCurBGNode->removeFromParentAndCleanup( true );
	}

	if ( pBGNode == nullptr )
	{
		return -1;
	}

	addChild( pBGNode, kEditTextFT_UITag_BG, kEditTextFT_UITag_BG );

	const Size bgSize = pBGNode->getContentSize();
	setContentSize( Size( bgSize.width * pBGNode->getScaleX(), bgSize.height * pBGNode->getScaleY() ) );

	FixPosition_BG();

	return 0;
}



Node *EditTextFT::GetBGNode()
{
	return getChildByTag( kEditTextFT_UITag_BG );
}



ClipNode *EditTextFT::GetTextClipNode()
{
	ClipNode *pClipNode = dynamic_cast<ClipNode *>( getChildByTag( kEditTextFT_UITag_TEXT_CLIP ) );
	if ( pClipNode == nullptr )
	{
		pClipNode = ClipNode::create();
		pClipNode->SetClipSize( getContentSize() );
		addChild( pClipNode, kEditTextFT_UITag_TEXT_CLIP, kEditTextFT_UITag_TEXT_CLIP );
	}
	return pClipNode;
}



TextViewFT *EditTextFT::GetHintNode()
{
	ClipNode *pTextClipNode = GetTextClipNode();
	if ( pTextClipNode == nullptr )
	{
		return nullptr;
	}
	TextViewFT *pNode = dynamic_cast<TextViewFT *>( pTextClipNode->getChildByTag( kEditTextFT_TextTag_HINT ) );
	if ( pNode == nullptr )
	{
		pNode = TextViewFT::create();
		pTextClipNode->addChild( pNode, kEditTextFT_TextTag_HINT, kEditTextFT_TextTag_HINT );
	}
	return pNode;
}



TextViewFT *EditTextFT::GetInputNode()
{
	ClipNode *pTextClipNode = GetTextClipNode();
	if ( pTextClipNode == nullptr )
	{
		return nullptr;
	}
	TextViewFT *pNode = dynamic_cast<TextViewFT *>( pTextClipNode->getChildByTag( kEditTextFT_TextTag_INPUT ) );
	if ( pNode == nullptr )
	{
		pNode = TextViewFT::create();
		pTextClipNode->addChild( pNode, kEditTextFT_TextTag_INPUT, kEditTextFT_TextTag_INPUT );
	}
	return pNode;
}



Sprite *EditTextFT::GetCursorNode()
{
	return dynamic_cast<Sprite *>( getChildByTag( kEditTextFT_UITag_CURSOR ) );
}



int EditTextFT::ClearInputText()
{
	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode == nullptr )
	{
		return -1;
	}
	
	SetHintNodeVisible( true );
	pInputNode->ChangeText( "" );

	UpdateCursorPosition();

	return 0;
}



int EditTextFT::SetHintNodeVisible( bool isVisible )
{
	TextViewFT *pHintNode = GetHintNode();
	if ( pHintNode == nullptr )
	{
		return -1;
	}

	pHintNode->setVisible( isVisible );
	return 0;
}



int EditTextFT::SetHintText( const char *text )
{
	TextViewFT *pHintNode = GetHintNode();
	if ( pHintNode == nullptr )
	{
		return -1;
	}

	return pHintNode->ChangeText( text );
}



const std::string &EditTextFT::GetHintText()
{
	TextViewFT *pHintNode = GetHintNode();
	if ( pHintNode == nullptr )
	{
		return STD_STRING_EMPTY;
	}

	return pHintNode->GetText();
}



int EditTextFT::SetInputText( const char *text )
{
	ClearInputText();
	return InsertInputText( text );
}



const std::string &EditTextFT::GetInputText()
{
	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode == nullptr )
	{
		return STD_STRING_EMPTY;
	}

	return pInputNode->GetText();
}



const unsigned long EditTextFT::GetInputWordCount()
{
	std::string strInputText = GetInputText();
	if ( strInputText.empty() )
	{
		return 0;
	}

	Utf8StrInfor utf8StrInfor;
	Encoding::get_utf8_str_infor( ( const unsigned char * )strInputText.c_str(), strInputText.length(), &utf8StrInfor );

	return utf8StrInfor.nWordRealCountOf1Byte + ( utf8StrInfor.nWordRealCount - utf8StrInfor.nWordRealCountOf1Byte ) * _gg_nRatioOfMBWord;
}



int EditTextFT::SetCursor( unsigned int nThick, const Color3B &color )
{
	if ( nThick > 0 )
	{
		_gg_nCursorThick = nThick;
	}

	unsigned int nFontSize = 20;
	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode )
	{
		nFontSize = pInputNode->_gg_fthTextDefine.nFontSize;// + ( pInputNode->_gg_isStrokeEnable ? pInputNode->_gg_fthStrokeDefine.nStrokeSize * 2 : 0 );
	}

	Texture2D *pTexture2D = new Texture2D();
	pTexture2D->autorelease();

	const unsigned int nPixelWidth = FTH_Util::next_power_of_2( _gg_nCursorThick );
	const unsigned int nPixelHeight = FTH_Util::next_power_of_2( nFontSize );
	const unsigned long nBufferWidth = nPixelWidth << 2;
	const unsigned long nBufferSize = nBufferWidth * nPixelHeight;

	unsigned char *buffer = new unsigned char[ nBufferSize ];
	memset( buffer, 0, nBufferSize );

	for ( unsigned int y = 0; y < nPixelHeight; y++ )
	{
		for ( unsigned int x = 0; x < nPixelWidth; x++ )
		{
			const unsigned long nTextureBufferIndex = y * nBufferWidth + ( x << 2 );
			if ( nTextureBufferIndex >= nBufferSize )
			{
				continue;
			}

			buffer[ nTextureBufferIndex ] = color.r;
			buffer[ nTextureBufferIndex + 1 ] = color.g;
			buffer[ nTextureBufferIndex + 2 ] = color.b;
			buffer[ nTextureBufferIndex + 3 ] = 255;
		}
	}
	if ( pTexture2D->initWithData( buffer, nBufferSize, Texture2D::PixelFormat::RGBA8888, nPixelWidth, nPixelHeight, Size( _gg_nCursorThick, nFontSize ) ) )
	{
		SetCursorTexture( pTexture2D );
	}

	CC_SAFE_DELETE_ARRAY( buffer );

	return 0;
}



int EditTextFT::SetCursorTexture( Texture2D *pTexture )
{
	Sprite *pCursorSprite = GetCursorNode();
	if ( pCursorSprite )
	{
		removeChild( pCursorSprite, true );
	}

	if ( pTexture == nullptr )
	{
		return -1;
	}

	pCursorSprite = Sprite::createWithTexture( pTexture );
	if ( pCursorSprite == nullptr )
	{
		return -2;
	}

	addChild( pCursorSprite, kEditTextFT_UITag_CURSOR, kEditTextFT_UITag_CURSOR );
	pCursorSprite->setVisible( false );

	pCursorSprite->runAction( RepeatForever::create( Sequence::createWithTwoActions(
		FadeOut::create( 0.3f ), FadeIn::create( 0.3f )
		) ) );

	return 0;
}



bool EditTextFT::IsInsertTextAvailable( const char *text )
{
	if ( text == nullptr || strlen( text ) <= 0 )
	{
		return false;
	}


	const unsigned int nLength = strlen( text );


	if ( nLength == 1 && ( text[ 0 ] == '\r' || text[ 0 ] == '\n' ) )
	{
		detachWithIME();
		return false;
	}


	if ( _gg_eInputMode == InputMode::ANY )
	{
		if ( _gg_eLineMode == LineMode::SINGLE )
		{
			for ( unsigned int i = 0; i < nLength; i++ )
			{
				const char itemChar = text[ i ];
				if ( itemChar == '\n' || itemChar == '\r' )
				{
					return false;
				}
			}
		}
		return true;
	}


	if ( _gg_eInputMode == InputMode::ONLY_NUM )
	{
		for ( unsigned int i = 0; i < nLength; i++ )
		{
			const char itemChar = text[ i ];
			if ( itemChar < '0' || itemChar > '9' )
			{
				return false;
			}
		}

		return true;
	}


	if ( _gg_eInputMode == InputMode::ONLY_CHARACTER )
	{
		for ( unsigned int i = 0; i < nLength; i++ )
		{
			const char itemChar = text[ i ];
			if ( itemChar <= 32 || itemChar > 126 )
			{
				return false;
			}
		}

		return true;
	}


	return false;
}



int EditTextFT::InsertInputText( const char *text )
{
	if ( text == nullptr || strlen( text ) <= 0 )
	{
		return -1;
	}


	if ( IsInsertTextAvailable( text ) == false )
	{
		return -2;
	}


	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode == nullptr )
	{
		return -3;
	}
	SetHintNodeVisible( false );


	const std::string strCurrentInputText = GetInputText();
	const std::string strInsertText( text );

	std::string strNewInputText;
	strNewInputText.append( strCurrentInputText );


	if ( _gg_nMaxWordCount == 0 )
	{
		strNewInputText.append( strInsertText );
		pInputNode->ChangeText( strNewInputText.c_str() );
		FixPosition_Input();
		return 0;
	}

	
	Utf8StrInfor utf8StrInfor;


	// 字数已经最大
	Encoding::get_utf8_str_infor( ( const unsigned char * )strCurrentInputText.c_str(), strCurrentInputText.length(), &utf8StrInfor );
	const unsigned long nCurrentRealCount = ( ( utf8StrInfor.nWordRealCount - utf8StrInfor.nWordRealCountOf1Byte ) * _gg_nRatioOfMBWord ) + utf8StrInfor.nWordRealCountOf1Byte;
	if ( nCurrentRealCount >= _gg_nMaxWordCount )
	{
		return 1;
	}


	const unsigned long nRemainInsertCount = _gg_nMaxWordCount - nCurrentRealCount;


	Encoding::get_utf8_str_infor( ( const unsigned char * )strInsertText.c_str(), strInsertText.length(), &utf8StrInfor );
	const unsigned long nInsertRealCount = ( ( utf8StrInfor.nWordRealCount - utf8StrInfor.nWordRealCountOf1Byte ) * _gg_nRatioOfMBWord ) + utf8StrInfor.nWordRealCountOf1Byte;


	// 剩余字数足够，可以添加
	if ( nInsertRealCount <= nRemainInsertCount )
	{
		strNewInputText.append( strInsertText );
		pInputNode->ChangeText( strNewInputText.c_str() );
		FixPosition_Input();
		return 0;
	}


	unsigned long nStartIndex = 0xFFFFFFFF;
	unsigned long nEndIndex = 0xFFFFFFFF;
	const int nResult = Encoding::get_real_word_index_in_utf8_str( ( const unsigned char * )strInsertText.c_str(), strInsertText.length(),
		nRemainInsertCount, _gg_nRatioOfMBWord, nStartIndex, nEndIndex );
	if ( nResult != 0 || nStartIndex == 0xFFFFFFFF || nEndIndex == 0xFFFFFFFF )
	{
		return 2;
	}


	const unsigned long nSubIndex = ( nEndIndex + 1 ) <= strInsertText.length() - 1 ? ( nEndIndex + 1 ) : strInsertText.length() - 1;


	const std::string strRemainInsert = strInsertText.substr( 0, nSubIndex );
	strNewInputText.append( strRemainInsert );
	pInputNode->ChangeText( strNewInputText.c_str() );
	FixPosition_Input();


	const std::string strDropedInsert = strInsertText.substr( nSubIndex );
	

	return 10;
}



int EditTextFT::DeleteBackInputText()
{
	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode == nullptr )
	{
		return -1;
	}

	
	const std::string strCurrentInputText = GetInputText();
	const unsigned int nCurLength = strCurrentInputText.length();
	if ( nCurLength <= 0 )
	{
		//LOG_D( "EditTextFT", "DeleteBackInputText >> input text empty" );
		return 1;
	}


	unsigned int nDeleteLength = 1;
	while( 0x80 == ( 0xC0 & strCurrentInputText.at( nCurLength - nDeleteLength ) ) )
	{
		++nDeleteLength;
	}


	if ( nCurLength <= nDeleteLength )
	{
		ClearInputText();
		return 2;
	}


	const std::string strNewText = strCurrentInputText.substr( 0, nCurLength - nDeleteLength );
	SetInputText( strNewText.c_str() );


	return 0;
}



int EditTextFT::FixPosition_All()
{
	FixPosition_BG();
	FixPosition_Touch();
	FixPosition_ClipNode();
	FixPosition_Hint();
	FixPosition_Input();

	return 0;
}



int EditTextFT::FixPosition_BG()
{
	Node *pBGNode = GetBGNode();
	if ( pBGNode == nullptr )
	{
		return -1;
	}
	pBGNode->setAnchorPoint( Point::ANCHOR_TOP_LEFT );

	const Size contentSize = pBGNode->getContentSize();

	pBGNode->setPosition( Point( - contentSize.width * pBGNode->getScaleX() * _gg_editTextAnchor.x, contentSize.height * pBGNode->getScaleY() * ( 1.0f - _gg_editTextAnchor.y ) ) );

	return 0;
}



int EditTextFT::FixPosition_Touch()
{
	if ( _gg_pSingleTouchNode == nullptr )
	{
		return -1;
	}

	const Size contentSize = _gg_pSingleTouchNode->GetTouchSize();

	_gg_pSingleTouchNode->setPosition( Point( contentSize.width * 0.5f - contentSize.width * _gg_editTextAnchor.x,
		-contentSize.height * 0.5f + contentSize.height * ( 1.0f - _gg_editTextAnchor.y ) ) );

	return 0;
}



int EditTextFT::FixPosition_ClipNode()
{
	ClipNode *pClipNode = GetTextClipNode();
	if ( pClipNode == nullptr )
	{
		return -1;
	}
	pClipNode->setAnchorPoint( Point::ANCHOR_MIDDLE );
	
	pClipNode->setPosition( GetAnchorPosition( Point::ANCHOR_MIDDLE ) );

	return 0;
}



int EditTextFT::FixPosition_Hint()
{
	TextViewFT *pHintNode = GetHintNode();
	if ( pHintNode == nullptr )
	{
		return -1;
	}

	Point position;

	if ( _gg_eLineMode == LineMode::SINGLE )
	{
		pHintNode->setAnchorPoint( Point::ANCHOR_MIDDLE_LEFT );
		position = GetClipAnchorPosition( Point::ANCHOR_MIDDLE_LEFT );
	}
	else if ( _gg_eLineMode == LineMode::MULTIPLE )
	{
		pHintNode->setAnchorPoint( Point::ANCHOR_TOP_LEFT );
		position = GetClipAnchorPosition( Point::ANCHOR_TOP_LEFT );
	}

	pHintNode->setPosition( position );

	return 0;
}



int EditTextFT::FixPosition_Input()
{
	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode == nullptr )
	{
		return -1;
	}

	const Size inputContentSize = pInputNode->getContentSize();
	const Size clipVisibleSize = GetClipVisibleSize();
	Point position = Point::ZERO;

	if ( _gg_eLineMode == LineMode::SINGLE )
	{
		pInputNode->setAnchorPoint( Point::ANCHOR_MIDDLE_LEFT );

		position = GetClipAnchorPosition( Point::ANCHOR_MIDDLE_LEFT );

		if ( inputContentSize.width > clipVisibleSize.width )
		{
			position.x -= inputContentSize.width;
			position.x += clipVisibleSize.width;
		}
	}
	else if ( _gg_eLineMode == LineMode::MULTIPLE )
	{
		pInputNode->setAnchorPoint( Point::ANCHOR_TOP_LEFT );

		position = GetClipAnchorPosition( Point::ANCHOR_TOP_LEFT );

		if ( inputContentSize.height > clipVisibleSize.height )
		{
			position.y += inputContentSize.height;
			position.y -= clipVisibleSize.height;
		}
	}

	pInputNode->setPosition( position );

	UpdateCursorPosition();

	return 0;
}



int EditTextFT::UpdateInputWidth()
{
	TextViewFT *pInputText = GetInputNode();
	if ( pInputText == nullptr )
	{
		return -1;
	}

	Size contentSize = getContentSize();
	contentSize.width -= ( _gg_padding.x * 2 );

	if ( _gg_eLineMode == LineMode::SINGLE )
	{
		pInputText->Prepare_Line( 0, 0, 0 );
	}
	else if ( _gg_eLineMode == LineMode::MULTIPLE )
	{
		pInputText->Prepare_Line( 2, contentSize.width, 0 );
	}

	return 0;
}



int EditTextFT::UpdateCursorPosition()
{
	Sprite *pCursorNode = GetCursorNode();
	if ( pCursorNode == nullptr )
	{
		return -1;
	}

	pCursorNode->setVisible( _gg_isAttachedIME );

	TextViewFT *pInputNode = GetInputNode();
	if ( pInputNode == nullptr )
	{
		return -2;
	}

	const Size cursorContentSize = pCursorNode->getContentSize();
	Point cursorPosition = Point::ZERO;

	if ( pInputNode->IsTextEmpty() )
	{
		pCursorNode->setAnchorPoint( Point::ANCHOR_MIDDLE_LEFT );

		if ( _gg_eLineMode == LineMode::SINGLE )
		{
			cursorPosition = GetAnchorPosition( Point::ANCHOR_MIDDLE_LEFT );
		}
		else
		{
			cursorPosition = GetAnchorPosition( Point::ANCHOR_TOP_LEFT );
			cursorPosition.y -= ( _gg_padding.y + cursorContentSize.height * 0.5f );
		}

		cursorPosition.x += _gg_padding.x;
	}
	else
	{
		pCursorNode->setAnchorPoint( Point( 0.0f, pInputNode->GetTextBaseLineAnchor() ) );

		cursorPosition = convertToNodeSpace( pInputNode->GetTextEndWorldPosition() );

		const Point rightBottomPosition = GetAnchorPosition( Point::ANCHOR_BOTTOM_RIGHT );
		const float fCursorMaxX = rightBottomPosition.x - _gg_padding.x - cursorContentSize.width;
		if ( cursorPosition.x > fCursorMaxX )
		{
			cursorPosition.x = fCursorMaxX;
		}
	}
	
	pCursorNode->setPosition( cursorPosition );

	return 0;
}



int EditTextFT::UpdateClipSize()
{
	ClipNode *pClipNode = GetTextClipNode();
	if ( pClipNode == nullptr )
	{
		return -1;
	}

	Size contentSize = getContentSize();
	contentSize.width -= ( _gg_padding.x * 2 );
	contentSize.height -= ( _gg_padding.y * 2 );
	pClipNode->SetClipSize( contentSize );

	return 0;
}



void EditTextFT::SetSlotTouchEnable( bool isEnable )
{
	if ( _gg_pSingleTouchNode )
	{
		_gg_pSingleTouchNode->SetTouchEnable( isEnable );
	}
}



int EditTextFT::SetTouchPrioritySwallow( int nPriorty )
{
	if ( _gg_pSingleTouchNode )
	{
		_gg_pSingleTouchNode->RegisterTouchEventListener( SingleTouchNode::RegisterTouchEventType::SCENE_GRAPH_PRIORITY, nPriorty, false );
	}

	_eventDispatcher->removeEventListenersForTarget( this );

	// Keyboard Listener
	auto pKeyboardListener = EventListenerKeyboard::create();

	pKeyboardListener->onKeyPressed = CC_CALLBACK_2( EditTextFT::OnKeyPressed, this );
	pKeyboardListener->onKeyReleased = CC_CALLBACK_2( EditTextFT::OnKeyReleased, this );
    
	_eventDispatcher->addEventListenerWithSceneGraphPriority( pKeyboardListener, this );

	return 0;
}



void EditTextFT::OnKeyPressed( EventKeyboard::KeyCode keyCode, Event *pEvent )
{
	
}
    


void EditTextFT::OnKeyReleased( EventKeyboard::KeyCode keyCode, Event *pEvent )
{
	if ( _gg_isAttachedIME && keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
    {
		DeleteBackInputText();
    }
}



int EditTextFT::SingleTouch_OnTouchBegin_Pre( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	if ( pSingleTouch && pSingleTouch->IsTouchMe( pTouch ) )
	{
		attachWithIME();
	}
	else
	{
		detachWithIME();
	}

	return 0;
}



int EditTextFT::SingleTouch_OnTouchBegin( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	return 0;
}



int EditTextFT::SingleTouch_OnTouchDouble( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	return 0;
}



int EditTextFT::SingleTouch_OnTouchLong( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	return 0;
}



int EditTextFT::SingleTouch_OnTouchMoved( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	return 0;
}



int EditTextFT::SingleTouch_OnTouchEnded( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	return 0;
}



int EditTextFT::SingleTouch_OnTouchCancelled( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	return 0;
}



bool EditTextFT::attachWithIME()
{
	_gg_isAttachedIME = IMEDelegate::attachWithIME();

	//_GG_LOG_D( "EditTextFT", "attachWithIME >> %d", _gg_isAttachedIME );

	if ( _gg_isAttachedIME )
	{
		GLView *pGlView = Director::getInstance()->getOpenGLView();
		if ( pGlView )
		{
			pGlView->setIMEKeyboardState( true );
		}
	}

	UpdateCursorPosition();

	return _gg_isAttachedIME;
}



bool EditTextFT::detachWithIME()
{
	const bool isDetach = IMEDelegate::detachWithIME();
	
	//_GG_LOG_D( "EditTextFT", "detachWithIME >> %d", isDetach );

	if ( isDetach )
	{
		GLView *pGlView = Director::getInstance()->getOpenGLView();
		if ( pGlView )
		{
			pGlView->setIMEKeyboardState( false );
		}
	}

	_gg_isAttachedIME = false;

	UpdateCursorPosition();

	return isDetach;
}



bool EditTextFT::canAttachWithIME()
{
	//_GG_LOG_D( "EditTextFT", "canAttachWithIME" );
	return true;
}



void EditTextFT::didAttachWithIME()
{
	//_GG_LOG_D( "EditTextFT", "didAttachWithIME" );
}



bool EditTextFT::canDetachWithIME()
{
	//_GG_LOG_D( "EditTextFT", "canDetachWithIME" );
	return true;
}



void EditTextFT::didDetachWithIME()
{
	//_GG_LOG_D( "EditTextFT", "didDetachWithIME" );
}



void EditTextFT::insertText( const char *text, size_t nLength )
{
	if ( _gg_pListener )
	{
		_gg_pListener->EditTextFT_InsertText_Before( this, text );
	}
	
	InsertInputText( text );

	if ( _gg_pListener )
	{
		_gg_pListener->EditTextFT_InsertText_After( this, text );
	}
}



void EditTextFT::deleteBackward()
{
	if ( _gg_pListener )
	{
		_gg_pListener->EditTextFT_DeleteBack_Before( this );
	}

	DeleteBackInputText();

	if ( _gg_pListener )
	{
		_gg_pListener->EditTextFT_DeleteBack_After( this );
	}
}



const std::string &EditTextFT::getContentText()
{
	return GetInputText();
}



void EditTextFT::keyboardWillShow( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo )
{
	if ( _gg_isKeyboardShow == false )
	{
		_gg_InputOrgPos = getPosition();
		_gg_nInputOrgZorder = getLocalZOrder();
	}

	if ( _gg_isAttachedIME == false )
	{
		return ;
	}

	_gg_isKeyboardShow = true;

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )

	const Size keyboardSize = imeKeyboardNotificationInfo.end.size;
	const Point visibleOrigin = Director::getInstance()->getVisibleOrigin();
	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Point position = Point( visibleOrigin.x + visibleSize.width * 0.5f - getContentSize().width * ( 0.5f - _gg_editTextAnchor.x ),
		visibleOrigin.y + keyboardSize.height + getContentSize().height * _gg_editTextAnchor.y );
		//visibleOrigin.y + visibleSize.height - getContentSize().height * ( 1.0f - _gg_editTextAnchor.y ) );

	Node *pParentNode = getParent();
	if ( pParentNode )
	{
		setPosition( pParentNode->convertToNodeSpace( position ) );
	}
	else
	{
		setPosition( position );
	}

	setZOrder( 0x7FFF );

#endif
}



void EditTextFT::keyboardDidShow( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo )
{
	
}



void EditTextFT::keyboardWillHide( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo )
{
	

	_gg_isKeyboardShow = false;

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	setPosition( _gg_InputOrgPos );
	setZOrder( _gg_nInputOrgZorder );
#endif
}



void EditTextFT::keyboardDidHide( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo )
{
	
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
