#include "SingleTouchNode.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



SingleTouchNode::SingleTouchNode()
{
	_gg_eRegisterTouchEventType = RegisterTouchEventType::UNKNOWN;
	_gg_TouchSize.setSize( 0.0f, 0.0f );
}



SingleTouchNode::~SingleTouchNode()
{
	
}



bool SingleTouchNode::init()
{
	return true;
}



void SingleTouchNode::onEnter()
{
	Node::onEnter();
}



void SingleTouchNode::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
}



void SingleTouchNode::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}



void SingleTouchNode::onExit()
{
	Node::onExit();
}



void SingleTouchNode::SetRegisterTouchEventType( RegisterTouchEventType eRegisterTouchEventType )
{
	_gg_eRegisterTouchEventType = eRegisterTouchEventType;
}



SingleTouchNode::RegisterTouchEventType SingleTouchNode::GetRegisterTouchEventType() const
{
	return _gg_eRegisterTouchEventType;
}



void SingleTouchNode::SetTouchSize( const Size &touchSize )
{
	_gg_TouchSize = touchSize;
}



Size SingleTouchNode::GetTouchSize() const
{
	return _gg_TouchSize;
}



int SingleTouchNode::RegisterTouchEventListener( RegisterTouchEventType eRegisterTouchEventType, int nNewTouchPriority, bool isSwallowTouch )
{
	if ( _gg_pEventListenerTouch && _gg_eRegisterTouchEventType == eRegisterTouchEventType
			&& _gg_nTouchPriority == nNewTouchPriority && _gg_isSwallowTouch == isSwallowTouch )
	{
		return 1;
	}

	_gg_nTouchPriority = nNewTouchPriority;
	_gg_isSwallowTouch = isSwallowTouch;

	// remove old
	if ( _gg_pEventListenerTouch )
	{
		_eventDispatcher->removeEventListener( _gg_pEventListenerTouch );
		_gg_pEventListenerTouch = nullptr;
	}

	auto pNewListener = EventListenerTouchOneByOne::create();
	pNewListener->setSwallowTouches( isSwallowTouch );

    pNewListener->onTouchBegan = CC_CALLBACK_2( SingleTouchNode::OnTouchBegan, this );
    pNewListener->onTouchMoved = CC_CALLBACK_2( SingleTouchNode::OnTouchMoved, this );
    pNewListener->onTouchEnded = CC_CALLBACK_2( SingleTouchNode::OnTouchEnded, this );
    pNewListener->onTouchCancelled = CC_CALLBACK_2( SingleTouchNode::OnTouchCancelled, this );

	if ( eRegisterTouchEventType == RegisterTouchEventType::SCENE_GRAPH_PRIORITY )
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority( pNewListener, this );
	}
	else if ( eRegisterTouchEventType == RegisterTouchEventType::FIXED_PRIORITY )
	{
		_eventDispatcher->addEventListenerWithFixedPriority( pNewListener, nNewTouchPriority );
	}

    _gg_pEventListenerTouch = pNewListener;
	
	return 0;
}



bool SingleTouchNode::IsTouchMe( Touch *pTouch ) const
{
	if ( pTouch == nullptr )
	{
		return false;
	}
	
	if ( _gg_TouchSize.width <= 0.0f || _gg_TouchSize.height <= 0.0f )
	{
		return SingleTouch::IsTouchMe( pTouch );
	}

	const Point anchorPoint = Point::ANCHOR_MIDDLE;
	const Node *pParentNode = getParent();
	const Point localPosition = getPosition();
	const Point worldPosition = pParentNode ? pParentNode->convertToWorldSpace( localPosition ) : localPosition;
	Rect rect( worldPosition.x - _gg_TouchSize.width * anchorPoint.x, worldPosition.y - _gg_TouchSize.height * anchorPoint.y, _gg_TouchSize.width, _gg_TouchSize.height );

	return rect.containsPoint( pTouch->getLocation() );
}



void SingleTouchNode::DebugDrawEnable( bool isEnable )
{
	if ( isEnable == false )
	{
		removeChildByTag( kSingleTouchNode_UITag_DEBUG );
		return ;
	}

	if ( getChildByTag( kSingleTouchNode_UITag_DEBUG ) )
	{
		return ;
	}

	LayerColor *pLayerColor =LayerColor::create( Color4B( 0x00, 0xAE, 0xEF, 150 ), _gg_TouchSize.width, _gg_TouchSize.height );
	addChild( pLayerColor, 20000, kSingleTouchNode_UITag_DEBUG );
	pLayerColor->ignoreAnchorPointForPosition( false );
	pLayerColor->setAnchorPoint( Point::ANCHOR_MIDDLE );
}



bool SingleTouchNode::OnTouchBegan( Touch *pTouch, Event *pEvent )
{
	for ( Node *pParent = this->_parent; pParent != nullptr; pParent = pParent->getParent() )
	{
		if ( pParent->isVisible() == false )
		{
			return false;
		}
	}
	
	return SingleTouch::OnTouchBegan( pTouch, pEvent );
}



void SingleTouchNode::OnTouchMoved( Touch *pTouch, Event *pEvent )
{
	SingleTouch::OnTouchMoved( pTouch, pEvent );
}



void SingleTouchNode::OnTouchEnded( Touch *pTouch, Event *pEvent )
{
	SingleTouch::OnTouchEnded( pTouch, pEvent );
}



void SingleTouchNode::OnTouchCancelled( Touch *pTouch, Event *pEvent )
{
	SingleTouch::OnTouchCancelled( pTouch, pEvent );
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
