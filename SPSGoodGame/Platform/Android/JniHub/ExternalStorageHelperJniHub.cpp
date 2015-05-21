#include "ExternalStorageHelperJniHub.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_PLATFORM;



bool ExternalStorageHelperJniHub::is_available()
{
	bool isAva = false;


	JniMethodInfo methodInfo; 
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_ExternalStorageHelperJniHub, "is_available", "()Z" );
	if ( isHave == false ) 
	{
		
	}
	else
	{
		isAva = methodInfo.env->CallStaticBooleanMethod( methodInfo.classID, methodInfo.methodID );

		methodInfo.env->DeleteLocalRef( methodInfo.classID );
	}


	return isAva;
}



std::string ExternalStorageHelperJniHub::get_root_path()
{
	std::string strRootPath = "";


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_ExternalStorageHelperJniHub, "get_root_path", "()Ljava/lang/String;" );
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



long long ExternalStorageHelperJniHub::get_available_size()
{
	long long nAvailableSize = 0;


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_ExternalStorageHelperJniHub, "get_available_size", "()J" );
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



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
