#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__PHYSICAL_NODE_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_NODE__PHYSICAL_NODE_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "SPSGoodGame/Physical/Common/World.h"
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_PHYSICAL;



__SPS_GG__NS__B_EXTEND_COCOS

class PhysicalNode;
class PhysicalNodeListener
{
public:
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	// return 0 sync sprite by PhysicalNode
	virtual int PhysicalNode_UpdateBody( PhysicalNode *pPhysicalNode, b2Body *pBody, float delta ) { return 0; }
#endif
};

class PhysicalNode : public Node
{
protected:
	World *_gg_pWorld;
	PhysicalNodeListener *_gg_pListener;
	Mat4 _gg_modelViewMV;
    CustomCommand _gg_customCommand;


public:


	CREATE_FUNC( PhysicalNode );

	PhysicalNode();
	virtual ~PhysicalNode();
	virtual bool init() override;
	
	virtual void SetWorld( World *pWorld );

	virtual void SetListener( PhysicalNodeListener *pListener );
	virtual PhysicalNodeListener *GetListener();

    virtual void update( float delta ) override;

    virtual void draw( Renderer *pRenderer, const Mat4& transform, uint32_t flags ) override;
	virtual void OnDraw();
}; // end class PhysicalNode

__SPS_GG__NS__END


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__PHYSICAL_NODE_H__
