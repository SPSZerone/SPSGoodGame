#include "NetworkHelper.h"
__SPS_GG__NS__U_PLATFORM;



NetworkHelper *NetworkHelper::_gg_g_NetworkHelper = nullptr;

void NetworkHelper::destroy_instance()
{
	__SPS_GG__SAFE_DELETE( _gg_g_NetworkHelper );
}



NetworkHelper::NetworkHelper()
{
	_gg_strIP.clear();
}



NetworkHelper::~NetworkHelper()
{

}
