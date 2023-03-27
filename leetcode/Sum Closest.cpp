# include<iostream>
# include<string>
# include<vector>
using namespace std ;

/*
Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).
 

Constraints:

3 <= nums.length <= 500
-1000 <= nums[i] <= 1000
-104 <= target <= 104

*
先排序(小<->大) 
從頭開始當基底i
基底下一個(i+1)是j nums.size()-1是k
和大於target k往左走一格
和小於target j往右走一格
每次更新最短距離 
直到 j !< k


**********for可以 while不行??? 
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
    	for(int i = 0 ; i < nums.size() ; i++ ) {
    		for( int j = i+1; j < nums.size() ; j++ ) {
				if (nums[i]>nums[j]) swap(nums[i],nums[j])	;
			} // for
		} //for
		
        int ans = 0, temp = 10000 ;
		int tail = nums.size() ;
		for(int i = 0 ; i < tail - 2 ; i++ ) {
			j = i+1 ;
			k = tail - 1 ;
			while ( j < k ) {
				if(nums[i]+nums[j]+nums[k] == target ) return target ;
								
				else if ( abs( nums[i]+nums[j]+nums[k]-target ) < temp ) {
					ans = nums[i]+nums[j]+nums[k] ;
					temp = abs( nums[i]+nums[j]+nums[k]-target ) ;
				} // else if  
				
				if( nums[i]+nums[j]+nums[k] > target ) {
					k-- ;
				} // if
				
				else if ( nums[i]+nums[j]+nums[k] < target ) {
					j++ ;
				} // else if
			} // while

		} // while
		
		return ans ;
        
    }
};

class Solution2 {
public:
    int threeSumClosest(vector<int>& nums, int target) {
    	for(int i = 0 ; i < nums.size() ; i++ ) {
    		for( int j = i+1; j < nums.size() ; j++ ) {
				if (nums[i]>nums[j]) swap(nums[i],nums[j])	;
			} // for
		} //for
		
        int diff = INT_MAX;
        int ans = 0;
        for(int i=0;i<nums.size();i++)
        {
            int first = nums[i];  //first element
            int start = i+1;
            int end  = nums.size()-1;
            while(start < end){
                if(first + nums[start] + nums[end] == target) return target;
                else if(abs(first + nums[start]+nums[end] - target) < diff)
                {
                    diff = abs(first + nums[start]+nums[end] - target);
                    ans = first + nums[start]+nums[end];
                }
                
                if(first + nums[start] + nums[end] > target)
                {
                    end--;
                }
                else{
                    start++;
                }
            }
        }
        return ans;
    }
};



int main() {
	vector<int> nums = { -1,2,1,-4 } ;
	int target = 1 ; 
	Solution s1 ;
	cout << s1.threeSumClosest(nums,target) << ",done" << endl ;
	
} // main

