#define X real() // can sign values point a; a.real(5) , a.image(2)
#define Y imag() // angle with orignial

typedef complex<double> point2d;

const double PI = acos( -1 );
const double EPS = 1e-4;

int cmp( double& a , double& b ) {
  if ( fabs( a - b ) < EPS ) return 0;
  if ( a > b ) return 1;
  else return -1;
  }

double areaOfInterestTwoCircle( point2d c1 , double r1 , point2d c2 , double r2 ) {
  double d = sqrt( ( c1.X - c2.X ) * ( c1.X - c2.X ) + ( c1.Y - c2.Y ) * ( c1.Y - c2.Y ) );
  double R = r1 + r2;
  double zero = 0.0;
  double x = d + min( r1 , r2 );
  double mx = max( r1 , r2 );
  if ( cmp( d , R ) >= 0 || cmp( d , zero ) == 0 || cmp( x , mx ) < 0 ) // no intersection or two circle are same
    return -1;
  double d1 = r1 * r1 - r2 * r2 + d * d;
  d1 /= 2.0 * d;
  double d2 = d - d1;
  double A1 = r1 * r1 * acos( d1 / r1 ) - d1 * sqrt( r1 * r1 - d1 * d1 );
  double A2 = r2 * r2 * acos( d2 / r2 ) - d2 * sqrt( r2 * r2 - d2 * d2 );
  double A = A1 + A2;
  double area1 = PI * r1 * r1;
  double area2 = PI * r2 * r2;
  double ans1 = area1 - A;
  double ans2 = area2 - A;
  if ( cmp( ans1 , ans2 ) >= 0 )return ans1;
  return ans2;
  }
