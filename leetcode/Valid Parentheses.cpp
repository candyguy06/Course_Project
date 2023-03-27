# include<iostream>
# include<string>
# include<vector>
using namespace std ;
/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
 

Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.

*** stack 後進先出 
*/

class Solution {
public:
    bool isValid(string s) {
    	if ( s.size() % 2 != 0 ) return false ;
		vector<char> temp ;
    	for( int i = 0 ; i < s.size() ; i++ ) {
			if ( s[i] == '(' || s[i] == '[' || s[i] == '{' ) temp.push_back(s[i]) ;
			else {
				if( temp.empty() ) return false ;
				
				if( s[i] == ')' && temp[temp.size()-1] == '(' ) temp.pop_back() ;

				else if( s[i] == ']' && temp[temp.size()-1] == '[' ) temp.pop_back() ;

				else if( s[i] == '}' && temp[temp.size()-1] == '{' ) temp.pop_back() ;
				
				else return false ;
				
			} // else
		} // for
		
		if( temp.empty() ) return true ;
		else return false ;
        
    }
};

int main() {
	string s = "()" ;
	Solution s1 ;
	if( s1.isValid(s) ) cout << "true" ;
	else cout << "false" ;
	
}
