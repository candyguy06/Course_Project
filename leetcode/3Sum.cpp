# include<string>
# include<vector>
# include<iostream>
using namespace std ;

/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
 

Constraints:

3 <= nums.length <= 3000
-105 <= nums[i] <= 105

*
先排序(小<->大) 
從頭開始當基底i
基底下一個(i+1)是j nums.size()-1是k
和大於0 k往左走一格
和小於0 j往右走一格
等於0 加入答案 j往右,k往左 走到值與答案不同為止 
直到 j !< k

***while不行 for可以? 

*/


class Solution {
public:	
    vector<vector<int>> threeSum(vector<int>& nums) {   			    	
    	for( int i = 0 ; i < nums.size()-1 ; i++ ) {
    		for( int j = i+1 ; j < nums.size() ; j++ ) {
    			if ( nums[i] > nums[j] ) swap(nums[i],nums[j]) ;	
			} // for
		} //for		
		vector<vector<int>> ans ;
		int tail = nums.size() ;
		for( int i = 0 ; i < tail - 1 ; i++ ) {
//			while ( i < tail - 2 && nums[i] == nums[i-1] ) i++ ;  // runtime error ?
            if((i > 0) && nums[i]==nums[i-1])
            	continue;

			int j = i+1 ;
			int k = tail - 1 ;
			while ( j < k ) {
				int sum = nums[i] + nums[j] + nums[k] ;
				if ( sum == 0 ) {
					ans.push_back( { nums[i],nums[j],nums[k] } ) ;
					while ( j < k && nums[j] == nums[j+1] ) j++ ;
					j++ ;
					while ( j < k && nums[k] == nums[k-1] ) k-- ;
					k-- ;
				} // if
				
				else if ( sum < 0 ) {
					j++ ;
				} // else if

				else if ( sum > 0 ) {
					k-- ;
				} // else if				
				
			} // while
			
			
		} // while
				
		
		return ans ;
        
    }
};

class Solution2 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
    	vector<vector<int>> res;

    	for( int i = 0 ; i < nums.size()-1 ; i++ ) {
    		for( int j = i+1 ; j < nums.size() ; j++ ) {
    			if ( nums[i] > nums[j] ) swap(nums[i],nums[j]) ;	
			} // for
		} //for
    
       for(int i = 0; i < nums.size();i++) {

            if((i > 0) && nums[i]==nums[i-1])
            	continue;
        
        	int l = i + 1; 
        	int r = nums.size() - 1; 
        
        	while (l < r) {
            
            	int sum = nums[i] + nums[l] + nums[r];
            
            	if(sum < 0)	l++;
            	else if(sum > 0) r--;
            	else if(sum == 0) {
                	res.push_back(vector<int>{nums[i],nums[l],nums[r]});
            
                	while (l<r && nums[l] == nums[l+1]) l++;

                	while (l<r && nums[r] == nums[r-1]) r--;
                	l++;
                	r--;
             } // else if 
           } // whiile
        } // for
        
        return res;        
    }
};

int main() {
	vector<int> nums = {-1,0,1,2,-1,-4};
	Solution s1 ;
	vector<vector<int>> ans = s1.threeSum(nums) ;

	for(int i = 0; i < ans.size() ; i++ ) {
		cout << ans[i][0] << "," << ans[i][1] << "," << ans[i][2]  << endl ;
	} // for

	cout << "done!";
	
} // main

