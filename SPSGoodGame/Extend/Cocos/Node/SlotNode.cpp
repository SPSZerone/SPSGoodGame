#include "SlotNode.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "DataNode.h"
__SPS_GG__NS__U_EXTEND_COCOS;



SlotNode::SlotNode()
{
	_gg_pSingleTouchNode = nullptr;
	_gg_pSlotNodeListener = nullptr;

	_gg_nSlotType = -1;
	_gg_nSlotIndex = -1;
	_gg_isLocked = false;

	_gg_pCollidedSlotNode = nullptr;
}



SlotNode::~SlotNode()
{

}



bool SlotNode::init()
{
	_gg_pSingleTouchNode = SingleTouchNode::create();
	if ( _gg_pSingleTouchNode )
	{
		addChild( _gg_pSingleTouchNode );
		_gg_pSingleTouchNode->SetListener( this );
	}

	return true;
}



void SlotNode::onEnter()
{
	Node::onEnter();

	UpdateTouchSizeWithSlotIcon();
}



void SlotNode::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
}



void SlotNode::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}



void SlotNode::onExit()
{
	Node::onExit();
}



void SlotNode::SetSlotNodeListener( SlotNodeListener *pSlotNodeListener )
{
	_gg_pSlotNodeListener = pSlotNodeListener;
}



SlotNodeListener *SlotNode::GetSlotNodeListener()
{
	return _gg_pSlotNodeListener;
}



void SlotNode::SetSlotType( int nSlotType )
{
	_gg_nSlotType = nSlotType;
}



int SlotNode::GetSlotType()
{
	return _gg_nSlotType;
}



void SlotNode::SetSlotIndex( int nSlotIndex )
{
	_gg_nSlotIndex = nSlotIndex;
}



int SlotNode::GetSlotIndex()
{
	return _gg_nSlotIndex;
}



bool SlotNode::IsLocked()
{
	return _gg_isLocked;
}



void SlotNode::SetCollidedSlotNode( Node *pCollidedSlotNode )
{
	_gg_pCollidedSlotNode = pCollidedSlotNode;
}



Node *SlotNode::GetCollidedSlotNode()
{
	return _gg_pCollidedSlotNode;
}



void SlotNode::SetSlotIconNode( Node *pSlotIconNode )
{
	if ( pSlotIconNode == nullptr )
	{
		removeChildByTag( kSlotNode_UITag_SlotIcon );
	}
	else
	{
		Node *pNode = getChildByTag( kSlotNode_UITag_SlotIcon );
		if ( pNode )
		{
			removeChild( pNode, true );
		}
		if ( pNode != pSlotIconNode )
		{
			addChild( pSlotIconNode, kSlotNode_UITag_SlotIcon, kSlotNode_UITag_SlotIcon );
			setContentSize( pSlotIconNode->getContentSize() );
		}
	}

	UpdateTouchSizeWithSlotIcon();
}



Node *SlotNode::GetSlotIconNode()
{
	return getChildByTag( kSlotNode_UITag_SlotIcon );
}



void SlotNode::SetSlotShadingNode( Node *pSlotBGNode )
{
	if ( pSlotBGNode == nullptr )
	{
		removeChildByTag( kSlotNode_UITag_SlotShading );
	}
	else
	{
		Node *pNode = getChildByTag( kSlotNode_UITag_SlotShading );
		if ( pNode )
		{
			removeChild( pNode, true );
		}
		if ( pNode != pSlotBGNode )
		{
			addChild( pSlotBGNode, kSlotNode_UITag_SlotShading, kSlotNode_UITag_SlotShading );
		}
	}
}



Node *SlotNode::GetSlotShadingNode()
{
	return getChildByTag( kSlotNode_UITag_SlotShading );
}



void SlotNode::SetHighLightNode( Node *pHighLightNode )
{
	if ( pHighLightNode == nullptr )
	{
		removeChildByTag( kSlotNode_UITag_HighLight );
	}
	else
	{
		Node *pNode = getChildByTag( kSlotNode_UITag_HighLight );
		if ( pNode )
		{
			removeChild( pNode, true );
		}
		if ( pNode != pHighLightNode )
		{
			addChild( pHighLightNode, kSlotNode_UITag_HighLight, kSlotNode_UITag_HighLight );
		}
	}
}



Node *SlotNode::GetHighLightNode()
{
	return getChildByTag( kSlotNode_UITag_HighLight );
}



void SlotNode::SetLockNode( Node *pLockNode )
{
	if ( pLockNode == nullptr )
	{
		removeChildByTag( kSlotNode_UITag_Lock );
	}
	else
	{
		Node *pNode = getChildByTag( kSlotNode_UITag_Lock );
		if ( pNode )
		{
			removeChild( pNode, true );
		}
		if ( pNode != pLockNode )
		{
			addChild( pLockNode, kSlotNode_UITag_Lock, kSlotNode_UITag_Lock );
		}
	}
}



Node *SlotNode::GetLockNode()
{
	return getChildByTag( kSlotNode_UITag_Lock );
}



void SlotNode::BindDataNode( Node *pDataNode )
{
	if ( pDataNode == nullptr )
	{
		UnBindDataNode();
	}
	else
	{
		Node *pNode = getChildByTag( kSlotNode_UITag_Data );
		if ( pNode != pDataNode )
		{
			UnBindDataNode();
			addChild( pDataNode, kSlotNode_UITag_Data, kSlotNode_UITag_Data );
		}
	}
}



void SlotNode::UnBindDataNode()
{
	Node *pDataNode = getChildByTag( kSlotNode_UITag_Data );
	if ( pDataNode )
	{
		removeChild( pDataNode, true );
	}
}



Node *SlotNode::GetBindedDataNode()
{
	return getChildByTag( kSlotNode_UITag_Data );
}



bool SlotNode::IsHaveBindedDataNode()
{
	return GetBindedDataNode() ? true : false;
}



bool SlotNode::IsBindedDataNodeAvailable()
{
	DataNode *pDataNode = dynamic_cast<DataNode *>( GetBindedDataNode() );
	
	if ( pDataNode )
	{
		return pDataNode->IsAnyDataAvailable();
	}

	return false;
}



Size SlotNode::GetSlotIconContentSize()
{
	Node *pNode = getChildByTag( kSlotNode_UITag_SlotIcon );
	if ( pNode )
	{
		return pNode->getContentSize();
	}

	return getContentSize();
}



void SlotNode::SwitchHighLight( bool isOn )
{
	Node *pNode = GetHighLightNode();
	if ( pNode )
	{
		pNode->setVisible( isOn );
	}
}



void SlotNode::Lock( Node *pLockNode )
{
	_gg_isLocked = true;

	if ( pLockNode )
	{
		SetLockNode( pLockNode );
	}
	else
	{
		Node *pNode = GetLockNode();
		if ( pNode )
		{
			pNode->setVisible( true );
		}
	}
}



void SlotNode::UnLock( bool isRemove )
{
	_gg_isLocked = false;

	Node *pNode = GetLockNode();
	if ( isRemove )
	{
		if ( pNode )
		{
			removeChild( pNode, true );
		}
	}
	else
	{
		if ( pNode )
		{
			pNode->setVisible( false );
		}
	}
}



void SlotNode::MoveDataNodeByTouch( Touch *pTouch )
{
	DataNode *pDataNode = dynamic_cast<DataNode *>( GetBindedDataNode() );
	if ( pDataNode )
	{
		pDataNode->SetPositionByTouch( pTouch );
	}
}



bool SlotNode::IsCollidedWithMe( Node *pNode )
{
	if ( pNode == nullptr )
	{
		return false;
	}

	Node *pParentNode = getParent();
	const Point localPosition = getPosition();
	const Point worldPosition = pParentNode ? pParentNode->convertToWorldSpace( localPosition ) : localPosition;
	const Size contentSize = getContentSize() * getScale();
	Rect worldRect( worldPosition.x - contentSize.width * 0.5f, worldPosition.y - contentSize.height * 0.5f, contentSize.width, contentSize.height );
	
	return worldRect.containsPoint( worldPosition );
}



void SlotNode::SetSlotTouchEnable( bool isEnable )
{
	if ( _gg_pSingleTouchNode )
	{
		_gg_pSingleTouchNode->SetTouchEnable( isEnable );
	}
}



int SlotNode::SetTouchPrioritySwallow( int nPriorty, bool isSwallowTouch )
{
	if ( _gg_pSingleTouchNode )
	{
		return _gg_pSingleTouchNode->RegisterTouchEventListener( SingleTouchNode::RegisterTouchEventType::SCENE_GRAPH_PRIORITY, nPriorty, isSwallowTouch );
	}
	return -1;
}



void SlotNode::ResetZorderToTopInParent()
{
	setLocalZOrder( 30000 );
}



void SlotNode::ResetZorderToBottomInParent()
{
	setLocalZOrder( -30000 );
}



void SlotNode::ResetDataNodeToOriginPosition()
{
	Node *pDataNode = GetBindedDataNode();
	if ( pDataNode )
	{
		pDataNode->setPosition( Point::ZERO );
	}
}



void SlotNode::SetDataNodeVisible( bool isVisible )
{
	Node *pDataNode = GetBindedDataNode();
	if ( pDataNode )
	{
		pDataNode->setVisible( isVisible );
	}
}



int SlotNode::SingleTouch_OnTouchBegin( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	if ( _gg_pSlotNodeListener )
	{
		_gg_pSlotNodeListener->SlotNode_OnTouchBegin( this, pTouch, pEvent );
	}

	return 0;
}



int SlotNode::SingleTouch_OnTouchDouble( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	if ( _gg_pSlotNodeListener )
	{
		_gg_pSlotNodeListener->SlotNode_OnTouchDouble( this, pTouch, pEvent );
	}

	return 0;
}



int SlotNode::SingleTouch_OnTouchLong( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	if ( _gg_pSlotNodeListener )
	{
		_gg_pSlotNodeListener->SlotNode_OnTouchLong( this, pTouch, pEvent );
	}

	return 0;
}



int SlotNode::SingleTouch_OnTouchMoved( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	bool isDoubleTouch = false;
	if ( _gg_pSingleTouchNode )
	{
		isDoubleTouch = _gg_pSingleTouchNode->IsDoubleTouch();
	}
	if ( isDoubleTouch )
	{
		return 1;
	}


	if ( _gg_pSlotNodeListener )
	{
		Point beginPoint;
		if ( _gg_pSingleTouchNode )
		{
			beginPoint = _gg_pSingleTouchNode->GetTouchBeginPosition();
		}
		Point point = pTouch->getLocation();
		float offsetX = point.x - beginPoint.x;
		float offsetY = point.y - beginPoint.y;
		float offset = sqrtf( offsetX * offsetX + offsetY * offsetY );
		if ( offset > 20 )
		{
			_gg_pSlotNodeListener->SlotNode_OnTouchMoved( this, pTouch, pEvent );
		}
	}


	return 0;
}



int SlotNode::SingleTouch_OnTouchEnded( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	bool isDoubleTouch = false;
	if ( _gg_pSingleTouchNode )
	{
		isDoubleTouch = _gg_pSingleTouchNode->IsDoubleTouch();
	}
	if ( isDoubleTouch )
	{
		return 1;
	}

	if ( _gg_pSlotNodeListener )
	{
		_gg_pSlotNodeListener->SlotNode_OnTouchEnded( this, pTouch, pEvent );
	}

	return 0;
}



int SlotNode::SingleTouch_OnTouchCancelled( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent )
{
	bool isDoubleTouch = false;
	if ( _gg_pSingleTouchNode )
	{
		isDoubleTouch = _gg_pSingleTouchNode->IsDoubleTouch();
	}
	if ( isDoubleTouch )
	{
		return 1;
	}

	if ( _gg_pSlotNodeListener )
	{
		_gg_pSlotNodeListener->SlotNode_OnTouchCancelled( this, pTouch, pEvent );
	}

	return 0;
}



void SlotNode::UpdateTouchSizeWithSlotIcon()
{
	if ( _gg_pSingleTouchNode == nullptr )
	{
		return ;
	}

	Size contentSize = getContentSize();
	float fScaleX = getScaleX();
	float fScaleY = getScaleY();

	Node *pSlotIconNode = getChildByTag( kSlotNode_UITag_SlotIcon );
	if ( pSlotIconNode )
	{
		contentSize = pSlotIconNode->getContentSize();
		fScaleX = pSlotIconNode->getScaleX();
		fScaleY = pSlotIconNode->getScaleY();
	}

	_gg_pSingleTouchNode->SetTouchSize( Size( contentSize.width * fScaleX, contentSize.height * fScaleY ) );
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
