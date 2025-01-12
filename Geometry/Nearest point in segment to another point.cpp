

typedef complex<double> point2d;
#define length(a) (hypot((a).imag(), (a).real()))
#define vec(a, b) ((b) - (a))  // diff x1-x2 , y1-y2 return vec (x,y)
#define dp(a, b) ((conj(a) * (b)).real()) // a*b cos(T), if zero -> prep dot product A.B

const double EPS = 1e-6;

pair<double , point2d> distAndPointToSegment( point2d p0 , point2d p1 , point2d p2 ) {
  double d1 , d2;
  point2d v1 = p1 - p0 , v2 = p2 - p0;
  if ( ( d1 = dp( v1 , v2 ) ) <= 0 )return { length( vec( p0 , p2 ) ),p0 };
  if ( ( d2 = dp( v1 , v1 ) ) <= d1 )return { length( vec( p1 , p2 ) ),p1 };
  double t = d1 / d2;
  return { length( vec( p0 + v1 * t , p2 ) ), p0 + v1 * t };
  }
