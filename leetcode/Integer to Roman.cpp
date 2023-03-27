# include<string>
# include<iostream> 
# include<vector> 

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
For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral.

 

Example 1:

Input: num = 3
Output: "III"
Explanation: 3 is represented as 3 ones.
Example 2:

Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
Example 3:

Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 

Constraints:

1 <= num <= 3999

*** 
'*'�N����0��h�� 
1(0*) - 5(0*) - 10(0*)
1~3 -> 1(+1)*
4 -> |1-5|
5 -> 5
6~8 -> 5(+1)*
9 -> |1-10|

�ѥ���k��r����
1(0*),5(0*),10(0*)�O�򥻦r�� �ҥH�C�J�Ÿ���
4(0*),9(0*) �]���e���n"���J"����� �ҥH�C�J�Ÿ��� �j�׳B�̴��J

�Ÿ���q�j��p�h���H��J �Y>0 -> �N��Ÿ��i�H�Q��J
��J�Ÿ��Ỽ��Ȩ� = 0 �b���U�@�ӲŸ�  

*/

class Solution {
public:
    string intToRoman(int num) {
        vector<string> symbol = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1} ;
        string output;       
        for (int i=0; i<nums.size(); i++) {
            if (num >= nums[i]) {
                for (int j=0; j<(num/nums[i]); j++) {
                    output += symbol[i];
                } // for
                num = num % nums[i];
            } // if
        } // for
        
        return output;
    }
};

int main() {
	int num = 1994 ;
	Solution s1 ;
	cout << s1.intToRoman(num) << ",done!" << endl ;
	
} // main
