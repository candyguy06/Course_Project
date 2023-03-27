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

�D�q : �X�r��1�Fn=2�ɡA�ƤW���r�ꤤ���ƭȭӼơA�]���W���r�꦳1��1�A�ҥH��X11�Fn=3�ɡA�ѩ�W���r���O11�A��2��1�A�ҥH��X21�Fn=4�ɡA�ѩ�W���r��O21�A��1��2�M1��1�A�ҥH��X1211�C�̦������A�g��countAndSay(n)�禡��^�r��C

 
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
 
