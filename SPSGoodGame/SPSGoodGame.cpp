#include "SPSGoodGame.h"
__SPS_GG__NS__U_GG;
__SPS_GG__NS__U_ADAPTER;
__SPS_GG__NS__U_ENCODING;
__SPS_GG__NS__U_EXTEND_COCOS;
__SPS_GG__NS__U_EXTEND_FREETYPE;
__SPS_GG__NS__U_PLATFORM;
__SPS_GG__NS__U_UTIL;



void SPSGoodGame::destroy_all_instances()
{
	AppHelper::destroy_instance();
	ExternalStorageHelper::destroy_instance();
	FileSystemHelper::destroy_instance();
	LogHelper::destroy_instance();
	NetworkHelper::destroy_instance();

	FTH_Maker::destroy_ft_library();
}
