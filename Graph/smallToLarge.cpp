#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e5 + 5;

vector<int>adj [ N + 1 ];
vector<int>in( N ) , sz( N ) , tree( N ) , frq( N ) , arr( N ) , lvl( N );
int n , res = 0 , cnt = 0;


void add( int d ) {  }

void rem( int d ) { }

void dfs0( int u , int p ) {
  static int id = 0;
  in [ u ] = ++id;
  tree [ id ] = u;
  sz [ u ] = 1;
  for ( auto v : adj [ u ] ) {
    if ( v == p ) continue;
    lvl [ v ] = lvl [ u ] + 1;
    dfs0( v , u );
    sz [ u ] += sz [ v ];
    }
  }

void dfs( int u , int p , bool keep ) {
  int mx = -1 , bg = -1;
  for ( int v : adj [ u ] )
    if ( sz [ v ] > mx and v != p ) mx = sz [ v ] , bg = v;

  for ( int v : adj [ u ] ) {
    if ( v != p and v != bg ) {
      dfs( v , u , false );
      }
    }

  if ( ~bg ) dfs( bg , u , true );


  // add all small nodes
  for ( int v : adj [ u ] ) {
    if ( v == p or v == bg ) continue;

    }

  add( u );
  res += cnt;

  // remover small nodes
  if ( not keep ) {
    int l = in [ u ] , r = in [ u ] + sz [ u ];
    for ( int i = l; i < r; i++ ) {
      int node = tree [ i ];
      rem( node );
      }
    }
  }