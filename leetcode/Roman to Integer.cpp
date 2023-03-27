# include <map> 
# include <iostream>
# include <string>
using namespace std ;
/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer.

 

Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.
Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 

Constraints:

1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].

***
string = char1 + char2 -> error
string = char1 ; string += char2 -> right

*/

class Solution {
public:
    int romanToInt(string s) {
    	map<string,int> symbol = { {"M",1000},{"CM",900},{"D",500},{"CD",400},{"C",100},{"XC",90},{"L",50},{"XL",40},{"X",10},{"IX",9},{"V",5},{"IV",4},{"I",1} } ;
		int i = 0, output = 0 ;
		string temp ;

    	while( i < s.size() ) {
    		if( i+1 < s.size() && s[i] == 'C' && ( ( s[i+1] == 'M' ) || ( s[i+1] == 'D' ) ) ) {
    			temp = s.substr(i,2) ;
				output = output + symbol[temp] ;
				i += 2 ;
			} // if

    		else if( i+1 < s.size() && s[i] == 'X' && ( ( s[i+1] == 'C' ) || ( s[i+1] == 'L' ) ) ) {
    			temp = s.substr(i,2) ;
				output = output + symbol[temp] ;
				i += 2 ;
			} // else if

    		else if( i+1 < s.size() && s[i] == 'I' && ( ( s[i+1] == 'X' ) || ( s[i+1] == 'V' ) ) ) {
    			temp = s.substr(i,2) ;
				output = output + symbol[temp] ;
				i += 2 ;
			} // else if
			
			else {
    			temp = s[i];
				output = output + symbol[temp] ;
				i += 1 ;
			} // else
			
		} // while
		
		return output ;
        
    }
    
};

class Solution2 {
public:
int romanToInt(string s) {
    map<char,int> mp{
        {'I',1},
        {'V',5},
        {'X',10},
        {'L',50},
        {'C',100},
        {'D',500},
        {'M',1000},
    };
    int ans =0;
    for(int i=0;i<s.size();i++){
        if(i+1<s.size() && mp[s[i]]<mp[s[i+1]])
            ans-=mp[s[i]];
        else
            ans+=mp[s[i]];
    }
    return ans;
    
}
};




int main() {
	string s = "MCMXCIV" ;
//	s = "I" ;
	Solution s1 ;
	cout << s1.romanToInt(s) << ",done!" << endl ;	
}  // main
