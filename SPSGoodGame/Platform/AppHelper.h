#ifndef __SPS__GOOD_GAME__PLATFORM__APP_HELPER_H__
#define __SPS__GOOD_GAME__PLATFORM__APP_HELPER_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "SPSGoodGame/Base/Common.h"
#include <string>
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_PLATFORM

class AppHelper
{
protected:
	long _gg_nVersionCode;
	std::string _gg_strVersionName;
	long _gg_nVersionMajor;
	long _gg_nVersionMinor;
	long _gg_nVersionRevision;


	std::string _gg_strUUID;
	std::string _gg_strAppDataRootPath;

	
	static AppHelper *_gg_g_AppHelper;
	AppHelper();


public:
	static AppHelper *get_instance();
	static void destroy_instance();
	virtual ~AppHelper();


	virtual int ParserVersionName();

	virtual const long GetVersionCode() = 0;
	virtual const std::string &GetVersionName() = 0;
	virtual const long GetVersionMajor() = 0;
	virtual const long GetVersionMinor() = 0;
	virtual const long GetVersionRevision() = 0;
	
	virtual const std::string &GetUUID() = 0;
	virtual const std::string &GetAppDataRootPath() = 0;
	virtual const long long GetAppDataPathAvailableSize() = 0;

	virtual const long InstallApp( const std::string &strAppFile ) = 0;
	virtual const long OpenUrl( const std::string &strUrl ) = 0;
}; // end class AppHelper

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__APP_HELPER_H__
