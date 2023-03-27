#include <iostream>
#include <vector>

/*
Question :
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example :
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Input: l1 = [0], l2 = [0]
Output: [0]

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]


Constraints:
The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.
*/

using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val; // �x�s�� 
	ListNode *next; // �U��point 
	ListNode() : val(0), next(nullptr) {} // �ŧi 
	ListNode(int x) : val(x), next(nullptr) {} // �ŧi 
	ListNode(int x, ListNode *next) : val(x), next(next) {} // �ŧi 
} ;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    	// ��Ȭۥ[ 
        ListNode *l3 = new ListNode(0) ; // �^�ǫ��� 
        ListNode *p = l1, *q = l2, *r = l3 ; // �B�@���� 
        int sum = 0 , carry = 0 ; // �`�M�H�ζi�� 
        while(p!=NULL && q!=NULL) { // l1 l2 �Ҧ��Ȯ� 
            sum = p->val + q->val + carry ;
            carry = sum / 10 ;
            r->next = new ListNode(sum%10) ;
            p = p->next ;
            q = q->next ;
            r = r->next ;
        } // while
        
        while ( p!=NULL || q!=NULL || carry!=0 ) { 
		// l1 l2 �i�� �䤤���@���Ȯ� 
            sum = carry ;
            if ( p != NULL ) {
                sum += p->val ;
                p = p->next ;
            } // if
            else if ( q != NULL ) {
                sum += q->val ;
                q = q->next ;                
            } // else if
            
            carry = sum / 10 ;
            r->next = new ListNode(sum%10) ;
            r=r->next ;
            
        } // while
        
        return l3->next ;
    } // addTwoNumbers

};

int main() {
	ListNode *l1 = new ListNode(7) ;
	ListNode *l2 = new ListNode(9) ;
	Solution S ;
	ListNode * temp = S.addTwoNumbers(l1,l2) ;
	while (temp!=NULL) {
		cout << temp->val ;
		temp = temp->next ;
	} //while
} // main()
