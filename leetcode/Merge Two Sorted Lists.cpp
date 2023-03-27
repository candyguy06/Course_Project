# include<iostream>
using namespace std ;

/*
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

 

Example 1:


Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Example 2:

Input: list1 = [], list2 = []
Output: []
Example 3:

Input: list1 = [], list2 = [0]
Output: [0]
 

Constraints:

The number of nodes in both lists is in the range [0, 50].
-100 <= Node.val <= 100
Both list1 and list2 are sorted in non-decreasing order.
*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    	if( list1 == NULL ) return list2 ;
    	if( list2 == NULL ) return list1 ;
    	
    	ListNode* head = NULL ;
    	ListNode* temp = NULL ;
    	if ( list1->val < list2->val ) {
    		head = list1 ;
    		temp = list1 ;
    		list1 = list1->next ;
		} // if 
    	else {
    		head = list2 ;
    		temp = list2 ;
    		list2 = list2->next ;
		} // else 
    	while( list1 != NULL && list2 != NULL ) {
    		if( list1->val < list2->val ) {
    			temp->next = list1 ;
    			temp = temp->next ;
				list1 = list1->next ; 
			} // else if
			
			else {
    			temp->next = list2 ;
    			temp = temp->next ;
				list2 = list2->next ; 				
			} // else
		} // while
        
        while ( list1 != NULL ) {
    		temp->next = list1 ;
    		temp = temp->next ;
			list1 = list1->next ; 
        } // while

        while ( list2 != NULL ) {
    		temp->next = list2 ;
    		temp = temp->next ;
			list2 = list2->next ; 
        } // while

        return head ;
    	
    }
};

class Solution2 {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

		if(l1 == NULL) return l2

		if(l2 == NULL) return l1

		if(l1 -> val <= l2 -> val) {
			l1 -> next = mergeTwoLists(l1 -> next, l2);
			return l1;
		} // if

		else {
			l2 -> next = mergeTwoLists(l1, l2 -> next);
			return l2;            
		} // else
	}
};


int main() {
	ListNode* list1 = new ListNode(1) ;
	list1->next = new ListNode(2) ;
	list1->next->next = new ListNode(4) ;	
	ListNode* list2 = new ListNode(1) ;
	list2->next = new ListNode(3) ;
	list2->next->next = new ListNode(4) ;
	Solution s1 ;
	ListNode* head = s1.mergeTwoLists(list1,list2) ;
	while( head != NULL ) {
		cout << head->val << "<-" ;
		head = head->next ;
	} //while
	
	cout << endl << "done!" ;
} // main

