#ifndef __SPS__GOOD_GAME__MATH_UTIL__SHAPE_UTIL_H__
#define __SPS__GOOD_GAME__MATH_UTIL__SHAPE_UTIL_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#include "../Base/Vector.h"



__SPS_GG__NS__B_MATH

class ShapeUtil
{
public:
	// 三角形的面积
	static float area_of_triangle( Vector2D<float> &A, Vector2D<float> &B, Vector2D<float> &C );
	
	// 坐标系，x轴：左到右，y轴：下到上
	// P( Px,Py )点是否三角形中A( Ax,Ay ) B( Bx,By ) C( Cx,Cy )
	static bool is_inside_triangle( Vector2D<float> &P, Vector2D<float> &A, Vector2D<float> &B, Vector2D<float> &C );
	
	// 三角形的面积( polygon 为有序的 )
	// > 0 逆时针(counter-clockwise)，< 0 顺时针(clockwise)
	static float area_of_polygon( const Vector2DVectorF &polygon );

	// 将一个多边形转化为多个三角形( polygon 为有序的 )
	static int convert_polygon_to_triangles( const Vector2DVectorF &polygon, Vector2DVectorF &triangles );
	
	
private:
	static int snip( const Vector2DVectorF &polygon, int u, int v, int w, int n, int *V );
}; // end class ShapeUtil

__SPS_GG__NS__END



#endif // #ifndef __SPS__GOOD_GAME__MATH_UTIL__SHAPE_UTIL_H__
