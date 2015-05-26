#include "AppHelperIOS.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
__SPS_GG__NS__U_PLATFORM;



AppHelper *AppHelper::get_instance()
{
	if ( _gg_g_AppHelper == nullptr )
	{
		_gg_g_AppHelper = new AppHelperIOS();
	}
	return _gg_g_AppHelper;
}



AppHelperIOS::AppHelperIOS()
{

}



AppHelperIOS::~AppHelperIOS()
{

}



const long AppHelperIOS::GetVersionCode()
{
	return _gg_nVersionCode;
}



const std::string &AppHelperIOS::GetVersionName()
{
	return _gg_strVersionName;
}



const long AppHelperIOS::GetVersionMajor()
{
	if ( _gg_strVersionName.empty() )
	{
		GetVersionName();
	}

	return _gg_nVersionMajor;
}



const long AppHelperIOS::GetVersionMinor()
{
	if ( _gg_strVersionName.empty() )
	{
		GetVersionName();
	}

	return _gg_nVersionMinor;
}



const long AppHelperIOS::GetVersionRevision()
{
	if ( _gg_strVersionName.empty() )
	{
		GetVersionName();
	}

	return _gg_nVersionRevision;
}



const std::string &AppHelperIOS::GetUUID()
{
	if ( _gg_strUUID.empty() )
	{
		// TODO
		// _gg_strUUID = ;
	}

	return _gg_strUUID;
}



const std::string &AppHelperIOS::GetAppDataRootPath()
{
	if ( _gg_strAppDataRootPath.empty() )
	{
		// TODO
		// _gg_strAppDataRootPath = ;
	}

	return _gg_strAppDataRootPath;
}



const long long AppHelperIOS::GetAppDataPathAvailableSize()
{
	// TODO
	return 0;
}



const long AppHelperIOS::InstallApp( const std::string &strAppFile )
{
	// TODO
	return 0;
}



const long AppHelperIOS::OpenUrl( const std::string &strUrl )
{
	// TODO
	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
