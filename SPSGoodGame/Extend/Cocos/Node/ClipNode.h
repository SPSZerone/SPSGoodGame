#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__CLIP_NODE_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_NODE__CLIP_NODE_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_EXTEND_COCOS

class ClipNode : public Node
{
protected:
	Size _gg_ClipSize;
	Point _gg_ClipAnchor;



public:
	CREATE_FUNC( ClipNode );

	ClipNode();
	virtual ~ClipNode();
	virtual bool init() override;


	virtual Size SetClipSize( const Size &size );
	virtual Size GetClipSize() const;
	virtual Point SetClipAnchor( const Point &anchor );
	virtual Point GetClipAnchor() const;
	

	/* 坐标系为节点自身
		以左下角为起点
	*/
	virtual Point GetOriginPosition() const;
	// 相对坐标：0~1 e.g. 左下角、右下角、中心
	virtual Point GetAnchorPosition( const Point &anchor ) const;

	
    // Overrides
	virtual void visit( Renderer *pRenderer, const Mat4& parentTransform, uint32_t parentFlags ) override;
}; // end class ClipNode

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_NODE__CLIP_NODE_H__
