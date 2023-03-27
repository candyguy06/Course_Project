#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000

解題思維 :
分成n階層時
第一層與最後一層每個index相隔[2*(n-1)] 
中間所有層 奇數彼此間相隔 [2*(n-1)]  奇數的下一個(偶數)相隔 [ 2*(n-1) - 2*該層數 ]
ex numRows == 3
0   4   8     -> 第一層每個相隔 2*(3-1) = 4 ; 0-4-8 
 1 3 5 7 9    ->  1-5-9 相隔 2*(3-1) = 4 ; 1-3,5-7 相隔 2*(3-1) - 2 * 1 = 2 
  2   6   10  -> 最後一層每個相隔 2*(3-1) = 4 ; 2-6-10 

 
*/

class Solution {
public:
    string convert(string s, int numRows) {
		string output = "" ;
		
		int step = 2 * (numRows-1) ; // 間隔 
		if ( numRows == 1 || s.size() <= numRows ) return s ; // 字串太短或層數太低 排不排結果一樣 
		for ( int i = 0 ; i < numRows ; i++ ) { // 從第一層開始排 
			for ( int j = i ; j < s.size() ; j+= step ) { // 從該層第一個字元開始排 
				output += s[j] ;
				if ( i != 0 && i != numRows - 1 ) { // 如果不是第一或最後層 排偶數index 
					if ( j + step - 2 * i < s.size() ) output += s[j + step - 2 * i] ;
				} // if
			} // for
		}	// for	
		
		return output ;
    }
};

int main() {
	string s = "PAYPALISHIRING" ;
	int numRows = 4 ;
	Solution s1 ;
	cout << s1.convert(s,numRows) << endl << "done" ;
/*
	bool b = false ;
	for ( int i = 0 ; i < 10 ; i++ ) {
		cout << b << endl ;
		b = !b ;
	}	
*/
}
