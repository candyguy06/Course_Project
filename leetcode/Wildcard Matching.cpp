# include<iostream>
# include<string>
# include<vector>
using namespace std ;

/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
 

Constraints:

0 <= s.length, p.length <= 2000
s contains only lowercase English letters.
p contains only lowercase English letters, '?' or '*'.
*/

class Solution {
public:
    bool isMatch(string s, string p) {
    	vector<vector<bool>> dp( s.size() + 1,( vector<bool>(p.size()+1,false) )) ;
    	dp[0][0] = true ;
    	
    	if( p[0] == '*' ) {
    		for( int i = 0 ; i <= s.size() ; i++ ) dp[i][1] = true ;
		} // if
    	
    	for(int i = 0 ; i <= s.size() ; i++ ) {
    		for( int j = 1 ; j <= p.size() ; j++ ) {
    			if( p[j-1] == '*' ) {
    				if( i ) dp[i][j] = dp[i-1][j] || dp[i][j-1] ;
    				else dp[i][j] = dp[i][j-1] ;
				} // if
				else if( i && (p[j-1] == '?' || p[j-1] == s[i-1])  ) {
					dp[i][j] = dp[i-1][j-1] ;
				} // else
			} // for
		} // for
/*				
    	for(int i = 0 ; i <= p.size() ; i++ ) {
    		for( int j = 0 ; j <= s.size() ; j++ ) {
				cout << dp[j][i] << "," ;
			} // for
			cout << endl ;
		} // for
*/		
		
		return dp[s.size()][p.size()] ;
        
    }
};

int main() {
	string s = "aabc" ;
	string p = "*aa*c" ;
	Solution s1 ;
	if( s1.isMatch(s,p) ) cout << "T" ;
	else cout << "F" ;
	
}

// aab
// c*a*b

// 
// ******

