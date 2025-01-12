struct DSUSubarray {
  vector<int> par , res;
  DSUSubarray( int n ) {
    res = par = vector<int>( n + 1 );
    iota( par.begin( ) , par.end( ) , 0 );
    }

  int find( int u ) {
    return par [ u ] = ( par [ u ] == u ? u : find( par [ u ] ) );
    }

  void upd( int l , int r , int val ) {
    for ( int v = find( l ); v <= r; v = find( v ) ) {
      res [ v ] = val;
      par [ v ] = v + 1;
      }
    }

  //  find( l ) > r => to check if all segment is updated or not 
  };
