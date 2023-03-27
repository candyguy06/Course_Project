# include<iostream>
# include<string>

using namespace std ;
/*
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:

Read in and ignore any leading whitespace.
Check if the next character (if not already at the end of the string) is '-' or '+'. Read this character in if it is either. This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
Read in next the characters until the next non-digit character or the end of the input is reached. The rest of the string is ignored.
Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then clamp the integer so that it remains in the range. Specifically, integers less than -231 should be clamped to -231, and integers greater than 231 - 1 should be clamped to 231 - 1.
Return the integer as the final result.
Note:

Only the space character ' ' is considered a whitespace character.
Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.
 

Example 1:

Input: s = "42"
Output: 42
Explanation: The underlined characters are what is read in, the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
The parsed integer is 42.
Since 42 is in the range [-231, 231 - 1], the final result is 42.
Example 2:

Input: s = "   -42"
Output: -42
Explanation:
Step 1: "   -42" (leading whitespace is read and ignored)
            ^
Step 2: "   -42" ('-' is read, so the result should be negative)
             ^
Step 3: "   -42" ("42" is read in)
               ^
The parsed integer is -42.
Since -42 is in the range [-231, 231 - 1], the final result is -42.
Example 3:

Input: s = "4193 with words"
Output: 4193
Explanation:
Step 1: "4193 with words" (no characters read because there is no leading whitespace)
         ^
Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a non-digit)
             ^
The parsed integer is 4193.
Since 4193 is in the range [-231, 231 - 1], the final result is 4193.
 

Constraints:

0 <= s.length <= 200
s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.

** 文字與數字的關係
-> '0' != 0  | '0' - '0' == 0 | 字元的數值是編碼值! 
** 如何處理邊界 與 溢位問題 
-> 用更大的變數型態取邊界避免溢位問題 
*/



class Solution {
public:
	
	bool pn = true ;
	const int I_MAX = 2147483647 ;
	const int I_MIN = -2147483648 ;

    int myAtoi(string s) {
    	int i = 0 ;
    	long long output = 0 ;
    	skipwhitespace(s,i) ;
		skipsign(s,i) ;
		
    	while ( i < s.size() && s[i] - '0' >= 0 && s[i]-'0' <= 9  ) {
    		output = output * 10 + ( s[i] - '0' ) ;
    		if ( output >= 2147483647 && pn ) {
				return I_MAX ;
				break ;				
			} // if
			
			else if ( output >= 2147483648 && !pn ) {
				return I_MIN ;
				break ;
			} // else if
			
			i++ ; 
			   		
		} // while
				
		if ( !pn ) output = -output ;
		return output ;
    	   	
        
    }
    
    void skipwhitespace( string s , int & i ) {
    	while ( i < s.size() && s[i] == ' ' ) i++ ;
    	
	} // 
	
	void skipsign( string s , int & i ) {
		if ( i < s.size() && s[i] == '+' ) {
			i++ ;
		} // if
		
		else if ( i < s.size() && s[i] == '-' ) {
			i++ ;
			pn = false ;
		} // else if
		
		/*
		while ( i < s.size() && ( s[i] == '+' || s[i] == '-' ) ) {
    		if ( s[i] == '-' ) pn = !pn ;			
			i++ ;
		} // while 
		*/
		
	} //
	
};


int main() {
	string s = "-2147483646" ;
	s = "2147483800" ;
	Solution s1 ;
	long long ans = s1.myAtoi(s) ;
	cout << ans << ",done!" ;
} 
