# include<string>
# include<iostream>
/*
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

 

Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 

Constraints:

1 <= haystack.length, needle.length <= 104
haystack and needle consist of only lowercase English characters.
*/

using namespace std ;

class Solution {
public:
    int strStr(string haystack, string needle) {
    	for( int i = 0 ; i < haystack.size() ; ) {
    		if( haystack[i] == needle[0] ) {
    			int temp = i ;
    			int j = 0 ;
    			while( j < needle.size() && i < haystack.size() ) {
    				if( haystack[i] == needle[j] ) {
    					i++ ;
    					j++ ;
					} // if
					else break ;
				} // while
				if( j == needle.size() ) return temp ;
			} // if
			else i++ ;
		} // for
		
		return -1 ;
        
    }
};

class Solution2 {
public:
    int strStr(string haystack, string needle) {
        int n=haystack.size();
        
        int m=needle.size();
        
        int range=n-m+1;
        
        for(int i=0;i<range;i++){
            string ans=haystack.substr(i,m);
            if(ans==needle){
                return i;
            }
            
        }
        return -1;
    }
};

int main() {
	string haystack = "apple" ;
	string needle = "pp" ;
	Solution s1 ;
	int k = s1.strStr(haystack,needle) ;
	cout << k << ",done" << endl ;
} // main()
