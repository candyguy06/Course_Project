# include<iostream>
# include<string>
# include<vector>

using namespace std ;
/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.????
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
 

Constraints:

1 <= s.length <= 20
1 <= p.length <= 30
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.

***
DP : dp = bool[s.size()+1][p.size()+1] = false -> 0���� �ҥH�n�h�@�� 
1.��� 
	s,n�Ҭ��Ů� -> true
	s != 0 && n == 0 �� -> false
	s == 0 && n != 0 �� -> �b�C�Ӧr���᭱����*�� true(*�ҵ���0) �_�h false 
2.�B�@�覡 
	* i_index = i-1 (j�P�z) * -> dp���Ŧr�ꪺ�i�� �ҥH��r��h1 
	s[i_index] == p[j_index] || p[j] == '.' �� -> �r���۵� �ҥH�u�n�e�������N�۵� dp[i][j] = dp[i-1][j-1]
	p[j_index] == '*' �� -> ��إi��
		�Ĥ@ : * == 0 �h dp[i][j] = dp[i][j-2]
								����char* 
		�ĤG : * >= 1 �h dp[i][j] = ( s[i_index] == p[j_index] || p[j_index] == '.' ) && dp[i-1][j]  ;
												�r���۵�								���Ʀܤ֤@�� 
dp[s.size()+1][p.size()+1] == result
*/

class Solution {
public:
  bool isMatch(string s, string p) {
    vector<vector<bool>> dp(s.length() + 1, vector<bool>(p.length() + 1, false));

    dp[0][0] = true; // �Ŧr�ꬰ�u 

    /* "" v.s. X*X*X*..... */
 
    for(int i = 2 ; i <= p.length() && p[i-1] == '*' ; i += 2){
      dp[0][i] = true;
    }
 
    /* s[0...i-1] v.s. p[0...j-1] */
    for(int i = 1 ; i <= s.length() ; ++i){
      for(int j = 1 ; j <= p.length() ; ++j ){
        int sIndex = i-1;
        int pIndex = j-1;

        if(p[pIndex] == '.' || s[sIndex] == p[pIndex]){ // ��U�r���ǰt �u�n�e����ǰt�N���u 
          dp[i][j] = dp[i-1][j-1];  
        }
        else if(p[pIndex] == '*'){ // �S��r�� �i��S���Ϊ̭���n�� 
          dp[i][j] = dp[i][j-2] || ( (s[sIndex] == p[pIndex-1] || p[pIndex-1] == '.') && dp[i-1][j]); // ���p1 * = 0 �h�u�np�e��ӯ�ǰt�N�� ���p2 * >= 1 p���e�@�ӯ�P��es�ǰt(�ۦP��.) dp[i-1][j] == ���Ƥ@��h�� 
        }
      }
    }

    return dp[s.size()][p.size()];
  }
};

class Solution2 {
public:
  bool isMatch(string s, string p) {
    vector<vector<bool>> dp(s.length() + 1, vector<bool>(p.length() + 1, false));

    dp[0][0] = true; // �Ŧr�ꬰ�u 

    /* s[0...i-1] v.s. p[0...j-1] */
    for(int i = 0 ; i <= s.length() ; ++i){
      for(int j = 1 ; j <= p.length() ; ++j ){
        int sIndex = i-1;
        int pIndex = j-1;

        if( i && (p[pIndex] == '.' || s[sIndex] == p[pIndex]) ) { // ��U�r���ǰt �u�n�e����ǰt�N���u 
          dp[i][j] = dp[i-1][j-1];  
        }
        else if(p[pIndex] == '*'){ // �S��r�� �i��S���Ϊ̭���n�� 
          dp[i][j] = dp[i][j-2] || ( i && (s[sIndex] == p[pIndex-1] || p[pIndex-1] == '.') && dp[i-1][j]); // ���p1 * = 0 �h�u�np�e��ӯ�ǰt�N�� ���p2 * >= 1 p���e�@�ӯ�P��es�ǰt(�ۦP��.) dp[i-1][j] == ���Ƥ@��h�� 
        }
      }
    }

    return dp[s.size()][p.size()];
  }
};

int main() {
	string s = "aaa",p = "a*a*a" ;
	Solution s1 ;
	if ( s1.isMatch(s,p) )	cout << "True" << endl ;
	else cout << "False" << endl ;
	
	
} // main()
