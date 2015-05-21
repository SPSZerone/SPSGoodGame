#include "Box2DUtil.h"
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
__SPS_GG__NS__U_EXTEND_BOX2D;



void Box2DUtil::destroy_joint( b2Body *pBody )
{
	if ( pBody )
	{
		b2World *pWorld = pBody->GetWorld();
		if ( pWorld )
		{
			b2JointEdge *pJointEdge = pBody->GetJointList();
			if ( pJointEdge )
			{
				b2Joint *pJointDestroy = pJointEdge->joint;
				if ( pJointDestroy )
				{
					pWorld->DestroyJoint( pJointDestroy );
				}
			}
		}
	}	
}



void Box2DUtil::disable_collision( b2Body *pBody )
{
	if ( pBody )
	{
		for ( b2Fixture *pFixture = pBody->GetFixtureList(); pFixture; pFixture = pFixture->GetNext() )
		{
			disable_collision( pFixture );
		}
	}
}



void Box2DUtil::disable_collision( b2Fixture *pFixture )
{
	if ( pFixture )
	{
		b2Filter filter;
		filter.groupIndex = -999;
		filter.categoryBits = 0;
		filter.maskBits = 0;
		pFixture->SetFilterData( filter );
	}
}



#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) )
