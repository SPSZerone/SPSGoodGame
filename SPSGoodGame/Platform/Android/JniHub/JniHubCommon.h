#ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_JNIHUB_COMMON_H__
#define __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_JNIHUB_COMMON_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"

#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h> 

#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__ANDROID )



#define __GG__JNI_HUB__CLASS_AppHelperJniHub          "sps/android/jni_hub/AppHelperJniHub"
#define __GG__JNI_HUB__CLASS_ExternalStorageHelperJniHub          "sps/android/jni_hub/ExternalStorageHelperJniHub"
#define __GG__JNI_HUB__CLASS_FileSystemHelperJniHub          "sps/android/jni_hub/FileSystemHelperJniHub"
#define __GG__JNI_HUB__CLASS_NetworkHelperJniHub          "sps/android/jni_hub/NetworkHelperJniHub"



#define __GG__JNI_HUB__LOG_TAG_AppHelperJniHub          "AppHelperJniHub"
#define __GG__JNI_HUB__LOG_TAG_ExternalStorageHelperJniHub          "ExternalStorageHelperJniHub"
#define __GG__JNI_HUB__LOG_TAG_FileSystemHelperJniHub          "FileSystemHelperJniHub"
#define __GG__JNI_HUB__LOG_TAG_NetworkHelperJniHub          "NetworkHelperJniHub"



#endif // #ifndef __SPS__GOOD_GAME__PLATFORM__ANDROID_JNIHUB_JNIHUB_COMMON_H__
