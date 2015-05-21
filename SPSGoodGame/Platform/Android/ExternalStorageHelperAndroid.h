#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_EXTERNAL_STORAGE_HELPER_ANDROID_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_EXTERNAL_STORAGE_HELPER_ANDROID_H__

#include "../ExternalStorageHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



__SPS_GG__NS__B_PLATFORM

class ExternalStorageHelperAndroid : public ExternalStorageHelper
{
friend class ExternalStorageHelper;

protected:	
	ExternalStorageHelperAndroid();


public:
	virtual ~ExternalStorageHelperAndroid();


	virtual const bool IsAvailable() override;
	virtual const std::string & GetRootPath() override;
	virtual const long long GetAvailableSize() override;
}; // end class ExternalStorageHelperAndroid

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_EXTERNAL_STORAGE_HELPER_ANDROID_H__
