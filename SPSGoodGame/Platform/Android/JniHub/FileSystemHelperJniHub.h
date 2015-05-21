#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_FILE_SYSTEM_HELPER_JNIHUB_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_FILE_SYSTEM_HELPER_JNIHUB_H__

#include "JniHubCommon.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



__SPS_GG__NS__B_PLATFORM

class FileSystemHelperJniHub
{
public:
	static long long get_available_size( const std::string &strFullPath );
}; // end class FileSystemHelperJniHub

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_FILE_SYSTEM_HELPER_JNIHUB_H__
