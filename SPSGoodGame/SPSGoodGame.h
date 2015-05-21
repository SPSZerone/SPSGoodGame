/*
  Copyright (c) ChenWei（陈威）
*/
#ifndef __SPS__GOOD_GAME__GOOD_GAME_H__
#define __SPS__GOOD_GAME__GOOD_GAME_H__



#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Common.h"
#include "SPSGoodGame/Base/Config.h"
#include "SPSGoodGame/Base/Const.h"
#include "SPSGoodGame/Base/Version.h"

#include "SPSGoodGame/Adapter/DataAdapter.h"

#include "SPSGoodGame/Encoding/Encoding.h"

#include "SPSGoodGame/Extend/Box2D/Common/B2DrawGLES.h"
#include "SPSGoodGame/Extend/Box2D/Util/Box2DUtil.h"

#include "SPSGoodGame/Extend/Cocos/Adapter/DataAdapterObject.h"
#include "SPSGoodGame/Extend/Cocos/Node/ArmatureAdapterNode.h"
#include "SPSGoodGame/Extend/Cocos/Node/ClipNode.h"
#include "SPSGoodGame/Extend/Cocos/Node/DataNode.h"
#include "SPSGoodGame/Extend/Cocos/Node/PhysicalNode.h"
#include "SPSGoodGame/Extend/Cocos/Node/SingleTouchNode.h"
#include "SPSGoodGame/Extend/Cocos/Node/SlotNode.h"
#include "SPSGoodGame/Extend/Cocos/Touch/SingleTouch.h"
#include "SPSGoodGame/Extend/Cocos/Util/ScreenUtil.h"
#include "SPSGoodGame/Extend/Cocos/Widget/EditTextFT.h"
#include "SPSGoodGame/Extend/Cocos/Widget/SingleDisplayView.h"
#include "SPSGoodGame/Extend/Cocos/Widget/TextViewFT.h"

#include "SPSGoodGame/Extend/FreeType/Base/FTH_Base.h"
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Config.h"
#include "SPSGoodGame/Extend/FreeType/Base/FTH_Common.h"
#include "SPSGoodGame/Extend/FreeType/Helper/FTH_Maker.h"
#include "SPSGoodGame/Extend/FreeType/Util/FTH_Util.h"

#include "SPSGoodGame/Math/Base/Vector.h"
#include "SPSGoodGame/Math/Util/MathUtil.h"
#include "SPSGoodGame/Math/Util/ShapeUtil.h"

#include "SPSGoodGame/Physical/Common/Draw.h"
#include "SPSGoodGame/Physical/Common/World.h"

#include "SPSGoodGame/Platform/AppHelper.h"
#include "SPSGoodGame/Platform/ExternalStorageHelper.h"
#include "SPSGoodGame/Platform/FileSystemHelper.h"
#include "SPSGoodGame/Platform/LogHelper.h"
#include "SPSGoodGame/Platform/NetworkHelper.h"

#include "SPSGoodGame/Util/CPUUtil.h"
#include "SPSGoodGame/Util/TimeUtil.h"



__SPS_GG__NS__B_GG

class SPSGoodGame
{
public:
	static void destroy_all_instances();
}; // end class SPSGoodGame

__SPS_GG__NS__END // end __SPS_GG__NS__B_GG



#endif // #ifndef __SPS__GOOD_GAME__GOOD_GAME_H__
