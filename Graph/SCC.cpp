

using vi = vector<int>;
using vb = vector<bool>;
using vpi = vector<pair<int , int>>;
using vvi = vector<vector<int>>;
#define all(x) x.begin(),x.end()

// assuming nodes are zero based
struct SCC {
  vvi adj , adjRev , comps;
  vpi edges;
  vi revOut , compOf;
  vb vis;
  int N;

  void init( int n ) {
    N = n;
    adj.resize( n );
    adjRev.resize( n );
    vis.resize( n );
    compOf.resize( n );
    }

  void addEdge( int u , int v ) {
    edges.emplace_back( make_pair( u , v ) );
    adj [ u ].emplace_back( v );
    adjRev [ v ].emplace_back( u );
    }

  void dfs1( int u ) {
    vis [ u ] = true;
    for ( auto v : adj [ u ] )
      if ( !vis [ v ] )
        dfs1( v );
    revOut.emplace_back( u );
    }

  void dfs2( int u ) {
    vis [ u ] = true;
    comps.back( ).emplace_back( u );
    compOf [ u ] = comps.size( ) - 1;
    for ( auto v : adjRev [ u ] )
      if ( !vis [ v ] )dfs2( v );
    }

  void gen( ) {
    fill( all( vis ) , false );
    for ( int i = 0; i < N; ++i ) {
      if ( !vis [ i ] )
        dfs1( i );
      }
    reverse( all( revOut ) );
    fill( all( vis ) , false );
    for ( auto node : revOut ) {
      if ( vis [ node ] )continue;
      comps.emplace_back( vi( ) );
      dfs2( node );
      }
    }

  vvi generateCondensedGraph( ) {
    vvi adjCon( comps.size( ) );
    for ( auto [u , v] : edges )
      if ( compOf [ u ] != compOf [ v ] )
        adjCon [ compOf [ u ] ].emplace_back( compOf [ v ] );
    return adjCon;
    }
  };
