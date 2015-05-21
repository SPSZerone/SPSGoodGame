#ifndef __SPS__GOOD_GAME__PLATFORM__WINDOWS_FILE_SYSTEM_HELPER_WINDOWS_H__
#define __SPS__GOOD_GAME__PLATFORM__WINDOWS_FILE_SYSTEM_HELPER_WINDOWS_H__

#include "../NetworkHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )



__SPS_GG__NS__B_PLATFORM

class NetworkHelperWindows : public NetworkHelper
{
friend class NetworkHelper;

protected:
	
	NetworkHelperWindows();


public:
	virtual ~NetworkHelperWindows();


	virtual const bool IsConnectedOfActiveNetwork() override;
	virtual const long GetActiveNetworkType() override;
	virtual const bool IsWifiOfActiveNetworkType() override;
	virtual const bool IsMobileOfActiveNetworkType() override;
	virtual const bool IsWifiConnected() override;
	virtual const bool IsMobileConnected() override;
	virtual const std::string & GetIPAddress() override;
}; // end class NetworkHelperWindows

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )

#endif // #ifndef __NETWORK_HELPER_WINDOWS_H__
