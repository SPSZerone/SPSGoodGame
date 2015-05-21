#ifndef __SPS__GOOD_GAME__PLATFORM__IOS_NETWORK_HELPER_IOS_H__
#define __SPS__GOOD_GAME__PLATFORM__IOS_NETWORK_HELPER_IOS_H__

#include "../NetworkHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



__SPS_GG__NS__B_EXTEND_COCOS2DX

class NetworkHelperIOS : public NetworkHelper
{
friend class NetworkHelper;

protected:
	
	NetworkHelperIOS();


public:
	virtual ~NetworkHelperIOS();


	virtual const bool IsConnectedOfActiveNetwork() override;
	virtual const long GetActiveNetworkType() override;
	virtual const bool IsWifiOfActiveNetworkType() override;
	virtual const bool IsMobileOfActiveNetworkType() override;
	virtual const bool IsWifiConnected() override;
	virtual const bool IsMobileConnected() override;
	virtual const std::string & GetIPAddress() override;
}; // end class NetworkHelperIOS

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS2DX



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__IOS_NETWORK_HELPER_IOS_H__
