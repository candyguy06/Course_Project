# include<iostream>
# include<vector>
using namespace std ;
/*
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses 
substring
.

 

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
Example 3:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 3 * 104
s[i] is '(', or ')'.

*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0 ;
        vector<int> temp = {-1} ;
        for( int i = 0 ; i < s.size() ; i++ ) {
        	if(  s[i] == '(' ) {
				 temp.push_back(i) ;
			}  // if
			else if ( s[i] == ')' ) {
				int j = temp[temp.size()-1] ;
				temp.pop_back() ;
				if( temp.empty() ) {
					temp.push_back(i) ;
				} // if
				else {
					if( ans < i - temp[temp.size()-1] ) ans = i - temp[temp.size()-1] ;
				} // else
			} // else if
			
		} // for
		
		return ans ;
    }
};

class Solution2 {
public:
    int longestValidParentheses(string s) {
        int ans = 0 ;
        vector<int> dp(s.size()+1,0) ;
        for (int i = 1; i <= s.size(); ++i) {
            int j = i - 2 - dp[i - 1];
            if (s[i - 1] == '(' || j < 0 || s[j] == ')') {
                dp[i] = 0;
            } else {
                dp[i] = dp[i - 1] + 2 + dp[j];
                ans = max(ans, dp[i]);
            }
        }
		
		return ans ;
    }
};


int main() {
	string s = "()(()" ;
	Solution s1 ;
	int ans = s1.longestValidParentheses(s) ;
	cout << ans << ",done!" ;
} // main ;
 
