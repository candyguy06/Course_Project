#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>

using namespace std;

/*
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

 

Example 1:

Input: x = 123
Output: 321
Example 2:

Input: x = -123
Output: -321
Example 3:

Input: x = 120
Output: 21
 

Constraints:

-231 <= x <= 231 - 1

­«ÂI : 
1. -123 % 10 = -3 
2. 2**21 =  2147483648

*/

class Solution {
public:
    int reverse(int x) {
    	int output = 0 ;		
		while ( x != 0  ) {
            if ( output > 214748364 || output < -214748364 ) {
                output = 0 ;
                break ;
            } // if
			output = output*10 + (x % 10) ;
			x = x / 10 ;
		} // while
		
		return output ;   
    }
};

class Solution1 { // time out
public:
    int reverse(int x) {
    	bool pn = true ;
    	if ( x < 0 ) {
    		x = -x ;
    		pn = false ;
		} // if
		
		while ( x%10 == 0 ) x = x / 10 ;
    	
    	string temp1 = to_string(x) ;
    	string temp2 = "" ;
		if ( !pn ) temp2 += '-' ;

    	for ( int i = temp1.size() - 1 ; i >= 0 ; i-- ) {
    		temp2 += temp1[i] ;
		} // for
		
		return stoi(temp2) ;
    	
        
    }
};


int main() {
	int x = -123 ; 
	Solution s1 ;
	cout << s1.reverse(x) << endl << "done!" ;

}
