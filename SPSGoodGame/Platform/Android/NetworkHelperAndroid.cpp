#include "NetworkHelperAndroid.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "JniHub/NetworkHelperJniHub.h"
__SPS_GG__NS__U_PLATFORM;



NetworkHelper *NetworkHelper::get_instance()
{
	if ( _gg_g_NetworkHelper == nullptr )
	{
		_gg_g_NetworkHelper = new NetworkHelperAndroid();
	}

	return _gg_g_NetworkHelper;
}



NetworkHelperAndroid::NetworkHelperAndroid()
{
	
}



NetworkHelperAndroid::~NetworkHelperAndroid()
{
	
}



const bool NetworkHelperAndroid::IsConnectedOfActiveNetwork()
{
	return NetworkHelperJniHub::is_connected_of_active_network();
}



const long NetworkHelperAndroid::GetActiveNetworkType()
{
	return NetworkHelperJniHub::get_active_network_type();
}



const bool NetworkHelperAndroid::IsWifiOfActiveNetworkType()
{
	return NetworkHelperJniHub::is_wifi_of_active_network_type();
}



const bool NetworkHelperAndroid::IsMobileOfActiveNetworkType()
{
	return NetworkHelperJniHub::is_mobile_of_active_network_type();
}



const bool NetworkHelperAndroid::IsWifiConnected()
{
	return NetworkHelperJniHub::is_wifi_connected();
}



const bool NetworkHelperAndroid::IsMobileConnected()
{
	return NetworkHelperJniHub::is_mobile_connected();
}



const std::string & NetworkHelperAndroid::GetIPAddress()
{
	if ( _gg_strIP.empty() )
	{
		_gg_strIP = NetworkHelperJniHub::get_ip_address();
	}

	return _gg_strIP;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
