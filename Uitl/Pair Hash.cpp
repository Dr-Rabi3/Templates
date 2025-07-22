
struct pair_hash {
  size_t operator()( const pair<int , int>& x ) const {
    return hash<long long>( )( ( ( long long ) x.first ) ^ ( ( ( long long ) x.second ) << 32 ) );
    }
  };
unordered_map<pair<int, int>, int, pair_hash> lst;
lst.reserve(1 << 20);
