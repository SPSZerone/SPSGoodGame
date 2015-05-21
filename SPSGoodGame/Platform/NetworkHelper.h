#ifndef __SPS__GOOD_GAME__PLATFORM__NETWORK_HELPER_H__
#define __SPS__GOOD_GAME__PLATFORM__NETWORK_HELPER_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "SPSGoodGame/Base/Common.h"
#include <string>
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_PLATFORM

class NetworkHelper
{
protected:
	std::string _gg_strIP;
	

	static NetworkHelper *_gg_g_NetworkHelper;
	NetworkHelper();
	

public:
	static NetworkHelper *get_instance();
	static void destroy_instance();
	virtual ~NetworkHelper();


	virtual const bool IsConnectedOfActiveNetwork() = 0;
	virtual const long GetActiveNetworkType() = 0;
	virtual const bool IsWifiOfActiveNetworkType() = 0;
	virtual const bool IsMobileOfActiveNetworkType() = 0;
	virtual const bool IsWifiConnected() = 0;
	virtual const bool IsMobileConnected() = 0;
	virtual const std::string & GetIPAddress() = 0;
}; // end class NetworkHelper

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__NETWORK_HELPER_H__
