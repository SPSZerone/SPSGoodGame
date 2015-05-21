#ifndef __SPS__GOOD_GAME__PLATFORM__WINDOWS_FILE_SYSTEM_HELPER_WINDOWS_H__
#define __SPS__GOOD_GAME__PLATFORM__WINDOWS_FILE_SYSTEM_HELPER_WINDOWS_H__

#include "../FileSystemHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )



__SPS_GG__NS__B_PLATFORM

class FileSystemHelperWindows : public FileSystemHelper
{
friend class FileSystemHelper;

protected:	
	FileSystemHelperWindows();
public:
	virtual ~FileSystemHelperWindows();

	virtual std::string GetSystemFontPath();

	virtual const long long GetAvailableSize( const std::string &strFullPath ) override;
}; // end class FileSystemHelperWindows

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__WINDOWS_FILE_SYSTEM_HELPER_WINDOWS_H__
