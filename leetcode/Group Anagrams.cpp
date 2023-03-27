# include<iostream>
# include<vector>
# include<string>
# include<unordered_map>
# include<algorithm>
using namespace std ;
/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.

*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> output ;
        unordered_map<string,vector<string>> mp ;
        for( int i = 0 ; i < strs.size() ; i++ ) {
        	string s = strs[i] ;
        	sort(s.begin(),s.end()) ;
        	mp[s].push_back(strs[i]) ;
		} // for
		
		for( auto i : mp ) {
			output.push_back(i.second) ;
		} // for
		
		return output ;
    }
};

int main() {
	vector<string> strs = {"bat","eat","ate","tea"} ;
	Solution s1 ;
	vector<vector<string>> ans = s1.groupAnagrams(strs) ;
	for( int i = 0 ; i < ans.size() ; i++ ) {
		for( int j = 0 ; j < ans[i].size() ; j++ ) {
			cout << ans[i][j] << "," ;
		} // for
		cout << endl ;
	} // for
	
	cout << "done!" ;
}


