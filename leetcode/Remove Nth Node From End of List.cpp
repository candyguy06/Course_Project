# include<iostream>
# include<string>
# include<vector>
using namespace std ;

/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.

 

Example 1:


Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]
 

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz

***
遞迴 : 找到底部回傳遞迴幾層 回傳到target層時 connect and delete
	*剛好在head需在遞迴外處理
迴圈 : 兩個指標一個(front)指向頭 另一個(back)指向頭後n個
	兩個一起往下走(next) 直到back == NULL
 	front的下一個就會是刪除的指定位置 
	 
	 
*/



struct ListNode { // recurtion
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if( head->next == NULL ) return NULL ;
    	int a = findtail(head,head->next,n) ;
        if( a == n ) head = head->next ; 
    	return head ;     
    }
    
    int findtail(ListNode* pre,ListNode* temp,int n) {
    	if( temp == NULL ) return 1 ;
    	
    	else {
    		int a = findtail(temp,temp->next,n) ;
    		if( a == n ) {
    			pre->next = temp->next ;
    			delete temp ;
			} // if
   			return (a+1) ;			
		} // else 
    	
	} //
};

class Solution2 { // iter
public : 
	ListNode* removeNthFromEnd(ListNode* head, int n) {
    
		if(head==NULL) return head;
    
    	ListNode *front=head, *back=head;          
    
    	for(int i=1;i<=n+1;i++){            
        	if(back==NULL) return head->next;  
        	back=back->next;
    	} // for
    
    	while(back!=NULL){                     
        	front=front->next;
        	back=back->next;
    	}
    
    	back = front->next ;
    	front->next=front->next->next;
		delete back ;              
    	return head;
	}
};

int main() {
	ListNode* head = new ListNode(1) ;
	head->next = new ListNode(2) ;  
	int n = 2 ;
	Solution s1 ;
	ListNode* ans = s1.removeNthFromEnd(head,n) ;
	while( ans != NULL ) {
		cout << ans->val << endl ;
		ans = ans->next ;
	} // while
	
} // main()
 
