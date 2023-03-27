# include<iostream>
# include<vector>
# include<string>
using namespace std ;
/*
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

 

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
 

Constraints:

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109

***
*1 + 3sum*
4個指標 a + b + c + d = target
a 0~nums.size()
b a+1~nums.size()
c b+1 ~ <d
d nums.size() ~ >c
c d為主要運作指標
在a,b固定的情況下 c d 左右移動找解 直到交錯
把所有a b的情況走過時結束 

*/

class Solution { // iter
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
		if ( nums.size() < 4 ) return {} ;
		vector<vector<int>> ans ;
    	for( int i = 0 ; i < nums.size()-1 ; i++ ) {
    		for( int j = i+1 ; j < nums.size() ; j++ ) {
    			if ( nums[i] > nums[j] ) swap(nums[i],nums[j]) ;	
			} // for
		} //for
		
		for( int i = 0 ; i < nums.size() ; ) {
			long sum = nums[i] ;
			for ( int j = i+1 ; j < nums.size() ; ) {
				long sum2 = sum + nums[j] ;
				int k = j+1, l = nums.size() - 1 ;
				while ( k < l ) {
					if( sum2 + nums[k] + nums[l] == target ) {
						ans.push_back( {nums[i],nums[j],nums[k],nums[l]} ) ;
						k++ ;
						while ( k < l && nums[k] == nums[k-1] ) k++ ;
						l-- ;
						while ( k < l && nums[l] == nums[l+1] ) l-- ;
					} // if
					
					else if ( sum2 + nums[k] + nums[l] > target ) l-- ;
					
					else if ( sum2 + nums[k] + nums[l] < target ) k++ ;		
					
				} // while
				
				j++ ;
				while( j < nums.size() && nums[j] == nums[j-1] ) j++ ;
				
			} // for
;
			i++ ;
			while( i < nums.size() && nums[i] == nums[i-1] ) i++ ;
			
		} // for
        
        return ans ;
    }
};

class Solution2 { // recursion -> TLE
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
    	if ( nums.size() < 4 ) return {} ;
    	vector<vector<int>> ans ;
    	vector<int> temp ; 
    	sort(nums.begin(), nums.end());
        solve( 0,0,0,target,nums,ans,temp) ;
        return ans ;
    }
    
    void solve( int step, int loop_i , int sum, int target, vector<int>& nums,vector<vector<int>> & ans, vector<int> temp ) {
    	if ( step == 4 ) {
    		if ( target == sum )  ans.push_back(temp) ;
    		return ;
		} // if
		
		for( int i = loop_i ; i < nums.size() ; ) {
			temp.push_back(nums[i]) ;
			solve(step+1,i+1,sum+nums[i],target,nums,ans,temp) ;
			temp.pop_back() ;
            i++ ;
            while( i < nums.size() && nums[i] == nums[i-1] ) i++ ;
		} // for
    	
	} // solve
};

int main() {
	vector<int>	nums = {1,0,-1,0,-2,2} ;
	int target = 0 ;
	Solution s1 ;
	 vector<vector<int>> ans = s1.fourSum(nums,target) ;
	for(int i = 0 ; i < ans.size() ; i++ ) {
		for(int j = 0 ; j < ans[i].size() ; j++ ) cout << ans[i][j] << " " ;
		cout << endl ;
	}	// for
	
	cout << "done!" ;
	
} //

