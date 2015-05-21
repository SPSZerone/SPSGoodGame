#ifndef __SPS__GOOD_GAME__EXTEND_BOX2D_COMMON__B2DRAWGLES_H__
#define __SPS__GOOD_GAME__EXTEND_BOX2D_COMMON__B2DRAWGLES_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "Box2D/Box2D.h"
#include "cocos2d.h"
using namespace cocos2d;


struct b2AABB;


__SPS_GG__NS__B_EXTEND_BOX2D

class B2DrawGLES : public b2Draw
{
protected:
    float32 mRatio;
    cocos2d::GLProgram* mShaderProgram;
    GLint        mColorLocation;

    void initShader( void );


public:
	B2DrawGLES();
	B2DrawGLES( float fPTMRatio );
	virtual ~B2DrawGLES();


	virtual void EnableAllDrawFlags();


	// >>>>>>>>>> b2Draw [begin] <<<<<<<<<<
    virtual void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    virtual void DrawTransform(const b2Transform& xf);
    virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
    virtual void DrawString(int x, int y, const char* string, ...);
    virtual void DrawAABB(b2AABB* aabb, const b2Color& color);
	// >>>>>>>>>> b2Draw [end] <<<<<<<<<<

}; // end class B2DrawGLES

__SPS_GG__NS__END



#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_BOX2D_COMMON__B2DRAWGLES_H__
