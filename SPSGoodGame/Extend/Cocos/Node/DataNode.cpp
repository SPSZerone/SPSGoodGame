#include "DataNode.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



DataNode::UpdateUIConfig::UpdateUIConfig()
{
	nFilter = UpdateUICode::kDataNode_UpdateUICode_NONE;
	nRefresh = UpdateUICode::kDataNode_UpdateUICode_NONE;

	fIconScale = 1.0f;
	dwMaterialNeedCount = ULONG_MAX;
}



DataNode::UpdateUIConfig & DataNode::UpdateUIConfig::operator= ( const UpdateUIConfig &newConfig )
{
	nFilter = newConfig.nFilter;
	nRefresh = newConfig.nRefresh;

	fIconScale = newConfig.fIconScale;
	dwMaterialNeedCount = newConfig.dwMaterialNeedCount;

	return *this;
}



DataNode::DetailInforConfig::DetailInforConfig()
{
	pContainerNode = nullptr;
	pBGNode = nullptr;
	pDivideLineTexture = nullptr;
	pDivideLineFrame = nullptr;

	isAutoPosition = true;
	screenAnchor = Point::ANCHOR_MIDDLE;
	nTag = -1;
	nZorder = 1;
}



DataNode::DataNode()
{
	_gg_pDetailRootNode = nullptr;
	_gg_pDetailRootNode_BG = nullptr;
	_gg_pDetailRootNode_Content = nullptr;
}



DataNode::~DataNode()
{
	
}



bool DataNode::init()
{
	return true;
}



Point DataNode::GetPositionInWorld()
{
	Node *pParentNode = getParent();
	if ( pParentNode )
	{
		return pParentNode->convertToWorldSpace( getPosition() );
	}
	return getPosition();
}



int DataNode::SetPositionByTouch( Touch *pTouch )
{
	if ( pTouch == nullptr )
	{
		return -1;
	}
	
	Node *pParentNode = getParent();
	if ( pParentNode )
	{
		setPosition( pParentNode->convertToNodeSpace( pTouch->getLocation() ) );
	}
	else
	{
		setPosition( pTouch->getLocation() );
	}

	return 0;
}



int DataNode::SetDetailInforPosition( const Point &screenAnchor )
{
	if ( _gg_pDetailRootNode == nullptr )
	{
		return -1;
	}

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Point visibleOrigin = Director::getInstance()->getVisibleOrigin();
	Node *pParentNode = _gg_pDetailRootNode->getParent();
	if ( pParentNode )
	{
		_gg_pDetailRootNode->setPosition( pParentNode->convertToNodeSpace( Point(
			visibleOrigin.x + visibleSize.width * screenAnchor.x, visibleOrigin.y + visibleSize.height * screenAnchor.y ) ) );
	}
	else
	{
		_gg_pDetailRootNode->setPosition( Point( visibleOrigin.x + visibleSize.width * screenAnchor.x, visibleOrigin.y + visibleSize.height * screenAnchor.y ) );
	}

	return 0;
}



int DataNode::UpdateUI( const UpdateUIConfig &config )
{
	setVisible( false );

	if ( IsAnyDataAvailable() )
	{
		setVisible( true );
	}

	return -1;
}



int DataNode::ShowDetailInfor( const DetailInforConfig &config )
{
	CloseDetailInfor();

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Point visibleOrigin = Director::getInstance()->getVisibleOrigin();

	_gg_pDetailRootNode = Node::create();
	if ( config.pContainerNode )
	{
		config.pContainerNode->addChild( _gg_pDetailRootNode, config.nZorder, config.nTag );
	}
	else
	{
		addChild( _gg_pDetailRootNode, config.nZorder, config.nTag );
	}

	if ( config.isAutoPosition )
	{
		const Point worldPosition = GetPositionInWorld();
		if ( worldPosition.x > visibleOrigin.x + visibleSize.width * 0.5f )
		{
			SetDetailInforPosition( Point( 0.25f, 0.5f ) );
		}
		else
		{
			SetDetailInforPosition( Point( 0.75f, 0.5f ) );
		}
	}
	else
	{
		SetDetailInforPosition( config.screenAnchor );
	}

	_gg_pDetailRootNode_BG = Node::create();
	_gg_pDetailRootNode_Content = Node::create();

	_gg_pDetailRootNode->addChild( _gg_pDetailRootNode_BG, -1 );		
	_gg_pDetailRootNode->addChild( _gg_pDetailRootNode_Content, 0 );
	
	return 0;
}



int DataNode::CloseDetailInfor()
{
	if ( _gg_pDetailRootNode == nullptr )
	{
		return 1;
	}

	_gg_pDetailRootNode->removeFromParentAndCleanup( true );
	_gg_pDetailRootNode = nullptr;

	return 0;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
