#include <bits/stdc++.h>
using namespace std;

struct BS {
  int n;
  vector<int>seg;
  BS( int n ) : seg( 4 * n + 1 , 0 ) , n( n ) { }
  void insert( int v , int x , int lx , int rx ) {
    int mid = ( lx + rx ) / 2 , c = 2 * x + 1;
    if ( lx == rx )
      return void( seg [ x ] = 1 );
    if ( v <= mid )
      insert( v , c , lx , mid );
    else
      insert( v , c + 1 , mid + 1 , rx );
    seg [ x ] = seg [ c ] + seg [ c + 1 ];
    }
  void insert( int v ) {
    insert( v , 0 , 0 , n - 1 );
    }
  void erase( int v , int x , int lx , int rx ) {
    int mid = ( lx + rx ) / 2 , c = 2 * x + 1;
    if ( lx == rx )
      return void( seg [ x ] = 0 );
    if ( v <= mid )
      erase( v , c , lx , mid );
    else
      erase( v , c + 1 , mid + 1 , rx );
    seg [ x ] = seg [ c ] + seg [ c + 1 ];
    }
  void erase( int v ) {
    erase( v , 0 , 0 , n - 1 );
    }
  int find_by_order( int k , int x , int lx , int rx ) {
    int mid = ( lx + rx ) / 2 , c = 2 * x + 1;
    if ( lx == rx )
      return lx;
    if ( k < seg [ c ] )
      return find_by_order( k , c , lx , mid );
    else
      return find_by_order( k - seg [ c ] , c + 1 , mid + 1 , rx );
    }
  int find_by_order( int k ) {
    return find_by_order( k , 0 , 0 , n - 1 );
    }
  int order_of_key( int k , int x , int lx , int rx ) {
    int mid = ( lx + rx ) / 2 , c = 2 * x + 1;
    if ( lx == rx )
      return 0;
    if ( k <= mid )
      return order_of_key( k , c , lx , mid );
    else
      return seg [ c ] + order_of_key( k , c + 1 , mid + 1 , rx );
    }
  int order_of_key( int k ) {
    return order_of_key( k , 0 , 0 , n - 1 );
    }
  };