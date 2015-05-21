#include "FileSystemHelperAndroid.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "JniHub/FileSystemHelperJniHub.h"
__SPS_GG__NS__U_PLATFORM;



FileSystemHelper *FileSystemHelper::get_instance()
{
	if ( _gg_g_FileSystemHelper == nullptr )
	{
		_gg_g_FileSystemHelper = new FileSystemHelperAndroid();
	}

	return _gg_g_FileSystemHelper;
}



FileSystemHelperAndroid::FileSystemHelperAndroid()
{
	
}



FileSystemHelperAndroid::~FileSystemHelperAndroid()
{
	
}



const long long FileSystemHelperAndroid::GetAvailableSize( const std::string &strFullPath )
{
	if ( strFullPath.empty() )
	{
		return 0;
	}
	return FileSystemHelperJniHub::get_available_size( strFullPath );
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
