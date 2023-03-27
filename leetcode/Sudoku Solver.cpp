# include<iostream>
# include<vector>
using namespace std ;
/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> row(9,(vector<bool>(10,false))),col(9,(vector<bool>(10,false))),block(9,(vector<bool>(10,false)))  ;
        int i = 0, j = 0 ;
        while( i < 9 ) {
        	int temp = i/3*3 ;
        	j = 0 ;
        	while( j < 9 ) {
        		int temp2 = j / 3 ;
        		if( board[i][j] == '.' ) {
        			j++ ;
        			continue ;
				} // if
        		int c = board[i][j] - '0' ;
        		if( row[i][c] == true || col[j][c] == true || block[temp+temp2][c] == true ) return ;
        		else {
        			row[i][c] = true ;
        			col[j][c] = true ; 
					block[temp+temp2][c] = true ;       			
				} // else
        		j++ ;
			} // while
			i++ ;
		} // while
		
		if (fill(board,0,0,row,col,block)) cout << "T" << endl ;
		else cout << "F" << endl ; 
		return ;       
    }
    
    bool fill( vector<vector<char>>& board, int i , int j, vector<vector<bool>> row,vector<vector<bool>> col, vector<vector<bool>> block ) {
    	if( i == 9 ) return true ;
    	int nj = (j+1) % 9 ;
		int ni  = ( nj == 0 ) ? i+1 : i ;
		if( board[i][j] != '.' ) return fill(board,ni,nj,row,col,block) ;
		for( int k = 1 ; k <= 9 ; k++ ) {
			if( row[i][k] || col[j][k] || block[i/3*3+j/3][k] ) continue ;
			board[i][j] = k + '0' ;
			row[i][k] = true ;
			col[j][k] = true ;
			block[i/3*3+j/3][k] = true ;
			if( fill(board,ni,nj,row,col,block) ) return true ;
			board[i][j] = '.' ;			
			row[i][k] = false ;
			col[j][k] = false ;
			block[i/3*3+j/3][k] = false ;
		} // for
		
		return false ;	
		  
	} // fill
    
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
	s1.solveSudoku(board) ;
	for(int i = 0 ; i < board.size() ; i++ ) {
		for( int j = 0 ; j < board[i].size() ; j++ ) {
			cout << board[i][j] << "," ;
		} // for
		cout << endl ;
	} //for
	
} // main()

