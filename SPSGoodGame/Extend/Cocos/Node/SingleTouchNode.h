#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__SINGLE_TOUCH_NODE_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_NODE__SINGLE_TOUCH_NODE_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "SPSGoodGame/Extend/Cocos/Touch/SingleTouch.h"
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_EXTEND_COCOS

class SingleTouchNode : public Node, public SingleTouch
{
public:
	enum class RegisterTouchEventType
	{
		SCENE_GRAPH_PRIORITY,
		FIXED_PRIORITY,
		UNKNOWN,
	};

	enum UITag
	{
		kSingleTouchNode_UITag_DEBUG = -10000,
	};

protected:
	RegisterTouchEventType _gg_eRegisterTouchEventType;
	Size _gg_TouchSize;


public:
	CREATE_FUNC( SingleTouchNode );
	SingleTouchNode();
	virtual ~SingleTouchNode();
	virtual bool init() override;

	
	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExitTransitionDidStart() override;
	virtual void onExit() override;


	virtual void SetRegisterTouchEventType( RegisterTouchEventType eRegisterTouchEventType );
	virtual RegisterTouchEventType GetRegisterTouchEventType() const;
	virtual void SetTouchSize( const Size &touchSize );
	virtual Size GetTouchSize() const;
	virtual int RegisterTouchEventListener( RegisterTouchEventType eRegisterTouchEventType, int nNewTouchPriority, bool isSwallowTouch = true );


	virtual bool IsTouchMe( Touch *pTouch ) const override;


	virtual void DebugDrawEnable( bool isEnable );


	virtual bool OnTouchBegan( Touch *pTouch, Event *pEvent ) override;
	virtual void OnTouchMoved( Touch *pTouch, Event *pEvent ) override;
	virtual void OnTouchEnded( Touch *pTouch, Event *pEvent ) override;
	virtual void OnTouchCancelled( Touch *pTouch, Event *pEvent ) override;
}; // end class SingleTouchNode

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // __SPS__GOOD_GAME__EXTEND_COCOS_NODE__SINGLE_TOUCH_NODE_H__
