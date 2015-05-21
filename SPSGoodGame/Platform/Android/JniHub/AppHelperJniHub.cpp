#include "AppHelperJniHub.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_PLATFORM;



long AppHelperJniHub::get_version_code()
{
	long nVersionCode = 0;


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "get_version_code", "()I" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		nVersionCode = methodInfo.env->CallStaticIntMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return nVersionCode;
}



std::string AppHelperJniHub::get_version_name()
{
	std::string strVersionName = "";


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "get_version_name", "()Ljava/lang/String;" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		jobject jobj = methodInfo.env->CallStaticObjectMethod( methodInfo.classID, methodInfo.methodID );

		strVersionName = JniHelper::jstring2string( ( jstring )jobj );

		methodInfo.env->DeleteLocalRef( jobj );
		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return strVersionName;
}



std::string AppHelperJniHub::get_uuid()
{
	std::string strUUID = "";


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "get_uuid", "()Ljava/lang/String;" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		jobject jobj = methodInfo.env->CallStaticObjectMethod( methodInfo.classID, methodInfo.methodID );

		strUUID = JniHelper::jstring2string( ( jstring )jobj );

		methodInfo.env->DeleteLocalRef( jobj );
		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return strUUID;
}



std::string AppHelperJniHub::get_app_data_root_path()
{
	std::string strRootPath = "";


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "get_app_data_root_path", "()Ljava/lang/String;" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		jobject jobj = methodInfo.env->CallStaticObjectMethod( methodInfo.classID, methodInfo.methodID );

		strRootPath = JniHelper::jstring2string( ( jstring )jobj );

		methodInfo.env->DeleteLocalRef( jobj );
		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return strRootPath;

}



long long AppHelperJniHub::get_app_data_path_available_size()
{
	long long nAvailableSize = 0;


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "get_app_data_path_available_size", "()J" );
	if ( isHave == false )
	{
		
	}
	else
	{
		nAvailableSize = methodInfo.env->CallStaticLongMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID);
	}


	return nAvailableSize;
}



long AppHelperJniHub::open_url( std::string strUrl )
{
	if ( strUrl.empty() )
	{
		return -1;
	}


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "open_url", "(Ljava/lang/String;)I" );
	if ( isHave == false ) 
	{
		return -10;
	}
	else
	{
		jstring jstrUrl = methodInfo.env->NewStringUTF( strUrl.c_str() );

		methodInfo.env->CallStaticIntMethod( methodInfo.classID, methodInfo.methodID, jstrUrl );

		methodInfo.env->DeleteLocalRef( jstrUrl );
		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return 0;
}



long AppHelperJniHub::install_app( std::string strAppFile )
{
	if ( strAppFile.empty() )
	{
		return -1;
	}


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_AppHelperJniHub, "install_app", "(Ljava/lang/String;)I" );
	if ( isHave == false ) 
	{
		return -10;
	}
	else
	{
		jstring jstrAppFile = methodInfo.env->NewStringUTF( strAppFile.c_str() );

		methodInfo.env->CallStaticIntMethod( methodInfo.classID, methodInfo.methodID, jstrAppFile );

		methodInfo.env->DeleteLocalRef( jstrAppFile );
		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return 0;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
