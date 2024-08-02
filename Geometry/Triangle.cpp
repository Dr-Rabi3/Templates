#include <bits/stdc++.h>
using namespace std;

double fixAngle( double a ) {
  return ( a > 1 ? 1 : ( a < -1 ? -1 : a ) );
  }
    // a^2 = b^2 + c^2 - 2 * b * c * cos(A)
double getAngle_A_abc( double a , double b , double c ) {
  return acos( fixAngle( ( b * b + c * c - a * a ) / ( 2 * b * c ) ) );
  }
  // sin(A)/a = sin(B)/b = sin(C)/c
double getAngle_A_abB( double a , double b , double B ) {
  return asin( fixAngle( ( a * sin( B ) ) / b ) );
  }
  // sin(A)/a = sin(B)/b = sin(C)/c
double getSide_a_bAB( double b , double A , double B ) {
  return ( sin( A ) * b ) / sin( B );
  }
