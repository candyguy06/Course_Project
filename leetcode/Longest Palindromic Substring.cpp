#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
Given a string s, return the longest palindromic substring in s.

A string is called a palindrome string if the reverse of that string is the same as the original string.

 

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.
*/

/*
解題思維 : 
字串從頭到尾找回文子字串
每個字元先找出最左邊與最右邊的位置 
最左往右 最右往左 依序比對字元
直到不相同或者交錯

不相同 : 不是回文字串 
將最右邊的值改成第二右邊的相同字元
值到最左與最右位置相同時結束

交錯 : 是回文字串
比對output 若較長則取代output 

 
重複做到輸入字串結束

*** size_t 只能是正數 相減 < 0 時 溢位為大值
 
*/

class Solution { // my
public:
	
    string longestPalindrome(string s) {
    	if ( s.size() <= 1 ) return s ; 
    	string output = "" ;
    	size_t first_found = s.find_first_of(s[0]) ; 
    	size_t last_found = s.find_last_of(s[0]) ;  
    	bool brk = false ;
    	for ( int i = 0 ; i < s.size() ; ) {
    		if ( first_found == s.npos ) break ;
			while (last_found != s.npos) {
//				cout << first_found << "," << last_found << endl ; 
				int j = 0 ;
				while ( j <= last_found && first_found + j < s.size() && (first_found + j ) <= ( last_found - j )  ) {
//					cout  << first_found + j << ": "<< s[first_found + j] << ',' << last_found - j << ":" << s[last_found - j] << endl ;
					if ( s[first_found + j] != s[last_found - j] ) {
//						cout << "do" ;
						brk = true ;
						break ;
					} // if		
					j++ ;
				} // while
				
//				cout << first_found << "," << last_found << ',' << j  << ','<< brk << endl ; 
				if ( brk == false  && last_found >= first_found && (last_found - first_found) >= output.size() ) {
					output = s.substr(first_found ,(last_found - first_found)+ 1  ) ;
//					cout << "output change : " << output << endl ;
					break ;
				} // if
				brk = false ;
				last_found = s.find_last_of(s[i],last_found-1) ;
				if ( last_found == first_found ) break ;
			}  // while 

			i++ ;
    		first_found = s.find_first_of(s[i],first_found+1) ;
    		last_found = s.find_last_of(s[i]) ;
			
//			cout << output << endl ;		
    		
		} // for
        
        return output ;
    }
    
};



int main() {
	string s = "zudfweormatjycujjirzjpyrmaxurectxrtqedmmgergwdvjmjtstdhcihacqnothgttgqfywcpgnuvwglvfiuxteopoyizgehkwuvvkqxbnufkcbodlhdmbqyghkojrgokpwdhtdrwmvdegwycecrgjvuexlguayzcammupgeskrvpthrmwqaqsdcgycdupykppiyhwzwcplivjnnvwhqkkxildtyjltklcokcrgqnnwzzeuqioyahqpuskkpbxhvzvqyhlegmoviogzwuiqahiouhnecjwysmtarjjdjqdrkljawzasriouuiqkcwwqsxifbndjmyprdozhwaoibpqrthpcjphgsfbeqrqqoqiqqdicvybzxhklehzzapbvcyleljawowluqgxxwlrymzojshlwkmzwpixgfjljkmwdtjeabgyrpbqyyykmoaqdambpkyyvukalbrzoyoufjqeftniddsfqnilxlplselqatdgjziphvrbokofvuerpsvqmzakbyzxtxvyanvjpfyvyiivqusfrsufjanmfibgrkwtiuoykiavpbqeyfsuteuxxjiyxvlvgmehycdvxdorpepmsinvmyzeqeiikajopqedyopirmhymozernxzaueljjrhcsofwyddkpnvcvzixdjknikyhzmstvbducjcoyoeoaqruuewclzqqqxzpgykrkygxnmlsrjudoaejxkipkgmcoqtxhelvsizgdwdyjwuumazxfstoaxeqqxoqezakdqjwpkrbldpcbbxexquqrznavcrprnydufsidakvrpuzgfisdxreldbqfizngtrilnbqboxwmwienlkmmiuifrvytukcqcpeqdwwucymgvyrektsnfijdcdoawbcwkkjkqwzffnuqituihjaklvthulmcjrhqcyzvekzqlxgddjoir" ;
	Solution s1 ;
	cout << s1.longestPalindrome(s) << "done" ;

}
