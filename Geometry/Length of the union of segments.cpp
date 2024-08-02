#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point2d;

#define X real() // can sign values point a; a.real(5) , a.image(2)
#define Y imag() // angle with orignial

int length_union( const vector<point2d>& a ) {
  int n = a.size( );
  vector<pair<int , bool>> x( n * 2 );
  for ( int i = 0; i < n; i++ ) {
    x [ i * 2 ] = { a [ i ].X, false };
    x [ i * 2 + 1 ] = { a [ i ].Y, true };
    }
  sort( x.begin( ) , x.end( ) );

  int result = 0;
  int c = 0;
  for ( int i = 0; i < n * 2; i++ ) {
    if ( i > 0 && x [ i ].first > x [ i - 1 ].first && c > 0 )
      result += x [ i ].first - x [ i - 1 ].first;
    if ( x [ i ].second ) c--;
    else c++;
    }
  return result;
  }
