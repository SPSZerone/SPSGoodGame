#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__SLOT_NODE_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_NODE__SLOT_NODE_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "SingleTouchNode.h"
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_EXTEND_COCOS

class SlotNode;
class SlotNodeListener
{
public:
	virtual int SlotNode_OnTouchBegin( SlotNode *pSlotNode, Touch *pTouch, Event *pEvent ) = 0;
	virtual int SlotNode_OnTouchDouble( SlotNode *pSlotNode, Touch *pTouch, Event *pEvent ) = 0;
	virtual int SlotNode_OnTouchLong( SlotNode *pSlotNode, Touch *pTouch, Event *pEvent ) = 0;
	virtual int SlotNode_OnTouchMoved( SlotNode *pSlotNode, Touch *pTouch, Event *pEvent ) = 0;
	virtual int SlotNode_OnTouchEnded( SlotNode *pSlotNode, Touch *pTouch, Event *pEvent ) = 0;
	virtual int SlotNode_OnTouchCancelled( SlotNode *pSlotNode, Touch *pTouch, Event *pEvent ) = 0;
};

class SlotNode : public Node, public SingleTouchListener
{
public:	
	enum UITag
	{
		kSlotNode_UITag_SingleTouchNode = -1,
		kSlotNode_UITag_SlotIcon = 0,
		kSlotNode_UITag_SlotShading,  // 槽的底纹
		kSlotNode_UITag_HighLight,
		kSlotNode_UITag_Data,
		kSlotNode_UITag_Lock
	};

protected:

	SingleTouchNode *_gg_pSingleTouchNode;
	SlotNodeListener *_gg_pSlotNodeListener;

	int _gg_nSlotType;
	int _gg_nSlotIndex;
	bool _gg_isLocked; // 是否锁定

	// 移动DataNode时碰撞的SlotNode
	Node *_gg_pCollidedSlotNode;



public:
	CREATE_FUNC( SlotNode );
	SlotNode();
	virtual ~SlotNode();
	virtual bool init() override;


	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExitTransitionDidStart() override;
	virtual void onExit() override;


	virtual void SetSlotNodeListener( SlotNodeListener *pSlotNodeListener );
	virtual SlotNodeListener *GetSlotNodeListener();

	virtual void SetSlotType( int nSlotType );
	virtual int GetSlotType();
	virtual void SetSlotIndex( int nSlotIndex );
	virtual int GetSlotIndex();
	virtual bool IsLocked();

	
	virtual void SetCollidedSlotNode( Node *pCollidedSlotNode );
	virtual Node *GetCollidedSlotNode();


	virtual void SetSlotIconNode( Node *pSlotIconNode );
	virtual Node *GetSlotIconNode();
	virtual void SetSlotShadingNode( Node *pSlotShadingNode );
	virtual Node *GetSlotShadingNode();
	virtual void SetHighLightNode( Node *pHighLightNode );
	virtual Node *GetHighLightNode();
	virtual void SetLockNode( Node *pLockNode );
	virtual Node *GetLockNode();


	virtual void BindDataNode( Node *pDataNode );
	virtual void UnBindDataNode();
	virtual Node *GetBindedDataNode();
	virtual bool IsHaveBindedDataNode();
	virtual bool IsBindedDataNodeAvailable();


	virtual Size GetSlotIconContentSize();
	virtual void SwitchHighLight( bool isOn );
	virtual void Lock( Node *pLockNode = nullptr );
	virtual void UnLock( bool isRemove = true );


	virtual void MoveDataNodeByTouch( Touch *pTouch );
	virtual bool IsCollidedWithMe( Node *pNode );


	virtual void SetSlotTouchEnable( bool isEnable );
	virtual int SetTouchPrioritySwallow( int nNewTouchPriority, bool isSwallowTouch = true );
	virtual void ResetZorderToTopInParent();
	virtual void ResetZorderToBottomInParent();
	virtual void ResetDataNodeToOriginPosition();
	virtual void SetDataNodeVisible( bool isVisible );


	virtual int SingleTouch_OnTouchBegin( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent );
	virtual int SingleTouch_OnTouchDouble( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent );
	virtual int SingleTouch_OnTouchLong( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent );
	virtual int SingleTouch_OnTouchMoved( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent );
	virtual int SingleTouch_OnTouchEnded( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent );
	virtual int SingleTouch_OnTouchCancelled( SingleTouch *pSingleTouch, Touch *pTouch, Event *pEvent );


private:
	virtual void UpdateTouchSizeWithSlotIcon();
}; // end class SlotNode

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__SLOT_NODE_H__
