# include<iostream>
# include<vector>
using namespace std ;
/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the 
frequency
 of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []
 

Constraints:

1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
*/

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    	vector<vector<int>> output ;
		vector<int> temp ;
		int i = 0 ;
		solve(candidates,target,i,temp,output) ;
		return output ;
        
    }
    
    void solve(vector<int> & candidates, int target, int i, vector<int> temp, vector<vector<int>> & output) {
    	if( target < 0 ) return ;
    	if( target == 0 ) {
    		output.push_back(temp) ;
    		return ;
		} // if
		for( int j = i ; j < candidates.size() ; j++ ) {
			temp.push_back(candidates[j]) ;
			solve(candidates,target-candidates[j],j,temp,output) ;
			temp.pop_back() ;
		} // for
		
		return ;    	
	} // solve
};

class Solution2 {
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
		// dp vector to store all possible combinations that achieves sum
        // like dp[2] stores all combination that achieves sum 2 by using given candidates.
       // Similarly dp[target] stores all possible combinations that achieves sum target. That is our ans.
        vector <vector <vector <int>>> dp(target+1);
        // there is no possible combination to achieve sum 0, so we strore empty vector in dp[0]
        dp[0]={{}};
        for(int i:nums)
        {
		// Iterating through all the elements from array nums aka candidates
            for(int j=i;j<=target;j++)
            {
			// Finding all possible ways to achieve sum j from element i
                for(auto v:dp[j-i])
                {
                    v.push_back(i);
                    dp[j].push_back(v);
                }
            }
        }
		// Finally, returning our ans ??
        return dp[target];
    }
};


int main() {
	vector<int> candidates = {2,3,5,7} ;
	int target = 10 ;
	Solution s1 ;
	vector<vector<int>> ans = s1.combinationSum(candidates,target) ;
	for(int i = 0 ; i < ans.size() ; i++ ) {
		for(int j = 0 ; j < ans[i].size() ; j++ ) {
			cout << ans[i][j] << "," ;
		}
		cout << endl ;
	}
	
	cout << "done!" ;
	
}
 
