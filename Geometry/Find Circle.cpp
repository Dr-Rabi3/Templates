

typedef complex<double> point2d;

#define cp(a, b) ((conj(a) * (b)).imag()) // a*b sin(T), if zero -> parllel cross product = area of parllelogram
#define X real() // can sign values point a; a.real(5) , a.image(2)
#define Y imag() // angle with orignial
#define length(a) (hypot((a).imag(), (a).real()))


const double EPS = 1e-6;
bool intersectSegments( point2d a , point2d b , point2d c , point2d d , point2d& intersect ) {
  double d1 = cp( a - b , d - c ) , d2 = cp( a - c , d - c ) , d3 = cp( a - b , a - c );
  if ( fabs( d1 ) < EPS )
    return false;  // Parllel || identical

  double t1 = d2 / d1 , t2 = d3 / d1;
  intersect = a + ( b - a ) * t1;
  // t2 < -EPS || t2 > 1 + EPS if is segment
  // t1 < -EPS if is ray
  if ( t1 < -EPS || t2 < -EPS || t2 > 1 + EPS )
    return false;  //e.g ab is ray, cd is segment ... change to whatever
  return true;
  }
    // 2 points has infinite circles
    // Find circle passes with 3 points, some times, there is no circle! (in case colinear)
    // Draw two perpendicular lines and intersect them
pair<double , point2d> findCircle( point2d a , point2d b , point2d c ) {
    //create median, vector, its prependicular
  point2d m1 = ( b + a ) * 0.5 , v1 = b - a , pv1 = point2d( v1.Y , -v1.X );
  point2d m2 = ( b + c ) * 0.5 , v2 = b - c , pv2 = point2d( v2.Y , -v2.X );
  point2d end1 = m1 + pv1 , end2 = m2 + pv2 , center;
  intersectSegments( m1 , end1 , m2 , end2 , center );
  return make_pair( length( a - center ) , center );
  }
