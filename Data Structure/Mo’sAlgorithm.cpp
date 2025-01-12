

const int M = 450;
struct query { int l , r , id; };

vector <query> queries;
vector<int> nums , ans;
int n , q , curAns;
void add( int x ) { }
void rem( int x ) { }

vector<int> mo_process( ) {
  sort( queries.begin( ) , queries.end( ) , [ & ] ( query& a , query& b ) {
    int A = a.l / M;
    int B = b.l / M;
    return make_pair( A , a.r ) < make_pair( B , b.r );
      } );
  int l = queries [ 0 ].l , r = l - 1;
  for ( auto& query : queries ) {
    while ( l > query.l ) add( nums [ --l ] );
    while ( r < query.r ) add( nums [ ++r ] );
    while ( l < query.l ) rem( nums [ l++ ] );
    while ( r > query.r ) rem( nums [ r-- ] );
    ans [ query.id ] = curAns;
    }
  return ans;
  }
