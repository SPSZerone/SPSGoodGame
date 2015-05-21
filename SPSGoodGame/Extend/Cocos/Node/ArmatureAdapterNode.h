#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__ARMATURE_ADAPTER_NODE_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_NODE__ARMATURE_ADAPTER_NODE_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocostudio;



__SPS_GG__NS__B_EXTEND_COCOS

#define ArmatureAdapterNode_ArmatureTag          0

class ArmatureAdapterNode;
class ArmatureAdapterNodeListener
{
public:
	virtual int ArmatureAdapter_OnMovementEvent( ArmatureAdapterNode *pArmatureAdapterNode, Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID ) { return 0; }
	virtual int ArmatureAdapter_OnFrameEvent( ArmatureAdapterNode *pArmatureAdapterNode, Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex ) { return 0; }
};

class ArmatureAdapterNode : public Node
{
protected:
	std::string _gg_strArmatureName;
	ArmatureAdapterNodeListener *_gg_pListener;


public:
	CREATE_FUNC( ArmatureAdapterNode );
	ArmatureAdapterNode();
	virtual ~ArmatureAdapterNode();
	virtual bool init();


	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExitTransitionDidStart() override;
	virtual void onExit() override;


	virtual void SetArmatureName( const std::string &strArmatureName );
	virtual const std::string &GetArmatureName() final;
	virtual void SetListener( ArmatureAdapterNodeListener *pListener );
	virtual ArmatureAdapterNodeListener *GetListener();

	
	virtual void OnMovementEvent( Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID ) final;
	virtual void OnFrameEvent( Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex ) final;
protected:
	virtual void OnMovementEvent_Before_ListenerCallBack( Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID );
	virtual void OnMovementEvent_After_ListenerCallBack( Armature *pArmature, MovementEventType eMovementEventType, const std::string &strMovementEventID );

	virtual void OnFrameEvent_Before_ListenerCallBack( Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex );
	virtual void OnFrameEvent_After_ListenerCallBack( Bone *pBone, const std::string &strEventID, int nOriginFrameIndex, int nCurrentFrameIndex );


public:
	virtual int Build() final;
protected:
	virtual int Build_Base() final;
	virtual int Build_Items();


public:
	virtual void RefreshDelay( float fDelay ) final;
	virtual void Refresh();
	

	virtual Armature *GetArmature() final;
	virtual ArmatureAnimation *GetArmatureAnimation() final;
	virtual int SetArmatureVisible( bool isVisible ) final;
	virtual int RemoveBone( Bone *pBone, bool isRecursion ) final;
	virtual Bone *GetBone( const std::string &strName ) final;
	virtual Node *GetChildInArmature( int nTag ) final;
	virtual Point GetWorldPosition() final;

	virtual int PlayAnimation( const std::string &strName ) final;
	// >>>>>>>>>>>>>>>>>>>> UI [ end ] <<<<<<<<<<<<<<<<<<<<


	
	static int safe_change_display( Bone *pBone, int nIndex, bool isForce );
	static int set_display_render_node_visible( Bone *pBone, bool isVisible );
	static Size get_content_size_of_display_render_node( Bone *pBone );
}; // end class ArmatureAdapterNode

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__ARMATURE_ADAPTER_NODE_H__
