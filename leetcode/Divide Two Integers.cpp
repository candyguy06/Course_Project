# include<iostream>
using namespace std ;
/*
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [?231, 231 ? 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.

 

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.
 

Constraints:

-231 <= dividend, divisor <= 231 - 1
divisor != 0

*** 
long int < -2^31 不能轉正????    
unsigned int  才能? 
*/


class Solution {
public:
    int divide(int dividend, int divisor) {
		if( ( dividend == 2147483647 && divisor == 1 ) || ( dividend == -2147483648 && divisor == -1 ) ) return 2147483647 ;
		if( dividend == -2147483648 && divisor == 1 ) return -2147483648 ;
		
		int ans = 0 ;
//		long int d1 = dividend ;
//		long int d2 = divisor ;
        unsigned int d1 = abs(dividend);
        unsigned int d2 = abs(divisor);
		while( d1 >= d2 ) {
			ans++ ;
			d1 -= d2 ;
		} // while
		
		if( ( dividend > 0 && divisor > 0) || ( dividend < 0 && divisor < 0) ) return ans ;
		else return -ans ;
    }
};


class Solution2 { // faster
public:
    int divide(int dividend, int divisor) {
		if( ( dividend == 2147483647 && divisor == 1 ) || ( dividend == -2147483648 && divisor == -1 ) ) return 2147483647 ;
		if( dividend == -2147483648 && divisor == 1 ) return -2147483648 ;
		
		int ans = 0 ;
        unsigned int d1 = abs(dividend);
        unsigned int d2 = abs(divisor);
		while( d1 >= d2 ) {
			long temp = d2 ;
			long mul = 1 ;
			while( d1 > (temp<<1) ) { // temp << 1 == temp * 2 
				temp = temp << 1 ;
				mul= mul << 1 ;
			}  //while
			ans += mul ;
			d1 -= temp ;
		} // while
		
		if( ( dividend > 0 && divisor > 0) || ( dividend < 0 && divisor < 0) ) return ans ;
		else return -ans ;
    }
};


int main() {
	int dividend = -2147483648 ;
	int divisor =  2 ;
	Solution s1 ;
	int ans = s1.divide(dividend,divisor) ;
	cout << ans << ",done!" ;
	
} // main
