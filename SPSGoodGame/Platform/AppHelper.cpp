#include "AppHelper.h"
__SPS_GG__NS__U_PLATFORM;



AppHelper *AppHelper::_gg_g_AppHelper = nullptr;

void AppHelper::destroy_instance()
{
	__SPS_GG__SAFE_DELETE( _gg_g_AppHelper );
}



AppHelper::AppHelper()
{
	_gg_nVersionCode = -1;
	_gg_strVersionName.clear();
	_gg_nVersionMajor = -1;
	_gg_nVersionMinor = -1;
	_gg_nVersionRevision = -1;

	_gg_strUUID.clear();
	_gg_strAppDataRootPath.clear();
}



AppHelper::~AppHelper()
{

}



int AppHelper::ParserVersionName()
{
	_gg_nVersionMajor = 1;
	_gg_nVersionMinor = 0;
	_gg_nVersionRevision = 0;


	if ( _gg_strVersionName.empty() )
	{
		return -1;
	}


	std::string strTmpVersionName = _gg_strVersionName;


	// Major
	int nIndex = strTmpVersionName.find( "." );
	if ( nIndex <= 0 )
	{
		return -10;
	}
	std::string strMajor = strTmpVersionName.substr( 0, nIndex );
	_gg_nVersionMajor = atol( strMajor.c_str() );


	// Minor
	strTmpVersionName = strTmpVersionName.substr( nIndex + 1, strTmpVersionName.length() );
	nIndex = strTmpVersionName.find( "." );
	if ( nIndex <= 0 )
	{
		return -11;
	}
	std::string strMinor = strTmpVersionName.substr( 0, nIndex );
	_gg_nVersionMinor = atol( strMinor.c_str() );


	// Revision
	strTmpVersionName = strTmpVersionName.substr( nIndex + 1, strTmpVersionName.length() );
	_gg_nVersionRevision = atol( strTmpVersionName.c_str() );


	return 0;
}
