#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
  size_t operator()( const pair<int , int>& x ) const {
    return hash<long long>( )( ( ( long long ) x.first ) ^ ( ( ( long long ) x.second ) << 32 ) );
    }
  };
