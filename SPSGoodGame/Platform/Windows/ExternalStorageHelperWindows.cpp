#include "ExternalStorageHelperWindows.h"
__SPS_GG__NS__U_PLATFORM;

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )



ExternalStorageHelper *ExternalStorageHelper::get_instance()
{
	if ( _gg_g_ExternalStorageHelper == nullptr )
	{
		_gg_g_ExternalStorageHelper = new ExternalStorageHelperWindows();
	}
	return _gg_g_ExternalStorageHelper;
}



ExternalStorageHelperWindows::ExternalStorageHelperWindows()
{
	
}



ExternalStorageHelperWindows::~ExternalStorageHelperWindows()
{
	
}



const bool ExternalStorageHelperWindows::IsAvailable()
{
	return false;
}



const std::string & ExternalStorageHelperWindows::GetRootPath()
{
	return _gg_strRootPath;
}



const long long ExternalStorageHelperWindows::GetAvailableSize()
{
	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
