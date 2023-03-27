# include<iostream>
using namespace std ;
/*
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
Example 2:


Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
 

Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000
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
	bool enough(ListNode* head,int k)	{
		int count = 0;
		while (head) {
			count++;
			head = head->next;
			if( count == k ) break ;
		} // while
		
		if( head != NULL || count == k ) return 1 ; //count == k ­è¦n°÷ 
		else return 0 ;
	}
	ListNode* reverseKGroup(ListNode *head, int k)  {
		if ( !enough(head,k) ) return head;
		ListNode *prev = NULL;
		ListNode *curr = head;
		ListNode *forward = NULL;
    	int count = 0;
    	while (count != k && curr != NULL) {
 	        forward = curr->next;
    	    curr->next = prev;
        	prev = curr;
        	curr = forward;
        	count++;
    	} // while
	    head->next = reverseKGroup(forward, k);
    	return prev;
	}
};
	
	
int main() {
	ListNode* list = new ListNode(1) ;
	list->next = new ListNode(2) ;
	list->next->next = new ListNode(3) ;
	list->next->next->next = new ListNode(4) ;
	list->next->next->next->next = new ListNode(5) ;
	Solution s1 ;
	ListNode* ans = s1.reverseKGroup(list,2) ;
	while( ans ) {
		cout << ans->val << "->" ;
		ans = ans->next ;
	} // while
	cout << endl << "done!" ;
} 
