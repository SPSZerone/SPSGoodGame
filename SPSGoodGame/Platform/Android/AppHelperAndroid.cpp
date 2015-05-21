#include "AppHelperAndroid.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "JniHub/AppHelperJniHub.h"
__SPS_GG__NS__U_PLATFORM;



AppHelper *AppHelper::get_instance()
{
	if ( _gg_g_AppHelper == nullptr )
	{
		_gg_g_AppHelper = new AppHelperAndroid();
	}
	return _gg_g_AppHelper;
}



AppHelperAndroid::AppHelperAndroid()
{

}



AppHelperAndroid::~AppHelperAndroid()
{

}



const long AppHelperAndroid::GetVersionCode()
{
	if ( _gg_nVersionCode < 0 )
	{
		_gg_nVersionCode = AppHelperJniHub::get_version_code();
	}

	return _gg_nVersionCode;
}



const std::string &AppHelperAndroid::GetVersionName()
{
	if ( _gg_strVersionName.empty() )
	{
		_gg_strVersionName = AppHelperJniHub::get_version_name();
		ParserVersionName();
	}

	return _gg_strVersionName;
}



const long AppHelperAndroid::GetVersionMajor()
{
	if ( _gg_strVersionName.empty() )
	{
		GetVersionName();
	}

	return _gg_nVersionMajor;
}



const long AppHelperAndroid::GetVersionMinor()
{
	if ( _gg_strVersionName.empty() )
	{
		GetVersionName();
	}

	return _gg_nVersionMinor;
}



const long AppHelperAndroid::GetVersionRevision()
{
	if ( _gg_strVersionName.empty() )
	{
		GetVersionName();
	}

	return _gg_nVersionRevision;
}



const std::string &AppHelperAndroid::GetUUID()
{
	if ( _gg_strUUID.empty() )
	{
		_gg_strUUID = AppHelperJniHub::get_uuid();
	}

	return _gg_strUUID;
}



const std::string &AppHelperAndroid::GetAppDataRootPath()
{
	if ( _gg_strAppDataRootPath.empty() )
	{
		_gg_strAppDataRootPath = AppHelperJniHub::get_app_data_root_path();
	}

	return _gg_strAppDataRootPath;
}



const long long AppHelperAndroid::GetAppDataPathAvailableSize()
{
	return AppHelperJniHub::get_app_data_path_available_size();
}



const long AppHelperAndroid::InstallApp( const std::string &strAppFile )
{
	return AppHelperJniHub::open_url( strAppFile );
}



const long AppHelperAndroid::OpenUrl( const std::string &strUrl )
{
	return AppHelperJniHub::install_app( strUrl );
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
