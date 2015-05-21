#ifndef __SPS__GOOD_GAME__PLATFORM__EXTERNAL_STORAGE_HELPER_H__
#define __SPS__GOOD_GAME__PLATFORM__EXTERNAL_STORAGE_HELPER_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "SPSGoodGame/Base/Common.h"
#include <string>
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_PLATFORM

class ExternalStorageHelper
{
protected:
	std::string _gg_strRootPath;
	

	static ExternalStorageHelper *_gg_g_ExternalStorageHelper;
	ExternalStorageHelper();
	

public:
	static ExternalStorageHelper *get_instance();
	static void destroy_instance();
	virtual ~ExternalStorageHelper();


	virtual const bool IsAvailable() = 0;
	virtual const std::string & GetRootPath() = 0;
	virtual const long long GetAvailableSize() = 0;
}; // end class ExternalStorageHelper

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__EXTERNAL_STORAGE_HELPER_H__
