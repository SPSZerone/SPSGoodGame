#include "NetworkHelperWindows.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <httpext.h>
#include <windef.h>
#include <Nb30.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"netapi32.lib")

__SPS_GG__NS__U_PLATFORM;



NetworkHelper *NetworkHelper::get_instance()
{
	if ( _gg_g_NetworkHelper == nullptr )
	{
		_gg_g_NetworkHelper = new NetworkHelperWindows();
	}

	return _gg_g_NetworkHelper;
}



NetworkHelperWindows::NetworkHelperWindows()
{
	
}



NetworkHelperWindows::~NetworkHelperWindows()
{
	
}



const bool NetworkHelperWindows::IsConnectedOfActiveNetwork()
{
	return false;
}



const long NetworkHelperWindows::GetActiveNetworkType()
{
	return -1;
}



const bool NetworkHelperWindows::IsWifiOfActiveNetworkType()
{
	return false;
}



const bool NetworkHelperWindows::IsMobileOfActiveNetworkType()
{
	return false;
}



const bool NetworkHelperWindows::IsWifiConnected()
{
	return false;
}



const bool NetworkHelperWindows::IsMobileConnected()
{
	return false;
}



//在Win32平台上的Winsock编程都要经过下列的基本步骤：定义变量->获得Winsock版本->加载Winsock库->
//初始化->创建套接字->设置套接字选项->关闭套接字->卸载Winsock库，释放所有资源。
const std::string &NetworkHelperWindows::GetIPAddress()
{
	if ( _gg_strIP.empty() == false )
	{
		return _gg_strIP;
	}
	
	
	_gg_strIP.clear();


	WSADATA wsaData;
	char name[155];      //定义用于存放获得主机名的变量
	char *ip = nullptr;            //定义IP地址变量
	PHOSTENT hostinfo; 

	//调用MAKEWORD()获得Winsocl版本的正确值，用于下面的加载Winscok库
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 ) 
	{   //加载Winsock库，如果WSAStartup()函数返回值为0，说明加载成功，程序可以继续往下执行
		if( gethostname ( name, sizeof(name)) == 0) 
		{ //如果成功，将本地主机名存放入由name参数指定的缓冲区中
			if((hostinfo = gethostbyname(name)) != nullptr) 
			{ //这是获取主机，如果获得主机名成功的话，将返回一个指针，指向hostinfo,hostinfo为PHOSTENT型的变量。
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
				//inet_addr()函数把地址串转换为IP地址
				//调用inet_ntoa()函数,将hostinfo结构变量中的h_addr_list转化为标准的IP地址(如202.197.11.12.)
				//printf(" IP地址: %s/n",ip);        //输出IP地址
			} 
		} 
		WSACleanup( );         //卸载Winsock库，并释放所有资源
	}


	if ( ip == nullptr || strlen( ip ) <= 0 )
	{
		return STD_STRING_EMPTY;
	}


	_gg_strIP = ip;
	return _gg_strIP;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
