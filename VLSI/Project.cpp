# include <string>
# include <iostream>
# include <vector>
# include <stdio.h>
# include <iomanip>
# include<fstream>
using namespace std ;


struct Node {
  string name ;
  string weight ;
  string edgename ;
  int num ;
  int begin ;
  int end ;
  bool visit ;
} ; // Node()

struct Adjlist {
  string name ;
  vector<Node> path ;
  int begin ;
  int end ;
} ; // Adjlist()

struct Edge {
  string name ;
  string in ;
  string out ;
  string weight ;
} ; // Node()

vector<Adjlist> glist ;
vector<string> gtext ; 
vector<Edge> gedge ;

bool Read( string input ) {
  char ch ;
  string temp = "" ;
  input += ".txt" ;
  fstream file ;
  file.open(input, ios::in) ;
  if ( !file ) return false ;
  else {
  	while ( ch != '\n' ) file.get(ch) ;	
  	while ( file.get(ch) ) {
      if ( ch != '\n' ) {
      	temp += ch ;
	  } // if
	  else {
	  	gtext.push_back(temp) ;
	  	temp = "" ;
	  } // else
	} // while
	
	file.close() ;
  } // else
  
  return true ;



} // Read()

void Getadjlist() {
	Node tempn ;
	tempn.begin = 0 ;
	tempn.end = 0 ;
	tempn.visit = false ;
	tempn.num = 0 ;
	int i = 0 ;
	int j = 0 ;
	while ( i < glist.size() ) {
		while ( j < gedge.size() ) {
			if ( glist[i].name == gedge[j].out ) {
				tempn.name = gedge[j].in ;
				tempn.weight = gedge[j].weight ;
				tempn.edgename = gedge[j].name ;
				if (tempn.name == "S" ) tempn.num = 0 ;
				else if (tempn.name == "V1" ) tempn.num = 1 ;
				else if (tempn.name == "V2" ) tempn.num = 2 ;
				else if (tempn.name == "V3" ) tempn.num = 3 ;
				else if (tempn.name == "V4" ) tempn.num = 4 ;
				else if (tempn.name == "V5" ) tempn.num = 5 ;
				else if (tempn.name == "V6" ) tempn.num = 6 ;
				else if (tempn.name == "V7" ) tempn.num = 7 ;
				else if (tempn.name == "V8" ) tempn.num = 8 ;
				else if (tempn.name == "V9" ) tempn.num = 9 ;
				else if (tempn.name == "V10" ) tempn.num = 10 ;
				else if (tempn.name == "D" ) tempn.num = 11 ;
				glist[i].path.push_back(tempn) ;
			} // if
			
			j++ ;
		} // while
		j = 0 ;
		i++ ;
	} // while
	
	
	for( int a = 0 ; a < glist.size() ; a++ ) { // 由weight排續 
		for ( int b = 0 ; b < glist[a].path.size() ; b++ ) {
//			cout << b << endl ;
			for ( int c = b+1 ; c < glist[a].path.size() ; c++ ) {
//				cout << c << endl ;
				if ( glist[a].path[b].weight > glist[a].path[c].weight ) {
					tempn.name = glist[a].path[b].name ;
					tempn.weight = glist[a].path[b].weight ;
					tempn.edgename = glist[a].path[b].edgename ;
					tempn.num = glist[a].path[b].num ;
					glist[a].path[b].name = glist[a].path[c].name ;
					glist[a].path[b].weight = glist[a].path[c].weight ;
					glist[a].path[b].edgename = glist[a].path[c].edgename ;
					glist[a].path[b].num = glist[a].path[c].num ;
					glist[a].path[c].name = tempn.name ;
					glist[a].path[c].weight = tempn.weight ;
					glist[a].path[c].edgename = tempn.edgename ;
					glist[a].path[c].num = tempn.num ;
				}
			}
		}
	}
	

/*
	for( int a = 0 ; a < glist.size() ; a++ ) {
		cout  << "Node : " << glist[a].name << endl ;
		for ( int b = 0 ; b < glist[a].path.size() ; b++ ) {
			cout << glist[a].path[b].edgename << " "<< glist[a].path[b].name << " " << glist[a].path[b].weight << ", NUM : " <<  glist[a].path[b].num <<  endl ;
		}
	}
*/	
}

void Getnode() {
	string nodename = "" ;
	string edgename = "" ;
	string weight = "" ;
	string io = "" ;
	Adjlist templ ;
	templ.begin = 0 ;
	templ.end = 0 ;	
	Edge tempe ;
	int i = 0 ;
	int j = 0 ;
	int a = 0 ;
	while ( i < gtext.size() - 1 ) {
//		cout << gtext[i] << endl ;
//		i++ ;
		
		while ( gtext[i][j] != ' ' && gtext[i][j] != '	' ) j++ ;
		while ( gtext[i][j] == ' ' || gtext[i][j] == '	' ) j++ ;
		while ( gtext[i][j] != ' ' && gtext[i][j] != '	' ) {
		  nodename += gtext[i][j] ;
		  j++ ; 
		} // while
		
		
		i++ ;
		j = 0 ;

		while ( gtext[i][j] == ' ' || gtext[i][j] == '	' ) j++ ;
		while ( j < gtext[i].size() ) {
			while (gtext[i][j] != '(' ) {
			  edgename += gtext[i][j] ;
			  j++ ;
			}
			
			j++ ;
			while ( gtext[i][j] != ',' ) {
				weight += gtext[i][j] ;
				j++ ;
			}
			j++ ;
			io += gtext[i][j] ;
			j = j + 2 ;
			while ( gtext[i][j] == ' ' || gtext[i][j] == '	' ) j++ ;
//			cout << io << endl ;

		    while( a < gedge.size() && edgename != gedge[a].name ) a++ ;
		    if ( a < gedge.size() ) {
				if ( io == "i" ) {
				    gedge[a].in = nodename ;
				}
			
				else if ( io == "o" ) {
					gedge[a].out = nodename ;
				}
			}
				
			else {
				tempe.name = edgename ;
				if ( io == "i" ) {
					tempe.in = nodename ;
				}
			
				else if ( io == "o" ) {
				    tempe.out = nodename ;
			    }
			    
			    tempe.weight = weight ;
			
				gedge.push_back(tempe) ;
			}
			
			a = 0 ;
			io = "" ;
			edgename = "" ;
			weight = "" ;
			
		}
				
		
		templ.name = nodename ;
		glist.push_back(templ) ;

		i++ ;
		j = 0 ;
	    nodename = "" ;
	    edgename = "" ;
	    weight = "" ;
	    io = "" ;

				
				
	} // while
	
	Getadjlist() ;
	
	
/*
	cout << glist.size() << endl ;
	for ( int aa = 0 ; aa < glist.size() ; aa++ ) {
		cout << glist[aa].name << endl ;
	}

*/

/*	cout << gedge.size() << endl ;
	for ( int aa = 0 ; aa < gedge.size() ; aa++ ) {
		cout << gedge[aa].name << ", in : " << gedge[aa].in << ",out : "<< gedge[aa].out << ",weight : " << gedge[aa].weight << endl ;
	}
*/
}

void Dfs() {
  int begin[glist.size()] ;
  int end[glist.size()] ;
  int i = 0 ;
  int j = 0 ;
  for ( int a = 0 ; a< glist.size() ; a++ ) {
  	begin[a] = 0 ;
  	end[a] = 0 ;
  }
  
  vector<int> stack ;
  begin[0] = 1 ;
  int step = 0 ;
  stack.push_back(0) ;
  int time = 2 ;
  cout << "DFS 權重優先 : " << endl ; 
  
  while ( time < 25 ) {
  	while( i < glist[step].path.size() ) {
  		if ( begin[glist[step].path[i].num] == 0 ) {
  			break ;
		}
		i++ ;
	}
//	cout << "time " << endl ;
	if ( i >= glist[step].path.size() ) {
		end[step] = time ;
		cout << glist[stack[stack.size()-1]].name << " -> " ;
		stack.pop_back() ;
		if ( !stack.empty() ) step = stack[stack.size()-1] ;
		else break ;
	}
	
	else {
  			begin[glist[step].path[i].num] = time ;
  			step = glist[step].path[i].num ;
  			stack.push_back(step) ;
		
	}
	
//	cout << "Now node : " << glist[step].name << ",time :" << time << endl ;
//	cout << stack.size() << endl ;
	i = 0 ;
	time++ ;
  }
  
  cout << endl << "NODE : " ;
  
  for ( int a = 0 ; a< glist.size() ; a++ ) {
  	cout << glist[a].name << " " ;
  }
  
  cout << endl << "Visit : " ;
  
  for ( int a = 0 ; a< glist.size() ; a++ ) {
  	cout << begin[a] << " " ;
  }
  
  cout << endl << "Finish : " ;

  for ( int a = 0 ; a< glist.size() ; a++ ) {
  	cout << end[a] << " ";
  }

  cout << endl ;

}

void Spd() {
	int map[glist.size()][glist.size()] ;
	int dis[glist.size()] ;
	int vis[glist.size()] ;
	for ( int a = 0 ; a < glist.size() ; a++ ) vis[a] = -1 ;
    int min	= 1000 ;
	for ( int a = 0 ; a < glist.size() ; a++ ) {
		for ( int b = 0 ; b < glist.size() ; b++ ) {
			if ( a == b ) map[a][b] = 0 ; 
			else map[a][b] = 1000 ;
		}
		
		dis[a] = 1000 ;
	}



	
	int i = 0 ; 
	int j = 0 ;
	int k = 0 ;
	while ( i < glist.size() ) {
		while ( j < glist[i].path.size()  ) {
			k = glist[i].path[j].num ;
			map[i][k] = glist[i].path[j].weight[0] - '0' ;
			j++ ;
		}
		i++ ;
		j = 0 ;
	}


    for ( int a = 0 ; a < glist.size() ; a++ ) {
    	dis[a] = map[0][a] ;
	}
/*
	for ( int a = 0 ; a < glist.size() ; a++ ) {
		cout << dis[a] << " " ;		
	}

	cout << endl ;
*/
    i = 1 ;
	j = 0 ;	
	k = 0 ;
	vis[0] = 0 ;
	int counter = 0 ; // 記數 
	int pre = 0 ; // 上一個 

	while ( i < glist.size() ) {
//		cout << "第i次" << i << endl ; 
		for( int a = 0 ; a < glist.size() ; a++ ) { 
			if ( vis[a] == -1 ) min = a ;
		}
		for( int a = 0 ; a < glist.size() ; a++ ) {
			if ( dis[a] < dis[min]  && vis[a] == -1 ) {
				min = a ;
			}
			
		}
		
		if ( vis[min] == -1 ) vis[min] = 0 ; 
		else break ;
//		cout << "find min : " << min << endl ;
		while ( j < glist[min].path.size() )  {
			if ( min != j && ( map[min][glist[min].path[j].num] + dis[min] < dis[glist[min].path[j].num] ) ) {
				dis[glist[min].path[j].num] = map[min][glist[min].path[j].num] + dis[min] ;
			}
			
			j++ ;
			
		}
		i++ ;
		j = 0 ;
	}
	


/*	
	for ( int a = 0 ; a < glist.size() ; a++ ) {
		for ( int b = 0 ; b < glist.size() ; b++ ) {
			cout << map[a][b] << "    " ;
		}
		
		cout << endl ;
		
	}
*/
	cout << "STF : " << endl ;
	for ( int a = 0 ; a < glist.size() ; a++ ) {
		cout << "Nodename : " << glist[a].name << ",dis : " << dis[a] << endl ; 
	}



	
}

int main() {

  string input ;
  cout << "Please enter file name : " << endl ;
  cin >> input ;
  while ( input != "quit" ) {
    if ( Read(input) ) {
      Getnode() ;
      Dfs() ;
      Spd() ;
      
/*
      for(int i = 0 ; i < gtext.size() ; i++ ) {
      	cout << "["  << i << "]"<< gtext[i] << endl ;
      } // for
*/

    }
	  
    cout << "Please enter file name : " << endl ;
    cin >> input ;
    glist.clear() ;
    gtext.clear() ;
    gedge.clear() ;

  }

  
} // main()


