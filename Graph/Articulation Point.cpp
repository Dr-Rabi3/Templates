

vector<vector<int>>adj;
set<int> artPoint;
vector<int>lowLink;// n size
vector<int>dfn;  // n size
int id = 1;
void ArticulationPoint( int node , int par = -1 ) {
  lowLink [ node ] = dfn [ node ] = id++;
  for ( auto& child : adj [ node ] ) {
    if ( dfn [ child ] == -1 ) {
      ArticulationPoint( child , node );
      lowLink [ node ] = min( lowLink [ node ] , lowLink [ child ] );
      if ( lowLink [ child ] >= dfn [ node ] ) {
        if ( par != -1 )
          artPoint.insert( node );
        }
      }
    else if ( child != par )
      lowLink [ node ] = min( lowLink [ node ] , dfn [ child ] );
    }
  }
