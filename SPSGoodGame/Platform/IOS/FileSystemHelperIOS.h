#ifndef __SPS__GOOD_GAME__PLATFORM__IOS_FILE_SYSTEM_HELPER_IOS_H__
#define __SPS__GOOD_GAME__PLATFORM__IOS_FILE_SYSTEM_HELPER_IOS_H__

#include "../FileSystemHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



__SPS_GG__NS__B_PLATFORM

class FileSystemHelperIOS : public FileSystemHelper
{
friend class FileSystemHelper;

protected:	
	FileSystemHelperIOS();
public:
	virtual ~FileSystemHelperIOS();


	virtual const long long GetAvailableSize( const std::string &strFullPath ) override;
}; // end class FileSystemHelperIOS

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__IOS_FILE_SYSTEM_HELPER_IOS_H__
