 

#define ll long long
#define ull unsigned long long
ll mul( ll a , ll b , ll M ) {
  ll ret = a * b - M * ( ll ) ( 1.L / M * a * b );
  return ret + M * ( ret < 0 ) - M * ( ret >= ( ll ) M );
  }
ll Fp( ll b , ll e , ll mod ) {
  ll ans = 1;
  for ( ; e; b = mul( b , b , mod ) , e /= 2 )
    if ( e & 1 )
      ans = mul( ans , b , mod );
  return ans;
  }

bool isPrime( ll n ) {
  if ( n < 2 || n % 6 % 4 != 1 )
    return ( n | 1 ) == 3;
  ll A [ ] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 } ,
    s = __builtin_ctzll( n - 1 ) , d = n >> s;
  for ( ll a : A ) { // ^ count trailing zeroes
    ll p = Fp( a % n , d , n ) , i = s;
    while ( p != 1 && p != n - 1 && a % n && i-- )
      p = mul( p , p , n );
    if ( p != n - 1 && i != s )
      return 0;
    }
  return 1;
  }

ll pollard( ll n ) {
  auto f = [ n ] ( ull x ) { return mul( x , x , n ) + 1; };
  ll x = 0 , y = 0 , t = 30 , prd = 2 , i = 1 , q;
  while ( t++ % 40 || __gcd( prd , n ) == 1 ) {
    if ( x == y )
      x = ++i , y = f( x );
    if ( ( q = mul( prd , max( x , y ) - min( x , y ) , n ) ) )
      prd = q;
    x = f( x ) , y = f( f( y ) );
    }
  return __gcd( prd , n );
  }
vector<ll> factor( ll n ) {
  if ( n == 1 )
    return {};
  if ( isPrime( n ) )
    return { n };
  ull x = pollard( n );
  auto l = factor( x ) , r = factor( n / x );
  l.insert( l.end( ) , r.begin( ) , r.end( ) );
  return l;
  }
vector<ll> get( ll n ) {
  auto d = factor( n );
  sort( d.begin( ) , d.end( ) );
  d.resize( unique( d.begin( ) , d.end( ) ) - d.begin( ) );
  return d;
  }
