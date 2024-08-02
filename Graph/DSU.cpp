#include <bits/stdc++.h>
using namespace std;


struct DSU {
  vector<int>par , siz;
  int forests;
  DSU( int n ) {
    par = vector<int>( n + 1 );
    siz = vector<int>( n + 1 , 1 );
    iota( par.begin( ) , par.end( ) , 0 );
    forests = n;
    }
  int find( int u ) { return par [ u ] = ( par [ u ] == u ? u : find( par [ u ] ) ); }
  bool connect( int u , int v ) { return find( u ) == find( v ); }
  void marge( int u , int v ) {
    u = find( u ) , v = find( v );
    if ( u == v )return;
    forests--;
    if ( siz [ u ] < siz [ v ] ) swap( u , v );
    siz [ u ] += siz [ v ];
    par [ v ] = u;
    }
  };