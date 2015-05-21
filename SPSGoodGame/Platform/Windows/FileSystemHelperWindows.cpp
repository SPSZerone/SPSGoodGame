#include "FileSystemHelperWindows.h"
__SPS_GG__NS__U_PLATFORM;

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )



FileSystemHelper *FileSystemHelper::get_instance()
{
	if ( _gg_g_FileSystemHelper == nullptr )
	{
		_gg_g_FileSystemHelper = new FileSystemHelperWindows();
	}
	return _gg_g_FileSystemHelper;
}



FileSystemHelperWindows::FileSystemHelperWindows()
{
	
}



FileSystemHelperWindows::~FileSystemHelperWindows()
{
	
}



std::string FileSystemHelperWindows::GetSystemFontPath()
{
	WCHAR wcWindowsRootPath[ MAX_PATH ] = { 0 };
	GetWindowsDirectoryW( wcWindowsRootPath, sizeof( WCHAR ) * MAX_PATH );
	const unsigned int nWCLength = wcslen( wcWindowsRootPath ) + 1;
	const unsigned int nCLength = ( MAX_PATH + 1 ) * 2;
	char windowsRootPath[ nCLength ] = { 0 };
	WideCharToMultiByte( CP_ACP, 0, wcWindowsRootPath, nWCLength, windowsRootPath, nCLength, nullptr, nullptr ); 

	std::string strFontsRootPath( windowsRootPath );
	strFontsRootPath.append( "\\Fonts\\" );

	return strFontsRootPath;
}



const long long FileSystemHelperWindows::GetAvailableSize( const std::string &strFullPath )
{
	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
