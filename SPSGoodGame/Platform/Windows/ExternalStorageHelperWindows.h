#ifndef __SPS__GOOD_GAME__PLATFORM__WINDOWS_EXTERNAL_STORAGE_HELPER_WINDOWS_H__
#define __SPS__GOOD_GAME__PLATFORM__WINDOWS_EXTERNAL_STORAGE_HELPER_WINDOWS_H__

#include "../ExternalStorageHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )



__SPS_GG__NS__B_PLATFORM

class ExternalStorageHelperWindows : public ExternalStorageHelper
{
friend class ExternalStorageHelper;

protected:	
	ExternalStorageHelperWindows();
public:
	virtual ~ExternalStorageHelperWindows();


	virtual const bool IsAvailable() override;
	virtual const std::string & GetRootPath() override;
	virtual const long long GetAvailableSize() override;
}; // end class ExternalStorageHelperWindows

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__WINDOWS_EXTERNAL_STORAGE_HELPER_WINDOWS_H__
