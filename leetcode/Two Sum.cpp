#include <iostream>
#include <vector>
#include <map>

/*
Question : 
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
 

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

using namespace std;
class Solution1 {
	// my
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> reg,output ;
        if ( nums.size() < 2 ) return output ;
        reg.push_back(nums[0]) ;
        int i = 1, j = 0 ;
        while (i < nums.size() ) {
            while ( j < reg.size() ) {
                if ( (nums[i] + reg[j]) == target ) {
                    output.push_back(j) ;
                    output.push_back(i) ;
                    return output ;
                } // if
                j++ ;
            } // while
            
            reg.push_back(nums[i]) ;
            i++ ;
            j = 0 ;
            
        } // while
                
        return output ; 
        
        
    }
};

class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        map<int,int> dict;
        map<int,int>::iterator iter;
        vector<int> ans;

        for (int i=0; i<nums.size();i++){

            iter = dict.find(target-nums[i]);
            // cout<<iter;
            // printf("(%d,%d)",iter->first,iter->second);
            if (iter != dict.end()){ // num found
                ans.push_back(iter->second); //nums find in dict (smaller)
                ans.push_back(i); // current index (bigger)                
                return ans;     
            }
            else{ //iter == dict.end(), not found
                dict[nums[i]]=i;    
            }
        }
        return ans;
    }
};

class Solution3 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        for(int i=0;i<nums.size()-1;i++)
        {
            for(int j=i+1;j<nums.size();j++)
                if(nums[i]+nums[j]==target) return{i,j};
        }
        return {};
    }
};

int main() {
	Solution1 S ;
	vector<int> input = {0,4,3,0} ;
	vector<int> ans = S.twoSum(input,0) ;
	for ( int i = 0 ; i < ans.size() ; i++ ) {
		cout << ans[i] << endl ;
	} // for
	
} // main()
