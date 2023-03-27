# include<iostream>
# include<vector>
using namespace std ;
/*
You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].

Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at nums[i], you can jump to any nums[i + j] where:

0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n - 1].

***
每一步更新可跳最遠距離 
到極限距離時 更新當下最遠距離為極限 

*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size() , jumps = 0;
        int currEnd = 0;
        int currFarthest = 0;
        // [2,3,1,1,4]
        for (int i = 0; i < n - 1; i++) {
            currFarthest = currFarthest > i + nums[i] ? currFarthest : i + nums[i] ;
            if (i == currEnd) {
                jumps++;
                currEnd = currFarthest;
            }
        }

        return jumps;
    }
};

int main() {
	vector<int> nums = {2,3,1,1,4} ;
	Solution s1 ;
	int ans = s1.jump(nums) ;
	cout << ans << "done!" ;
	
}

// [4,1,1,3,1,1,1]
// [5,9,3,2,1,0,2,3,3,1,0,0]
