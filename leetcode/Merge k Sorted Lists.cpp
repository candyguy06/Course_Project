# include<vector>
# include<iostream>
# include<queue>
using namespace std ;
/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
 

Constraints:

k == lists.length
0 <= k <= 104
0 <= lists[i].length <= 500
-104 <= lists[i][j] <= 104
lists[i] is sorted in ascending order.
The sum of lists[i].length will not exceed 104.
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
    	if( lists.size() < 1 ) return NULL ;
    	priority_queue<int,vector<int>,greater<int>>pq;
		for( int i = 0 ; i < lists.size() ; i++ ) {
			ListNode* head = lists[i] ;
			while( head != NULL ) {
				pq.push(head->val) ;
				head = head->next ;
			} // while
		}   // for     
		
		ListNode* ans = new ListNode(0) ;
		ListNode* head = ans ;
		while( !pq.empty() ) {
			head->next = new ListNode(pq.top()) ;
            pq.pop() ;
			head = head->next ;
		} // while
		
		return ans->next ;
    }
};

class Solution2 {
public:
    
    ListNode* mergeTwoSorted(ListNode *a, ListNode* b)
    {
        if(a==NULL) return b;
        if(b==NULL) return a;
        
        if(a->val<=b->val){
            a->next = mergeTwoSorted(a->next, b);
            return a;
        }
        else{
            b->next = mergeTwoSorted(a, b->next);
            return b;
        }
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        if(lists.size()==0) return NULL;
        while(lists.size() > 1){
            lists.push_back(mergeTwoSorted(lists[0], lists[1])); 
            lists.erase(lists.begin()); 
            lists.erase(lists.begin());
        }
        return lists[0];
    }
};

class Solution3 {
public:
    class MyCmp{
        public:
            bool operator()(ListNode *l1,ListNode *l2){
                return l1->val>l2->val;
            }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int l=lists.size();
        priority_queue<ListNode*,vector<ListNode*>,MyCmp>pq;
        for(int i=0;i<l;i++){
            if(lists[i]!=NULL){
                pq.push(lists[i]);
            }
        }
        ListNode *head=new ListNode();
        ListNode* curr=head;
        while(!pq.empty()){
            curr->next=pq.top();
            curr=curr->next;
            pq.pop();
            if(curr->next!=NULL){
                pq.push(curr->next);
            }
        }
        return head->next;
        

        
    }
};

int main() {
	ListNode* list = new ListNode(1) ;
	list->next = new ListNode(2) ;
	list->next->next = new ListNode(3) ;
	vector<ListNode*> lists ;
	lists.push_back(list) ;
	lists.push_back(list) ;
	Solution s1 ;
	ListNode* ans = s1.mergeKLists(lists) ;
	while( ans != NULL ) {
		cout << ans->val << "," ;
		ans = ans->next ;
	} // while
	
	cout << endl << "done!" ;
}


