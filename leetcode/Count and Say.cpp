# include<iostream>
# include<string>
using namespace std ;
/*
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

countAndSay(1) = "1"
countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then converted into a different digit string.
To determine how you "say" a digit string, split it into the minimal number of substrings such that each substring contains exactly one unique digit. Then for each substring, say the number of digits, then say the digit. Finally, concatenate every said digit.

For example, the saying and conversion for digit string "3322251":


Given a positive integer n, return the nth term of the count-and-say sequence.

 

Example 1:

Input: n = 1
Output: "1"
Explanation: This is the base case.
Example 2:

Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1's = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"
 

Constraints:

1 <= n <= 30

題義 : 出字串1；n=2時，數上次字串中的數值個數，因為上次字串有1個1，所以輸出11；n=3時，由於上次字元是11，有2個1，所以輸出21；n=4時，由於上次字串是21，有1個2和1個1，所以輸出1211。依次類推，寫個countAndSay(n)函式返回字串。

 
*/
class Solution {
public:
    string countAndSay(int n) {
		if( n == 1 ) return "1" ;
		string s = countAndSay(n-1) ;
		string output = "" ;
		int c = 1 ;
		char cc ;
		for( int i = 0; i < s.size() ; i++ ) {
			if( i+1 < s.size() && s[i] == s[i+1] ) {
				c++ ;
			} // if
			
			else {
				cc = c + '0' ;
				output += cc ;
				output+=s[i] ;
				c = 1 ;
			} // else
		} // for

		return output ;
    }
    
};

int main() {
	int n = 4 ;
	Solution s1 ;
	string s = s1.countAndSay(n) ;
	cout << s << ",done!" ;
	
}
 
