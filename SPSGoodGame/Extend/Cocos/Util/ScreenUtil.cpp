#include "ScreenUtil.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



Point ScreenUtil::origin_visible()
{
	return Director::getInstance()->getVisibleOrigin();
}



Size ScreenUtil::size_visible()
{
	return Director::getInstance()->getVisibleSize();
}



Rect ScreenUtil::rect_visible()
{
	Point origin = origin_visible();
	Size size = size_visible();
	return Rect( origin.x, origin.y, size.width, size.height );
}



Point ScreenUtil::position_visible( Anchor eAnchor )
{
	switch( eAnchor )
	{
	case Anchor::ORIGIN: return position_visible( Point::ZERO );
	case Anchor::CENTER: return position_visible( Point::ANCHOR_MIDDLE );
	case Anchor::LEFT_BOTTOM: return position_visible( Point::ANCHOR_BOTTOM_LEFT );
	case Anchor::LEFT_TOP: return position_visible( Point::ANCHOR_TOP_LEFT );
	case Anchor::RIGHT_BOTTOM: return position_visible( Point::ANCHOR_BOTTOM_RIGHT );
	case Anchor::RIGHT_TOP: return position_visible( Point::ANCHOR_TOP_RIGHT );
	}

	return position_visible( Point::ZERO );
}



Point ScreenUtil::position_visible( const Point &anchor )
{
	return position_visible( anchor.x, anchor.y );
}



Point ScreenUtil::position_visible( float anchorX, float anchorY )
{
	auto originVisible = origin_visible();
	auto sizeVisible = size_visible();
	return Point( originVisible.x + sizeVisible.width * anchorX, originVisible.y + sizeVisible.height * anchorY );
}



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
