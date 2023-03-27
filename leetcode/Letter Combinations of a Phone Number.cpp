# include<string> 
# include<vector> 
# include<map>
# include<iostream>

using namespace std ;

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.


 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = ""
Output: []
Example 3:

Input: digits = "2"
Output: ["a","b","c"]
 

Constraints:

0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].

***
從頭往後放
在慢慢pop回來 

*/

class Solution {
public:
    vector<string> letterCombinations(string digits) {
    	map<char,string> symbol = {{'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}} ;
    	vector<string> ans ;

    	if ( digits.size() < 1 ) return {} ;
		else solve(0,digits,ans,"",symbol) ;
		return ans ;
    }
    
    void solve( int step, string digits, vector<string> & ans, string temp, map<char,string> symbol ) {
    	if ( step >= digits.size() ) {
    		ans.push_back(temp) ;
    		return ;
		} // if
		
		for( int i = 0 ; i < symbol[digits[step]].size() ; i++ ) {
			temp += symbol[digits[step]][i] ;
			solve(step+1,digits,ans,temp,symbol) ;
			temp.pop_back() ;
		} // for

	} // solve
};

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
    	map<char,string> symbol = {{'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}} ;
        vector<string> ans{""};
        for ( char c : digits ) {
            vector<string> t;
            string str = symbol[c];
            for (int j = 0; j < str.size(); ++j) {
                for (string s : ans) t.push_back(s + str[j]);
            }
            ans = t;
        }
        return ans;
    }
};




int main() {
	string ss = "23" ;
	Solution s1 ;
	vector<string> ans = s1.letterCombinations(ss) ;

	for( int i = 0 ; i < ans.size() ; i++ ) {
		cout << ans[i] << endl ;
	} // for
	
	cout << ",done!" << endl ;

} // main

