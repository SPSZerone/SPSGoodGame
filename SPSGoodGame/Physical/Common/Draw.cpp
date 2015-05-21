#include "Draw.h"
__SPS_GG__NS__U_PHYSICAL;



Draw::Draw( float fPTMRatio )
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
	_gg_pB2Draw = new B2DrawGLES( fPTMRatio );
#endif
}



Draw::~Draw()
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
	if ( _gg_pB2Draw )
	{
		delete _gg_pB2Draw;
		_gg_pB2Draw = nullptr;
	}
#endif
}



void Draw::EnableAllDrawFlags()
{
#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
	if ( _gg_pB2Draw )
	{
		_gg_pB2Draw->EnableAllDrawFlags();
	}
#endif
}



#if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

b2Draw *Draw::GetB2Draw()
{
	return _gg_pB2Draw;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__BOX2D ) ) && ( __SPS_GG__SUPPORT__BOX2D ) && ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
