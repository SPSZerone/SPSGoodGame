#include "LogHelperWindows.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
#include <time.h>
__SPS_GG__NS__U_PLATFORM;



LogHelper *LogHelper::get_instance()
{
	if ( _gg_g_LogHelper == nullptr )
	{
		_gg_g_LogHelper = new LogHelperWindows();
	}
	return _gg_g_LogHelper;
}




LogHelperWindows::LogHelperWindows()
{
	
}



LogHelperWindows::~LogHelperWindows()
{
	
}



int LogHelperWindows::OnWrite_FinalOutputContent( const time_t &time, std::string &strOutputContent, Type eLogType, const char *tag, const char *content, Mode eForMode )
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



int LogHelperWindows::OnWrite_Windows_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content )
{
	char buffer[ __GG__LOG_FILE_MAX_LENGTH ] = { 0 };	
	size_t nSize = __SPS_GG__MIN( strOutputContent.length(), __GG__LOG_FILE_MAX_LENGTH );
	memcpy( buffer, strOutputContent.c_str(), nSize );

	WCHAR wszBuf[ __GG__LOG_FILE_MAX_LENGTH ] = { 0 };
    MultiByteToWideChar( CP_UTF8, 0, buffer, -1, wszBuf, sizeof( wszBuf ) );
    OutputDebugStringW( wszBuf );
	
    WideCharToMultiByte( CP_ACP, 0, wszBuf, -1, buffer, sizeof( buffer ), nullptr, nullptr );
    printf( "%s", buffer );

	return 0;
}



std::string LogHelperWindows::OnWrite_File_GetFilePath( const time_t &time )
{
	tm *curTM = localtime( &time );
	char format_txt[ 100 ] = { 0 };

	std::string strFilePath = FileUtils::getInstance()->getWritablePath();
	strftime( format_txt, 100, "_log_%Y.%m.%d_%H.%M.%S.txt", curTM );
	strFilePath.append( format_txt );

	return strFilePath;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
