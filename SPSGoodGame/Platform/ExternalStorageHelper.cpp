#include "ExternalStorageHelper.h"
__SPS_GG__NS__U_PLATFORM;



ExternalStorageHelper *ExternalStorageHelper::_gg_g_ExternalStorageHelper = nullptr;

void ExternalStorageHelper::destroy_instance()
{
	__SPS_GG__SAFE_DELETE( _gg_g_ExternalStorageHelper );
}



ExternalStorageHelper::ExternalStorageHelper()
{
	_gg_strRootPath.clear();
}



ExternalStorageHelper::~ExternalStorageHelper()
{

}
