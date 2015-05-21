#include "SingleTouch.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



SingleTouch::SingleTouch()
{
	_gg_pEventListenerTouch = nullptr;

	_gg_pListener = nullptr;

	_gg_isTouchEnable = true;
	_gg_nTouchPriority = 0;
	_gg_isSwallowTouch = true;
	_gg_nDoubleTouchInternalTime = SingleTouchDoubleTouchDeltaMilliSecond;
	_gg_TouchRect = Rect::ZERO;

	_gg_TouchBeginPosition = Point::ZERO;
	_gg_LastTouchTime.tv_sec = 0;
	_gg_LastTouchTime.tv_usec = 0;
	_gg_eState = State::UNKNOWN;
}



SingleTouch::~SingleTouch()
{
	
}



void SingleTouch::SetTouchEnable( bool isEnable )
{
	_gg_isTouchEnable = isEnable;
}



bool SingleTouch::IsTouchEnable() const
{
	return _gg_isTouchEnable;
}


void SingleTouch::SetTouchRect( const Rect &rect )
{
	_gg_TouchRect = rect;
}



Rect SingleTouch::GetTouchRect() const
{
	return _gg_TouchRect;
}



int SingleTouch::RegisterTouchEventListener( int nNewTouchPriority, bool isSwallowTouch )
{
	if ( _gg_pEventListenerTouch && _gg_nTouchPriority == nNewTouchPriority && _gg_isSwallowTouch == isSwallowTouch )
	{
		return 1;
	}
	
	EventDispatcher *pEventDispatcher = Director::getInstance()->getEventDispatcher();
	if ( pEventDispatcher == nullptr )
	{
		return -1;
	}

	_gg_nTouchPriority = nNewTouchPriority;
	_gg_isSwallowTouch = isSwallowTouch;

	// remove old
	if ( _gg_pEventListenerTouch )
	{
		pEventDispatcher->removeEventListener( _gg_pEventListenerTouch );
		_gg_pEventListenerTouch = nullptr;
	}

	auto pNewListener = EventListenerTouchOneByOne::create();
	pNewListener->setSwallowTouches( isSwallowTouch );

    pNewListener->onTouchBegan = CC_CALLBACK_2( SingleTouch::OnTouchBegan, this );
    pNewListener->onTouchMoved = CC_CALLBACK_2( SingleTouch::OnTouchMoved, this );
    pNewListener->onTouchEnded = CC_CALLBACK_2( SingleTouch::OnTouchEnded, this );
    pNewListener->onTouchCancelled = CC_CALLBACK_2( SingleTouch::OnTouchCancelled, this );

	pEventDispatcher->addEventListenerWithFixedPriority( pNewListener, nNewTouchPriority );

    _gg_pEventListenerTouch = pNewListener;

	return 0;
}



bool SingleTouch::IsTouchMe( Touch *pTouch ) const
{
	if ( pTouch == nullptr )
	{
		return false;
	}
	
	return _gg_TouchRect.containsPoint( pTouch->getLocation() );
}



Point SingleTouch::GetTouchBeginPosition() const
{
	return _gg_TouchBeginPosition;
}



void SingleTouch::ResetLastTouchTime()
{
	_gg_LastTouchTime.tv_sec = 0.0f;
	_gg_LastTouchTime.tv_sec = 0.0f;
}



SingleTouch::State SingleTouch::GetState() const
{
	return _gg_eState;
}



bool SingleTouch::IsDoubleTouch() const
{
	if ( _gg_eState == State::DOUBLE )
	{
		return true;
	}

	return false;
}



void SingleTouch::SetDoubleTouchInternalTime( unsigned int nMilliSecond )
{
	_gg_nDoubleTouchInternalTime = nMilliSecond;
}



void SingleTouch::SetListener( SingleTouchListener *pListener )
{
	_gg_pListener = pListener;
}



SingleTouchListener *SingleTouch::GetListener() const
{
	return _gg_pListener;
}



void SingleTouch::Step( float dt )
{

}



bool SingleTouch::OnTouchBegan( Touch *pTouch, Event *pEvent )
{
	if ( _gg_isTouchEnable == false )
	{
		return false;
	}

	int nPreCode = 0;
	if ( _gg_pListener )
	{
		nPreCode = _gg_pListener->SingleTouch_OnTouchBegin_Pre( this, pTouch, pEvent );
	}
	if ( nPreCode == 0 && IsTouchMe( pTouch ) == false )
	{
		return false;
	}


	_gg_eState = State::UNKNOWN;
	_gg_TouchBeginPosition = pTouch->getLocation();
	const long nDoubleTouchDeltaTime = _gg_nDoubleTouchInternalTime;


	timeval currentTouchTime;
	gettimeofday( &currentTouchTime, nullptr );	
	const long nDeltaMilliSecond = ( currentTouchTime.tv_sec - _gg_LastTouchTime.tv_sec ) * 1e3 + ( currentTouchTime.tv_usec - _gg_LastTouchTime.tv_usec ) / 1e3;
	_gg_LastTouchTime = currentTouchTime;


	if ( nDeltaMilliSecond <= nDoubleTouchDeltaTime )
	{
		_gg_eState = State::DOUBLE;

		ResetLastTouchTime();

		if ( _gg_pListener )
		{
			_gg_pListener->SingleTouch_OnTouchDouble( this, pTouch, pEvent );
		}
	}
	else
	{
		if ( _gg_pListener )
		{
			_gg_pListener->SingleTouch_OnTouchBegin( this, pTouch, pEvent );
		}
	}


	return true;
}



void SingleTouch::OnTouchMoved( Touch *pTouch, Event *pEvent )
{
	if ( _gg_pListener )
	{
		_gg_pListener->SingleTouch_OnTouchMoved( this, pTouch, pEvent );
	}
}



void SingleTouch::OnTouchEnded( Touch *pTouch, Event *pEvent )
{
	if ( _gg_pListener )
	{
		_gg_pListener->SingleTouch_OnTouchEnded( this, pTouch, pEvent );
	}
}



void SingleTouch::OnTouchCancelled( Touch *pTouch, Event *pEvent )
{
	if ( _gg_pListener )
	{
		_gg_pListener->SingleTouch_OnTouchCancelled( this, pTouch, pEvent );
	}
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
