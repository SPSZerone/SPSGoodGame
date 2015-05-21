#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_NETWORK_HELPER_JNIHUB_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_NETWORK_HELPER_JNIHUB_H__

#include "JniHubCommon.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



__SPS_GG__NS__B_PLATFORM

class NetworkHelperJniHub
{
public:
	static bool is_connected_of_active_network();
	static long get_active_network_type();
	static bool is_wifi_of_active_network_type();
	static bool is_mobile_of_active_network_type();
	static bool is_wifi_connected();
	static bool is_mobile_connected();
	static std::string get_ip_address();
};; // end class NetworkHelperJniHub

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_NETWORK_HELPER_JNIHUB_H__
