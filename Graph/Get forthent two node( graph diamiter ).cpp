#include <bits/stdc++.h>
using namespace std;

const int N = 100;

vector<int> g [ N ] , visited( N );
int dp [ N ][ 2 ];
int dfs( int u ) {
  visited [ u ] = true;
  int ret = 0;
  for ( auto child : g [ u ] ) {
    if ( visited [ child ] )continue;
    ret = max( ret , dfs( child ) );
    if ( dp [ u ][ 0 ] < dp [ child ][ 0 ] + 1 ) {
      dp [ u ][ 1 ] = dp [ u ][ 0 ];
      dp [ u ][ 0 ] = dp [ child ][ 0 ] + 1;
      }
    else if ( dp [ u ][ 1 ] < dp [ child ][ 0 ] + 1 ) {
      dp [ u ][ 1 ] = dp [ child ][ 0 ] + 1;
      }
    }
  return max( ret , dp [ u ][ 0 ] + dp [ u ][ 1 ] );
  }
