#include <bits/stdc++.h>
using namespace std;

template < typename T > struct SqrtD {
  int blockSize;
  vector<T> nums;
  vector<T> blocks;
  T add( int a , int b ) {
    return a + b;
    }
  T remove( int a , int b ) {
    return a - b;
    }
  SqrtD( int n , const vector<T>& arr ) {
    blockSize = ceill( sqrtl( n ) );
    blocks = vector<T>( blockSize , 0 );
    nums = arr;
    for ( int i = 0; i < nums.size( ); i++ ) {
      blocks [ i / blockSize ] = add( blocks [ i / blockSize ] , nums [ i ] );
      }
    }
    /** O(1) update to set nums[x] to v */
  void update( int x , int v ) {
    blocks [ x / blockSize ] = remove( blocks [ x / blockSize ] , nums [ x ] );
    nums [ x ] = v;
    blocks [ x / blockSize ] = add( blocks [ x / blockSize ] , nums [ x ] );
    }
    /** O(sqrt(n)) query for sum of [l, r) */
 // if the base of array 0 pass l and r base 1
  T query( int l , int r ) {
    return query( r ) - query( l - 1 );
    }
    /** O(sqrt(n)) query for sum of [0, r) */
  T query( int r ) {
    T res = 0;
    for ( int i = 0; i < r / blockSize; i++ ) {
      res = add( res , blocks [ i ] );
      }
    for ( int i = ( r / blockSize ) * blockSize; i < r; i++ ) {
      res = add( res , nums [ i ] );
      }
    return res;
    }
  };
