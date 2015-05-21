#include "NetworkHelperJniHub.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_PLATFORM;



bool NetworkHelperJniHub::is_connected_of_active_network()
{
	bool isConnected = false;


	JniMethodInfo methodInfo; 
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "is_connected_of_active_network", "()Z" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		isConnected = methodInfo.env->CallStaticBooleanMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return isConnected;
}



long NetworkHelperJniHub::get_active_network_type()
{
	long nType = -1;


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "get_active_network_type", "()I" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		nType = methodInfo.env->CallStaticIntMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return nType;
}



bool NetworkHelperJniHub::is_wifi_of_active_network_type()
{
	bool isConnected = false;


	JniMethodInfo methodInfo; 
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "is_wifi_of_active_network_type", "()Z" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		isConnected = methodInfo.env->CallStaticBooleanMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return isConnected;
}



bool NetworkHelperJniHub::is_mobile_of_active_network_type()
{
	bool isConnected = false;


	JniMethodInfo methodInfo; 
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "is_mobile_of_active_network_type", "()Z" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		isConnected = methodInfo.env->CallStaticBooleanMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return isConnected;
}



bool NetworkHelperJniHub::is_wifi_connected()
{
	bool isConnected = false;


	JniMethodInfo methodInfo; 
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "is_wifi_connected", "()Z" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		isConnected = methodInfo.env->CallStaticBooleanMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return isConnected;
}



bool NetworkHelperJniHub::is_mobile_connected()
{
	bool isConnected = false;


	JniMethodInfo methodInfo; 
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "is_mobile_connected", "()Z" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		isConnected = methodInfo.env->CallStaticBooleanMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return isConnected;
}



std::string NetworkHelperJniHub::get_ip_address()
{
	std::string strIP = "";


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_NetworkHelperJniHub, "get_ip_address", "()Ljava/lang/String;" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		jobject jobj = methodInfo.env->CallStaticObjectMethod( methodInfo.classID, methodInfo.methodID );

		strIP = JniHelper::jstring2string( ( jstring )jobj );

		methodInfo.env->DeleteLocalRef( jobj );
		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return strIP;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
