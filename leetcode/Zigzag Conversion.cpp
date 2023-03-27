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

���D��� :
����n���h��
�Ĥ@�h�P�̫�@�h�C��index�۹j[2*(n-1)] 
�����Ҧ��h �_�Ʃ������۹j [2*(n-1)]  �_�ƪ��U�@��(����)�۹j [ 2*(n-1) - 2*�Ӽh�� ]
ex numRows == 3
0   4   8     -> �Ĥ@�h�C�Ӭ۹j 2*(3-1) = 4 ; 0-4-8 
 1 3 5 7 9    ->  1-5-9 �۹j 2*(3-1) = 4 ; 1-3,5-7 �۹j 2*(3-1) - 2 * 1 = 2 
  2   6   10  -> �̫�@�h�C�Ӭ۹j 2*(3-1) = 4 ; 2-6-10 

 
*/

class Solution {
public:
    string convert(string s, int numRows) {
		string output = "" ;
		
		int step = 2 * (numRows-1) ; // ���j 
		if ( numRows == 1 || s.size() <= numRows ) return s ; // �r��ӵu�μh�ƤӧC �Ƥ��Ƶ��G�@�� 
		for ( int i = 0 ; i < numRows ; i++ ) { // �q�Ĥ@�h�}�l�� 
			for ( int j = i ; j < s.size() ; j+= step ) { // �q�Ӽh�Ĥ@�Ӧr���}�l�� 
				output += s[j] ;
				if ( i != 0 && i != numRows - 1 ) { // �p�G���O�Ĥ@�γ̫�h �ư���index 
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
