#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__EDIT_TEXT_FT_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__EDIT_TEXT_FT_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )
#include "SPSGoodGame/Extend/Cocos/Widget/TextViewFT.h"
#include "SPSGoodGame/Extend/Cocos/Node/SingleTouchNode.h"
#include "SPSGoodGame/Extend/Cocos/Node/ClipNode.h"
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_EXTEND_COCOS

class EditTextFT;
class EditTextFTListener
{
public:
	virtual int EditTextFT_InsertText_Before( EditTextFT *pEditTextFT, const char *insert_text ) { return 0; }
	virtual int EditTextFT_InsertText_After( EditTextFT *pEditTextFT, const char *insert_text ) { return 0; }
	virtual int EditTextFT_DeleteBack_Before( EditTextFT *pEditTextFT ) { return 0; }
	virtual int EditTextFT_DeleteBack_After( EditTextFT *pEditTextFT ) { return 0; }
};

class EditTextFT : public Node, public IMEDelegate, public SingleTouchListener
{
public:
	enum class InputMode
	{
		ANY,
		ONLY_NUM,
		ONLY_CHARACTER,
	};

	enum class LineMode
	{
		SINGLE,
		MULTIPLE,
	};
	
	enum UITag
	{
		kEditTextFT_UITag_BG,
		kEditTextFT_UITag_TOUCH,
		kEditTextFT_UITag_TEXT_CLIP,
		kEditTextFT_UITag_CURSOR,
	};

	enum TextTag
	{
		kEditTextFT_TextTag_HINT,
		kEditTextFT_TextTag_INPUT,
	};

protected:
	InputMode _gg_eInputMode;
	LineMode _gg_eLineMode;
	Point _gg_editTextAnchor;

	SingleTouchNode *_gg_pSingleTouchNode;

	EditTextFTListener *_gg_pListener;

	bool _gg_isAttachedIME;

	unsigned long _gg_nMaxWordCount;
	unsigned short _gg_nRatioOfMBWord; // 多字节的字符代表几个字

	unsigned int _gg_nCursorThick;
	Point _gg_padding;// x:Horizontal, y:Vertical

	bool _gg_isKeyboardShow;
	// 初始位置（用于：弹出键盘时自动调整位置）
	Point _gg_InputOrgPos;
	int _gg_nInputOrgZorder;


public:
	CREATE_FUNC( EditTextFT );
	EditTextFT();
	virtual ~EditTextFT();
	virtual bool init() override;
	

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExitTransitionDidStart() override;
	virtual void onExit() override;

	virtual void setAnchorPoint( const Point &anchor ) override;
	virtual void setContentSize( const Size &contentSize ) override;

	virtual void SetListener( EditTextFTListener *pListener );
	virtual const EditTextFTListener *GetListener() const;
	virtual bool IsAttachedIME() const;

	
	/* 坐标系EditTextFT
		以左下角为起点
	*/
	virtual const Point GetOriginPosition() const;
	// 相对坐标：0~1 e.g. 左下角、右下角、中心
	virtual const Point GetAnchorPosition( const Point &anchor ) const;


	// 坐标系EditTextFT
	virtual const Point GetClipOriginPosition();
	virtual const Point GetClipAnchorPosition( const Point &anchor );
	virtual const Size GetClipVisibleSize();

	virtual void SetInputMode( InputMode eInputMode );
	virtual const InputMode GetInputMode() const;

	virtual void SetLineMode( LineMode eLineMode );
	virtual const LineMode GetLineMode() const;

	virtual void SetMaxWordCount( unsigned long nMaxCount );
	virtual const unsigned long GetMaxWordCount() const;
	virtual void SetRatioOfMBWord( unsigned short nRatio );
	virtual const unsigned short GetRatioOfMBWord() const;

	virtual void SetPadding( const Point &padding );
	virtual const Point &GetPadding() const;

	virtual int SetBGNode( Node *pBGNode );
	virtual Node *GetBGNode();
	virtual ClipNode *GetTextClipNode();
	virtual TextViewFT *GetHintNode();
	virtual TextViewFT *GetInputNode();
	virtual Sprite *GetCursorNode();

	virtual int ClearInputText();
	virtual int SetHintNodeVisible( bool isVisible );

	virtual int SetHintText( const char *text );
	virtual const std::string &GetHintText();

	virtual int SetInputText( const char *text );
	virtual const std::string &GetInputText();
	virtual const unsigned long GetInputWordCount();


	virtual int SetCursor( unsigned int nThick, const Color3B &color );
	virtual int SetCursorTexture( Texture2D *pTexture );


	virtual bool IsInsertTextAvailable( const char *text );


protected:
	virtual int InsertInputText( const char *text );
	virtual int DeleteBackInputText();

	
	virtual int FixPosition_All();
	virtual int FixPosition_BG();
	virtual int FixPosition_Touch();
	virtual int FixPosition_ClipNode();
	virtual int FixPosition_Hint();
	virtual int FixPosition_Input();


	virtual int UpdateInputWidth();
	virtual int UpdateCursorPosition();
	virtual int UpdateClipSize();


public:
	virtual void SetSlotTouchEnable( bool isEnable );
	virtual int SetTouchPrioritySwallow( int nNewTouchPriority );


	virtual void OnKeyPressed( EventKeyboard::KeyCode keyCode, Event *pEvent );
    virtual void OnKeyReleased( EventKeyboard::KeyCode keyCode, Event *pEvent );


	// ========== SingleTouchListener [ begin ] ==========
public:
	virtual int SingleTouch_OnTouchBegin_Pre( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	virtual int SingleTouch_OnTouchBegin( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	virtual int SingleTouch_OnTouchDouble( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	virtual int SingleTouch_OnTouchLong( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	virtual int SingleTouch_OnTouchMoved( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	virtual int SingleTouch_OnTouchEnded( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	virtual int SingleTouch_OnTouchCancelled( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) override;
	// ========== SingleTouchListener [ begin ] ==========


	// ========== IMEDelegate [ begin ] ==========
public:
    virtual bool attachWithIME() override;
    virtual bool detachWithIME() override;


protected:
    virtual bool canAttachWithIME() override;
    virtual void didAttachWithIME() override;

    virtual bool canDetachWithIME() override;
    virtual void didDetachWithIME() override;

    virtual void insertText( const char *text, size_t nLength ) override;
    virtual void deleteBackward() override;

	virtual const std::string& getContentText() override;

    virtual void keyboardWillShow( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo ) override;
    virtual void keyboardDidShow( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo ) override;
    virtual void keyboardWillHide( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo ) override;
    virtual void keyboardDidHide( IMEKeyboardNotificationInfo &imeKeyboardNotificationInfo ) override;
	// ========== IMEDelegate [ end ] ==========
}; // end class EditTextFT

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) && ( defined( __SPS_GG__SUPPORT__FREE_TYPE ) ) && ( __SPS_GG__SUPPORT__FREE_TYPE ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__EDIT_TEXT_FT_H__
