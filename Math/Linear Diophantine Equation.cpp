#include <bits/stdc++.h>
using namespace std;
#define ll long long
// ax + by + c = 0.Given a , b , c , x1 , x2 , y1 , y2 you must determine ,
// how many integer roots of this equation are satisfy to the following conditions : x1 <= x <= x2 , y1 <= y <= y2.Integer root of this equation is a pair of integer numbers( x , y ).

ll x , y , d;
void extendedEuclid( ll a , ll b ) {
  if ( b == 0 ) { x = 1 , y = 0 , d = a; return; }
  extendedEuclid( b , a % b );
  ll x1 = y;
  ll y1 = x - ( a / b ) * y;
  x = x1 , y = y1;
  }

int main( ) {
  ll a , b , c , x2 , x1 , x2 , y1 , y2;
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
    if ( c % d == 0 ) {
      double xo = ( ( -1 ) * c * x ) / d;
      double yo = ( ( -1 ) * c * y ) / d;
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