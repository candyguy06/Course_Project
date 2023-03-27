# include<string>
# include<iostream>
# include<vector>
using namespace std ;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
    	string temp = "" ;
    	vector<string> ans ;
    	solve(n,0,0,temp,ans) ;
    	return ans ;
    }
    
    void solve( int n, int left, int right, string temp, vector<string> & ans ) {
    	if ( temp.size() == n*2 ) {
			ans.push_back(temp) ;
			return ;
		} // if
		
		else {
			if( left < n ) solve(n,left+1,right,temp+'(',ans) ;
			if( right < left ) solve(n,left,right+1,temp+')',ans) ;
		}				
		
	} // solve
};

class Solution2 {
public:
    vector<string> generateParenthesis(int n) {
    	string temp = "" ;
    	vector<string> ans ;
    	solve(n,0,0,temp,ans) ;
    	return ans ;
    }
    
    void solve( int n, int left, int right, string temp, vector<string> & ans ) {
    	if ( left == n ) {
    		while( right < n ) {
    			temp += ')' ;
    			right++ ;
			} // while
			ans.push_back(temp) ;
			return ;
		}	// if
		
		solve(n,left+1,right,temp+'(',ans) ;
		
		if( right < left ) solve(n,left,right+1,temp+')',ans) ;		
		
	} // solve
};

int main() {
	int n = 4 ;
	Solution2 s1 ;
	vector<string> ans = s1.generateParenthesis(n) ;
	for( int i = 0 ; i < ans.size() ; i++ ) {
		cout << ans[i] << endl ;
	} // for
	cout << "done!" ;
	
} // main

