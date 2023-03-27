# include<iostream>
using namespace std ;

/*
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 

Example 1:


Input: head = [1,2,3,4]
Output: [2,1,4,3]
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [1]
Output: [1]
 

Constraints:

The number of nodes in the list is in the range [0, 100].
0 <= Node.val <= 100
 
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
    ListNode* swapPairs(ListNode* head) {
    	if( head == NULL || head->next == NULL ) return head ;
    	ListNode* ans = new ListNode(0) ;
    	ListNode* pre =  ans ;
    	for( ListNode* temp = head ; temp != NULL ; temp = temp->next) {
    		if( temp->next == NULL ) break ;
			ListNode* temp2 = temp->next ;
			temp->next = temp2->next ;
			temp2->next = temp;
			pre->next = temp2 ;
			pre = pre->next->next ;
			cout << temp->val << "," << temp2->val << endl ;
		} // for
		
		return ans->next ;
        
    }
};

class Solution2 {
public:
    ListNode* swapPairs(ListNode* head) {
    	if( head == NULL || head->next == NULL ) return head ;
    	ListNode* temp = head->next ;  
    	ListNode* temp2 =  temp->next ;
    	head->next = swapPairs(temp2) ;
    	temp->next = head ;
    			
		return temp ;
        
    }
};

int main() {
	ListNode* list = new ListNode(1) ;
	list->next = new ListNode(2) ;
	list->next->next = new ListNode(3) ;
	list->next->next->next = new ListNode(4) ;
	list->next->next->next->next = new ListNode(5) ;
	Solution s1 ;
	ListNode* ans = s1.swapPairs(list) ;
	while( ans ) {
		cout << ans->val << "->" ;
		ans = ans->next ;
	} // while
	cout << endl << "done!" ;
} 
