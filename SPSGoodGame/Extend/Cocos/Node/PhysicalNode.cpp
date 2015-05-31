#include "PhysicalNode.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



PhysicalNode::PhysicalNode()
{
	_gg_pWorld = nullptr;
	_gg_pListener = nullptr;
	_gg_isShowDebugDraw = false;
}



PhysicalNode::~PhysicalNode()
{
	
}



bool PhysicalNode::init()
{
	Node::init();

    scheduleUpdate();
	
	return true;
}



void PhysicalNode::SetWorld( World *pWorld )
{
	_gg_pWorld = pWorld;
}



void PhysicalNode::SetListener( PhysicalNodeListener *pListener )
{
	_gg_pListener = pListener;
}



PhysicalNodeListener *PhysicalNode::GetListener()
{
	return _gg_pListener;
}


void PhysicalNode::SwitchDebugDraw(bool isShowDebugDraw)
{
	_gg_isShowDebugDraw = isShowDebugDraw;
}


void PhysicalNode::update( float delta )
{
	if ( _gg_pWorld == nullptr )
	{
		return ;
	}

	
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )


	b2World *pb2World = _gg_pWorld->GetB2World();
	if ( pb2World == nullptr )
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
	pb2World->Step( delta, velocityIterations, positionIterations );


	//Iterate over the bodies in the physics world
	for ( b2Body *pBody = pb2World->GetBodyList(); pBody; pBody = pBody->GetNext() )
	{
		int nCode = 0;
		if ( _gg_pListener )
		{
			nCode = _gg_pListener->PhysicalNode_UpdateBody( this, pBody, delta );
		}

		if ( nCode != 0 )
		{
			continue;
		}
		
		//Synchronize the AtlasSprites position and rotation with the corresponding body
		Node *pNode = ( Node * )( pBody->GetUserData() );
		if ( pNode == nullptr )
		{
			continue;
		}

		if ( pNode->isVisible() == false )
		{
			continue;
		}

		b2Vec2 position = pBody->GetPosition();
		pNode->setPosition( Point( position.x * _gg_pWorld->GetPTMRadio(), position.y * _gg_pWorld->GetPTMRadio() ) );
		pNode->setRotation( -1 * CC_RADIANS_TO_DEGREES( pBody->GetAngle() ) );
	} // end for Iterate over the bodies in the physics world


#endif // #if ( __GG__PHYSICAL_ENGINE == __GG__PHYSICAL_ENGINE_BOX2D )
	
}



void PhysicalNode::draw( Renderer *pRenderer, const Mat4& transform, uint32_t flags )
{
    Node::draw( pRenderer, transform, flags );

	if (_gg_isShowDebugDraw)
	{
		GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
		Director* director = Director::getInstance();
		director->pushMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );
    
		_gg_modelViewMV = director->getMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );

		_gg_customCommand.init( _globalZOrder );
		_gg_customCommand.func = CC_CALLBACK_0( PhysicalNode::OnDraw, this );
		pRenderer->addCommand( &_gg_customCommand );

		director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	}
}



void PhysicalNode::OnDraw()
{
	if ( _gg_pWorld == nullptr )
	{
		return ;
	}

    Director* director = Director::getInstance();
    
    Mat4 oldMV;
    oldMV = director->getMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW );
    director->loadMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _gg_modelViewMV );
	
	glLineWidth( 1.0f );
    _gg_pWorld->DrawDebugData();

    director->loadMatrix( MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV );
}



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
