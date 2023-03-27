# include<iostream>
# include<vector>
using namespace std ;
/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]
 

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
*/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
		int n = nums.size() ;
		if( n <= 1 ) return {nums} ;
		vector<bool> vis( n,false ) ;
		vector<vector<int>> output ;
		vector<int> temp ;
		Solve(nums,vis,temp,output) ;   
		return output ;    
    }
    
    void Solve( vector<int>& nums , vector<bool> vis, vector<int> temp, vector<vector<int>> & output ) {
    	if ( temp.size() == nums.size() ) {
    		output.push_back(temp) ;
    		return ;
		} // if
		
		for( int i = 0 ; i < nums.size() ; i++ ) {
			if( vis[i] == true ) continue ;
			vis[i] = true ;
			temp.push_back(nums[i]) ;
			Solve(nums,vis,temp,output) ;
			vis[i] = false ;
			temp.pop_back() ;
		} // for
		
		return ;
	}
};

class Solution2 {
public:
    vector<vector<int>> permute(vector<int>& num) {
        vector<vector<int>> res;
        permuteDFS(num, 0, res);
        return res;
    }
    void permuteDFS(vector<int>& num, int start, vector<vector<int>>& res) {
        if (start >= num.size()) res.push_back(num);
        for (int i = start; i < num.size(); ++i) {
            swap(num[start], num[i]);
            permuteDFS(num, start + 1, res);
            swap(num[start], num[i]);
        }
    }
};


int main() {
	vector<int> nums = {1,2,3} ;
	Solution s1 ;
	vector<vector<int>> ans = s1.permute(nums) ;
	for( int i = 0 ; i < ans.size() ; i++ ) {
		for( int j = 0 ; j < ans[i].size() ; j++ ) cout << ans[i][j] << "," ;
		cout << endl ;
	} // for
	cout << "done!" ;
	
}
 
