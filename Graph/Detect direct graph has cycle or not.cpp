#include <bits/stdc++.h>
using namespace std;

const int N = 100;
vector<int>adj [ N ];
bool isCyclicUtil( int v , vector<bool>& visited , vector<bool>& recStack ) {
  if ( visited [ v ] == false ) {
    visited [ v ] = true;
    recStack [ v ] = true;
    for ( auto i : adj [ v ] ) {
      if ( !visited [ i ] && isCyclicUtil( i , visited , recStack ) )
        return true;
      else if ( recStack [ i ] )
        return true;
      }
    }
  recStack [ v ] = false;
  return false;
  }
bool isCyclic( int n ) {
  vector<bool>visited( n + 1 , false );
  vector<bool>recStack( n + 1 , false );
  for ( int i = 1; i <= n; i++ ) {
    visited [ i ] = false;
    recStack [ i ] = false;
    }
  for ( int i = 1; i <= n; i++ )
    if ( !visited [ i ] && isCyclicUtil( i , visited , recStack ) )
      return true;
  return false;
  }
