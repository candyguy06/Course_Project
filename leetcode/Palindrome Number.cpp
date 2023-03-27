# include<string>
# include<iostream>
using namespace std ;

/*
Given an integer x, return true if x is palindrome integer.

An integer is a palindrome when it reads the same backward as forward.

For example, 121 is a palindrome while 123 is not.
 

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 

Constraints:

-231 <= x <= 231 - 1
*/

class Solution {
public :
	bool isPalindrome(int x) {
		if ( x < 0 ) return false ;
		unsigned int temp = x, y = 0 ;
		while ( temp > 0 ) {
			y = y * 10 + (temp%10) ;
			temp = temp/10 ;
		} // while
		
		if ( x == y ) return true ;
		else return false ;
        
    }
};

int main() {
	int x = 123 ;
	Solution s1 ;
	if ( s1.isPalindrome(x) ) cout << "is Palindrome" << endl ;
	else cout << "is not Palindrome" << endl ;
	
} // main
