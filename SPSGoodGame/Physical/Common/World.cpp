#include "World.h"
__SPS_GG__NS__U_PHYSICAL;



World::World( float fGravityX, float fGravityY, float fPTMRadio )
	: _gg_fPTMRadio( fPTMRadio )
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	_gg_pB2World = new b2World( b2Vec2( fGravityX, fGravityY ) );
#endif

	_gg_pDraw = nullptr;
}



World::~World()
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	if ( _gg_pB2World )
	{
		delete _gg_pB2World;
		_gg_pB2World = nullptr;
	}
#endif
}



void World::SetDraw( Draw *pDraw )
{
	_gg_pDraw = pDraw;

	if ( _gg_pDraw )
	{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
		if ( _gg_pDraw->GetB2Draw() )
		{
			_gg_pB2World->SetDebugDraw( _gg_pDraw->GetB2Draw() );
		}
#endif
	}
}



void World::CreateWorldBoundary( float fOriginX, float fOriginY, float fWidth, float fHeight )
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	if ( _gg_pB2World == nullptr )
	{
		return ;
	}

	
	b2BodyDef bodyDef;
	b2EdgeShape edgeShape;
	b2FixtureDef fixtureDef;


	bodyDef.type = b2_staticBody;
	bodyDef.position.Set( fOriginX, fOriginY );

	fixtureDef.shape = &edgeShape;


	b2Body *worldBody = _gg_pB2World->CreateBody( &bodyDef );

	// Left vertical
	edgeShape.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( 0.0f, fHeight ) );
	worldBody->CreateFixture( &fixtureDef );

	// Right vertical
	edgeShape.Set( b2Vec2( fWidth, 0.0f ), b2Vec2( fWidth, fHeight ) );
	worldBody->CreateFixture( &fixtureDef );

	// Top horizontal
	edgeShape.Set( b2Vec2( 0.0f, fHeight ), b2Vec2( fWidth, fHeight ) );
	worldBody->CreateFixture( &fixtureDef );

	// Bottom horizontal
	edgeShape.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( fWidth, 0.0f ) );
	worldBody->CreateFixture( &fixtureDef );
#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
}



void World::CreateWorldBoundaryByPixel( float fOriginX, float fOriginY, float fWidth, float fHeight )
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	if ( _gg_pB2World == nullptr )
	{
		return ;
	}

	
	b2BodyDef bodyDef;
	b2EdgeShape edgeShape;
	b2FixtureDef fixtureDef;


	bodyDef.type = b2_staticBody;
	bodyDef.position.Set( fOriginX, fOriginY );

	fixtureDef.shape = &edgeShape;


	b2Body *worldBody = _gg_pB2World->CreateBody( &bodyDef );

	// Left vertical
	edgeShape.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( 0.0f, fHeight / _gg_fPTMRadio ) );
	worldBody->CreateFixture( &fixtureDef );

	// Right vertical
	edgeShape.Set( b2Vec2( fWidth / _gg_fPTMRadio, 0.0f ), b2Vec2( fWidth / _gg_fPTMRadio, fHeight / _gg_fPTMRadio ) );
	worldBody->CreateFixture( &fixtureDef );

	// Top horizontal
	edgeShape.Set( b2Vec2( 0.0f, fHeight / _gg_fPTMRadio ), b2Vec2( fWidth / _gg_fPTMRadio, fHeight / _gg_fPTMRadio ) );
	worldBody->CreateFixture( &fixtureDef );

	// Bottom horizontal
	edgeShape.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( fWidth / _gg_fPTMRadio, 0.0f ) );
	worldBody->CreateFixture( &fixtureDef );
#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
}



void World::Step( float fDeltaTime )
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	if ( _gg_pB2World == nullptr )
	{
		return ;
	}

	
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	int velocityIterations = 8;
	int positionIterations = 1;


	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	_gg_pB2World->Step( fDeltaTime, velocityIterations, positionIterations );
#endif
}



void World::DrawDebugData()
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
	if ( _gg_pB2World )
	{
		_gg_pB2World->DrawDebugData();
	}
#endif
}



void World::SetPTMRadio( float fPTMRadio )
{
	_gg_fPTMRadio = fPTMRadio;
}



float World::GetPTMRadio()
{
	return _gg_fPTMRadio;
}



#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )

b2World *World::GetB2World()
{
	return _gg_pB2World;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
