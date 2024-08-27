#include <bits/stdc++.h>
using namespace std;

template < typename T > class suffix_array {
  int n;
  string str;
  vector<int>order;
  int getOrder( int a ) const {
    return ( a < ( int ) order.size( ) ? order [ a ] : 0 );
    }
  void radix_sort( int k ) {
    vector<int> frq( n ) , tmp( n );
    for ( auto& it : suf ) frq [ getOrder( it + k ) ]++;
    for ( int i = 1; i < n; i++ ) frq [ i ] += frq [ i - 1 ];
    for ( int i = n - 1; i >= 0; i-- )
      tmp [ --frq [ getOrder( suf [ i ] + k ) ] ] = suf [ i ];
    suf = tmp;
    }
  int cmp( string& t , int md ) {
    int i = 0 , j = suf [ md ];
    while ( i < t.size( ) and j < str.size( ) ) {
      if ( t [ i ] < str [ j ] ) return 1;
      else if ( t [ i ] > str [ j ] ) return -1;
      ++i , ++j;
      }
    return 0;
    }
  int BS( string& t , int type ) {
    int l = 0 , r = str.size( ) - 1 , ans = ( type == 2 ? n : -1 );
    while ( l <= r ) {
      int md = ( l + r ) >> 1;
      int x = cmp( t , md );
      if ( type == 1 ) {
        if ( x == 1 || x == 0 ) r = md - 1;
        else if ( x == -1 ) l = md + 1 , ans = md;
        }
      else if ( type == 2 ) {
        if ( x == -1 || x == 0 ) l = md + 1;
        else if ( x == 1 ) r = md - 1 , ans = md;
        }
      else {
        if ( x == -1 ) l = md + 1;
        else if ( x == 1 ) r = md - 1;
        else return 1;
        }
      }
    return ( type == 3 ? 0 : ans );
    }
  public:
  vector<int>suf;
  suffix_array( const string& s ) {
    str = s + "$";
    n = s.size( ) + 1;
    suf = order = vector<int>( n );
    vector<int> newOrder( n );
    for ( int i = 0; i < n; i++ )
      suf [ i ] = i;
    {
    vector<int> tmp( n );
    for ( int i = 0; i < n; i++ )
      tmp [ i ] = s [ i ];
    sort( tmp.begin( ) , tmp.end( ) );
    for ( int i = 0; i < n; i++ )
      order [ i ] = ( lower_bound( tmp.begin(), tmp.end() , s [ i ] ) - tmp.begin( ) );
    }
    for ( int len = 1; newOrder.back( ) != n - 1; len <<= 1 ) {
      auto cmp = [ & ] ( const int& a , const int& b ) -> bool {
        if ( getOrder( a ) != getOrder( b ) )
          return getOrder( a ) < getOrder( b );
        return getOrder( a + len ) < getOrder( b + len );
        };
      radix_sort( len );
      radix_sort( 0 );
      newOrder [ 0 ] = 0;
      for ( int i = 1; i < n; i++ )
        newOrder [ i ] = newOrder [ i - 1 ] + cmp( suf [ i - 1 ] , suf [ i ] );
      for ( int i = 0; i < n; i++ )
        order [ suf [ i ] ] = newOrder [ i ];
      }
    }

  vector<int> LCP( ) {
    int n = str.size( );
    vector<int> rank( n , 0 );
    for ( int i = 0; i < n; i++ ) rank [ suf [ i ] ] = i;

    int k = 0;
    vector<int> lcp( n - 1 , 0 );
    for ( int i = 0; i < n; i++ ) {
      if ( rank [ i ] == n - 1 ) {
        k = 0;
        continue;
        }
      int j = suf [ rank [ i ] + 1 ];
      while ( i + k < n && j + k < n && str [ i + k ] == str [ j + k ] )
        k++;
      lcp [ rank [ i ] ] = k;
      if ( k )
        k--;
      }
    return lcp;
    }
  int lower( string& t ) { return BS( t , 1 ); }
  int upper( string& t ) { return BS( t , 2 ); }
  bool search( string& t ) { return BS( t , 3 ); }
  int count( string& t ) { return upper( t ) - lower( t ) - 1; }
  };
