#include "ExternalStorageHelperIOS.h"
__SPS_GG__NS__U_PLATFORM;

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



ExternalStorageHelper *ExternalStorageHelper::get_instance()
{
	if ( _gg_g_ExternalStorageHelper == nullptr )
	{
		_gg_g_ExternalStorageHelper = new ExternalStorageHelperIOS();
	}
	return _gg_g_ExternalStorageHelper;
}



ExternalStorageHelperIOS::ExternalStorageHelperIOS()
{
	
}



ExternalStorageHelperIOS::~ExternalStorageHelperIOS()
{
	
}



const bool ExternalStorageHelperIOS::IsAvailable()
{
	return false;
}



const std::string & ExternalStorageHelperIOS::GetRootPath()
{
	return _gg_strRootPath;
}



const long long ExternalStorageHelperIOS::GetAvailableSize()
{
	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
