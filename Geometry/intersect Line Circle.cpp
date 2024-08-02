#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point2d;

#define dp(a, b) ((conj(a) * (b)).real()) // a*b cos(T), if zero -> prep dot product A.B
const double EPS = 1e-6;
int dcmp( double a , double b ) {
  if ( fabs( a - b ) <= EPS ) return 0;
  return a < b ? -1 : 1;
  }
      // If line intersect cirlce at point p, and p = p0 + t(p1-p0)
      // Then (p-c)(p-c) = r^2 substitute p and rearrange
      // (p1-p0)(p1-p0)t^2 + 2(p1-p0)(p0-C)t + (p0-C)(p0-C) = r*r; -> Quadratic
vector<point2d> intersectLineCircle( point2d p0 , point2d p1 , point2d C , double r ) {
  double a = dp( p1 - p0 , p1 - p0 ) , b = 2 * dp( p1 - p0 , p0 - C ) ,
    c = dp( p0 - C , p0 - C ) - r * r;
  double f = b * b - 4 * a * c;
  vector<point2d> v;
  if ( dcmp( f , 0 ) >= 0 ) {
    if ( dcmp( f , 0 ) == 0 ) f = 0;
    double t1 = ( -b + sqrt( f ) ) / ( 2 * a );
    double t2 = ( -b - sqrt( f ) ) / ( 2 * a );
    v.push_back( p0 + t1 * ( p1 - p0 ) );
    if ( dcmp( f , 0 ) != 0 ) v.push_back( p0 + t2 * ( p1 - p0 ) );
    }
  return v;
  }
