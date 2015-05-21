#ifndef __SPS__GOOD_GAME__EXTEND_BOX2D_UTIL__BOX2D_UTIL_H__
#define __SPS__GOOD_GAME__EXTEND_BOX2D_UTIL__BOX2D_UTIL_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
#include "Box2D/Box2D.h"



__SPS_GG__NS__B_EXTEND_BOX2D

class Box2DUtil
{
public:

	static void destroy_joint( b2Body *pBody );
	static void disable_collision( b2Fixture *pFixture );
	static void disable_collision( b2Body *pBody );

}; // end class Box2DUtil

__SPS_GG__NS__END



#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_BOX2D_UTIL__BOX2D_UTIL_H__
