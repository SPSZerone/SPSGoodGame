#include "LogHelperAndroid.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
__SPS_GG__NS__U_PLATFORM;



LogHelper *LogHelper::get_instance()
{
	if ( _gg_g_LogHelper == nullptr )
	{
		_gg_g_LogHelper = new LogHelperAndroid();
	}
	return _gg_g_LogHelper;
}



LogHelperAndroid::LogHelperAndroid()
{
	
}



LogHelperAndroid::~LogHelperAndroid()
{
	
}



int LogHelperAndroid::OnWrite_FinalOutputContent( const time_t &time, std::string &strOutputContent, Type eLogType, const char *tag, const char *content, Mode eForMode )
{
	strOutputContent.clear();


	if ( tag == nullptr || strlen( tag ) <= 0 || content == nullptr || strlen( content ) <= 0 )
	{
		return -1;
	}
	

	if ( eForMode == Mode::FILE )
	{
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
	}


	strOutputContent.append( content );
	strOutputContent.append( "\n" );


	return 0;
}



int LogHelperAndroid::OnWrite_Windows_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content )
{
	std::string strTag( "GoodGame Native" );
	if ( tag && strlen( tag ) > 0 )
	{
		strTag.append( " -> " );
		strTag.append( tag );
	}

	android_LogPriority eLogPriority = ANDROID_LOG_DEFAULT;

	switch ( eLogType )
	{
	case Type::LT_VERBOSE:	eLogPriority = ANDROID_LOG_VERBOSE;		break;
	case Type::LT_DEBUG:		eLogPriority = ANDROID_LOG_DEBUG;			break;
	case Type::LT_INFOR:		eLogPriority = ANDROID_LOG_INFO;			break;
	case Type::LT_WARN:		eLogPriority = ANDROID_LOG_WARN;			break;
	case Type::LT_ERROR:		eLogPriority = ANDROID_LOG_ERROR;			break;
	case Type::LT_FATAL:			eLogPriority = ANDROID_LOG_FATAL;			break;
	case Type::LT_SLIENT:		eLogPriority = ANDROID_LOG_SILENT;			break;
	}

	__android_log_print( eLogPriority, strTag.c_str(), "%s", strOutputContent.c_str() );

	return 0;
}



std::string LogHelperAndroid::OnWrite_File_GetFilePath( const time_t &time )
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



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
