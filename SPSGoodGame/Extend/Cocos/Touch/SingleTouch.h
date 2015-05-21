#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_TOUCH__SINGLE_TOUCH_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_TOUCH__SINGLE_TOUCH_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "cocos2d.h"
USING_NS_CC;



#define SingleTouchDoubleTouchDeltaMilliSecond     500



__SPS_GG__NS__B_EXTEND_COCOS

class SingleTouch;
class SingleTouchListener
{
public:
	// 返回0，检查touch区域
	virtual int SingleTouch_OnTouchBegin_Pre( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
	virtual int SingleTouch_OnTouchBegin( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
	virtual int SingleTouch_OnTouchDouble( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
	virtual int SingleTouch_OnTouchLong( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
	virtual int SingleTouch_OnTouchMoved( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
	virtual int SingleTouch_OnTouchEnded( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
	virtual int SingleTouch_OnTouchCancelled( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent ) { return 0; }
};


class SingleTouch
{
public:
	enum class State
	{
		UNKNOWN,
		WAITING,
		DOUBLE,
	};

protected:
	EventListenerTouchOneByOne *_gg_pEventListenerTouch;
	SingleTouchListener *_gg_pListener;

	bool _gg_isTouchEnable;
	int _gg_nTouchPriority;
	bool _gg_isSwallowTouch;
	unsigned int _gg_nDoubleTouchInternalTime;
	Rect _gg_TouchRect;

	Point _gg_TouchBeginPosition;
	timeval _gg_LastTouchTime;
	State _gg_eState;



public:
	SingleTouch();
	virtual ~SingleTouch();

	
	virtual void SetTouchEnable( bool isEnable );
	virtual bool IsTouchEnable() const;
	virtual void SetTouchRect( const Rect &rect );
	virtual Rect GetTouchRect() const;
	virtual int RegisterTouchEventListener( int nNewTouchPriority, bool isSwallowTouch = true );


	virtual bool IsTouchMe( Touch *pTouch ) const;
	virtual Point GetTouchBeginPosition() const;	
	virtual void ResetLastTouchTime();
	virtual State GetState() const;
	virtual bool IsDoubleTouch() const;
	virtual void SetDoubleTouchInternalTime( unsigned int nMilliSecond );


	virtual void SetListener( SingleTouchListener *pListener );
	virtual SingleTouchListener *GetListener() const;


	virtual void Step( float dt );


	virtual bool OnTouchBegan( Touch *pTouch, Event *pEvent );
	virtual void OnTouchMoved( Touch *pTouch, Event *pEvent );
	virtual void OnTouchEnded( Touch *pTouch, Event *pEvent );
	virtual void OnTouchCancelled( Touch *pTouch, Event *pEvent );

}; // end class SingleTouch

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // __SPS__GOOD_GAME__EXTEND_COCOS_TOUCH__SINGLE_TOUCH_H__
