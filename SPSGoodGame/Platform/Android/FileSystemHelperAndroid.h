#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_FILE_SYSTEM_HELPER_ANDROID_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_FILE_SYSTEM_HELPER_ANDROID_H__

#include "../FileSystemHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



__SPS_GG__NS__B_PLATFORM

class FileSystemHelperAndroid : public FileSystemHelper
{
friend class FileSystemHelper;

protected:	
	FileSystemHelperAndroid();


public:
	virtual ~FileSystemHelperAndroid();


	virtual const long long GetAvailableSize( const std::string &strFullPath ) override;
}; // end class FileSystemHelperAndroid

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_FILE_SYSTEM_HELPER_ANDROID_H__
