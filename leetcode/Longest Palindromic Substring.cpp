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
���D��� : 
�r��q�Y�����^��l�r��
�C�Ӧr������X�̥���P�̥k�䪺��m 
�̥����k �̥k���� �̧Ǥ��r��
���줣�ۦP�Ϊ̥��

���ۦP : ���O�^��r�� 
�N�̥k�䪺�ȧ令�ĤG�k�䪺�ۦP�r��
�Ȩ�̥��P�̥k��m�ۦP�ɵ���

��� : �O�^��r��
���output �Y�����h���Noutput 

 
���ư����J�r�굲��

*** size_t �u��O���� �۴� < 0 �� ���쬰�j��
 
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
