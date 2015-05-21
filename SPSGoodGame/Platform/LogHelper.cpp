#include "LogHelper.h"
__SPS_GG__NS__U_PLATFORM;



LogHelper *LogHelper::_gg_g_LogHelper = nullptr;

void LogHelper::destroy_instance()
{
	__SPS_GG__SAFE_DELETE( _gg_g_LogHelper );
}



LogHelper::LogHelper()
{
	_gg_pFile = nullptr;
}



LogHelper::~LogHelper()
{
	if ( _gg_pFile )
	{
		fclose( _gg_pFile );
		_gg_pFile = nullptr;
	}
}



int LogHelper::Write( Mode eMode, Type eLogType, const char *tag, const char *format, ... )
{
	if ( format == nullptr || strlen( format ) <= 0 )
	{
		return -1;
	}

	char buffer[ __GG__LOG_FILE_MAX_LENGTH ] = { 0 };	
	
	va_list args;
    va_start( args, format );
    vsnprintf( buffer, __GG__LOG_FILE_MAX_LENGTH - 3, format, args );
    va_end( args );

	return OnWrite( time( nullptr ), eMode, eLogType, tag, buffer );
}



int LogHelper::OnWrite( const time_t &time, Mode eMode, Type eLogType, const char *tag, const char *content )
{
	if ( eMode == Mode::WINDOWS || eMode == Mode::WINDOWS_FILE )
	{
		OnWrite_Windows( time, eLogType, tag, content );
	}

	if ( eMode == Mode::FILE || eMode == Mode::WINDOWS_FILE )
	{
		OnWrite_File( time, eLogType, tag, content );
	}

	return 0;
}



int LogHelper::OnWrite_Windows( const time_t &time, Type eLogType, const char *tag, const char *content )
{
	std::string strOutputContent( "" );
	OnWrite_FinalOutputContent( time, strOutputContent, eLogType, tag, content, Mode::WINDOWS );

	OnWrite_Windows_Flush( time, strOutputContent, eLogType, tag, content );

	return 0;
}



int LogHelper::OnWrite_File( const time_t &time, Type eLogType, const char *tag, const char *content )
{
	std::string strOutputContent( "" );
	OnWrite_FinalOutputContent( time, strOutputContent, eLogType, tag, content, Mode::FILE );

	if ( _gg_pFile == nullptr )
	{
		std::string strFilePath = OnWrite_File_GetFilePath( time );
		if ( strFilePath.empty() == false )
		{
			_gg_pFile = fopen( strFilePath.c_str(), "w" );
		}
	}

	OnWrite_File_Flush( time, strOutputContent, eLogType, tag, content );

	return 0;
}



std::string LogHelper::OnWrite_File_GetFilePath( const time_t &time )
{
	tm *curTM = localtime( &time );
	char format_txt[ 100 ] = { 0 };

	std::string strFilePath = FileUtils::getInstance()->getWritablePath();
	strftime( format_txt, 100, "_log_%Y.%m.%d_%H.%M.%S.txt", curTM );
	strFilePath.append( format_txt );

	return strFilePath;
}



int LogHelper::OnWrite_File_Flush( const time_t &time, const std::string &strOutputContent, Type eLogType, const char *tag, const char *content )
{
	if ( _gg_pFile == nullptr )
	{
		return -1;
	}

	fputs( strOutputContent.c_str(), _gg_pFile );
	fflush( _gg_pFile );

	return 0;
}
