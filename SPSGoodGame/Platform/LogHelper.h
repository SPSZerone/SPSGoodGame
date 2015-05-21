#ifndef __SPS__GOOD_GAME__PLATFORM__LOG_HELPER_H__
#define __SPS__GOOD_GAME__PLATFORM__LOG_HELPER_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "SPSGoodGame/Base/Common.h"
#include <string>
#include "cocos2d.h"
USING_NS_CC;



#define __GG__LOG_FILE_MAX_LENGTH      16385



__SPS_GG__NS__B_PLATFORM

class LogHelper
{
public:
	enum class Mode
	{
		WINDOWS,
		FILE,
		WINDOWS_FILE,
	};

	enum class Type
	{
		LT_VERBOSE,
		LT_DEBUG,
		LT_INFOR,
		LT_WARN,
		LT_ERROR,
		LT_FATAL,
		LT_SLIENT,
	};


protected:	
	FILE *_gg_pFile;


protected:
	static LogHelper *_gg_g_LogHelper;
	LogHelper();
	

public:
	static LogHelper *get_instance();
	static void destroy_instance();
	virtual ~LogHelper();


	virtual int Write( Mode eMode, Type eLogType, const char *tag, const char *format, ... ) final;
protected:
	virtual int OnWrite( const time_t &time, Mode eMode, Type eLogType, const char *tag, const char *content ) final;
	
	virtual int OnWrite_FinalOutputContent( const time_t &time, std::string &strOutputContent, Type eLogType, const char *tag, const char *content, Mode eForMode ) = 0;

	virtual int OnWrite_Windows( const time_t &time, Type eLogType, const char *tag, const char *content ) final;
	virtual int OnWrite_Windows_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content ) = 0;

	virtual int OnWrite_File( const time_t &time, Type eLogType, const char *tag, const char *content ) final;
	virtual std::string OnWrite_File_GetFilePath( const time_t &time ) = 0;
	virtual int OnWrite_File_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content ) final;
}; // end class LogFileHelper

__SPS_GG__NS__END // end __SPS_GG__NS__B_PLATFORM



#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__LOG_HELPER_H__
