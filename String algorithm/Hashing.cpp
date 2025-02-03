
namespace Hash {
  const int mod = 1e9 + 7 , typeHash = 2;
  vector<vector<int>>pw , inv;
  array<int , typeHash>base = { 31,37 };

  inline int add( int a , int b ) { return ( ( 0LL + a + b ) % mod + mod ) % mod; }
  inline int mul( int a , int b ) { return ( 1LL * a * b ) % mod; }
  int fp( int b , int p ) {
    int res = 1; b %= mod; while ( p ) {
      if ( p & 1 ) res = mul( res , b );
      b = mul( b , b ); p >>= 1;
      }
    return res % mod;
    }

  void pre( int n ) {
    pw = vector<vector<int>>( typeHash , vector<int>( n + 1 ) );
    inv = vector<vector<int>>( typeHash , vector<int>( n + 1 ) );
    for ( int j = 0; j < typeHash; j++ )pw [ j ][ 0 ] = inv [ j ][ 0 ] = 1;
    int i = 0;
    while ( ++i <= n ) for ( int j = 0; j < typeHash; j++ )
      pw [ j ][ i ] = mul( pw [ j ][ i - 1 ] , base [ j ] ) , inv [ j ][ i ] = fp( pw [ j ][ i ] , mod - 2 );
    }

  vector<vector<int>> build_hash_prefix( const string& s ) {
    array<int , typeHash> hash;
    fill( hash.begin( ) , hash.end( ) , 0 );
    int n = s.size( );
    vector<vector<int>> pref( typeHash , vector<int>( n + 1 ) );
    for ( int i = 0; i < n; i++ ) {
      for ( int j = 0; j < typeHash; j++ ) {
        hash [ j ] = add( hash [ j ] , mul( pw [ j ][ i ] , ( s [ i ] - 'a' ) + 1 ) );
        pref [ j ][ i ] = hash [ j ];
        }
      }
    return pref;
    }
  array<int , typeHash> get_hash_prefix( int l , int r , const vector<vector<int>>& pref ) {
    array<int , typeHash>ans;
    for ( int j = 0; j < typeHash; j++ ) {
      int sum = add( pref [ j ][ r ] , ( l == 0 ? 0 : -pref [ j ][ l - 1 ] ) );
      ans [ j ] = mul( sum , inv [ j ][ l ] );
      }
    return ans;
    }

  // test it
  vector<vector<int>> build_hash_suffix( const string& s ) {
    array<int , typeHash> hash;
    fill( hash.begin( ) , hash.end( ) , 0 );
    int n = s.size( );
    vector<vector<int>> suffix( typeHash , vector<int>( n + 1 ) );
    for ( int i = n - 1; i >= 0; i-- ) {
      for ( int j = 0; j < typeHash; j++ ) {
        hash [ j ] = add( hash [ j ] , mul( ( s [ i ] - 'a' ) + 1 , pw [ j ][ i ] ) );
        suffix [ j ][ i ] = hash [ j ];
        }
      }
    }
    // test it
  array<int , typeHash> get_hash_suffix( int l , int r , const vector<vector<int>>& suf ) {
    int len = r - l + 1 , n = suf [ 0 ].size( );
    array<int , typeHash> ret;
    r++;
    for ( int j = 0; j < typeHash; j++ ) {
      ret [ j ] = suf [ j ][ l ];
      if ( r < n ) {
        ret [ j ] = add( ret [ j ] , -mul( suf [ r ][ j ] , pw [ j ][ len ] ) );
        }
      }
    return ret;
    }


  };
using namespace Hash;
