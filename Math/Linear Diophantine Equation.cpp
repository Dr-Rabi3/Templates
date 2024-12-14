#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll x , y , g;

ll lcm( int a , int b ) {
  return a / __gcd( a , b ) * b;
  }

void extendedEuclid( ll a , ll b ) {
  if ( b == 0 ) { x = 1 , y = 0 , g = a; return; }
  extendedEuclid( b , a % b );
  ll x1 = y;
  ll y1 = x - ( a / b ) * y;
  x = x1 , y = y1;
  }

// ax + by + c = 0.Given a , b , c , x1 , x2 , y1 , y2 you must determine ,
// how many integer roots of this equation are satisfy to the following conditions : x1 <= x <= x2 , y1 <= y <= y2.Integer root of this equation is a pair of integer numbers( x , y ).
int LinearDiophantine( ) {
  ll a , b , c , x2 , x1 , y1 , y2;
  if ( a == 0 && b == 0 ) {
    if ( c == 0 ) printf( "%lld\n" , ( ( x2 - x1 ) + 1 ) * ( ( y2 - y1 ) + 1 ) );
    else printf( "0\n" );
    }
  else if ( a == 0 ) {
    if ( c % b == 0 && ( -c / b ) <= y2 && ( -c / b ) >= y1 ) printf( "%lld\n" , ( x2 - x1 ) + 1 );
    else printf( "0\n" );
    }
  else if ( b == 0 && a != 0 ) {
    if ( c % a == 0 && ( -c / a ) <= x2 && ( -c / a ) >= x1 ) printf( "%lld\n" , ( y2 - y1 ) + 1 );
    else printf( "0\n" );
    }
  else {
    extendedEuclid( a , b );
    if ( c % g == 0 ) {
      double xo = ( ( -1 ) * c * x ) / g;
      double yo = ( ( -1 ) * c * y ) / g;
      double lcm_ab = lcm( a , b );
      double nx1 = ( ( ( double ) x1 - ( double ) xo ) * ( double ) a ) / ( double ) lcm_ab;
      double nx2 = ( ( ( double ) x2 - ( double ) xo ) * ( double ) a ) / ( double ) lcm_ab;
      double ny1 = ( ( ( double ) yo - ( double ) y1 ) * ( double ) b ) / ( double ) lcm_ab;
      double ny2 = ( ( ( double ) yo - ( double ) y2 ) * ( double ) b ) / ( double ) lcm_ab;
      if ( nx1 > nx2 ) swap( nx1 , nx2 );
      if ( ny1 > ny2 ) swap( ny1 , ny2 );
      x1 = ( ll ) ceil( nx1 );
      y1 = ( ll ) ceil( ny1 );
      x2 = ( ll ) floor( nx2 );
      y2 = ( ll ) floor( ny2 );
      if ( min( x2 , y2 ) < max( x1 , y1 ) ) printf( "0\n" );
      else printf( "%lld\n" , min( x2 , y2 ) - max( x1 , y1 ) + 1 );
      }
    else printf( "0\n" );
    }
  }


// c = a * x + b * y = a * ( x + b / g * k ) + b * ( y – a / g * k ) = a * x + b * y + k * ( a * b / g – b * a / g )
// Since a* x + b * y  is constant we want to minimize  k * ( a * b / g – b * a / g )
// so ceil( -x * g / b ) <= t <= floor( y * g / a )
bool interval( int& a , int& b , int& c , int& L , int& R ) {
  extendedEuclid( a , b );
  if ( c % g != 0 )
    return false;
  x *= c / g , y *= c / g;
  b /= g , a /= g;
  L = ceil( -( double ) x / b );
  R = floor( ( double ) y / a );
  if ( L > R )
    return false;
  return true;
  }
// find minimum c1 * a + c2 * b, if ax + by = c 
bool MinXY( int a , int b , int c , int c1 , int c2 ) {
  int L , R , x2 , y2;
  if ( interval( a , b , c , L , R ) ) {
    long mn = c1 * b - c2 * a;
    if ( mn * L < mn * R )
      x2 = x + b * L , y2 = y - a * L;
    else
      x2 = x + b * R , y2 = y - a * R;
    cout << x2 << " " << y2;
    return true;
    }
  return false;
  }