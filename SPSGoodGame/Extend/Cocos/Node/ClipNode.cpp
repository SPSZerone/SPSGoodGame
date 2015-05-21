#include "ClipNode.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



ClipNode::ClipNode()
{
	_gg_ClipSize = Size::ZERO;
	_gg_ClipAnchor = Point( 0.5f, 0.5f );
}



ClipNode::~ClipNode()
{

}



bool ClipNode::init()
{
	Node::init();

	_gg_ClipSize = Director::getInstance()->getVisibleSize();
	_gg_ClipAnchor = Point( 0.5f, 0.5f );

	return true;
}



Size ClipNode::SetClipSize( const Size &size )
{
	_gg_ClipSize = size;
	return _gg_ClipSize;
}



Size ClipNode::GetClipSize() const
{
	return _gg_ClipSize;
}



Point ClipNode::SetClipAnchor( const Point &anchor )
{
	_gg_ClipAnchor = anchor;
	return _gg_ClipAnchor;
}



Point ClipNode::GetClipAnchor() const
{
	return _gg_ClipAnchor;
}



Point ClipNode::GetOriginPosition() const
{
	return GetAnchorPosition( Point( 0.0f, 0.0f ) );
}



Point ClipNode::GetAnchorPosition( const Point &anchor ) const
{
	Point position;

	const Size contentSize = getContentSize();

	position.x = _gg_ClipSize.width * ( anchor.x - _gg_ClipAnchor.x );
	position.y = _gg_ClipSize.height * ( anchor.y - _gg_ClipAnchor.y );

	return position;
}



void ClipNode::visit( Renderer *pRenderer, const Mat4& parentTransform, uint32_t parentFlags )
{
	glEnable( GL_SCISSOR_TEST );

	const float fScaleX = getScaleX();
	const float fScaleY = getScaleY();
	Point worldPosition = getPosition();
	if ( getParent() )
	{
		worldPosition = getParent()->convertToWorldSpace( worldPosition );
	}
	
	Director::getInstance()->getOpenGLView()->setScissorInPoints(
		worldPosition.x - _gg_ClipSize.width * fScaleX * _gg_ClipAnchor.x,
		worldPosition.y - _gg_ClipSize.height * fScaleY * _gg_ClipAnchor.y,
		_gg_ClipSize.width * fScaleX,
		_gg_ClipSize.height * fScaleY );
	
	Node::visit( pRenderer, parentTransform, parentFlags );

	glDisable( GL_SCISSOR_TEST );
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
