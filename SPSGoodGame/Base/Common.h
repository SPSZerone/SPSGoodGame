#ifndef __SPS__GOOD_GAME__BASE__COMMON_H__
#define __SPS__GOOD_GAME__BASE__COMMON_H__



#define __SPS_GG__SAFE_DELETE(p)					do { delete (p); (p) = nullptr; } while(0)
#define __SPS_GG__SAFE_DELETE_ARRAY(p)		do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define __SPS_GG__SAFE_FREE(p)						do { if(p) { free(p); (p) = nullptr; } } while(0)
#define __SPS_GG__SAFE_RELEASE(p)				do { if(p) { (p)->release(); } } while(0)
#define __SPS_GG__SAFE_RELEASE_NULL(p)		do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define __SPS_GG__SAFE_RETAIN(p)					do { if(p) { (p)->retain(); } } while(0)
#define __SPS_GG__BREAK_IF(cond)					if(cond) break


#define __SPS_GG__RANDOM_0_1          ( ( float )rand() / RAND_MAX )


#define __SPS_GG__MIN( _GG_MIN_V1_, _GG_MIN_V2_ )				( ( ( _GG_MIN_V1_ ) < ( _GG_MIN_V2_ ) ) ? ( _GG_MIN_V1_ ) : ( _GG_MIN_V2_ ) )
#define __SPS_GG__MAX( _GG_MAX_V1_, _GG_MAX_V2_ )				( ( ( _GG_MAX_V1_ ) > ( _GG_MAX_V2_ ) ) ? ( _GG_MAX_V1_ ) : ( _GG_MAX_V2_ ) )



#endif // #ifndef __SPS__GOOD_GAME__BASE__COMMON_H__
