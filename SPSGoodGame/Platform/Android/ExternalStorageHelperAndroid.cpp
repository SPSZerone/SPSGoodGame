#include "ExternalStorageHelperAndroid.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "JniHub/ExternalStorageHelperJniHub.h"
__SPS_GG__NS__U_PLATFORM;



ExternalStorageHelper *ExternalStorageHelper::get_instance()
{
	if ( _gg_g_ExternalStorageHelper == nullptr )
	{
		_gg_g_ExternalStorageHelper = new ExternalStorageHelperAndroid();
	}
	return _gg_g_ExternalStorageHelper;
}



ExternalStorageHelperAndroid::ExternalStorageHelperAndroid()
{
	
}



ExternalStorageHelperAndroid::~ExternalStorageHelperAndroid()
{
	
}



const bool ExternalStorageHelperAndroid::IsAvailable()
{
	return ExternalStorageHelperJniHub::is_available();
}



const std::string & ExternalStorageHelperAndroid::GetRootPath()
{
	if ( _gg_strRootPath.empty() )
	{
		_gg_strRootPath = ExternalStorageHelperJniHub::get_root_path();
	}

	return _gg_strRootPath;
}



const long long ExternalStorageHelperAndroid::GetAvailableSize()
{
	return ExternalStorageHelperJniHub::get_available_size();
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
