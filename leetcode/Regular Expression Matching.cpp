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
DP : dp = bool[s.size()+1][p.size()+1] = false -> 0為空 所以要多一個 
1.邊界 
	s,n皆為空時 -> true
	s != 0 && n == 0 時 -> false
	s == 0 && n != 0 時 -> 在每個字元後面都接*時 true(*皆等於0) 否則 false 
2.運作方式 
	* i_index = i-1 (j同理) * -> dp有空字串的可能 所以比字串多1 
	s[i_index] == p[j_index] || p[j] == '.' 時 -> 字元相等 所以只要前面全等就相等 dp[i][j] = dp[i-1][j-1]
	p[j_index] == '*' 時 -> 兩種可能
		第一 : * == 0 則 dp[i][j] = dp[i][j-2]
								忽略char* 
		第二 : * >= 1 則 dp[i][j] = ( s[i_index] == p[j_index] || p[j_index] == '.' ) && dp[i-1][j]  ;
												字元相等								重複至少一次 
dp[s.size()+1][p.size()+1] == result
*/

class Solution {
public:
  bool isMatch(string s, string p) {
    vector<vector<bool>> dp(s.length() + 1, vector<bool>(p.length() + 1, false));

    dp[0][0] = true; // 空字串為真 

    /* "" v.s. X*X*X*..... */
 
    for(int i = 2 ; i <= p.length() && p[i-1] == '*' ; i += 2){
      dp[0][i] = true;
    }
 
    /* s[0...i-1] v.s. p[0...j-1] */
    for(int i = 1 ; i <= s.length() ; ++i){
      for(int j = 1 ; j <= p.length() ; ++j ){
        int sIndex = i-1;
        int pIndex = j-1;

        if(p[pIndex] == '.' || s[sIndex] == p[pIndex]){ // 當下字元匹配 只要前面能匹配就為真 
          dp[i][j] = dp[i-1][j-1];  
        }
        else if(p[pIndex] == '*'){ // 特殊字元 可能沒有或者重複n次 
          dp[i][j] = dp[i][j-2] || ( (s[sIndex] == p[pIndex-1] || p[pIndex-1] == '.') && dp[i-1][j]); // 狀況1 * = 0 則只要p前兩個能匹配就行 狀況2 * >= 1 p的前一個能與當前s匹配(相同或.) dp[i-1][j] == 重複一到多次 
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

    dp[0][0] = true; // 空字串為真 

    /* s[0...i-1] v.s. p[0...j-1] */
    for(int i = 0 ; i <= s.length() ; ++i){
      for(int j = 1 ; j <= p.length() ; ++j ){
        int sIndex = i-1;
        int pIndex = j-1;

        if( i && (p[pIndex] == '.' || s[sIndex] == p[pIndex]) ) { // 當下字元匹配 只要前面能匹配就為真 
          dp[i][j] = dp[i-1][j-1];  
        }
        else if(p[pIndex] == '*'){ // 特殊字元 可能沒有或者重複n次 
          dp[i][j] = dp[i][j-2] || ( i && (s[sIndex] == p[pIndex-1] || p[pIndex-1] == '.') && dp[i-1][j]); // 狀況1 * = 0 則只要p前兩個能匹配就行 狀況2 * >= 1 p的前一個能與當前s匹配(相同或.) dp[i-1][j] == 重複一到多次 
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
