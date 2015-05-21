#include "FileSystemHelper.h"
__SPS_GG__NS__U_PLATFORM;



FileSystemHelper *FileSystemHelper::_gg_g_FileSystemHelper = nullptr;

void FileSystemHelper::destroy_instance()
{
	__SPS_GG__SAFE_DELETE( _gg_g_FileSystemHelper );
}



FileSystemHelper::FileSystemHelper()
{
	
}



FileSystemHelper::~FileSystemHelper()
{

}



int FileSystemHelper::get_file_parent_path( const std::string &strFilePath, std::string &strFileParentPath )
{
	strFileParentPath.clear();

	if ( strFilePath.empty() )
	{
		return -1;
	}

	std::string strFilePathTmp = strFilePath;
	strFileParentPath = strFilePathTmp.substr( 0, strFilePathTmp.find_last_of( "/\\" ) + 1 );

	return 0;
}



int FileSystemHelper::format_file_size( std::string &strFileSize, const long long nFileSize )
{
	const long long nKB = 1LL << 10;
	const long long nMB = 1LL << 20;
	const long long nGB = 1LL << 30;
	const long long nTB = 1LL << 40;
	const long long nPB = 1LL << 50;
	const long long nEB = 1LL << 60;
	//const long long nZB = 1LL << 70;
	//const long long nYB = 1LL << 80;

	
	strFileSize.clear();
	char format_txt[ 256 ] = { 0 };


	if ( nFileSize < 0 )
	{
		sprintf( format_txt, "%lld", nFileSize );
		strFileSize.append( format_txt );
		return -1;
	}

	
	// x Bytes
	if ( nFileSize < nKB )
	{
		sprintf( format_txt, "%lldBytes", nFileSize );
		strFileSize.append( format_txt );
		return 1;
	}


	long long nValue = 0;
	double fPercent = 0.0;

	std::string strMeasureOfCapacity; // 容量单位
	strMeasureOfCapacity.clear();

	
	// x.xx KB
	if ( nFileSize < nMB )
	{
		nValue = nFileSize >> 10;
		fPercent = 1.0 * ( nFileSize - nKB * nValue ) / nKB;
		strMeasureOfCapacity.append( "KB" );
	}
	// x.xx MB
	else if ( nFileSize < nGB )
	{
		nValue = nFileSize >> 20;
		fPercent = 1.0 * ( nFileSize - nMB * nValue ) / nMB;
		strMeasureOfCapacity.append( "MB" );
	}
	// x.xx GB
	else if ( nFileSize < nTB )
	{
		nValue = nFileSize >> 30;
		fPercent = 1.0 * ( nFileSize - nGB * nValue ) / nGB;
		strMeasureOfCapacity.append( "GB" );
	}
	// x.xx TB
	else if ( nFileSize < nPB )
	{
		nValue = nFileSize >> 40;
		fPercent = 1.0 * ( nFileSize - nTB * nValue ) / nTB;
		strMeasureOfCapacity.append( "TB" );
	}
	// x.xx PB
	else if ( nFileSize < nEB )
	{
		nValue = nFileSize >> 50;
		fPercent = 1.0 * ( nFileSize - nPB * nValue ) / nPB;
		strMeasureOfCapacity.append( "PB" );
	}
	// x.xx EB
	else
	{
		nValue = nFileSize >> 60;
		fPercent = 1.0 * ( nFileSize - nEB * nValue ) / nEB;
		strMeasureOfCapacity.append( "EB" );
	}
	

	if ( fPercent >= 1.0 )
	{
		fPercent = 0.99;
	}
	const int nMantissa = fPercent * 100;
	sprintf( format_txt, "%lld.%02d%s", nValue, nMantissa, strMeasureOfCapacity.c_str() );
	strFileSize.append( format_txt );


	return 0;
}
