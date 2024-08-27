#include <bits/stdc++.h>
using namespace std;

const int N = 100 , B1 = 37 , B2 = 39 , MOD = 1e9 + 7;
#define fr first
#define sc second
int pw1 [ N ] , pw2 [ N ];

struct Hash {
  private:
  vector <pair<int , int>> prefix , suffix;
  int n;

  void hash_prefix( const string& str ) {
    int h1 = 0 , h2 = 0;
    prefix.clear( );
    prefix.reserve( str.size( ) );
    for ( char i : str ) {
      h1 = ( 1LL * h1 * B1 ) % MOD;
      h1 = ( h1 + i ) % MOD;
      h2 = ( 1LL * h2 * B2 ) % MOD;
      h2 = ( h2 + i ) % MOD;
      prefix.emplace_back( h1 , h2 );
      }
    }

  void hash_suffix( const string& str ) {
    int h1 = 0 , h2 = 0;
    suffix.assign( n , {} );
    for ( int i = n - 1; i >= 0; i-- ) {
      h1 = ( 1LL * h1 * B1 ) % MOD;
      h1 = ( h1 + str [ i ] ) % MOD;
      h2 = ( 1LL * h2 * B2 ) % MOD;
      h2 = ( h2 + str [ i ] ) % MOD;
      suffix [ i ] = { h1, h2 };
      }
    }

  public:
  Hash( ) {}

  Hash( const string& s ) { build( s ); }

  void build( const string& s ) {
    assert( B1 );
    n = s.size( );
    hash_prefix( s );
    hash_suffix( s ); /// we need this ?
    }

  pair<int , int> getSuffix( int l , int r ) {
    auto ret = suffix [ l ];
    int len = r - l + 1;
    r++;
    if ( r < n ) {
      ret.fr -= 1LL * suffix [ r ].fr * pw1 [ len ] % MOD;
      if ( ret.fr < 0 )ret.fr += MOD;

      ret.sc -= 1LL * suffix [ r ].sc * pw2 [ len ] % MOD;
      if ( ret.sc < 0 )ret.sc += MOD;

      }
    return ret;
    }

  pair<int , int> getPrefix( int l , int r ) {
    auto ret = prefix [ r ];
    int sz = r - l + 1;
    l--;
    if ( l >= 0 ) {
      ret.fr -= 1LL * prefix [ l ].fr * pw1 [ sz ] % MOD;
      if ( ret.fr < 0 )ret.fr += MOD;
      ret.sc -= 1LL * prefix [ l ].sc * pw2 [ sz ] % MOD;
      if ( ret.sc < 0 )ret.sc += MOD;
      }
    return ret;
    }
  };

void build( ) {
  pw1 [ 0 ] = pw2 [ 0 ] = 1;
  for ( int i = 1; i < N; ++i ) {
    pw1 [ i ] = 1LL * pw1 [ i - 1 ] * B1 % MOD;
    pw2 [ i ] = 1LL * pw2 [ i - 1 ] * B2 % MOD;
    }
  }
