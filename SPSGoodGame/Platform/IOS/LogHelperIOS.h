#ifndef __SPS__GOOD_GAME__PLATFORM__IOS_LOG_HELPER_IOS_H__
#define __SPS__GOOD_GAME__PLATFORM__IOS_LOG_HELPER_IOS_H__

#include "../LogHelper.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )



__SPS_GG__NS__B_PLATFORM

class LogHelperIOS : public LogHelper
{
friend class LogHelper;

protected:
	LogHelperIOS();


public:
	virtual ~LogHelperIOS();


protected:	
	virtual int OnWrite_FinalOutputContent( const time_t &time, std::string &strOutputContent, Type eLogType, const char *tag, const char *content, Mode eForMode ) override;

	virtual int OnWrite_Windows_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content ) override;

	virtual std::string OnWrite_File_GetFilePath( const time_t &time ) override;
	
}; // end class LogFileHelperWindows

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )

#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__IOS_LOG_HELPER_IOS_H__
