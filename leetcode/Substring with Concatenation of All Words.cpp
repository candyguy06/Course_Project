# include<iostream>
# include<string>
# include<vector>
# include<unordered_map>
/*
You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated substring in s is a substring that contains all the strings of any permutation of words concatenated.

For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated substring because it is not the concatenation of any permutation of words.
Return the starting indices of all the concatenated substrings in s. You can return the answer in any order.

 

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Since words.length == 2 and words[i].length == 3, the concatenated substring has to be of length 6.
The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
The output order does not matter. Returning [9,0] is fine too.
Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Explanation: Since words.length == 4 and words[i].length == 4, the concatenated substring has to be of length 16.
There is no substring of length 16 is s that is equal to the concatenation of any permutation of words.
We return an empty array.
Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
Explanation: Since words.length == 3 and words[i].length == 3, the concatenated substring has to be of length 9.
The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"] which is a permutation of words.
The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"] which is a permutation of words.
The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"] which is a permutation of words.
 

Constraints:

1 <= s.length <= 104
1 <= words.length <= 5000
1 <= words[i].length <= 30
s and words[i] consist of lowercase English letters.

***
map-紅黑樹 T = O(log(n)) , unordered_map-hashtable T = O(1) 
操作語法一樣
for( auto x : mp ) {
	cout << x.first << "," << x.second << endl ; 
}
*/
using namespace std ;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
		int m = words.size(), n = words[0].size() ;
		int range = s.size() - m*n ;
    	if( s.size() <= 0 || words.size() <=0 || range < 0 ) return {} ;
    	vector<int> ans ;
    	unordered_map<string,int> mp ;
    	for(int i = 0 ; i < words.size() ; i++ ) {
    		mp[words[i]]++ ;
		} // for
		
		for( int i = 0 ; i <= range ; i++ ) {
			unordered_map<string,int> mp2 = mp ;
			int j = 0 ;
			while( j < m ) {
				string temp_s = s.substr(i+j*n,n) ;
				if( mp2[temp_s] == 0 ) break ;
				mp2[temp_s]-- ;
				j++ ;
			} // while
			
			if( j == m ) ans.push_back(i) ;
			
		} // for
		
		return ans ;
        
    }
};

class Solution2 { // TLE
public:
    vector<int> findSubstring(string s, vector<string>& words) {
    	vector<int> ans ;
    	int range = words[0].size() * words.size() ;
    	range = s.size() - range ;
    	for( int i = 0 ; i <= range ; i++ ) {
    		if ( compare_string(s,words,i) ) ans.push_back(i)  ;
		} // for
		
		return ans ;
        
    }
    
    bool compare_string(string s, vector<string> words,int i) {
    	bool find = false ;
    	while( !words.empty() ) {
			for( int j = 0 ; j < words.size() ; j++ ) {
				int k = 0 ;
				int temp_i = i ;
				for( ; k < words[j].size() ; k++ ) {
					if( s[i] != words[j][k] ) {
						i = temp_i ;
						break ;
					} // if
					i++ ;
				} // for
				if( k == words[j].size() ) {
					words.erase(words.begin()+j) ;
					find = true ;
					break ;
				} // if
			} // for
			
			if( !find ) return false ;
			find = false ;
		} // while
		
		return true ;
	}
};

int main() {
	string s = "barfoofoobarthefoobarman" ;
	vector<string> words = {"bar","foo","the"} ;
	Solution s1 ;
	vector<int> ans = s1.findSubstring(s,words) ;
	for( int i = 0 ; i < ans.size() ; i++ ) cout << ans[i] << "," ;
	cout << "done!" << endl ;
		
} // main

/*

"barfoofoobarthefoobarman"
["bar","foo","the"]
	string s = "abaababbaba" ;
	vector<string> words = {"ab","ba","ab","ba"} ;
*/


 
