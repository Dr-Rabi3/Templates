

const int MAX = 31;
int comb [ MAX ][ MAX ];

void pre( ) {
  comb [ 0 ][ 0 ] = 1;
  for ( int i = 1; i < MAX; i++ ) {
    comb [ i ][ 0 ] = comb [ i ][ i ] = 1;
    for ( int j = 1; j < i; j++ )
      comb [ i ][ j ] = comb [ i - 1 ][ j ] + comb [ i - 1 ][ j - 1 ];
    }
  }


double nCr( int n , int r ) { // O(r)
  if ( r > n || r < 0 )
    return 0;
  long double ans = 1;
  int rfact = 1;

  for ( int g = n - r + 1; g <= n; g++ ) {
    ans *= g;
    ans /= rfact;
    rfact++;
    }
  return ans;
  }


int nCr(int n , int r) {
  int ans = 1;
  for (int i = 1;i <= r;i++) {
    ans = (ans * (n - i + 1)) / i;
  }
  return ans;
}