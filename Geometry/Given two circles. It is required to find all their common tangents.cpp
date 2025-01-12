

typedef complex<double> point2d;

#define X real() // can sign values point a; a.real(5) , a.image(2)
#define Y imag() // angle with orignial

struct line {
  double a , b , c;
  line( ) {}
  line( point2d p , point2d q ) {
    a = p.Y - q.Y;
    b = q.X - p.X;
    c = -a * p.X - b * p.Y;
    norm( );
    }
  void norm( ) {
    double z = sqrt( a * a + b * b );
    if ( fabs( z ) > EPS )
      a /= z , b /= z , c /= z;
    }
  double dest( point2d p ) const { return a * p.X + b * p.Y + c; }
  };

const double EPS = 1e-6;

     // Given two circles. It is required to find all their common tangents
vector<line> tangents( point2d a , double r1 , point2d b , double r2 ) {
  auto tangents = [ ] ( point2d c , double r1 , double r2 , vector<line>& ans ) {
    auto sqr = [ ] ( double a ) {
      return a * a;
      };
    double r = r2 - r1;
    double z = sqr( c.X ) + sqr( c.Y );
    double d = z - sqr( r );
    if ( d < -EPS )  return;
    d = sqrt( fabs( d ) );
    line l;
    l.a = ( c.X * r + c.Y * d ) / z;
    l.b = ( c.Y * r - c.X * d ) / z;
    l.c = r1;
    ans.push_back( l );
    };
  vector<line> ans;
  for ( int i = -1; i <= 1; i += 2 )
    for ( int j = -1; j <= 1; j += 2 )
      tangents( point2d( b.X - a.X , b.Y - a.Y ) , r1 * i , r2 * j , ans );
  for ( size_t i = 0; i < ans.size( ); ++i )
    ans [ i ].c -= ans [ i ].a * a.X + ans [ i ].b * a.Y;
  return ans;
  }
