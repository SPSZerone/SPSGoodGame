#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_NETWORK_HELPER_ANDROID_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_NETWORK_HELPER_ANDROID_H__

#include "../NetworkHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



__SPS_GG__NS__B_PLATFORM

class NetworkHelperAndroid : public NetworkHelper
{
friend class NetworkHelper;

protected:	
	NetworkHelperAndroid();


public:
	virtual ~NetworkHelperAndroid();


	virtual const bool IsConnectedOfActiveNetwork() override;
	virtual const long GetActiveNetworkType() override;
	virtual const bool IsWifiOfActiveNetworkType() override;
	virtual const bool IsMobileOfActiveNetworkType() override;
	virtual const bool IsWifiConnected() override;
	virtual const bool IsMobileConnected() override;
	virtual const std::string & GetIPAddress() override;
}; // end class NetworkHelperAndroid

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_NETWORK_HELPER_ANDROID_H__
