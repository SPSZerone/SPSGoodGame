#ifndef __SPS__GOOD_GAME__BASE__CONFIG_H__
#define __SPS__GOOD_GAME__BASE__CONFIG_H__



#define __SPS_GG__SUPPORT__COCOS					1
#define __SPS_GG__SUPPORT__FREE_TYPE				1
#define __SPS_GG__SUPPORT__BOX2D					1
#define __SPS_GG__SUPPORT__ICONV					0



// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PLATFORM [ begin ] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#define __SPS_GG__PLATFORM__UNKNOWN            0
#define __SPS_GG__PLATFORM__IOS							1
#define __SPS_GG__PLATFORM__ANDROID				2
#define __SPS_GG__PLATFORM__WIN32					3
#define __SPS_GG__PLATFORM__MARMALADE         4
#define __SPS_GG__PLATFORM__LINUX						5
#define __SPS_GG__PLATFORM__BADA						6
#define __SPS_GG__PLATFORM__BLACKBERRY			7
#define __SPS_GG__PLATFORM__MAC						8
#define __SPS_GG__PLATFORM__NACL						9
#define __SPS_GG__PLATFORM__EMSCRIPTEN			10
#define __SPS_GG__PLATFORM__TIZEN						11
#define __SPS_GG__PLATFORM__QT5						12



// mac
#if defined( CC_TARGET_OS_MAC )
	#define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__MAC
#endif

// iphone
#if defined( CC_TARGET_OS_IPHONE )
    #define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__IOS
#endif

// android
#if defined( ANDROID )
    #define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__ANDROID
#endif

// win32
#if defined( WIN32 ) && defined( _WINDOWS )
    #define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__WIN32
#endif

// linux
#if defined( LINUX )
    #define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__LINUX
#endif

// marmalade
#if defined( MARMALADE )
	#define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__MARMALADE
#endif

// bada
#if defined( SHP )
	#define __SPS_GG__TARGET_PLATFORM         __SPS_GG__PLATFORM__BADA
#endif

// qnx
#if defined(__QNX__)
    #define __SPS_GG__TARGET_PLATFORM     __SPS_GG__PLATFORM__BLACKBERRY
#endif

// native client
#if defined( __native_client__ )
    #define __SPS_GG__TARGET_PLATFORM     __SPS_GG__PLATFORM__NACL
#endif

// Emscripten
#if defined( EMSCRIPTEN )
    #define __SPS_GG__TARGET_PLATFORM     __SPS_GG__PLATFORM__EMSCRIPTEN
#endif

// tizen
#if defined( TIZEN )
    #define __SPS_GG__TARGET_PLATFORM     __SPS_GG__PLATFORM__TIZEN
#endif

// qt5
#if defined( CC_TARGET_QT5 )
    #define __SPS_GG__TARGET_PLATFORM     __SPS_GG__PLATFORM__QT5
#endif



#ifndef __SPS_GG__TARGET_PLATFORM
	#define __SPS_GG__TARGET_PLATFORM             __SPS_GG__PLATFORM__UNKNOWN
#endif



// check user set platform
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__UNKNOWN )
    #error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 



#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
#ifndef __MINGW32__
#pragma warning (disable:4127) 
#endif 
#endif  // __SPS_GG__PLATFORM__WIN32
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PLATFORM [ end ] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LOG [ begin ] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )

#define LOG_V( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_VERBOSE, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_D( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_DEBUG, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_I( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_INFOR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_W( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_WARN, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_E( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_ERROR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_F( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_FATAL, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_S( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_SLIENT, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )

#define LOG_FILE_V( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_VERBOSE, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_D( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_DEBUG, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_I( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_INFOR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_W( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_WARN, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_E( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_ERROR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_F( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_FATAL, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_S( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::FILE, LogHelper::Type::LT_SLIENT, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )

#define LOG_WF_V( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_VERBOSE, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_D( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_DEBUG, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_I( _TAG_, _FORMAT_, ... )						do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_INFOR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_W( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_WARN, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_E( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_ERROR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_F( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_FATAL, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_S( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS_FILE, LogHelper::Type::LT_SLIENT, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )

#else

#define LOG_V( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_VERBOSE, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_D( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_DEBUG, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_I( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_INFOR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_W( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_WARN, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_E( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_ERROR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_F( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_FATAL, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_S( _TAG_, _FORMAT_, ... )							do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_SLIENT, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )

#define LOG_FILE_V( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_VERBOSE, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_D( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_DEBUG, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_I( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_INFOR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_W( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_WARN, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_E( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_ERROR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_F( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_FATAL, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_FILE_S( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_SLIENT, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )

#define LOG_WF_V( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_VERBOSE, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_D( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_DEBUG, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_I( _TAG_, _FORMAT_, ... )						do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_INFOR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_W( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_WARN, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_E( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_ERROR, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_F( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_FATAL, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )
#define LOG_WF_S( _TAG_, _FORMAT_, ... )					do { using namespace sps_gg__platform; LogHelper::get_instance()->Write( LogHelper::Mode::WINDOWS, LogHelper::Type::LT_SLIENT, _TAG_, _FORMAT_, ##__VA_ARGS__ ); } while ( 0 )

#endif // #if ( __SPS_GG__TARGET_PLATFORM == __SPS_GG__PLATFORM__WIN32 )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LOG [ end ] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



#endif // #ifndef __SPS__GOOD_GAME__BASE__CONFIG_H__
