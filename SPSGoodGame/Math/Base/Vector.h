#ifndef __SPS__GOOD_GAME__MATH_BASE__VECTOR_H__
#define __SPS__GOOD_GAME__MATH_BASE__VECTOR_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include <vector>



__SPS_GG__NS__B_MATH

template<typename NUM>
class Vector2D
{
public:
	NUM x;
	NUM y;

	Vector2D() : x( 0 ), y( 0 ) {}
	Vector2D( NUM _x, NUM _y ) : x( _x ), y( _y ) { }
	Vector2D( const Vector2D &vec2d ) { x = vec2d.x; y = vec2d.y; }

	inline Vector2D operator = ( const Vector2D &vec2d )
	{
		x = vec2d.x;
		y = vec2d.y;
		return *this;
	}
	
	inline Vector2D operator + ( const Vector2D &vec2d )
	{
		return Vector2D( x + vec2d.x, y + vec2d.y );
	}
	
	inline Vector2D operator - ( const Vector2D &vec2d )
	{
		return Vector2D( x - vec2d.x, y - vec2d.y );
	}

	inline Vector2D operator += ( const Vector2D &vec2d )
	{
		x += vec2d.x;
		y += vec2d.y;
		return *this;
	}

	inline Vector2D operator -= ( const Vector2D &vec2d )
	{
		x -= vec2d.x;
		y -= vec2d.y;
		return *this;
	}
}; // end class Vector2D

typedef std::vector<Vector2D<float>> Vector2DVectorF;
typedef std::vector<Vector2D<double>> Vector2DVectorD;

__SPS_GG__NS__END



#endif // #ifndef __SPS__GOOD_GAME__MATH_BASE__VECTOR_H__
