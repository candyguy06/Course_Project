# include<iostream>
# include<vector>
# include<algorithm>
using namespace std ;
/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Example 2:


Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 

Constraints:

n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
*/

/*
90度轉動 : i,j <- n-1-j,i <- n-1-i,n-1-j <- j,n-1-i <- i,j
1  2  3               7  2  1            7  4  1

4  5  6      -->      4  5  6　　 -->  　 8  5  2　　

7  8  9               9  8  3　　　　   　 9  6  3
*/ 
 
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
    	int n = matrix.size() ;
    	for( int i = 0 ; i < n ; i++ ) {
    		for( int j = i ; j < n-1-i ; j++ ) {
    			int temp = matrix[i][j] ;
    			matrix[i][j] = matrix[n-1-j][i] ;
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = temp;
			} // for
		} // for
		
        
    }
};

/*
對角線翻轉 再以x軸翻值轉 
1  2  3　　　 　　 9  6  3　　　　　     7  4  1

4  5  6　　-->　　 8  5  2　　 -->   　 8  5  2　　

7  8  9 　　　 　　7  4  1　　　　　     9  6  3
*/ 
class Solution2 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i; ++j) {
                swap(matrix[i][j], matrix[n - 1- j][n - 1 - i]);
            }
        }
        reverse(matrix.begin(), matrix.end());
    }
};
/*
x,y軸翻轉 再以y軸翻轉
1  2  3　　　 　　 1  4  7　　　　　     7  4  1

4  5  6　　-->　　 2  5  8　　 -->  　  8  5  2　　

7  8  9 　　　 　　3  6  9　　　　       9  6  3 
*/ 

class Solution3 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

int main() {
	vector<vector<int>> matrix ;
	matrix.push_back({1,2,3}) ;
	matrix.push_back({4,5,6}) ;
	matrix.push_back({7,8,9}) ;
	Solution s1 ;
	s1.rotate(matrix) ;
	for( int j = 0 ; j < matrix[0].size() ; j++ ) {
		for(int i = 0 ; i < matrix.size() ; i++ ) {
			cout << matrix[j][i] << ',' ;
		}
		cout << endl ;
	}
	
}

