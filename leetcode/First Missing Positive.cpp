# include<iostream>
# include<vector>
# include<algorithm>
using namespace std ;

/*
Given an unsorted integer array nums, return the smallest missing positive integer.

You must implement an algorithm that runs in O(n) time and uses constant extra space.

 

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
***
hashtable
把n放到nums[n-1] 排好
在從頭檢查到n != nums[n-1] 就知道答案是n 
對的 : nums[nums[i] - 1] != nums[i]
錯的 :  nums[i] - 1 != i -> [1,1] -> 無窮 
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size() ;
        for(int i = 0 ; i < n ; i++ ) {
        	while( nums[i] <= n && nums[i] >  0 && nums[nums[i] - 1] != nums[i] ) {
        		swap(nums[i],nums[nums[i] - 1]) ;
			}
		} // for
		
		for(int i = 0 ; i < n ; i++ ) {
			if(nums[i] != i+1 ) return i+1 ;
		} // for
		
		return n+1 ;
    }
};


int main() {
	vector<int> nums {1,3,3,2} ;
	Solution s1 ;
	int ans = s1.firstMissingPositive(nums) ;
	cout << ans << ",done!" ; 
	
}
