#include <bits/stdc++.h>
using namespace std;


typedef complex<double> point2d;
#define vec(a, b) ((b) - (a))  // diff x1-x2 , y1-y2 return vec (x,y)
const double EPS = 1e-6;

int dcmp( double a , double b ) {
  if ( fabs( a - b ) <= EPS ) return 0;
  return a < b ? -1 : 1;
  }

bool cricleInsideCircle( point2d center , double R , point2d p , double r ) {
  double dis = dist( vec( center , p ) );
  return ( dcmp( dis + r , R ) <= 0 );
  }
