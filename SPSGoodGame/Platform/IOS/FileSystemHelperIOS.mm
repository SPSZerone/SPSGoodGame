#include "FileSystemHelperIOS.h"
__SPS_GG__NS__U_PLATFORM;

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



FileSystemHelper *FileSystemHelper::get_instance()
{
	if ( _gg_g_FileSystemHelper == nullptr )
	{
		_gg_g_FileSystemHelper = new FileSystemHelperIOS();
	}
	return _gg_g_FileSystemHelper;
}



FileSystemHelperIOS::FileSystemHelperIOS()
{
	
}



FileSystemHelperIOS::~FileSystemHelperIOS()
{
	
}



const long long FileSystemHelperIOS::GetAvailableSize( const std::string &strFullPath )
{
	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
