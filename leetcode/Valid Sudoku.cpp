# include<iostream>
# include<vector>
using namespace std ;
/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
*/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> mp(27,vector<bool>(10,false))  ;
        int i = 0, j = 0 ;
        int t = 3 ;
        while( i < 9 ) {
			t++ ;
        	int t1 = 3 ;
        	int temp = i/3*3 ;
        	j = 0 ;
        	while( j < 9 ) {
        		t1++ ;
        		int temp2 = j / 3 ;
        		if( board[i][j] == '.' ) {
        			j++ ;
        			continue ;
				} // if
        		int c = board[i][j] - '0' ;
        		if( mp[i][c] == true || mp[j+9][c] == true || mp[18+temp+temp2][c] == true ) return false ;
        		else {
        			mp[i][c] = true ;
        			mp[j+9][c] = true ; 
					mp[18+temp+temp2][c] = true ;       			
				} // else
        		j++ ;
			} // while
			i++ ;
		} // while
		
		return true ;
    }
};

int main() {
	vector<vector<char>> board{
	{'5','3','.','.','7','.','.','.','.'},
	{'6','.','.','1','9','5','.','.','.'},
	{'.','9','8','.','.','.','.','6','.'},
	{'8','.','.','.','6','.','.','.','3'},
	{'4','.','.','8','.','3','.','.','1'},
	{'7','.','.','.','2','.','.','.','6'},
	{'.','6','.','.','.','.','2','8','.'},
	{'.','.','.','4','1','9','.','.','5'},
	{'.','.','.','.','8','.','.','7','9'},
	} ;
	Solution s1 ;
	if( s1.isValidSudoku(board) ) cout << endl << "T" ;
	else cout << endl << "F" ;
	
	
} //

