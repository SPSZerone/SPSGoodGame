#ifndef __SPS__GOOD_GAME__PLATFORM__FILE_SYSTEM_HELPER_H__
#define __SPS__GOOD_GAME__PLATFORM__FILE_SYSTEM_HELPER_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "SPSGoodGame/Base/Common.h"
#include <string>
#include "cocos2d.h"
USING_NS_CC;



__SPS_GG__NS__B_PLATFORM

class FileSystemHelper
{
protected:
	
	static FileSystemHelper *_gg_g_FileSystemHelper;
	FileSystemHelper();
	

public:
	static FileSystemHelper *get_instance();
	static void destroy_instance();
	virtual ~FileSystemHelper();

	virtual std::string GetSystemFontPath() { return ""; }

	virtual const long long GetAvailableSize( const std::string &strFullPath ) = 0;


	static int get_file_parent_path( const std::string &strFilePath, std::string &strFileParentPath );

	
	/* XX.XXMB      e.g.  10.01MB
		2^63 - 1      9223372036854775807      0x7FFFFFFFFFFFFFFF
		test num
		long long nFileSize = 0x7FFFFFFFFFFFFFFFLL;
		long long nFileSize = ( 1LL << 60 ) + 512 * ( 1LL << 50 ); // x.xxEB
		long long nFileSize = ( 1LL << 50 ) + 512 * ( 1LL << 40 ); // x.xxPB
		long long nFileSize = ( 1LL << 40 ) + 512 * ( 1LL << 30 ); // x.xxTB
		long long nFileSize = ( 1LL << 30 ) + 512 * ( 1LL << 20 ); // x.xxGB
		long long nFileSize = ( 1LL << 20 ) + 512 * ( 1LL << 10 ); // x.xxMB
		long long nFileSize = ( 1LL << 10 ) + 512; // x.xxKB
		long long nFileSize = 512; // Bytes
		long long nFileSize = -512;
		long long nFileSize = -1e18;
	*/
	static int format_file_size( std::string &strFileSize, const long long nFileSize );
}; // end class FileSystemHelper

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__FILE_SYSTEM_HELPER_H__
