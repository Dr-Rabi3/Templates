
/*
 * radian * 180 / M_PI = degrees
 * arg(p1) = atan2(p1.y, p1.x) => This is the angle from the origin to the point (p1.x, p1.y) in the complex plane, in radians.
 * polar(r, angle) => convert polar coordinates into a complex number.
 *
 */

template <typename T> int sgn(T x) { // can write by compare whit EPS
    return (T(0) < x) - (x < T(0)); // return -1 for negative, 1 for positive, 0 for zero.
}
typedef long double T;
typedef complex<T> point;
#define x real()
#define y imag()
constexpr double ESP = 1e-9;
// squared absolute value can be used to compute and compare distances quickly and exactly if the coordinates are integers.
T sq(point p2) {return p2.x * p2.x + p2.y * p2.y;}
T abs(point p2) {return sqrt(sq(p2)); }

point translate(point v, point p) { return p + v;}
point scale(point c, T factor, point p) {
    return c + (p - c) * factor;
}
point rotate(point p, double angle, point c = {0, 0}) { // angle with radian
    // return p * polar(1.0, angle); // from orignal only
    point rot = {cos(angle), sin(angle)};
    return c + rot * (p - c);
}

// if i have image for two point can find for three fp image for p and fq image for q, we find image for r
point linearTransfo(point p, point q, point r, point fp, point fq) {
    return fp + (r - p) * (fq - fp) / (q - p);
}
// ------------------------------------------------------------------------
// use to find angle between two vectors
T dot(point v, point w) {
    // return v.x * w.x + v.y * w.y; // this equal to
    return (conj(v) * w).x;
}
// to find angle between two vectors smollest one
double angle(point v, point w) {
    // double cosTheta = dot(v, w) / abs(v) / abs(w);
    // return acos(max(-1.0, min(1.0, cosTheta)));// this equal to
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T)-1.0, (T)1.0));
}
// perpendicular if the angle between two vectors, segments is exactly 90° (a right angle).
bool isPrep(point v, point w){return fabs(dot(v, w)) < ESP;}
point prep(point v){return {-v.x, v.y};}

T cross(point v, point w) {
    // return v.x * w.y - v.y * w.x; // this equal to
    return (conj(v) * w).y;
}
// Orientation : orient(A, B, C) is positive if when going from A to B to C we turn left, negative if we turn right, and zero if A, B, C are collinear.
T orient(point a, point b, point c) { return cross(b - a, c - a); }
bool inAngle(point a, point b, point c, point p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 and orient(a, c, p) <= 0;
}
double oriantedAngle(point a, point b, point c) {
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    return 2 * M_PI - angle(b - a, c - a);
}
T angleTravelled(point a, point b, point c){
    double ampli = angle(b - a, c - a);
    if(orient(a, b, c) > 0) return ampli;
    return -ampli;
}
// checking if a polygon P1 · · · Pn is convex. The polygon is convex if they are all ≥ 0 or all ≤ 0
bool isConvex(vector<point> ps) {
    int n = ps.size();
    bool hasPos = false, hasNeg = false;
    for (int i = 0;i < n;i++) {
        int o = orient(ps[i], ps[(i + 1) % n], ps[(i + 2) % n]);
        if (o > 0) hasPos = 1;
        if (o < 0) hasNeg = 1;
    }
    return !(hasNeg && hasPos);
}

bool half(point p /*, point v */) { // want v to be first angle in the polar sort
    // return cross(v, p) < 0 || (cross(v, p) == 0 && dot(v, p) < 0);
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<point>& ps, point origin = {0, 0}) {
    // In general #»v should go before #»w when #»v × #»w > 0, because that means #»w is to the left of #»v when looking from the origin.
    sort(ps.begin(), ps.end(), [&](point a, point b) {
        // return make_tuple(half(a - origin), 0.0) <
        //        make_tuple(half(b - origin), cross(a - origin, b - origin));
        // for sort vectors and consider its direction , if two points are in the same direction, the point that is further from the origin will appear later
        return make_tuple(half(a - origin), 0.0, sq(a)) <
               make_tuple(half(b - origin), cross(a - origin, b - origin), sq(b));
    });
}