#include "ShapeUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

__SPS_GG__NS__U_MATH;



static const float EPSILON = 1e-10f;



float ShapeUtil::area_of_triangle( Vector2D<float> &A, Vector2D<float> &B, Vector2D<float> &C )
{
	const Vector2D<float> AB( B - A );
	const Vector2D<float> BC( C - B );
    return fabs( ( AB.x * BC.y - AB.y * BC.x ) ) / 2.0f;
}



bool ShapeUtil::is_inside_triangle( Vector2D<float> &P, Vector2D<float> &A, Vector2D<float> &B, Vector2D<float> &C )
{
	const float sABC = area_of_triangle( A, B, C );
	const float sABP = area_of_triangle( A, B, P );
	const float sACP = area_of_triangle( A, C, P );
	const float sBCP = area_of_triangle( B, C, P );
	
    const float sumS = sABP + sACP + sBCP;
  
    if ( fabs( sABC - sumS ) < 1e-5f )
	{
		return true;
	}

	return false;
}



float ShapeUtil::area_of_polygon( const Vector2DVectorF &polygon )
{
	const unsigned int nSize = polygon.size();
	if ( nSize < 3 )
	{
		return 0;
	}

	float A = 0.0f;
	
	for( unsigned int p = nSize - 1, q = 0; q < nSize; p = q, q++ )
	{
		A += polygon[ p ].x * polygon[ q ].y - polygon[ q ].x * polygon[ p ].y;
	}

	return A * 0.5f;
}



int ShapeUtil::snip( const Vector2DVectorF &polygon, int a, int b, int c, int n, int *V )
{
	int p;

	Vector2D<float> A( polygon[V[a]].x, polygon[V[a]].y );
	Vector2D<float> B( polygon[V[b]].x, polygon[V[b]].y );
	Vector2D<float> C( polygon[V[c]].x, polygon[V[c]].y );
	Vector2D<float> P;
	
	if ( EPSILON > ( ( (B.x-A.x)*(C.y-A.y) ) - ( (B.y-A.y)*(C.x-A.x)) ) ) return -1;
	
	for ( p = 0; p < n; p++ )
	{
		if( ( p == a ) || ( p == b ) || ( p == c ) ) continue;

		P = Vector2D<float>( polygon[V[p]].x, polygon[V[p]].y );

		if ( is_inside_triangle( P, A, B, C ) ) return -2;
	}
	
	return 0;
}



int ShapeUtil::convert_polygon_to_triangles( const Vector2DVectorF &polygon, Vector2DVectorF &triangles )
{
	triangles.clear();

	int n = polygon.size();
	if ( n < 3 ) return -1;
	
	int *V = new int[ n ];
	
	// we want a counter-clockwise polygon in V	
	if ( area_of_polygon( polygon ) > 0.0f )
		for ( int v = 0; v < n; v++ ) V[ v ] = v;
	else
		for( int v = 0; v < n; v++ ) V[ v ] = ( n - 1 ) - v;
	
	int nv = n;
	
	//  remove nv-2 Vertices, creating 1 triangle every time
	int count = 2 * nv;   /* error detection */
	
	for( int m = 0, v = nv - 1; nv > 2; )
	{
		// if we loop, it is probably a non-simple polygon
		if ( 0 >= ( count-- ) )
		{
			delete V;	
			// Triangulate: ERROR - probable bad polygon!
			return -2;
		}
		
		// three consecutive vertices in current polygon, <u,v,w>
		int u = v; if ( nv <= u ) u = 0;     // previous
		v = u + 1; if ( nv <= v ) v = 0;     // new v
		int w = v + 1; if ( nv <= w ) w = 0;     // next
		
		if ( snip( polygon, u, v, w, nv ,V ) == 0 )
		{
			int a, b, c, s, t;
			
			// true names of the vertices
			a = V[ u ]; b = V[ v ]; c = V[ w ];
			
			// output Triangle
			triangles.push_back( polygon[ a ] );
			triangles.push_back( polygon[ b ] );
			triangles.push_back( polygon[ c ] );
			
			m++;
			
			// remove v from remaining polygon
			for( s = v, t = v + 1; t < nv; s++, t++ ) V[ s ] = V[ t ];
			
			nv--;
			
			// resest error detection counter
			count = 2 * nv;
		}
	}
	
	delete V;
	
	return 0;
}
