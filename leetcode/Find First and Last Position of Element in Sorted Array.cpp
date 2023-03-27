# include<iostream>
# include<vector>
using namespace std ;
/*
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109
*/
 
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1 ;
        int r1 = -1 ,r2 = -1 ;
        while( start <= end ) {
            int mid = start + ( end - start ) / 2 ;

            if( nums[mid] == target ) {
                r1 = mid ;
                end = mid-1 ;
            } // if

            else if( target > nums[mid] ) start = mid + 1 ;
            else end = mid - 1 ;
        } // while

        if( r1 == -1 ) return {-1,-1} ;
        start = 0, end = nums.size() - 1 ;
        while( start <= end ) {
            int mid = start + ( end - start ) / 2 ;

            if( nums[mid] == target ) {
                r2 = mid ;
                start = mid+1 ;
            } // if

            else if( target > nums[mid] ) start = mid + 1 ;
            else end = mid - 1 ;
        } // while

        return {r1,r2} ;          
    }
};

int main() {
	vector<int> nums = {1,1,2,2,3,3,4,4,5,5} ;
	Solution s1 ;
	vector<int> ans = s1.searchRange(nums,4) ;
	cout << ans[0] << ","  << ans[1] << ",done!" ;	
} //
