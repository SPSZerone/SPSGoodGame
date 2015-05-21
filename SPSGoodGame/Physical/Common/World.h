#ifndef __SPS__GOOD_GAME__PHYSICAL_COMMON__WORLD_H__
#define __SPS__GOOD_GAME__PHYSICAL_COMMON__WORLD_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "Draw.h"
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
#include "Box2D/Box2D.h"
#endif



__SPS_GG__NS__B_PHYSICAL

class World
{
protected:

	float _gg_fPTMRadio;


#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	b2World *_gg_pB2World;
#endif // #if ( __GG__PHYSICAL_ENGINE == __GG__PHYSICAL_ENGINE_BOX2D )


	Draw *_gg_pDraw;



public:

	World( float fGravityX, float fGravityY, float fPTMRadio = 32 );
	virtual ~World();


	virtual void SetDraw( Draw *pDraw );
	virtual void CreateWorldBoundary( float fOriginX, float fOriginY, float fWidth, float fHeight );
	virtual void CreateWorldBoundaryByPixel( float fOriginX, float fOriginY, float fWidth, float fHeight );


	virtual void Step( float fDeltaTime );
	virtual void DrawDebugData();
	

	inline virtual void SetPTMRadio( float fPTMRadio );
	inline virtual float GetPTMRadio();


#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	virtual b2World *GetB2World();
#endif

}; // end class World

__SPS_GG__NS__END



#endif // #ifndef __SPS__GOOD_GAME__PHYSICAL_COMMON__WORLD_H__
