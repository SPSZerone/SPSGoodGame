#include "NetworkHelperIOS.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
#include <ifaddrs.h>
#include <arpa/inet.h>

__SPS_GG__NS__U_EXTEND_COCOS2DX;



NetworkHelper *NetworkHelper::GetInstance()
{
	if ( _gg_g_NetworkHelper == nullptr )
	{
		_gg_g_NetworkHelper = new NetworkHelperIOS();
	}

	return _gg_g_NetworkHelper;
}



NetworkHelperIOS::NetworkHelperIOS()
{
	
}



NetworkHelperIOS::~NetworkHelperIOS()
{
	
}



const bool NetworkHelperIOS::IsConnectedOfActiveNetwork()
{
	return false;
}



const long NetworkHelperIOS::GetActiveNetworkType()
{
	return -1;
}



const bool NetworkHelperIOS::IsWifiOfActiveNetworkType()
{
	return false;
}



const bool NetworkHelperIOS::IsMobileOfActiveNetworkType()
{
	return false;
}



const bool NetworkHelperIOS::IsWifiConnected()
{
	return false;
}



const bool NetworkHelperIOS::IsMobileConnected()
{
	return false;
}



const std::string & NetworkHelperIOS::GetIPAddress()
{
	if ( _gg_strIP.empty() == false )
	{
		return _gg_strIP;
	}
	

	NSString *address = @"";
	struct ifaddrs *interfaces = nil;
	struct ifaddrs *temp_addr = nil;
	int success = 0;

	// retrieve the current interfaces - returns 0 on success
	success = getifaddrs( &interfaces );
	if ( success == 0 )
	{
		// Loop through linked list of interfaces
		temp_addr = interfaces;
		while ( temp_addr != nil )
		{
			if( temp_addr->ifa_addr->sa_family == AF_INET )
			{
				// Check if interface is en0 which is the wifi connection on the iPhone
				if ( [[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"] )
				{
					// Get NSString from C String
					address = [ NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr) ];
				}
			}

			temp_addr = temp_addr->ifa_next;
		
		} // end while
	} // end if
	

	// Free memory
	freeifaddrs( interfaces );
	
	
	_gg_strIP = [address UTF8String];
	
	
	return _gg_strIP;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
