#include "LogHelperIOS.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
#include <time.h>
__SPS_GG__NS__U_PLATFORM;



LogHelper *LogHelper::get_instance()
{
	if ( _gg_g_LogHelper == nullptr )
	{
		_gg_g_LogHelper = new LogHelperIOS();
	}
	return _gg_g_LogHelper;
}




LogHelperIOS::LogHelperIOS()
{
	
}



LogHelperIOS::~LogHelperIOS()
{
	
}



int LogHelperIOS::OnWrite_FinalOutputContent( const time_t &time, std::string &strOutputContent, Type eLogType, const char *tag, const char *content, Mode eForMode )
{
	strOutputContent.clear();


	if ( tag == nullptr || strlen( tag ) <= 0 || content == nullptr || strlen( content ) <= 0 )
	{
		return -1;
	}
	

	tm *curTM = localtime( &time );
	char format_txt[ 100 ] = { 0 };
	strftime( format_txt, 100, "| %Y.%m.%d %H:%M:%S |", curTM );
	strOutputContent.append( format_txt );


	switch ( eLogType )
	{
	case Type::LT_VERBOSE: strOutputContent.append( " - | V | ->" ); break;
	case Type::LT_DEBUG: strOutputContent.append( " - | D | ->" ); break;
	case Type::LT_INFOR: strOutputContent.append( " - | I | ->" ); break;
	case Type::LT_WARN: strOutputContent.append( " - | W | ->" ); break;
	case Type::LT_ERROR: strOutputContent.append( " - | E | ->" ); break;
	case Type::LT_FATAL: strOutputContent.append( " - | F | ->" ); break;
	case Type::LT_SLIENT: strOutputContent.append( " - | S | ->" ); break;
	}
	

	strOutputContent.append( " [ " );
	strOutputContent.append( tag );
	strOutputContent.append( " ] " );


	strOutputContent.append( content );
	strOutputContent.append( "\n" );


	return 0;
}



int LogHelperIOS::OnWrite_Windows_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content )
{
    fprintf( stdout, "cocos2d: %s", strOutputContent.c_str() );
    fflush( stdout );
	return 0;
}



std::string LogHelperIOS::OnWrite_File_GetFilePath( const time_t &time )
{
	std::string strFilePath( "" );
	/*
	tm *curTM = localtime( &time );
	char format_txt[ 100 ] = { 0 };

	strFilePath = FileUtils::getInstance()->getWritablePath();
	strftime( format_txt, 100, "_log_%Y.%m.%d_%H.%M.%S.txt", curTM );
	strFilePath.append( format_txt );*/

	return strFilePath;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__IOS )
