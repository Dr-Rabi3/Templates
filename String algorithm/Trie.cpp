#include <bits/stdc++.h>
using namespace std;

class Trie {
  struct Node {
    bool isEndOfWord;
    unordered_map< char , Node* > child;
    string word;
    int cnt;
    Node( ) {
      cnt = 0;
      isEndOfWord = false;
      word = "";
      }
    };
  Node* root;
  int NoDistinctWord;
  public:
  Trie( ) { root = new Node( ); NoDistinctWord = 0; }
  void insert( string& s ) {
    Node* tamp = root;
    for ( auto& i : s ) {
      char c = i;
      if ( tamp->child.count( c ) == 0 || tamp->child [ c ]->cnt == 0 )
        tamp->child [ c ] = new Node( );
      tamp = tamp->child [ c ];
      tamp->cnt++;
      }
    NoDistinctWord += ( !tamp->isEndOfWord );
    tamp->isEndOfWord = true;
    tamp->word = s;
    }
  pair<int , int> Common( Node* node ) {
    queue<pair<Node* , pair<int , int>>>q;
    q.push( { node,{0,0} } );
    pair<int , int>ans;
    while ( !q.empty( ) ) {
      auto to = q.front( );
      ans = max( ans , to.second );
      q.pop( );
      for ( char c = 'a'; c <= 'z'; ++c ) {
        if ( to.first->child.count( c ) ) {
          if ( to.first->child [ c ]->cnt > 2 ) {
            q.push( { to.first->child [ c ],{to.second.first + 1,to.first->child [ c ]->cnt} } );
            }
          }
        }
      }
    return ans;
    }
  pair<int , int>getCommon( ) {
    return Common( root );
    }
  void erase( string& s ) {
    Node* tamp = root;
    for ( auto& i : s ) {
      char c = i;
      tamp = tamp->child [ c ];
      }
    if ( tamp->isEndOfWord ) {
      tamp = root;
      for ( auto& i : s ) {
        char c = i;
        tamp = tamp->child [ c ];
        tamp->cnt--;
        }
      tamp->isEndOfWord = false;
      tamp->word = "";
      }
    }
  bool isPrefix( string& s ) {
    Node* tamp = root;
    for ( auto& i : s ) {
      char c = i;
      if ( tamp->child.count( c ) == 0 || tamp->child [ c ]->cnt == 0 )
        return false;
      tamp = tamp->child [ c ];
      }
    return tamp->cnt > 1;// word itself and another word
    }
  bool search( string& s ) {
    Node* tamp = root;
    for ( auto& i : s ) {
      char c = i;
      if ( tamp->child.count( c ) == 0 || tamp->child [ c ]->cnt == 0 )
        return false;
      tamp = tamp->child [ c ];
      }
    return tamp->isEndOfWord;
    }
  void DFS( Node* node , set < string >& ans ) {
    if ( node->isEndOfWord )ans.insert( node->word );
    for ( char c = 'a'; c <= 'z'; c++ ) {
      if ( node->child.count( c ) == 0 )continue;
      DFS( node->child [ c ] , ans );
      }
    }
  
  set < string > Similar( string& s ) {
    Node* tamp = root;
    for ( auto& i : s ) {
      char c = i;
      if ( tamp->child.count( c ) == 0 || tamp->child [ c ]->cnt == 0 )
        return {};
      tamp = tamp->child [ c ];
      }
    set < string > ans;
    DFS( tamp , ans );
    ans.erase( s );
    return ans;
    }
  int CntSimilar( string& s ) {
    Node* tamp = root;
    for ( auto& i : s ) {
      char c = i;
      if ( tamp->child.count( c ) == 0 || tamp->child [ c ]->cnt == 0 )
        return 0;
      tamp = tamp->child [ c ];
      }
    return tamp->cnt;
    }
  int NoOfDistinctWord( ) {
    return NoDistinctWord;
    }
  };
