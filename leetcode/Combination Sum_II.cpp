# include<iostream>
# include<vector>
# include<algorithm>
using namespace std ;

/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
 

Constraints:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
*/

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end()) ;
        int i = 0 ;
        vector<int> temp ;
        vector<vector<int>> output ;
        solve(candidates,target,i,temp,output) ;
        return output ;
    }
    
    void solve(vector<int>& candidates, int target, int i, vector<int> temp, vector<vector<int>> & output ) {
    	if( target < 0 ) return ;
    	if( target == 0 ) {
    		output.push_back(temp) ;
    		return ;
		}

		for( int j = i ; j < candidates.size() ; ) {
			temp.push_back(candidates[j]) ;
			solve(candidates,target-candidates[j],j+1,temp,output) ;
			temp.pop_back() ;
            j++ ;
			while( j < candidates.size() && candidates[j] == candidates[j-1] ) j++ ;
		} // for
    	return ;
	}
};

int main() {
	vector<int> candidates = {1,3,5,2,3,5,7} ;
	int target = 10 ;
	Solution s1 ;
	vector<vector<int>> ans = s1.combinationSum2(candidates,target) ;
	for(int i = 0 ; i < ans.size() ; i++ ) {
		for(int j = 0 ; j < ans[i].size() ; j++ ) {
			cout << ans[i][j] << "," ;
		}
		cout << endl ;
	}
	
	cout << "done!" ;

	
}

