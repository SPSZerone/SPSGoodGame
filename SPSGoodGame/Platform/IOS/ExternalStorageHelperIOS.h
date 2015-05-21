#ifndef __SPS__GOOD_GAME__PLATFORM__IOS_EXTERNAL_STORAGE_HELPER_IOS_H__
#define __SPS__GOOD_GAME__PLATFORM__IOS_EXTERNAL_STORAGE_HELPER_IOS_H__

#include "../ExternalStorageHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



__SPS_GG__NS__B_PLATFORM

class ExternalStorageHelperIOS : public ExternalStorageHelper
{
friend class ExternalStorageHelper;

protected:	
	ExternalStorageHelperIOS();
public:
	virtual ~ExternalStorageHelperIOS();


	virtual const bool IsAvailable() override;
	virtual const std::string & GetRootPath() override;
	virtual const long long GetAvailableSize() override;
}; // end class ExternalStorageHelperIOS

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__IOS_EXTERNAL_STORAGE_HELPER_IOS_H__
