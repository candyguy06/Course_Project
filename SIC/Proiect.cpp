#include<iostream>
#include<fstream>
#include <string.h>
#include <vector>
#include <stdio.h>

using namespace std;

int dott = -1 ;
int dotl = -1 ;
int ot = -1 ;
int ol = -1 ;

struct Datapath {
	char name[10000] ;
	int table ;
	int num ;
	int line ;
	Datapath() {
		for ( int i = 0 ; i < 100 ; i++ ) name[i] = '\0' ;
		table = 0 ;
		num = 0 ;
		line = 1 ;
	}
};

vector <Datapath> save ;
Datapath st ;

void ReadFile ( char input[50], vector <Datapath> & data ) {
	fstream file ;
	strcat( input, ".txt" ) ;
	char a ;
	Datapath b ;
	file.open( input, ios::in ) ;	

	if ( !file ) {
		cout << "目標檔案不存在";
	}
	
	else {
		
		while ( !file.eof() ) {
			file.getline( b.name, sizeof(b.name) ) ;
			data.push_back(b) ;
		}


		file.close() ;
	}
}

bool T4 ( char s[100], vector <Datapath> table4 ) {
	for ( int a = 0; a < table4.size() ; a++ ) {
		for ( int b =0; s[b] != '\0' && b < 100 ; b++ ) {
			if ( s[b] == table4[a].name[0]  ) return true ;
		}
	}	
	

	return false ;
}

bool Find ( char s[100], vector <Datapath> table1, vector <Datapath> table2, vector <Datapath> table3, vector <Datapath> table4, vector <Datapath> table5, vector <Datapath> table6, vector <Datapath> table7 ) {
	for ( int t1 = 0 ; t1 < table1.size() ; t1++ ) {
		if ( strcasecmp( s, table1[t1].name) == 0 ) {
			sprintf (st.name, "(1,%d) ", t1+1 );
			save.push_back(st) ;

			cout << "(1," << t1+1 << ") " ; 
			return true ;
		}
	}

	for ( int t2 = 0 ; t2 < table2.size() ; t2++ ) {
		if ( strcasecmp( s, table2[t2].name) == 0 ) {
			sprintf (st.name, "(2,%d) ", t2+1 );
			save.push_back(st) ;

			cout << "(2," << t2+1 << ") " ; 
			return true ;
		}
	}

	for ( int t3 = 0 ; t3 < table3.size() ; t3++ ) {
		if ( strcasecmp( s, table3[t3].name) == 0 ) {
			sprintf (st.name, "(3,%d) ", t3+1 );
			save.push_back(st) ;

			cout << "(3," << t3+1 << ") " ; 
			return true ;
		}
	}

	for ( int t4 = 0 ; t4 < table4.size() ; t4++ ) {
		if ( strcasecmp( s, table4[t4].name) == 0 ) {
			sprintf (st.name, "(4,%d) ", t4+1 );
			save.push_back(st) ;
			cout << "(4," << t4+1 << ") " ; 
			return true ;
		}
	}

	for ( int t5 = 0 ; t5 < table5.size() ; t5++ ) {
		if ( strcasecmp( s, table5[t5].name) == 0 ) {
			sprintf (st.name, "(5,%d) ", t5 );
			save.push_back(st) ;

			cout << "(5," << t5 << ") " ; 
			return true ;
		}
	}

	for ( int t6 = 0 ; t6 < table6.size() ; t6++ ) {
		if ( strcasecmp( s, table6[t6].name) == 0 ) {
			sprintf (st.name, "(6,%d) ", t6 );
			save.push_back(st) ;
			cout << "(6," << t6 << ") " ; 
			return true ;
		}
	}

	for ( int t7 = 0 ; t7 < table7.size() ; t7++ ) {
		if ( strcasecmp( s, table7[t7].name) == 0 ) {
			sprintf (st.name, "(7,%d) ", t7 );
			save.push_back(st) ;

			cout << "(7," << t7 << ") " ; 
			return true ;
		}
	}
	
	return false ;

}

bool Double( char s[100] , int & step ) {
	while ( s[step] != '\0' ) {
		if ( s[step] == '\'' ) return true ;
		step++ ;
	}	
	return false ;	
}

bool Snum ( char s[100] ) {
	int tt = 0 ;
	while( s[tt] != '\0' && s[tt] >= '0' && s[tt] <= '9' ) tt++ ;
	if ( s[tt] == '\0' ) return true ;
	return false ;
}

bool WordCheck ( char s, vector <Datapath> table4 ) {
	for ( int c = 0 ; c < table4.size() ; c++ ) {
		if ( s == table4[c].name[0] ) return true ; 
	}
    return false ;
}

void Token( char s[100], vector <Datapath> & table1, vector <Datapath> & table2, vector <Datapath> & table3, vector <Datapath> & table4, vector <Datapath> & table5, vector <Datapath> & table6, vector <Datapath> & table7) {
	if ( !T4(s,table4) ) { 
		if ( Find( s, table1, table2, table3, table4, table5, table6, table7 ) ) {
			return ;
		}
		
		else if ( Snum( s ) ) {
			int num0 = 0 ;
			for ( int st =0 ; s[st] != '\0' ; st++) {
				num0 = num0 + s[st] ;
			}
			
			num0 = num0 % 100 ;
			while ( table6[num0].name[0] != '\0'  ) {
				if ( strcasecmp( s, table6[num0].name ) == 0 ) break ;
				num0++ ;
				if ( num0 == 100 ) num0 = 0 ;
			} 
			
			sprintf (st.name, "(6,%d) ", num0 );
			save.push_back(st) ;
			
			cout << "(6," << num0 << ") " ;
			strcpy( table6[num0].name , s ) ;
			
			return ;
			
			
		}
		
		else {
			int num = 0 ;
			for ( int st =0 ; s[st] != '\0' ; st++) {
				num = num + s[st] ;
			}
			
			num = num % 100 ;
			while ( table5[num].name[0] != '\0'  ) {
				if ( strcasecmp( s, table5[num].name ) == 0 ) break ;
				num++ ;
				if ( num == 100 ) num = 0 ;
			} 

			sprintf (st.name, "(5,%d) ", num );
			save.push_back(st) ;
						
			cout << "(5," << num << ") " ;

			strcpy( table5[num].name , s ) ;
			
			return ;
			
		}
		
	} // if
	
	else {
		if ( Find( s, table1, table2, table3, table4, table5, table6, table7 ) ) {
			return ;
		}
		
		else if ( ( s[0] == 'X' || s[0] == 'x' ) && s[1] == '\'' && s[2] != '\0' ) {
			int step = 2 ;
			int next = 0 ;
			int num2 = 0 ;
			if ( Double( s, step) ) {
				next = step+1 ;
				for ( int u = 2 ; u < step ; u++ ) {
					num2 = num2 + s[u] ;
				}
				
				num2 = num2 % 100 ;
				while ( table6[num2].name[0] != '\0'  ) {
					if ( strcasecmp( s, table6[num2].name ) == 0 ) break ;
					num2++ ;
					if ( num2 == 100 ) num2 = 0 ;
				} 

				sprintf (st.name, "(%d,%d) ", ot, ol );
				save.push_back(st) ;

				sprintf (st.name, "(6,%d) ", num2 );
				save.push_back(st) ;

				sprintf (st.name, "(%d,%d) ", ot, ol );
				save.push_back(st) ;

				cout << "(" << ot << "," << ol << ") " ;
			
				cout << "(6," << num2 << ") " ;

				cout << "(" << ot << "," << ol << ") " ;

				strcpy( table6[num2].name , s ) ;
				
				if ( s[next] != '\0' ) {
					char store[100] ;
					for ( int asd = 0 ; asd < 100 ; asd++ ) store[asd] = '\0' ;
					for ( int aaa = 0 ; next < 100 ; aaa++ ) {
						store[aaa] = s[next] ;
						next++ ;
					}
					Token(store, table1, table2, table3, table4, table5, table6, table7) ;
				}
			
				return ;
				
			}
		}
		
		else if ( ( s[0] == 'C' || s[0] == 'c' ) && s[1] == '\'' && s[2] != '\0' ) {
			int step = 2 ;
			int num3 = 0 ;
			int next2 = 0 ;
			if ( Double( s, step) ) {
				next2 = step+1 ;
				for ( int u = 2 ; u < step ; u++ ) {
					num3 = num3 + s[u] ;
				}
				
				num3 = num3 % 100 ;
				while ( table7[num3].name[0] != '\0'  ) {
					if ( strcasecmp( s, table7[num3].name ) == 0 ) break ;
					num3++ ;
					if ( num3 == 100 ) num3 = 0 ;
				} 
			

				sprintf (st.name, "(%d,%d) ", ot, ol );
				save.push_back(st) ;

				sprintf (st.name, "(7,%d) ", num3 );
				save.push_back(st) ;

				sprintf (st.name, "(%d,%d) ", ot, ol );
				save.push_back(st) ;


				cout << "(" << ot << "," << ol << ") " ;

				cout << "(7," << num3 << ") " ;

				cout << "(" << ot << "," << ol << ") " ;

				strcpy( table7[num3].name , s ) ;

				if ( s[next2] != '\0' ) {
					char store[100] ;
					for ( int asd = 0 ; asd < 100 ; asd++ ) store[asd] = '\0' ;
					for ( int bbb = 0 ; next2 < 100 ; bbb++ ) {
						store[bbb] = s[next2] ;
						next2++ ;
					}
					Token(store, table1, table2, table3, table4, table5, table6, table7) ;
				}
			
				return ;
				
			}
		}

		else if ( ( s[0] == 'C' || s[0] == 'c' ) && s[1] == '\'' && s[2] == '\0' ) {
				int num4 = 0 ;
				num4 = s[0] + s[1] ;
				num4 = num4 % 100 ;
				while ( table5[num4].name[0] != '\0'  ) {
					if ( strcasecmp( s, table5[num4].name ) == 0 ) break ;
					num4++ ;
					if ( num4 == 100 ) num4 = 0 ;
				} 

				sprintf (st.name, "(5,%d) ", num4 );
				save.push_back(st) ;
			
				cout << "(5," << num4 << ") " ;


				strcpy( table5[num4].name , s ) ;
				
				
			
				return ;
				
			
		}

		else if ( ( s[0] == 'X' || s[0] == 'x' ) && s[1] == '\'' && s[2] == '\0' ) {
				int num4 = 0 ;
				num4 = s[0] + s[1] ;
				num4 = num4 % 100 ;
				while ( table5[num4].name[0] != '\0'  ) {
					if ( strcasecmp( s, table5[num4].name ) == 0 ) break ;
					num4++ ;
					if ( num4 == 100 ) num4 = 0 ;
				} 
			
				sprintf (st.name, "(5,%d) ", num4 );
				save.push_back(st) ;

				cout << "(5," << num4 << ") " ;


				strcpy( table5[num4].name , s ) ;
				
				
			
				return ;
				
			
		}


		else if ( T4(s,table4) ) {
			char word[100] ;
			for ( int ax = 0 ; ax < 100 ; ax++ ) word[ax] = '\0' ;
			int canum = 0 ;

			for ( int ca = 0 ; s[ca] != '\0' ; ca++ ) {
				int d = ca+1 ;
/*				if ( s[ca] == '.' ) {
					if ( word == '\0' ) {
						cout << "(" << dott << "," << dotl << ") " ;
						ca = 99 ;	
					}
					
					else {
						Token(word, table1, table2, table3, table4, table5, table6, table7) ;
						cout << "(" << dott << "," << dotl << ") " ;
						ca = 99 ;	
					}
				}
*/				
				 if ( WordCheck(s[ca], table4 ) && word[0] == '\0' ) {
					word[0] = s[ca] ;
					Find(word, table1, table2, table3, table4, table5, table6, table7) ;
					word[0] = '\0' ;
					canum = 0 ;
				} 
				else if ( WordCheck(s[ca], table4 ) && word[0] != '\0' ) {
					Token(word, table1, table2, table3, table4, table5, table6, table7) ;
					for ( int gc = 0 ; gc < 100 ; gc++ ) word[gc] = '\0' ;
					word[0] = s[ca] ;
					Find(word, table1, table2, table3, table4, table5, table6, table7) ;
					word[0] = '\0' ;
					canum = 0 ;
				} 
				
				
				else if ( WordCheck(s[ca], table4 ) && s[ca] == '\''  && word[0] != '\0' && Double( s, d) ) {
					int ttt = 0 ;
					for ( int gc = 0 ; word[gc] != '\0' ; gc++ ) ttt = gc ;
					for ( int as = ca-1 ; as < 100 ; as++  ) {
					
						word[ttt] = s[as] ;
						if ( ttt < 99 ) ttt++ ;
					}
					Token(word, table1, table2, table3, table4, table5, table6, table7) ;
					for ( int as = 0 ; as < 100 ; as++  ) word[as] = '\0' ;
					
					canum = 0 ;
				} 

				else {
					word[canum] = s[ca] ;
					canum++ ;
					
				}

			} 
			
			if ( word[0] != '\0' ) {
				cout << endl << word << endl ;
				Token(word, table1, table2, table3, table4, table5, table6, table7) ;
			}
		} 


	} 
}

void ReadTable ( vector <Datapath> & table1, vector <Datapath> & table2, vector <Datapath> & table3, vector <Datapath> & table4 ) {
	fstream file ;
	char name[50] = "Table1.table" ;
	int line = 1 ;
	Datapath temp ;
    file.open( name, ios::in ) ;
    while ( !file.eof() ) {
    	file.getline( temp.name , sizeof(temp.name) ) ;
    	if ( strcmp( temp.name, "'" ) == 0 ) {
    		ot = 1 ;
    		ol = line ;
		}  
    	if ( strcmp( temp.name, "." ) == 0 ) {
    		dott = 1 ;
    		dotl = line ;
		}  

    	table1.push_back( temp ) ;
    	line++ ;
    	for( int x = 0 ; x < 100 ; x++ ) temp.name[x] = '\0' ;
	}
	file.close() ;
	
	line = 1 ;
	
	strcpy( name, "Table2.table" ) ;
    file.open( name, ios::in ) ;
    while ( !file.eof() ) {
    	file.getline( temp.name,sizeof(temp.name) ) ;
    	if ( strcmp( temp.name, "'" ) == 0 ) {
    		ot = 2 ;
    		ol = line ;
		}  
    	if ( strcmp( temp.name, "." ) == 0 ) {
    		dott = 2 ;
    		dotl = line ;
		}  

    	table2.push_back( temp ) ;
    	line++ ;
    	for( int x = 0 ; x < 100 ; x++ ) temp.name[x] = '\0' ;
	}
	file.close() ;
	line = 1 ;

	strcpy( name, "Table3.table" ) ;
    file.open( name, ios::in ) ;
    while ( !file.eof() ) {
    	file.getline( temp.name,sizeof(temp.name) ) ;
    	if ( strcmp( temp.name, "'" ) == 0 ) {
    		ot = 3 ;
    		ol = line ;
		}  
    	if ( strcmp( temp.name, "." ) == 0 ) {
    		dott = 3 ;
    		dotl = line ;
		}  
    	table3.push_back( temp ) ;
    	line++ ;
    	for( int x = 0 ; x < 100 ; x++ ) temp.name[x] = '\0' ;
	}
	file.close() ;
	line = 1 ;
	strcpy( name, "Table4.table" ) ;
    file.open( name, ios::in ) ;
    while ( !file.eof() ) {
    	file.getline( temp.name,sizeof(temp.name) ) ;
    	if ( strcmp( temp.name, "'" ) == 0 ) {
    		ot = 4 ;
    		ol = line ;
		}  
    	if ( strcmp( temp.name, "." ) == 0 ) {
    		dott = 4 ;
    		dotl = line ;
		}  

    	table4.push_back( temp ) ;
    	line++ ;
    	for( int x = 0 ; x < 100 ; x++ ) temp.name[x] = '\0' ;
	}
	file.close() ;
	line = 1 ;

    
}

void WriteFile( vector <Datapath> table5, vector <Datapath> table6, vector <Datapath> table7 ) {
	fstream file ;
	char name[50] = "Table5.table" ;
	file.open( name, ios::out | ios::trunc ) ;
	for ( int a = 0 ; a < 100 ; a++ ) {
		if ( table5[a].name[0] != '\0' ) file << table5[a].name << endl ; 
	}
	file.close() ;

    strcpy( name, "Table6.table" ) ;
	file.open( name, ios::out | ios::trunc ) ;
	for ( int a = 0 ; a < 100 ; a++ ) {
		if ( table6[a].name[0] != '\0' ) file << table6[a].name << endl ; 
	}

	file.close() ;

    strcpy( name, "Table7.table" ) ;
	file.open( name, ios::out | ios::trunc ) ;
	for ( int a = 0 ; a < 100 ; a++ ) {
		if ( table7[a].name[0] != '\0' ) file << table7[a].name << endl ; 
	}
	file.close() ;
	
	
}

void WriteOut( char input[50] , vector <Datapath> data ) {
	fstream file ;
	int a2 = 0;	
	strcat( input, "output.txt" ) ;
	
	file.open( input, ios::out | ios::trunc ) ;
	for ( int a1 = 0 ; a1 < data.size() ; a1++ ) {
		file << data[a1].name << endl ;
		while ( strcmp( save[a2].name, "\n" ) != 0 && a2 < save.size() ) {
			file << save[a2].name ;
			a2++ ;
		}
		file << endl ;
		a2++ ;
	}	
	file.close() ;


}


int main() {
	char input[50] ; 
	char s[100] ;
	vector <Datapath> data ;
	vector <Datapath> table1, table2, table3, table4, table5 ,table6 ,table7 ;
	Datapath temp123 ;
	for ( int ac = 0 ; ac < 100 ; ac++ ) {
		table5.push_back(temp123) ;
		table6.push_back(temp123) ;
		table7.push_back(temp123) ;
	}
	int step = 0 ;
	int j = 0 ;
	cin >> input ;
	while ( strcmp( input, "exit") != 0 ) {
		//cout << "1" ;

		ReadFile( input, data ) ;
		
		cout << data.size() << endl;
	   

		ReadTable( table1, table2, table3, table4 ) ;



		for ( int i = 0; i < data.size() ; i++ ) {
			cout << data[i].name << endl ;
		//	for ( int an = 0 ; an < 10000 && data[i].name[an] == ' ' ; an++ ) step = an ; 
			while ( data[i].name[step] != '\0' ) {
				while ( ( data[i].name[step] == ' ' || data[i].name[step] == '	' ) && data[i].name[step] != '\0' ) step++ ;
				if ( data[i].name[step] == '\0' && s[0] == '\0' ) break ;
				while ( data[i].name[step] != ' ' && data[i].name[step] != '	' && data[i].name[step] != '\0') {
					if ( data[i].name[step] == '\'') {
						s[j] = data[i].name[step] ;
						j++; 
						step++ ;
						while ( data[i].name[step] != '\'' && data[i].name[step] != ' ' && data[i].name[step] != '	' && data[i].name[step] != '\0' ) {
							s[j]= data[i].name[step] ;
							j++ ;
							step++ ;
						}
					}
					
					else if ( data[i].name[step] == '.' ) {
						break ;
					}
					
					else {
						s[j] = data[i].name[step] ;
						j++;
						step++ ;
					}
				}
				
				if ( data[i].name[step] == '.' ) {
					if ( s[0] != '\0' ) Token( s, table1, table2, table3, table4, table5, table6, table7 ) ;
					sprintf (st.name, "(%d,%d) ", dott, dotl);
					save.push_back(st) ;
					cout << "(" << dott << "," << dotl << ") " ;
					while ( data[i].name[step] != '\0' ) step++ ;
				}
				
				
				else Token( s, table1, table2, table3, table4, table5, table6, table7 ) ;
				j = 0 ;
//				cout << s << " " ;				
				for ( int ss = 0; ss <100 ; ss++) s[ss] = '\0' ;
			}
			strcpy( st.name, "\n" ) ;
			save.push_back(st) ;
			cout << endl ;
			step = 0 ;
		}
		

/*		cout << endl ;
		for ( int da = 0 ; da < save.size() ; da++ ) {
			cout << save[da].name ;
		}
*/
/*
		for ( int i = 0; i < table1.size() ; i++ ) {
			cout << table1[i].name << endl;

		}

		for ( int i = 0; i < table2.size() ; i++ ) {
			cout << table2[i].name << endl;

		}

		for ( int i = 0; i < table3.size() ; i++ ) {
			cout << table3[i].name << endl;

		}

		for ( int i = 0; i < table4.size() ; i++ ) {
			cout << table4[i].name << endl;

		}
*/
		WriteFile( table5, table6, table7 ) ;
		WriteOut( input, data ) ;
		save.clear() ;				
		data.clear() ;
		table1.clear() ;
		table2.clear() ;
		table3.clear() ;
		table4.clear() ;

		cin >> input ;
		
	} 
}
