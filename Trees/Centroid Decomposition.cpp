#include <bits/stdc++.h>
#define int long long
#define ed '\n'
using namespace std;

constexpr int N = 1e5 + 5;
vector<int>adj [ N ];
vector<int>subtree_size( N ) , is_removed( N );
// min_dist[v] := the minimal distance between v and a red node
vector<int> min_dist( N , 1e18 );
vector<vector<pair<int , int>>> ancestors( N );
int n , q;

int get_subtree_size( int u , int p = -1 ) {
  subtree_size [ u ] = 1;
  for ( int v : adj [ u ] ) {
    if ( v == p || is_removed [ v ] )continue;
    subtree_size [ u ] += get_subtree_size( v , u );
    }
  return subtree_size [ u ];
  }

int get_centroid( int u , int sz , int p = -1 ) {
  for ( int v : adj [ u ] ) {
    if ( v == p || is_removed [ v ] ) continue;
    if ( subtree_size [ v ] * 2 > sz ) return get_centroid( v , sz , u );
    }
  return u;
  }

/**
 * Calculate the distance between current `node` and the `centroid` it belongs
 * to. The distances between a node and all its centroid ancestors are stored
 * in the vector `ancestors`.
 * @param cur_dist the distance between `node` and `centroid`
 */
void get_dists( int u , int centroid , int p = -1 , int dist = 1 ) {
  for ( int v : adj [ u ] ) {
    if ( v == p || is_removed [ v ] ) continue;
    dist++;
    get_dists( v , centroid , u , dist );
    dist--;
    }
  ancestors [ u ].push_back( { centroid, dist } );
  }

void build_centroid_decomp( int u = 1 ) {
  int centroid = get_centroid( u , get_subtree_size( u ) );
  /*
   * For all nodes in the subtree rooted at `centroid`, calculate their
   * distances to the centroid
   */
  for ( int v : adj [ centroid ] ) {
    if ( is_removed [ v ] ) continue;
    get_dists( v , centroid , centroid );
    }

  is_removed [ centroid ] = true;
  for ( int v : adj [ centroid ] ) {
    if ( is_removed [ v ] ) continue;
    // build the centroid decomposition for all child components
    build_centroid_decomp( v );
    }
  }

/**
 * Paint `node` red by updating all of its ancestors' minimal distances
 * to a red node
 */
void update( int u ) {
  for ( auto temp : ancestors [ u ] ) {
    int anc = temp.first;
    int dist = temp.second;
    min_dist [ anc ] = min( min_dist [ anc ] , dist );
    }
  min_dist [ u ] = 0;
  }

/** Print the minimal distance between `node` to a red node */
int query( int u ) {
  int res = min_dist [ u ];
  for ( auto temp : ancestors [ u ] ) {
    int anc = temp.first;
    int dist = temp.second;
    if ( !dist ) continue;
    res = min( res , min_dist [ anc ] + dist );
    }
  return res;
  }
