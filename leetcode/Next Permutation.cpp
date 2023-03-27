# include<iostream>
# include<vector>
# include<algorithm>
using namespace std ;
/*
A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100

*** 
由尾往頭找 找到nums[i]比nums[i+1]小的時候停止
再回到尾往前找 找到第一個比nums[i]大的位置(j)
把nums[i]和nums[j]交換
再把nums[i](nums[i]不算)後面的陣列頭尾顛倒就是答案 
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
    	int i = nums.size() - 2 ;
    	int j = i+1 ;
    	while( i >= 0 ) {
    		if( nums[i] < nums[i+1] ) {
    			while( j > i ) {
    				if( nums[j] > nums[i] ) {
    					swap(nums[i],nums[j]) ;
    					reverse(nums.begin()+i+1,nums.end()) ;
    					return ;
					} // if
    				j-- ;
				} // while
			} // if
    		i-- ;
		} // while
		
		reverse(nums.begin(),nums.end()) ;
		return ;
        
    }
};

int main() {
	vector<int> nums = {1,2,7,4,3,1} ;
	Solution S1 ;
	S1.nextPermutation(nums) ;
	for( int i = 0 ; i < nums.size() ; i++ ) {
		cout << nums[i] << "," ; 
	}
	
	cout << "Done!" ;
	
} // main

