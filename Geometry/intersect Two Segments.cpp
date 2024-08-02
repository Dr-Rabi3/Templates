#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point2d;

#define cp(a, b) ((conj(a) * (b)).imag()) // a*b sin(T), if zero -> parllel cross product = area of parllelogram
#define X real() // can sign values point a; a.real(5) , a.image(2)
#define Y imag() // angle with orignial

const double EPS = 1e-6;
bool intersectSegments( point2d a , point2d b , point2d c , point2d d , point2d& intersect ) {
  double d1 = cp( a - b , d - c ) , d2 = cp( a - c , d - c ) , d3 = cp( a - b , a - c );
  if ( fabs( d1 ) < EPS )
    return false;  // Parllel || identical

  double t1 = d2 / d1 , t2 = d3 / d1;
  intersect = a + ( b - a ) * t1;
  // t2 < -EPS || t2 > 1 + EPS if is segment
  // t1 < -EPS if is ray
  if ( t1 < -EPS || t2 < -EPS || t2 > 1 + EPS )
    return false;  //e.g ab is ray, cd is segment ... change to whatever
  return true;
  }
int ccw( point2d a , point2d b , point2d c ) {
  point2d v1( b - a ) , v2( c - a );
  double t = cp( v1 , v2 );
  if ( t > +EPS )
    return +1;
  if ( t < -EPS )
    return -1;
  if ( v1.X * v2.X < -EPS || v1.Y * v2.Y < -EPS )
    return -1;
  if ( norm( v1 ) < norm( v2 ) - EPS )
    return +1;
  return 0;
  }
bool intersect( point2d p1 , point2d p2 , point2d p3 , point2d p4 ) {
    // special case handling if a segment is just a point
  bool x = ( p1 == p2 ) , y = ( p3 == p4 );
  if ( x && y )  return p1 == p3;
  if ( x )   return ccw( p3 , p4 , p1 ) == 0;
  if ( y )   return ccw( p1 , p2 , p3 ) == 0;
  return  ccw( p1 , p2 , p3 ) * ccw( p1 , p2 , p4 ) <= 0 && ccw( p3 , p4 , p1 ) * ccw( p3 , p4 , p2 ) <= 0;
  }
