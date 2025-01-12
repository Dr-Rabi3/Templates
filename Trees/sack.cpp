 

class SACK {
  vector<vector<int>>adj;
  vector<int>in , sz , tree;
  vector<int>frq , arr , lvl;
  int N , id , cur;
  vector<int> res;

  void add( const int& node ) { }
  void rem( const int& node ) { }
  public:
  SACK( int n ) : N( n ) {
    id = cur = 0;
    adj = vector<vector<int>>( n + 1 );
    res = vector<int>( n + 1 );
    in = sz = tree = vector<int>( n + 1 );
    frq = arr = lvl = vector<int>( n + 1 );
    }

  void nodeProp( const vector<int>& color ) {
    arr = color;
    }

  void addEdge( const int& u , const int& v ) {
    adj [ u ].push_back( v );
    adj [ v ].push_back( u );
    }

  void dfs0( int u , int p = -1 ) {
    in [ u ] = ++id;
    tree [ id ] = u;
    sz [ u ] = 1;
    for ( int v : adj [ u ] ) {
      if ( v == p ) continue;
      lvl [ v ] = lvl [ u ] + 1;
      dfs0( v , u );
      sz [ u ] += sz [ v ];
      }
    }

  void dfs1( int u , int p , bool keep ) {
    int bg = -1 , mx = -1;
    for ( int& v : adj [ u ] ) {
      if ( v != p && sz [ v ] > mx )
        mx = v , bg = v;
      }
    for ( int& v : adj [ u ] ) {
      if ( v == p or v == bg )continue;
      dfs1( v , u , false );
      }
    if ( ~bg ) {
      dfs1( bg , u , true );
      }
    add( u );
    for ( int v : adj [ u ] ) {
      if ( v == p or v == bg )continue;
      for ( int i = 0; i < sz [ v ]; ++i ) {
        int x = tree [ in [ v ] + i ];
        add( x );
        }
      }

      //// get the answers here

    if ( !keep ) {
      for ( int i = 0; i < sz [ u ]; ++i ) {
        int x = tree [ in [ u ] + i ];
        rem( x );
        }
      }
    }

  vector <int> smallToLarge( int root = 1 ) {
    dfs0( root , root );
    dfs1( root , root , 0 );
    return res;
    }
  };
