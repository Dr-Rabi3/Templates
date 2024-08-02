#include <bits/stdc++.h>
using namespace std;

vector<int> comp( vector<int>& v ) {
  vector<int> d = v;
  sort( d.begin( ) , d.end( ) );
  d.resize( unique( d.begin( ) , d.end( ) ) - d.begin( ) );
  for ( int i = 0; i < v.size( ); ++i ) {
    v [ i ] = lower_bound( d.begin( ) , d.end( ) , v [ i ] ) - d.begin( );
    }
  return d;
//original value of v[i] can be obtained through d[v[i]]
  }
