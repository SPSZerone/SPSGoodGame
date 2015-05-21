#ifndef __SPS__GOOD_GAME__PHYSICAL_COMMON__DRAW_H__
#define __SPS__GOOD_GAME__PHYSICAL_COMMON__DRAW_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "SPSGoodGame/Extend/Box2D/Common/B2DrawGLES.h"
__SPS_GG__NS__U_EXTEND_BOX2D;
#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )



__SPS_GG__NS__B_PHYSICAL

class Draw
{
protected:
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
	B2DrawGLES *_gg_pB2Draw;
#endif


public:
	Draw( float fPTMRatio );
	virtual ~Draw();


	virtual void EnableAllDrawFlags();


#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
	virtual b2Draw *GetB2Draw();
#endif
}; // end class Draw

__SPS_GG__NS__END



#endif // #ifndef __SPS__GOOD_GAME__PHYSICAL_COMMON__DRAW_H__
