

typedef complex<double> point2d;
#define length(a) (hypot((a).imag(), (a).real()))

const double PI = acos( -1 );
const double EPS = 1e-6;
int dcmp( double a , double b ) {
  if ( fabs( a - b ) <= EPS ) return 0;
  return a < b ? -1 : 1;
  }


point2d rotate( point2d p , point2d about , int cnt ) {
  while ( cnt-- )
    p = rotateA( p , PI / 2 , about );
  return p;
  }


bool isSquare( vector<point2d> p ) {// take 4 points
  struct Double {
    double d;
    Double( ) { d = 0.0; };
    Double( double d ) : d( d ) {}
    bool operator < ( const Double& D ) const {
      return dcmp( d , D.d ) < 0;
      }
    bool operator > ( const Double& D ) const {
      return dcmp( d , D.d ) > 0;
      }
    bool operator == ( const Double& D ) const {
      return dcmp( d , D.d ) == 0;
      }
    };
  map<Double , vector<pair<int , int>>> mp;

  // compute distance between every pair. 6 distances
  for ( int i = 0; i < ( int ) p.size( ); ++i ) {
    for ( int j = i + 1; j < ( int ) p.size( ); ++j ) {
      Double len( length( p [ i ] - p [ j ] ) );

      mp [ len ].push_back( { i, j } );
      }
    }
  if ( mp.size( ) != 2 )  // diagonal distance and side distance
    return false;

  auto iterSide = mp.begin( );
  auto iterDiagonal = mp.begin( );
  ++iterDiagonal;

  // 4 sides of equal length and 2 diagonals of equal length
  if ( iterSide->second.size( ) != 4 || iterDiagonal->second.size( ) != 2 )
    return false;

  set<int> s = { iterDiagonal->second [ 0 ].first, iterDiagonal->second [ 0 ].second,
          iterDiagonal->second [ 1 ].first, iterDiagonal->second [ 1 ].second, };

  return s.size( ) == 4;  // 2 distinct diagonals. don't share points
  }
