# include<vector>
# include<iostream>

using namespace std ;
/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Example 1:

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
 

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104

**頭尾開始算面積
高的不動低的動 -> 面積才有可能更大
若比當前最大的暫存值更大 則取代
直到頭尾相交 ( i <(=) j ) 
*/
class Solution {
public :
    int maxArea(vector<int>& height) {
    	int i = 0 , j = height.size() - 1, output = 0 ;
    	while ( i < j ) {
			if ( height[i] > height[j] ) { 
				if ( ( height[j] * (j-i) ) > output ) output = height[j] * (j-i) ;
				j-- ;  
			} // if 
			
			else {
				if ( ( height[i] * (j-i) ) > output ) output = height[i] * (j-i) ;
				i++ ;  				
			} // else
		} // while
        return output ;
    }
} ;

class Solution2 {
public:
    int maxArea(vector<int>& height) {
        int ans = 0, i=0, j=height.size()-1;
        
        while(i<j)
        {
            int x = min(height[i], height[j])*(j-i);
            ans = max(ans, x);
            if(height[i]<height[j])
            i++;
            else 
            j--;
        }
        return ans;
    }
};

int main() {
	vector<int> height = {1,8,6,2,5,4,8,3,7} ;
	Solution s1 ;
	cout << s1.maxArea(height) << ",done!" << endl ;
	
} // main
