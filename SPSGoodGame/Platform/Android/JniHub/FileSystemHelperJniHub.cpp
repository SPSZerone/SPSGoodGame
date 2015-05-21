#include "FileSystemHelperJniHub.h"
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_PLATFORM;



long long FileSystemHelperJniHub::get_available_size( const std::string &strFullPath )
{
	if ( strFullPath.empty() )
	{
		return 0;
	}


	long long nAvailableSize = 0;


	JniMethodInfo methodInfo;
	const bool isHave = JniHelper::getStaticMethodInfo( methodInfo, __GG__JNI_HUB__CLASS_FileSystemHelperJniHub, "get_available_size", "(Ljava/lang/String;)J" );
	if ( isHave == false )
	{
		
	}
	else
	{
		jstring jstrFullPath = methodInfo.env->NewStringUTF( strFullPath.c_str() );

		nAvailableSize = methodInfo.env->CallStaticLongMethod( methodInfo.classID, methodInfo.methodID, jstrFullPath );

		methodInfo.env->DeleteLocalRef( methodInfo.classID);
	}


	return nAvailableSize;
}



#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )
