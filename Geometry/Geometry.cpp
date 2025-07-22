#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#define int long long
#define ld long double
#define ed '\n'
using namespace std;

/*
 * radian * 180 / M_PI = degrees
 * arg(p1) = atan2(p1.y, p1.x) => This is the angle from the origin to the point (p1.x, p1.y) in the complex plane, in radians.
 * polar(r, angle) => convert polar coordinates into a complex number.
 *
 */

template<typename T>
int sgn(T x) {
    // can write by compare whit EPS
    return (T(0) < x) - (x < T(0)); // return -1 for negative, 1 for positive, 0 for zero.
}

typedef ld T;
typedef complex<T> point;
#define x real()
#define y imag()
constexpr double EPS = 1e-9;
// squared absolute value can be used to compute and compare distances quickly and exactly if the coordinates are integers.
T sq(point p2) { return p2.x * p2.x + p2.y * p2.y; }
T abs(point p2) { return sqrt(sq(p2)); }

point translate(point v, point p) { return p + v; }

point scale(point c, T factor, point p) {
    return c + (p - c) * factor;
}

point rotate(point p, double angle, point c = {0, 0}) {
    // angle with radian
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
T angle(point v, point w) {
    // double cosTheta = dot(v, w) / abs(v) / abs(w);
    // return acos(max(-1.0, min(1.0, cosTheta)));// this equal to
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T) -1.0, (T) 1.0));
}

// perpendicular if the angle between two vectors, segments is exactly 90° (a right angle).
bool isPrep(point v, point w) { return fabs(dot(v, w)) < EPS; }
point perp(point v) { return {-v.y, v.x}; }

T cross(point v, point w) {
    return v.x * w.y - v.y * w.x; // this equal to
    // return (conj(v) * w).y;
}

// Orientation : orient(A, B, C) is positive if when going from A to B to C we turn left, negative if we turn right, and zero if A, B, C are collinear.
T orient(point a, point b, point c) { return cross(b - a, c - a); }

bool inAngle(point a, point b, point c, point p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 and orient(a, c, p) <= 0;
}

T oriantedAngle(point a, point b, point c) {
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    return 2.0 * M_PI - angle(b - a, c - a);
}

T angleTravelled(point a, point b, point c) {
    double ampli = angle(b - a, c - a);
    if (orient(a, b, c) > 0) return ampli;
    return -ampli;
}

// checking if a polygon P1 · · · Pn is convex. The polygon is convex if they are all ≥ 0 or all ≤ 0
bool isConvex(vector<point> ps) {
    int n = ps.size();
    bool hasPos = false, hasNeg = false;
    for (int i = 0; i < n; i++) {
        int o = orient(ps[i], ps[(i + 1) % n], ps[(i + 2) % n]);
        if (o > 0) hasPos = 1;
        if (o < 0) hasNeg = 1;
    }
    return !(hasNeg && hasPos);
}

bool half(point p /*, point v */) {
    // want v to be first angle in the polar sort
    // return cross(v, p) < 0 || (cross(v, p) == 0 && dot(v, p) < 0);
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<point> &ps, point origin = {0, 0}) {
    // In general #»v should go before #»w when #»v × #»w > 0, because that means #»w is to the left of #»v when looking from the origin.
    sort(ps.begin(), ps.end(), [&](point a, point b) {
        // return make_tuple(half(a - origin), 0.0) <
        //        make_tuple(half(b - origin), cross(a - origin, b - origin));
        // for sort vectors and consider its direction , if two points are in the same direction, the point that is further from the origin will appear later
        return make_tuple(half(a - origin), 0.0, sq(a)) <
               make_tuple(half(b - origin), cross(a - origin, b - origin), sq(b));
    });
}

struct line {
    point v;
    T c;

    line() {
    }

    // from direction vector v and offset c
    line(point v, T c) : v(v), c(c) {
    }

    // from equation ax + by = c
    line(T a, T b, T c): v({b, -a}), c(c) {
    }

    // from point P, Q
    line(point p, point q): v(q - p), c(cross(v, p)) {
    }

    // point side of line right (+) or left (-) or in line (0) (ax + by - c == 0)
    T side(point p) { return cross(v, p) - c; }
    // distance between point and line => (ax + by - c) / (sqrt(b^2 + a^2))
    T dist(point p) { return abs(side(p)) / abs(v); }
    // get distance square
    T sqDist(point p) { return side(p) * side(p) / (double) sq(v); }
    // get line go through my line
    line perpThrough(point p) { return {p, p + perp(v)}; }
    // sort lines
    bool compProj(point p, point q) {
        return dot(v, p) < dot(v, q);
    }

    line translate(point t) { return {v, c + cross(v, t)}; }
    line shiftLeft(T dist) { return {v, c + dist * abs(v)}; }
    // the closest point of P in line
    point proj(point p) { return p - perp(v) * side(p) / sq(v); }
    // the point in other side of line reflection to P.
    point refl(point p) { return p - perp(v) * (T) 2.0 * side(p) / sq(v); }
};

bool inter(line l1, line l2, point &out) {
    T d = cross(l1.v, l2.v);
    if (fabs(d) < EPS) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

line bisector(line l1, line l2, bool interior) {
    // interior = 1 for inside line, 0 for outside line
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    T sign = interior ? 1 : -1;
    return {
        l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
        l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign
    };
}

// segments
// checks if a point P lies on the disk of diameter [AB]
bool inDisk(point a, point b, point p) {
    return dot(a - p, b - p) <= EPS;
}

bool onSegment(point a, point b, point c) {
    // ensure 3 point not co-linear and in disk
    return orient(a, b, c) == 0 && inDisk(a, b, c);
}

bool properInter(point a, point b, point c, point d, point &out) {
    T oa = orient(c, d, a),
            ob = orient(c, d, b),
            oc = orient(a, b, c),
            od = orient(a, b, d);
    // Proper intersection exists iff opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

set<pair<T, T> > inters(point a, point b, point c, point d) {
    set<pair<T, T> > s;
    point out;
    if (a == c || a == d) s.insert(make_pair(a.x, a.y));
    if (b == c || b == d) s.insert(make_pair(b.x, b.y));
    if (s.size()) return s;
    if (properInter(a, b, c, d, out)) return {make_pair(out.x, out.y)};
    if (onSegment(c, d, a)) s.insert(make_pair(a.x, a.y));
    if (onSegment(c, d, b)) s.insert(make_pair(b.x, b.y));
    if (onSegment(a, b, c)) s.insert(make_pair(c.x, c.y));
    if (onSegment(a, b, d)) s.insert(make_pair(d.x, d.y));
    return s;
}

// distance between point and segment
T segPoint(point a, point b, point p) {
    if (a != b) {
        line l(a, b);
        if (l.compProj(a, p) && l.compProj(p, b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}

T segSeg(point a, point b, point c, point d) {
    point dummy;
    if (properInter(a, b, c, d, dummy))
        return 0;
    return min({
        segPoint(a, b, c), segPoint(a, b, d),
        segPoint(c, d, a), segPoint(c, d, b)
    });
}


double areaTriangle(point a, point b, point c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

T areaPolygon(vector<point> p) {
    T area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n - 1
    }
    return abs(area) / 2.0; // if area positive the order of point clockwise else counterclockwise
}

bool above(point a, point p) {
    return p.y >= a.y;
}

// check if [PQ] crosses ray from A
bool crossesRay(point a, point p, point q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

bool inPolygon(vector<point> p, point a, bool strict = true) {
    // consider point in polygon lines or not
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

// get circle from three points
pair<point, T> circumCircle(point a, point b, point c) {
    b = b - a, c = c - a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return {
        // a + radis
        a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / (T) 2, abs(perp(b * sq(c) - c * sq(b)) / cross(b, c) / (T) 2)
    };
}

int circleLine(point o, double r, line l, pair<point, point> &out) {
    double h2 = r * r - l.sqDist(o);
    if (h2 >= 0) {
        // else not intersection
        // the line touches the circle
        point p = l.proj(o); // point P
        point h = l.v * (T) (sqrt(h2) / abs(l.v)); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}

int circleCircle(point o1, T r1, point o2, T r2, pair<point, point> &out) {
    point d = o2 - o1;
    T d2 = sq(d);
    if (d2 == 0) {
        assert(r1 != r2); // identical circles
        return 0;
    } // concentric circles
    T pd = (d2 + r1 * r1 - r2 * r2) / 2; // = |O_1P| * d
    T h2 = r1 * r1 - pd * pd / d2; // = hˆ2
    if (h2 >= 0) {
        point p = o1 + d * pd / d2, h = perp(d) * (T) sqrt(h2 / d2);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}

int tangents(point o1, T r1, point o2, T r2, bool inner, vector<pair<point, point>> &out) {// out.first for first circle and second for second circle
    if (inner) r2 = -r2;
    point d = o2 - o1;
    T dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) { // not intersection
        assert(h2 != 0);
        return 0;
    }
    for (T sign: {-1, 1}) {
        point v = (d * dr + perp(d) * (T) sqrt(h2) * sign) / d2;
        out.push_back({o1 + v * r1, o2 + v * r2});
    }
    return 1 + (h2 > 0);
}

pair<int, int> polygonLatticePoints(vector<point> & points) { // first for inside, second for boundry
    int n = points.size(), b = 0;

    auto lattice = [&](point a, point b) -> int {
        return __gcd(abs(a.x - b. x), abs(a.y - b.y)) + 1;
    };

    for (int i = 0;i < n;i++) {
        b += lattice(points[i], points[(i + 1) % n]);
    }

    auto area = areaPolygon(points); // take it square to avoid doubles
    b -= n;
    int I = (area - b + 2) / 2;
    return {I, b};
}

int MinDistancePoints(vector<point> & arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end(), [](point a, point b) {
        return a.x < b.x;
    });
    set<array<int, 2>> window;
    int ans = 8e18 + 5, inf = 1e9;
    for (int i = 0, j = 0;i < n;i++) {
        while (j < n && arr[i].x - arr[j].x > sqrt(ans)) {
            window.erase({arr[j].y, arr[j].x});
            j++;
        }

        auto st = window.lower_bound({arr[i].y - (T)sqrt(ans), -inf});
        auto en = window.lower_bound({arr[i].y + (T)sqrt(ans), -inf});
        if (en != window.end()) en++;
        while (st != en) {
            point cur = {(*st)[1], (*st)[0]};
            ans = min(ans, sq(arr[i] - cur));
            ++st;
        }
        window.insert({arr[i].y, arr[i].x});
    }
    return ans;
}
