#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point2d;

#define dp(a, b) ((conj(a) * (b)).real()) // a*b cos(T), if zero -> prep dot product A.B
#define length(a) (hypot((a).imag(), (a).real()))
#define same(a, b) ((dp(vec(a, b), vec(a, b))) <= EPS)  // check to points same or not
#define angle(a) (atan2l((a).imag(),(a).real()))
#define vec(a, b) ((b) - (a))  // diff x1-x2 , y1-y2 return vec (x,y)

const double EPS = 1e-6;
double fixAngle( double a ) {
  return ( a > 1 ? 1 : ( a < -1 ? -1 : a ) );
  }
double getAngle_A_abc( double a , double b , double c ) {
  return acos( fixAngle( ( b * b + c * c - a * a ) / ( 2 * b * c ) ) );
  }
int dcmp( double a , double b ) {
  if ( fabs( a - b ) <= EPS ) return 0;
  return a < b ? -1 : 1;
  }
vector<point2d> intersect2Circle( point2d c1 , double r1 , point2d c2 , double r2 ) {
    // Handle infinity case first: same center/radius and r > 0
  if ( same( c1 , c2 ) && dcmp( r1 , r2 ) == 0 && dcmp( r1 , 0 ) > 0 )
    return vector<point2d>( 3 , c1 );    // infinity 2 same circles (not points)

// Compute 2 intersection case and handle 0, 1, 2 cases
  double ang1 = angle( vec( c1 , c2 ) ) , ang2 = getAngle_A_abc( r2 , r1 , length( vec( c2 , c1 ) ) );

  if ( ::isnan( ang2 ) ) // if r1 or d = 0 => nan in getAngle_A_abc (/0)
    ang2 = 0; // fix corruption

  vector<point2d> v( 1 , polar( r1 , ang1 + ang2 ) + c1 );

  // if point NOT on the 2 circles = no intersection
  if ( dcmp( dp( vec( v [ 0 ] , c1 ) , vec( v [ 0 ] , c1 ) ) , r1 * r1 ) != 0 ||
      dcmp( dp( vec( v [ 0 ] , c2 ) , vec( v [ 0 ] , c2 ) ) , r2 * r2 ) != 0 )
    return vector<point2d>( );

  v.push_back( polar( r1 , ang1 - ang2 ) + c1 );
  if ( same( v [ 0 ] , v [ 1 ] ) )  // if same, then 1 intersection only
    v.pop_back( );
  return v;
  }
