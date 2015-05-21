#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__DATA_NODE_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_NODE__DATA_NODE_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "SPSGoodGame/Extend/Cocos/Adapter/DataAdapterObject.h"
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_EXTEND_COCOS

class DataNode : public Node, public DataAdapterObject
{
public:
	enum UITag
	{
		kDataNode_UITag_BG = 0,
		kDataNode_UITag_ICON,
		kDataNode_UITag_COUNT,
		kDataNode_UITag_NAME,
		kDataNode_UITag_STATE,
		kDataNode_UITag_MATERIAL_COUNT,
		kDataNode_UITag_LEVEL,
	}; // end enum UITag

	enum UpdateUICode
	{
		kDataNode_UpdateUICode_NONE = 0,
		kDataNode_UpdateUICode_ALL = 0xFFFF,

		kDataNode_UpdateUICode_BG = 1,
		kDataNode_UpdateUICode_ICON = 1 << 1,
		kDataNode_UpdateUICode_COUNT = 1 << 2,
		kDataNode_UpdateUICode_NAME = 1 << 3,
		kDataNode_UpdateUICode_STATE = 1 << 4,
		kDataNode_UpdateUICode_MATERIAL_COUNT = 1 << 5,
		kDataNode_UpdateUICode_LEVEL = 1 << 6,
	}; // end enum UpdateUICode

	class UpdateUIConfig
	{
	public:
		int nFilter;
		int nRefresh;
		float fIconScale;
		unsigned long dwMaterialNeedCount;

		UpdateUIConfig();
		UpdateUIConfig& operator= ( const UpdateUIConfig &newConfig );
		virtual ~UpdateUIConfig() {}
	}; // class UpdateUIConfig
	
	class DetailInforConfig
	{
	public:
		Node *pContainerNode; // 弱引用
		Node *pBGNode; // 弱引用
		Texture2D *pDivideLineTexture; // 弱引用
		SpriteFrame *pDivideLineFrame; // 弱引用

		bool isAutoPosition;
		Point screenAnchor;
		int nTag;
		int nZorder;

		DetailInforConfig();
		virtual ~DetailInforConfig() {}
	}; // end class DetailConfig

protected:
	
	Node *_gg_pDetailRootNode;
	Node *_gg_pDetailRootNode_BG;
	Node *_gg_pDetailRootNode_Content;


public:

	DataNode();
	virtual ~DataNode();
	virtual bool init() override;

	
	virtual Point GetPositionInWorld();
	virtual int SetPositionByTouch( Touch *pTouch );
	// detail infor 中心点在屏幕中的位置, 默认屏幕中心
	virtual int SetDetailInforPosition( const Point &screenAnchor );


	virtual int UpdateUI( const UpdateUIConfig &config );
	

	virtual int ShowDetailInfor( const DetailInforConfig &config );
	virtual int CloseDetailInfor();
}; // end class DataNode

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__DATA_NODE_H__
