#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
Given a string s, find the length of the longest substring without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
*/ 

class Solution { // my 
public:
    int lengthOfLongestSubstring(string s) {
    	int num = 0,output = 0 ; //  num ��U���� output �̤j���� 
    	string reg = "" ; // �X�{�L�r����(�Ȧs) 
    	if ( s.size() < 1 ) return 0 ; // �Ŧr�� �^��0 
    	for( int i = 0 ; i < s.size() ; i++ ) {  
			reg += s[i] ;
			num = 1 ;
			for ( int j = i+1 ; j < s.size() ; j++ ) {
				if ( reg.find(s[j]) >= 0 && reg.find(s[j]) < reg.size() ) { // find��Ʀ^�Ǧr���b�Ӧr�ꪺ"��m"  �ҥH�^�ǭȤ���r��d�򤺪�ܦ���� �S���h�^�ǶýX 
					// find
					break ;
				} // if
				
				else {
					// not find
					reg += s[j] ;
					num++ ;
				}
			} // for
			
			reg.clear() ;
			
			if ( num > output ) output = num ;

		} // for
		
        
        return output ;
    }
};

class Solution2 { // �����d�O�_�X�{�L 
public:
    int lengthOfLongestSubstring(string s) {
        int ascii[256];
        int ans=0;
        for(int i=0;i<s.length();i++)
        {
            int len=1;
            memset(ascii, 0, sizeof(ascii));
            ascii[int(s[i])]=1;
            for(int j=i+1;j<s.length();j++)
            {
                if(ascii[int(s[j])])
                {
                    if(len>ans)
                        ans=len;
                    break;
                }
                ascii[int(s[j])]=1;
                len++;
                if(j==s.length()-1&&len>ans)
                    ans=len;
            }
        }
        if(ans==0)
            ans=s.length();
        return ans;
    }
};

int main() {
	string input = "pwwkew" ;
//	if (!input.find('a')) cout << "find" ; 
	
	Solution s ;
	int len = s.lengthOfLongestSubstring(input) ;
	cout << len ;
}



