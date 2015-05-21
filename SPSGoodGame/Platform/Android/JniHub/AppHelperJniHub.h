#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_APP_HELPER_JNIHUB_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_APP_HELPER_JNIHUB_H__

#include "JniHubCommon.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



__SPS_GG__NS__B_PLATFORM

class AppHelperJniHub
{
public:

	static long get_version_code();
	static std::string get_version_name();
	static std::string get_uuid();
	static std::string get_app_data_root_path();
	static long long get_app_data_path_available_size();
	static long open_url( std::string strUrl );
	static long install_app( std::string strAppFile );
}; // end class AppHelperJniHub

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_APP_HELPER_JNIHUB_H__
