#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template < typename T , typename _Compare = less<T> >
using ordered_set = tree< T , null_type , _Compare , rb_tree_tag , tree_order_statistics_node_update >;

ordered_set<int>o_set;

int main( ) {

  // Finding the second smallest element in the set using * because find_by_order returns an iterator (value in index)
  *( o_set.find_by_order( 1 ) );

  
  // Finding the number of elements strictly less than k=4 (index of x)
  o_set.order_of_key( 4 );

  }
