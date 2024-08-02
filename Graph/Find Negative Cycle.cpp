#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll OO = 0x3f3f3f3f3f3f3f3f;

void FindNegativeCycle( ) {
  int n , m;
  cin >> n >> m;
  vector<tuple<ll , ll , ll>>edges;
  vector<ll>dest( n + 1 , OO );
  vector<ll>par( n + 1 );
  for ( int i = 0; i < m; i++ ) {
    ll a , b , w;
    cin >> a >> b >> w;
    edges.push_back( { a, b, w } );
    }
  bool negCycle = 0;
  int st = 1;
  for ( int j = 0; j < n; j++ ) {
    for ( int i = 0; i < m; i++ ) {
      ll a , b , w;
      tie( a , b , w ) = edges [ i ];
      if ( dest [ a ] + w < dest [ b ] ) {
        dest [ b ] = dest [ a ] + w;
        par [ b ] = a;
        if ( j == n - 1 )negCycle = 1 , st = a;
        }
      }
    }
  if ( negCycle ) {
    cout << "YES\n";
    vector<ll>path;
    for ( int i = 1; i <= n; i++ ) st = par [ st ];
    for ( int x = st;; x = par [ x ] ) {
      path.push_back( x );
      if ( x == st && path.size( ) > 1 ) break;
      }
    reverse( path.begin( ) , path.end( ) );
    for ( ll& i : path )
      cout << i << ' ';
    }
  else cout << "NO";
  }
