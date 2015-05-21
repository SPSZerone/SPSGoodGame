#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_UTIL__SCREEN_UTIL_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_UTIL__SCREEN_UTIL_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_EXTEND_COCOS

class ScreenUtil
{
public:
	enum class Anchor
	{
		ORIGIN,
		CENTER,
		LEFT_BOTTOM,
		LEFT_TOP,
		RIGHT_BOTTOM,
		RIGHT_TOP,
	};


	static Point origin_visible();
	static Size size_visible();
	static Rect rect_visible();


	static Point position_visible( Anchor eAnchor );
	static Point position_visible( float anchorX, float anchorY );
	static Point position_visible( const Point &anchor );
}; // end class ScreenUtil

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_UTIL__SCREEN_UTIL_H__
