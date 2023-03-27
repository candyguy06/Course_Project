# include<iostream>
/*
Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

 

Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000
Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100
Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
 

Constraints:

-100.0 < x < 100.0
-231 <= n <= 231-1
n is an integer.
-104 <= xn <= 104
*/

using namespace std ;

class Solution {
public:
    double myPow(double x, int n) {
        if( x == 1 || n == 0 ) return 1 ;
        double output = 1 ;
        for( int i = n ; i != 0 ; i = i / 2 ) {
            if( i%2 != 0 ) output = output * x ; // 虫计 - 1 = 蛮计 
            x = x * x ;  // ┏计 * ┏计 & 计 / 2 
        } // for

        return n > 0 ? output : 1/output ;
    }
};

int main() {
	double x = 2 ;
	int n = 2 ;
	Solution s1 ;
	double ans = s1.myPow(x,n) ;
	cout << ans << ",done!" ;
}
