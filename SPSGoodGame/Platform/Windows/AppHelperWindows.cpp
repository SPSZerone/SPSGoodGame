#include "AppHelperWindows.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
__SPS_GG__NS__U_PLATFORM;



AppHelper *AppHelper::get_instance()
{
	if ( _gg_g_AppHelper == nullptr )
	{
		_gg_g_AppHelper = new AppHelperWindows();
	}
	return _gg_g_AppHelper;
}



AppHelperWindows::AppHelperWindows()
{
	
}



AppHelperWindows::~AppHelperWindows()
{

}



const long AppHelperWindows::GetVersionCode()
{
	return _gg_nVersionCode;
}



const std::string & AppHelperWindows::GetVersionName()
{
	return _gg_strVersionName;
}



const long AppHelperWindows::GetVersionMajor()
{
	return _gg_nVersionMajor;
}



const long AppHelperWindows::GetVersionMinor()
{
	return _gg_nVersionMinor;
}



const long AppHelperWindows::GetVersionRevision()
{
	return _gg_nVersionRevision;
}



const std::string & AppHelperWindows::GetUUID()
{
	return _gg_strUUID;
}



const std::string & AppHelperWindows::GetAppDataRootPath()
{
	return _gg_strAppDataRootPath;
}



const long long AppHelperWindows::GetAppDataPathAvailableSize()
{
	return 0;
}



const long AppHelperWindows::InstallApp( const std::string &strAppFile )
{
	return 0;
}



const long AppHelperWindows::OpenUrl( const std::string &strUrl )
{
	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
