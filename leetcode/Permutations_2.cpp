# include<iostream>
# include<vector>
# include<algorithm>
using namespace std ;
/*
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

 

Example 1:

Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
Example 2:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

Constraints:

1 <= nums.length <= 8
-10 <= nums[i] <= 10
 
*/

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
    	sort(nums.begin(),nums.end()) ;
        vector<bool> mp(nums.size(),false) ;
        vector<vector<int>> output ;
        vector<int> temp ;
		Solve(nums,mp,output,temp) ; 
		return output ;
    }
    
    void Solve( vector<int> nums , vector<bool> mp, vector<vector<int>> & output, vector<int> temp) {
    	if( temp.size() == nums.size() ) {
    		output.push_back(temp) ;
    		return ;
		} // if
		
		for( int j = 0 ; j < nums.size() ; ) {
			if( mp[j] == true )  {
				j++ ;
				continue ;
			} // if
			temp.push_back(nums[j]) ;
			mp[j] = true ;
			Solve(nums,mp,output,temp) ;
			temp.pop_back() ;
			mp[j] = false ;
			j++ ;
			while( j < nums.size() && nums[j] == nums[j-1] ) j++ ;
		} // for
		
		return ;
    	
	}
};

int main() {
	vector<int> nums = {1,1,2} ;
	Solution s1 ;
	vector<vector<int>> ans = s1.permuteUnique(nums) ;
	for( int i = 0 ; i < ans.size() ; i++ ) {
		for( int j = 0 ; j < ans[i].size() ; j++ ) cout << ans[i][j] << "," ;
		cout << endl ;
	} // for
	cout << "done!" ;
 
	
}
 
