constexpr int N = 200001 + 5;
#define md ((lx+rx)>>1)

int n , q , ign = 0;/// update this

struct Node {
  Node* l , * r;
  int val;
  Node( int x ) : val( x ) , l( nullptr ) , r( nullptr ) { }
  Node( Node* l , Node* r ) {
    this->l = l , this->r = r;
    val = 0;
    if ( l ) val += l->val;
    if ( r ) val += r->val;
    }
  Node( Node* cp ) : val( cp->val ) , l( cp->l ) , r( cp->r ) { }
  };

int merge( const int& lf , const int& rt ) {
  return  lf + rt; /// update this
  }

Node* build( const vector<int>& a , int lx = 0 , int rx = n - 1 ) {
  if ( lx == rx ) return new Node( a [ lx ] );
  return new Node( build( a , lx , md ) , build( a , md + 1 , rx ) );
  }

Node* update( Node* node , int val , int pos , int lx = 0 , int rx = n - 1 ) {
  if ( lx == rx ) return new Node( val );
  if ( pos > md ) {
    return new Node( node->l , update( node->r , val , pos , md + 1 , rx ) );
    }
  return new Node( update( node->l , val , pos , lx , md ) , node->r );
  }

int query( Node* node , int l , int r , int lx = 0 , int rx = n - 1 ) {
  if ( r < lx || rx < l ) return ign;
  if ( l <= lx && rx <= r ) return node->val;
  return merge( query( node->l , l , r , lx , md ) ,
  query( node->r , l , r , md + 1 , rx ) );
  }
#undef md