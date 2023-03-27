#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/ 
class Solution { // my
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    	double output = 0 ; // 块い计 
    	if ( nums1.size() < 1 ) { //  计1 钡衡砃2い计肚 
			if ( nums2.size() % 2 == 0 ) {
				output = ( double ( nums2[nums2.size()/2] + nums2[nums2.size() / 2 - 1] ) ) / 2 ;			
			} // if
		
			else {
				output = double ( nums2[nums2.size()/2] ) ;
			} // else
    		return output ;
		} // if
		
    	for ( int i = 0 ; i < nums1.size() ; i++ ) { // 计1础计2 
    		if ( nums2.size() < 1 ) { // 计2 计1 钡 计2 
    			for ( int j = 0 ; j < nums1.size() ; j++ ) {
    				nums2.push_back(nums1[j]) ;
				} // for
				break ;
			} // if
    		for ( int j = 0 ; j < nums2.size() ; j++ ) { // 计1 ㄌ础计2 
    			if ( nums1[i] < nums2[j] ) {
    				nums2.insert(nums2.begin()+j,nums1[i]) ;
    				break ;
				} // if
				
				else if ( j == nums2.size() - 1  ) {
					nums2.push_back(nums1[i]) ;
					break ;
				} // else if
			} // for
		} // for
		
		if ( nums2.size() % 2 == 0 ) { // 璸衡い计 
			output = ( double ( nums2[nums2.size()/2] + nums2[nums2.size() / 2 - 1] ) ) / 2 ;			
		} // if
		
		else {
			output = double ( nums2[nums2.size()/2] ) ;
		} // else
		
		for(int i = 0 ; i < nums2.size() ; i++ ) {
			cout << nums2[i] << endl ;
		}
		return output ;
        
    }
};

class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> v;
        double median = 0;
        v.insert(v.begin(), nums1.begin(), nums1.end());
        v.insert(v.end(), nums2.begin(), nums2.end());
        sort(v.begin(), v.end());
        int l = v.size();
        if(l % 2 != 0)
        {
            median = v[l/2];
        }
        else
        {
            median = (v[l/2] + v[(l/2) - 1])/2.0;
        }
        return median;
    }
};

int main() {
	vector<int> nums1 = {} ; 
	vector<int> nums2 = {1,2,3,4} ;	
	Solution s ;
	double median = s.findMedianSortedArrays(nums1,nums2) ;
	cout << median ;
}
