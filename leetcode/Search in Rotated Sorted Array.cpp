# include<iostream>
# include<vector>
using namespace std ;
/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-104 <= target <= 104



***
0　　1　　2　　 4　　5　　6　　7

7　　0　　1　　 2　　4　　5　　6

6　　7　　0　　 1　　2　　4　　5

5　　6　　7　　 0　　1　　2　　4

4　　5　　6　　7　　0　　1　　2

2　　4　　5　　6　　7　　0　　1

1　　2　　4　　5　　6　　7　　0

start = 頭 ,mid = 中間,end = 尾 
end > mid -> 後半有序(旋轉點在前半)
	如果 end > target > mid -> 如果存在確定在後半
	反之去前半找找看  
end < mid -> 前半有序(旋轉點在後半)
	如果 start < target < mid -> 如果存在確定在前半
	反之去後半找找看 
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
    	int start = 0 , end = nums.size() - 1 ;
    	if( nums[start] == target ) return start ;
    	if( nums[end] == target ) return end ;    	
    	while( start+1 < end ) {
			int mid = start + ( end - start ) / 2 ;
			if( nums[mid] == target ) return mid ;
			if( nums[end] > nums[mid] ) { // 後半有序
				if( nums[end] > target && target > nums[mid] ) { // 在後半中 
					start = mid ;
				} // if
				else{ // 去前半看看
					end = mid ; 
				}			 
			} // if
			else { // 前半有序 
				if( nums[start] < target && target < nums[mid] ) { //在前半中 
					end = mid ;
				} // if
				else { // 去後半找找看 
					start = mid ;
				} // else
				
			} // else 
		} // while

    	if( nums[start] == target ) return start ;
    	else if( nums[end] == target ) return end ;    	
        else return -1 ;
    }
};

int main() {
	vector<int> nums = {7,8,0,1,2,3} ;
	Solution s1 ;
	int ans = s1.search(nums,2) ;
	cout << ans << "done!" ;	
} 
 
