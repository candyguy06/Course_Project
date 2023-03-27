# include<iostream>
# include<vector>
using namespace std ;
/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 

Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105

***
iterator : 從左右往中間找
左,右最大值中 動小的那邊 
動的過程中遇到較小的時後 把差值加到累積雨量中
動的過程中遇到較小的時後 更新為最大值 -> 再比較左右大小 由小的往中間移動 
DP : 一個dp先記錄左邊最大值
再從尾往頭更新右邊最大值 過程中遇到 height[i] 小於 dp[i] 的 將差值加入累計雨量 
*/

class Solution {
public:
    int trap(vector<int>& height) {
    	int l = 0 , r = height.size() - 1 ;
    	int max1 = height[l] , max2 = height[r] ;
    	int output = 0 ;
    	while( l < r ) {
    		if( max1 <= max2 ) {
				while( max1 <= max2 && l < r ) {
					l++ ;
					if( max1 < height[l] ) {
						max1 = height[l] ;
						break ;
					} // if
					output = output + max1 - height[l] ;
				} // while
			} // if
			
			else if( max1 > max2 ){
				while( max1 > max2 && l < r ) {
					r-- ;
					if( max2 < height[r] ) {
						max2 = height[r] ;
						break ;
					} // if
					output = output + max2 - height[r] ;
				} // while				
			} // else
			
			else break ;
						
		} // while
		
		return output ;        
    }
};

class Solution2 {
public:
    int trap(vector<int>& height) {
        int output = 0, temp = 0, n = height.size() ;
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            dp[i] = temp;
            temp = temp > height[i] ? temp : height[i] ; // max()
        }
        mx = 0;
        for (int i = n - 1; i >= 0; --i) {
			dp[i] = dp[i] < temp ? dp[i] : temp ; // min()
			temp = temp > height[i] ? temp : height[i] ; // max()
            if (dp[i] > height[i]) output += dp[i] - height[i]; 
        }
        return output;
    }
};

int main() {
	vector<int> height{4,2,0,3,2,5} ;
	Solution s1 ;
	int ans = s1.trap(height) ;
	cout << ans << ",done!" ;
}

