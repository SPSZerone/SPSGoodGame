#include "ArmatureAdapterNode.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "SPSGoodGame/Platform/LogHelper.h"
__SPS_GG__NS__U_EXTEND_COCOS;



ArmatureAdapterNode::ArmatureAdapterNode()
{
	_gg_strArmatureName.clear();
	_gg_pListener = nullptr;
}



ArmatureAdapterNode::~ArmatureAdapterNode()
{

}



bool ArmatureAdapterNode::init()
{
	Node::init();
	return true;
}



void ArmatureAdapterNode::onEnter()
{
	Node::onEnter();
}



void ArmatureAdapterNode::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
}



void ArmatureAdapterNode::onExitTransitionDidStart()
{
	Node::onExitTransitionDidStart();
}



void ArmatureAdapterNode::onExit()
{
	Node::onExit();
}



void ArmatureAdapterNode::SetArmatureName( const std::string &strArmatureName )
{
	_gg_strArmatureName = strArmatureName;
}



const std::string &ArmatureAdapterNode::GetArmatureName()
{
	return _gg_strArmatureName;
}



void ArmatureAdapterNode::SetListener( ArmatureAdapterNodeListener *pListener )
{
	_gg_pListener = pListener;
}



ArmatureAdapterNodeListener *ArmatureAdapterNode::GetListener()
{
	return _gg_pListener;
}



void ArmatureAdapterNode::OnMovementEvent( Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID )
{
	OnMovementEvent_Before_ListenerCallBack( pArmature, eMovementEventType, strMovementEventID );

	if ( _gg_pListener )
	{
		_gg_pListener->ArmatureAdapter_OnMovementEvent( this, pArmature, eMovementEventType, strMovementEventID );
	}
	
	OnMovementEvent_After_ListenerCallBack( pArmature, eMovementEventType, strMovementEventID );
}



void ArmatureAdapterNode::OnFrameEvent( Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex )
{
	OnFrameEvent_Before_ListenerCallBack( pBone, strEventID, nOriginFrameIndex, nCurrentFrameIndex );

	if ( _gg_pListener )
	{
		_gg_pListener->ArmatureAdapter_OnFrameEvent( this, pBone, strEventID, nOriginFrameIndex, nCurrentFrameIndex );
	}
	
	OnFrameEvent_After_ListenerCallBack( pBone, strEventID, nOriginFrameIndex, nCurrentFrameIndex );
}



void ArmatureAdapterNode::OnMovementEvent_Before_ListenerCallBack( Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID )
{

}



void ArmatureAdapterNode::OnMovementEvent_After_ListenerCallBack( Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID )
{

}



void ArmatureAdapterNode::OnFrameEvent_Before_ListenerCallBack( Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex )
{
	
}



void ArmatureAdapterNode::OnFrameEvent_After_ListenerCallBack( Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex )
{
	
}



int ArmatureAdapterNode::Build()
{
	Build_Base();
	Build_Items();

	Refresh();

	return 0;
}



int ArmatureAdapterNode::Build_Base()
{
	removeAllChildren();

	if ( _gg_strArmatureName.empty() )
	{
		LOG_WF_E( "ArmatureAdapterNode", "Build_Base >> ERROR: ArmatureName is empty" );
		return -1;
	}

	auto pArmature = Armature::create( _gg_strArmatureName );
	if ( pArmature == nullptr )
	{
		LOG_WF_E( "ArmatureAdapterNode", "Build_Base >> ERROR: create failed for (%s)", _gg_strArmatureName.c_str() );
		return -2;
	}
	
	addChild( pArmature, ArmatureAdapterNode_ArmatureTag, ArmatureAdapterNode_ArmatureTag );

	auto pAnimation = pArmature->getAnimation();
	if ( pAnimation == nullptr )
	{
		LOG_WF_E( "ArmatureAdapterNode", "Build_Base >> ERROR: Animation is null" );
		return -3;
	}
	pAnimation->setMovementEventCallFunc( CC_CALLBACK_0( ArmatureAdapterNode::OnMovementEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );
	pAnimation->setFrameEventCallFunc( CC_CALLBACK_0( ArmatureAdapterNode::OnFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 ) );

	return 0;
}



int ArmatureAdapterNode::Build_Items()
{
	return 0;
}



void ArmatureAdapterNode::RefreshDelay( float fDelay )
{
	if ( fDelay <= 0.0f )
	{
		Refresh();
		return ;
	}

	runAction( Sequence::createWithTwoActions(
		DelayTime::create( fDelay ),
		CallFunc::create( CC_CALLBACK_0( ArmatureAdapterNode::Refresh, this ) )
		) );
}



void ArmatureAdapterNode::Refresh()
{
	
}



Armature *ArmatureAdapterNode::GetArmature()
{
	return dynamic_cast<Armature *>( getChildByTag( ArmatureAdapterNode_ArmatureTag ) );
}



ArmatureAnimation *ArmatureAdapterNode::GetArmatureAnimation()
{
	auto pArmature = GetArmature();
	if ( pArmature == nullptr )
	{
		return nullptr;
	}

	return pArmature->getAnimation();
}



int ArmatureAdapterNode::SetArmatureVisible( bool isVisible )
{
	auto pArmature = GetArmature();
	if ( pArmature == nullptr )
	{
		return -1;
	}
	pArmature->setVisible( isVisible );
	return 0;
}



int ArmatureAdapterNode::RemoveBone( Bone *pBone, bool isRecursion )
{
	if ( pBone == nullptr )
	{
		return -1;
	}
	auto pCardNode = GetArmature();
	if ( pCardNode == nullptr )
	{
		return -2;
	}
	pCardNode->removeBone( pBone, isRecursion );
	return 0;
}



Bone *ArmatureAdapterNode::GetBone( const std::string &strName )
{
	auto pArmature = GetArmature();
	if ( pArmature == nullptr )
	{
		return nullptr;
	}

	return pArmature->getBone( strName );
}



Node *ArmatureAdapterNode::GetChildInArmature( int nTag )
{
	auto pArmature = GetArmature();
	if ( pArmature == nullptr )
	{
		return nullptr;
	}

	return pArmature->getChildByTag( nTag );
}



Point ArmatureAdapterNode::GetWorldPosition()
{
	auto pParentNode = getParent();
	return pParentNode ? pParentNode->convertToWorldSpace( getPosition() ) : getPosition();
}



int ArmatureAdapterNode::PlayAnimation( const std::string &strName )
{
	if ( strName.empty() )
	{
		return -1;
	}
	auto pArmature = GetArmature();
	if ( pArmature == nullptr )
	{
		return -2;
	}
	auto pAnimation = pArmature->getAnimation();
	if ( pAnimation == nullptr )
	{
		return -3;
	}
	pAnimation->play( strName );
	return 0;
}



int ArmatureAdapterNode::safe_change_display( Bone *pBone, int nIndex, bool isForce )
{
	if ( pBone == nullptr )
	{
		return -1;
	}

	auto vList = pBone->getDisplayManager()->getDecorativeDisplayList();
	if ( nIndex < 0 || nIndex >= vList.size() )
	{
		return -2;
	}

	pBone->changeDisplayWithIndex( nIndex, isForce );

	return 0;
}



int ArmatureAdapterNode::set_display_render_node_visible( Bone *pBone, bool isVisible )
{
	if ( pBone == nullptr )
	{
		return -1;
	}

	auto pDisplayRenderNode = pBone->getDisplayRenderNode();
	if ( pDisplayRenderNode == nullptr )
	{
		return -2;
	}

	pDisplayRenderNode->setVisible( isVisible );

	return 0;
}



Size ArmatureAdapterNode::get_content_size_of_display_render_node( Bone *pBone )
{
	if ( pBone == nullptr )
	{
		return Size::ZERO;
	}

	auto pDisplayRenderNode = pBone->getDisplayRenderNode();
	if ( pDisplayRenderNode == nullptr )
	{
		return Size::ZERO;
	}

	return pDisplayRenderNode->getContentSize();
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
