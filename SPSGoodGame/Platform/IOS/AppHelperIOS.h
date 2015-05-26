#ifndef __SPS__GOOD_GAME__PLATFORM__IOS_APP_HELPER_IOS_H__
#define __SPS__GOOD_GAME__PLATFORM__IOS_APP_HELPER_IOS_H__

#include "../AppHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



__SPS_GG__NS__B_PLATFORM

class AppHelperIOS : public AppHelper
{
friend class AppHelper;

protected:	
	AppHelperIOS();


public:
	virtual ~AppHelperIOS();


	virtual const long GetVersionCode() override;
	virtual const std::string &GetVersionName() override;
	virtual const long GetVersionMajor() override;
	virtual const long GetVersionMinor() override;
	virtual const long GetVersionRevision() override;
	
	virtual const std::string &GetUUID() override;
	virtual const std::string &GetAppDataRootPath() override;
	virtual const long long GetAppDataPathAvailableSize() override;

	virtual const long InstallApp( const std::string &strAppFile ) override;
	virtual const long OpenUrl( const std::string &strUrl ) override;
}; // end class AppHelperIOS

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__IOS_APP_HELPER_IOS_H__
