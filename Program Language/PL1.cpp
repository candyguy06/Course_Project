# include <string>
# include <iostream>
# include <vector>
# include <stdio.h>
# include <iomanip>
using namespace std ;


struct Token {
  int firstrow ; // token行位置 
  int firstcolumn ; // token列位置
  int precedence ;
  string text ; // token內容 
  string type ; // token型別 
  bool defined ;
  double value ; // 計算用 
} ; // Token()

struct Table {
  string id ;
  string type ;
  double value ;
} ; // Table()

vector<Token> gword ; // TOKEN串檢查PASER 
vector<Table> glist ; // 存變數 
int gerror3 ; // 存error3位址 
bool gunid = false ; 

bool Factor( int & i ) ;
bool Term( int & i ) ;
bool ArithExp( int & i ) ;
bool NOT_ID_StartFactor( int & i ) ;
bool NOT_ID_StartTerm( int & i ) ;
bool NOT_ID_StartArithExp( int & i ) ;
bool NOT_ID_StartArithExpOrBexp( int & i ) ; 
bool BooleanOperator( int & i ) ;
bool IDlessArithExpOrBexp( int & i ) ;
bool Command( int & i, bool & quit ) ;

void Read( vector<string> & input ) {
  string str ;
  char ch ; 
  while ( scanf( "%c", &ch ) != EOF ) {
    str = str + ch ;
    if ( ch == '\n' ) {
      input.push_back( str ) ;
      str = "\0" ;
    } // if()
    
  } // while ()
  
  if ( str != "\0" ) {
    input.push_back( str ) ;
    str = "\0" ;
  } // if()
  
  if ( !input.empty() ) input.erase( input.begin() ) ;

} // Read()

void Skipwhitespace( int & row, int & column, vector<string> input ) {
  while ( ( row < input.size() && column < input[row].length() ) && 
          ( input[row][column] == ' ' || input[row][column] == '\t' || input[row][column] == '\n' ) ) {

    if ( input[row][column] == '\n' ) {
      row += 1 ;
      column = 0 ;
    } // if 

    else column += 1 ;

  } // while()
  
} // Skipwhitespace()

void Getvalue( int & i ) {
  int j = 0 ;
  double value = 0 ;
  while ( j < gword[i].text.length() && gword[i].text[j] != '.' ) {
    value = value * 10 + ( ( double ) gword[i].text[j] - '0' ) ;
    j++ ;
  } // while
  
  j++ ;
  int k = 0 ; // 記小數點位數 
  while ( j < gword[i].text.length() ) {
    value = value * 10 + ( ( double ) gword[i].text[j] - '0' ) ;
    j++ ;
    k++ ; 
  } // while

  for ( int a = 0 ; a < k ; a++ ) {
    value = value / 10 ;
  } // for
  
  gword[i].value = value ;

} // Getvalue()


void In_to_post( vector<Token> & exe ) {
  Token temp1 ;
  temp1.text = "(" ;
  temp1.precedence = 0 ;
  Token temp2 ;
  temp2.precedence = 0 ;
  temp2.text = ")" ;
  vector<Token> stack ;
  vector<Token> output ;
  stack.push_back( temp1 ) ;
  exe.push_back( temp2 ) ;
  for ( int i = 0 ; i < exe.size() ; i++ ) {
    if ( exe[i].type == "IDENT" || exe[i].type == "FLOAT" || exe[i].type == "INT" ) {
      output.push_back( exe[i] ) ;
    } // if

    else if ( exe[i].text == "(" ) {
      stack.push_back( exe[i] ) ;
    } // else if

    else if ( exe[i].type == "SIGN" || exe[i].type == "OPERATOR" ) {
      for ( int j = stack.size() - 1 ; stack[j].precedence >= exe[i].precedence ; j-- ) {
        output.push_back( stack[j] ) ;
        stack.pop_back() ;
      } // for
 
      stack.push_back( exe[i] ) ;

    } // else if

    else if ( exe[i].text == ")" ) {
      for ( int j = stack.size() - 1  ; stack[j].text != "(" ; j-- ) {
        output.push_back( stack[j] ) ;

        stack.pop_back() ;
      } // for

      stack.pop_back() ;

    } // else if

  } // for 
  
  exe.clear() ;
  
  for ( int i = 0 ; i < output.size() ; i++ ) {
    exe.push_back( output[i] ) ;
  } // for 
  
} // In_to_post()


void Calculation( vector<Token> & exe ) {
  if ( exe.size() == 1 ) return ;
  
  int i = 0 ;

  double cut = 0 ;

  bool find = false ; // 找運算位子 
  while ( exe.size() > 1 ) {
    while ( i+2 < exe.size() && find == false ) {
      if ( ( exe[i].type == "INT" || exe[i].type == "FLOAT" ) &&
           ( exe[i+1].type == "INT" || exe[i+1].type == "FLOAT" )  &&
           ( exe[i+2].type == "SIGN" || exe[i+2].type == "OPERATOR" ) ) {
        find = true ;
      } // if

      i++ ;
    } // while

    if ( i != 0 ) i-- ; // if 有進while多+一次 


    if ( exe[i].type != exe[i+1].type ) {
      exe[i].type = "FLOAT" ;
      exe[i+1].type = "FLOAT" ;      
    } // if 

    if ( exe[i+2].text == "+" ) {
      exe[i].value = exe[i].value + exe[i+1].value ; 
    } // if

    else if ( exe[i+2].text == "-" ) {
      exe[i].value = exe[i].value - exe[i+1].value ; 
    } // else if

    else if ( exe[i+2].text == "*" ) {
      exe[i].value = exe[i].value * exe[i+1].value ; 
    } // else if

    else if ( exe[i+2].text == "/" ) {
      if ( exe[i+1].value == 0 ) return ;
      exe[i].value = exe[i].value / exe[i+1].value ; 
      if ( exe[i].type == "INT" && exe[i+1].type == "INT" ) {
        cut = exe[i].value % 1.0 ;
        exe[i].value -= cut ;
      } // if
    } // else if

    exe.erase( exe.begin()+ ( i + 1 ) ) ;
    exe.erase( exe.begin()+ ( i + 1 ) ) ; 
    find = false ;
    i = 0 ;

  } // while
  
  if ( exe[0].value != 0 && exe[0].value > 0 && exe[0].value < 0.0001 ) exe[0].value = 0 ;
  if ( exe[0].value != 0 && exe[0].value < 0 && exe[0].value > -0.0001 ) exe[0].value = 0 ;
  return ;

} // Calculation()

void Print( vector<Token> exe ) {
  if ( exe[0].type == "INT" ) {
    cout << ( int ) exe[0].value << endl ;
  } // if

  else if ( exe[0].type == "FLOAT" ) {
    double td = exe[0].value ;
    int ti = 0 ;
    td = td * 10000 ;
    ti = ( int ) td ;
    ti = ti % 10 ;
    if ( ti == 5 ) exe[0].value += 0.0001 ;
    cout << fixed  <<  setprecision( 3 ) << exe[0].value << endl ;
  } // else if

} // Print()

void Execution( int start, int end ) {
  int op = -1 ;
  bool id = false ; // id是否定義過 沒定義過新增 有定義過修改 
  vector<Token> exe ; // 右邊 
  vector<Token> templ ; // 左邊式子 
  Table temp ;
  string b ; // 紀錄bool字串 

  
  for ( int j = start ; j < end ; j++ ) {
    exe.push_back( gword[j] ) ;
  } // for
 
  if ( exe.size() == 1 ) { // 只有一個 
    Print( exe ) ;
    return ;
  } // if 
  
  for ( int i1 = 0 ; i1 < exe.size() && op == -1 ; i1++ ) {
    if ( exe[i1].type == "OP" || exe[i1].type == "EQUAL" ) {
      op = i1 ;
    }  // if

  } // for
  
  if ( op == -1 ) { // 單純計算式  ex : 1+2*3 
    In_to_post( exe ) ;
    Calculation( exe ) ;
    if ( exe.size() != 1 ) {
      cout << "Error" << endl ;
      return ;
    } // if

    else {
      Print( exe ) ;
    } // else

  } // if
  
  else if ( op == 1 && exe[1].text == ":=" ) { // 定義式  ex : A = 4*5+6
    temp.id = exe[0].text ;
    exe.erase( exe.begin() ) ;
    exe.erase( exe.begin() ) ;
    In_to_post( exe ) ; 
    Calculation( exe ) ;
    if ( exe.size() != 1 ) {
      cout << "Error" << endl ;
      return ;
    } // if

    else {
      Print( exe ) ;
    } // else

    for ( int j = 0 ; j < glist.size() && id == false ; j++ ) { // 找id是否定義過 
      if ( glist[j].id == temp.id ) { // 有定義過 修改 
        glist[j].type = exe[0].type ;
        glist[j].value = exe[0].value ;
        id = true ;
      } // if 
    } // for

    if ( id == false ) { // 沒定義過 新增 
      temp.type = exe[0].type ;
      temp.value = exe[0].value ;
      glist.push_back( temp ) ;      
    } // if

  } // else if

  else { // 判別式 ex : 7+8 <> 9+10 
    b = exe[op].text ; 
    for ( int i2 = 0 ; i2 < op ; i2++ ) {
      templ.push_back( exe[i2] ) ;
    } // for

    exe.erase( exe.begin(), exe.begin() + ( op + 1 ) ) ;
    In_to_post( templ ) ;    
    In_to_post( exe ) ;  
    Calculation( templ ) ;
    Calculation( exe ) ;
    if ( exe.size() != 1 || templ.size() != 1 ) {
      cout << "Error" << endl ;
      return ;
    } // if


    if ( b == ">" ) {
      if ( templ[0].value > exe[0].value ) {
        cout << "true" << endl ;
      } // if

      else {
        cout << "false" << endl ;
      } // else
    
    } // if

    if ( b == ">=" ) {
      if ( templ[0].value >= exe[0].value ) {
        cout << "true" << endl ;
      } // if

      else {
        cout << "false" << endl ;
      } // else
    
    } // if

    if ( b == "<" ) {
      if ( templ[0].value < exe[0].value ) {
        cout << "true" << endl ;
      } // if

      else {
        cout << "false" << endl ;
      } // else
    
    } // if
      
    if ( b == "<=" ) {
      if ( templ[0].value <= exe[0].value ) {
        cout << "true" << endl ;
      } // if

      else {
        cout << "false" << endl ;
      } // else
    
    } // if

    if ( b == "=" ) {
      if ( templ[0].value == exe[0].value ) {
        cout << "true" << endl ;
      } // if

      else {
        cout << "false" << endl ;
      } // else
    
    } // if

    if ( b == "<>" ) {
      if ( templ[0].value != exe[0].value ) {
        cout << "true" << endl ;
      } // if

      else {
        cout << "false" << endl ;
      } // else
    
    } // if
  
    
  } // else if
  
  op = -1 ;
  exe.clear() ;   
  templ.clear() ;   

} // Execution()

void Gettoken( vector<string> input ) {
  Token temp ;
  temp.value = 0 ;
  temp.defined = false ;
  int row, column = 0 ;
  int dot = 0 ;
  bool quit = false ; 
  Skipwhitespace( row, column, input ) ;
  while ( row < input.size() && column < input[row].length() && quit == false ) {
    if ( ( input[row][column] >= 'a' && input[row][column] <= 'z' ) ||  // IDENT 
         ( input[row][column] >= 'A' && input[row][column] <= 'Z' ) ) {
      temp.firstrow = row ;
      temp.firstcolumn = column ;
      temp.type = "IDENT" ;
      while ( ( ( input[row][column] >= 'a' && input[row][column] <= 'z' ) || 
                ( input[row][column] >= 'A' && input[row][column] <= 'Z' ) || 
                ( input[row][column] >= '0' && input[row][column] <= '9' ) || 
                input[row][column] == '_' ) && column < input[row].size() ) {
        temp.text += input[row][column] ;
        column += 1 ;
      } // while
  
      gword.push_back( temp ) ;
    } // if

    else if ( ( input[row][column] >= '0' && input[row][column] <= '9' ) || 
              input[row][column] == '.' ) { // NUM
      temp.firstrow = row ;
      temp.firstcolumn = column ;
      while ( ( ( input[row][column] >= '0' && input[row][column] <= '9' ) || input[row][column] == '.' ) && 
              dot < 2 && column < input[row].size() ) {
        temp.text += input[row][column] ;
        column += 1 ;
        if ( input[row][column] == '.' ) {
          dot++ ;
        } // if
  
      } // while

      if ( dot > 0 ) {
        temp.type = "FLOAT" ;
      } // if
  
      else {
        temp.type = "INT" ;
      } // else
  
      if ( temp.text == "." ) {
        temp.type = "ERROR1" ;
      } // if 
   
      gword.push_back( temp ) ;
    } // if

    else if ( input[row][column] == '/' &&  input[row][column+1] == '/' ) {  
      row++ ;  
      column = 0 ;
  
    } // else if

    else if ( input[row][column] == '+' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 1 ;
      temp.type = "SIGN" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;
      gword.push_back( temp ) ;
    } // if

    else if ( input[row][column] == '-' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 1 ;
      temp.type = "SIGN" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '*' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 2 ;
      temp.type = "OPERATOR" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '/' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 2 ;
      temp.type = "OPERATOR" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '=' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "OP" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == ';' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "OPERATOR" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '(' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "LP" ;
      temp.precedence = 0 ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == ')' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "RP" ;
      temp.precedence = 0 ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '>' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "OP" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) {
        column += 1 ;
        if ( input[row][column] == '=' ) {
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // if

      } // if
  
      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '<' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "OP" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) {
        column += 1 ;
        if ( input[row][column] == '=' || input[row][column] == '>' ) {
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // if

      } // if
  
      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == ':' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "EQUAL" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) {
        column += 1 ;
        if ( input[row][column] == '=' ) {
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // if

      } // if
  
      gword.push_back( temp ) ;
  
    } // else if


    else {
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.text += input[row][column] ;
      temp.type = "ERROR1" ;
      gword.push_back( temp ) ;
      row++ ;
      column = 0 ;
    } // else 


    temp.firstcolumn = 0 ;
    temp.firstrow = 0 ;
    temp.text = "" ;
    temp.type = "" ;
    temp.precedence = 0 ;
    dot = 0 ;
    if ( gword.size() > 1 && ( gword[gword.size()-1].text == "quit" ) ) {
      if ( gword[gword.size()-1].firstrow != gword[gword.size()-2].firstrow ) {
        quit = true ;
      } // if
      
    } // if
    
    else if ( gword.size() == 1 && ( gword[0].text == "quit"  ) ) {
      quit = true ;
    } // else if

    Skipwhitespace( row, column, input ) ;
    
  } // while
  
} // Gettoken()

void Error( int & i ) {
  int row = gword[i].firstrow ;
  if ( gword[i].type == "ERROR1" ) {
    cout << "Unrecognized token with first char : '" << gword[i].text << "'" << endl ;
  } // if
  
  else {
    cout << "Unexpected token : '" << gword[i].text << "'" << endl ;
  } // else
  
  while ( gword[i].firstrow == row ) i++ ;
  gunid = false ;
  
} // Error()


bool Factor( int & i ) {
  if ( gword[i].type == "IDENT" ) {
    int a = 0 ;
    while ( a < glist.size() && glist[a].id != gword[i].text ) a++ ;
    if ( a < glist.size() && glist[a].id == gword[i].text ) {
      gword[i].value = glist[a].value ;
      gword[i].type = glist[a].type ; 
      gword[i].defined = true ;     
    } // if

    i++ ;
  } // if
  
  else if ( gword[i].type == "FLOAT" || gword[i].type == "INT" ) {
    Getvalue( i ) ;
    i++ ;
  } // else if 
  
  else if ( gword[i].text == "+" || gword[i].text == "-" ) {
    i++ ;
    if ( gword[i].type == "FLOAT" || gword[i].type == "INT" ) {
      Getvalue( i ) ;
      if ( gword[i-1].text == "-" ) {
        gword[i].value = -1 * gword[i].value ; 
      } // if
      
      gword.erase( gword.begin() + ( i - 1 ) ) ;
    } // if

    else {
      return false ;
    } // else

  } // else if
  
  else if ( gword[i].text == "(" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
    if ( ArithExp( i ) ) {
      if ( gword[i].text == ")" ) {
        if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
          i-- ;
          throw ( i ) ;
        } // if

        i++ ;
      } // if
      
      else {
        return false ;
      } // else
   
    } // if 

    else {
      return false ;
    } // else

  } // else if

  else {
    return false ;
  } // else
  
  return true ;
  
} // Factor()

bool Term( int & i ) {
  if ( Factor( i ) ) {
    
  } // if
  
  else {
    return false ;
  } // else
  
  while ( gword[i].text == "*" || gword[i].text == "/" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
    if ( Factor( i ) ) {
      
    } // if
  
    else {
      return false ;
    } // else

  
  } // while
  
  return true ;
    
} // Term()

bool ArithExp( int & i ) {
  if ( Term( i ) ) {
    
  } // if
  
  else {
    return false ;
  } // else
  
  while ( gword[i].text == "+" || gword[i].text == "-" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
    if ( Term( i ) ) {
      
    } // if

    else {
      return false ;
    } // else


  } // while
  
  return true ;
  
} // ArithExp()

bool NOT_ID_StartFactor( int & i ) {
  if ( gword[i].text == "+" || gword[i].text == "-" ) {
    i++ ;
    if ( gword[i].type == "FLOAT" || gword[i].type == "INT" ) {
      Getvalue( i ) ;
      if ( gword[i-1].text == "-" ) {
        gword[i].value = -1 * gword[i].value ; 
      } // if

      gword.erase( gword.begin() + ( i - 1 ) ) ;
      
    } // if 

    else {
      return false ;
    } // else

  } // if
  
  else if ( gword[i].type == "FLOAT" || gword[i].type == "INT" ) {
    Getvalue( i ) ;
    i++ ;
  } // else if 
  
  else if ( gword[i].text == "(" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
    if ( ArithExp( i ) ) {
      if ( gword[i].text == ")" ) {
        if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
          i-- ;
          throw ( i ) ;
        } // if

        i++ ;
      } // if
    
      else {
        return false ;
      } // else
      
    } // if 

    else {
      return false ;
    } // else

  } // else if

  else {
    return false ;
  } // else
  
  return true ;
  
} // NOT_ID_StartFactor()

bool NOT_ID_StartTerm( int & i ) {
  if ( NOT_ID_StartFactor( i ) ) {
    
  } // if 
  
  else {
    return false ;
  } // else
  
  while ( gword[i].text == "*" || gword[i].text == "/" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
    if ( Factor( i ) ) {
     
    } // if 

    else {
      return false ;
    } // else

  } // while
  
  return true ;
  
} // NOT_ID_StartTerm()

bool NOT_ID_StartArithExp( int & i ) {
  if ( NOT_ID_StartTerm( i ) ) {

  } // if 
  
  else {
    return false ;
  } // else
  
  while ( gword[i].text == "+" || gword[i].text == "-" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
    if ( Term( i ) ) {
        
    } // if 
  
    else {
      return false ;
    } // else

  } // while
  
  return true ;
  
} // NOT_ID_StartArithExp()

bool NOT_ID_StartArithExpOrBexp( int & i ) {
  if ( NOT_ID_StartArithExp( i ) ) {
    
  } // if
  
  else {
    return false ;
  } // else
  
  if ( BooleanOperator( i ) ) { 
    if ( ArithExp( i ) ) {
  
    } // if

    else {
      return false ;
    } // else 

  } // if
  
  
  return true ;
  
} // NOT_ID_StartArithExpOrBexp()

bool BooleanOperator( int & i ) {
  if ( gword[i].text == "=" || gword[i].text == "<>" || gword[i].text == ">" || 
       gword[i].text == "<" || gword[i].text == ">=" || gword[i].text == "<=" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
  } // if
  
  else {
    return false ;
  } // else
  
  return true ;
  
} // BooleanOperator()

bool IDlessArithExpOrBexp( int & i ) {
  if ( gword[i].text == "+" || gword[i].text == "-" || gword[i].text == "*" || gword[i].text == "/" ) {
    while ( gword[i].text == "+" || gword[i].text == "-" || gword[i].text == "*" || gword[i].text == "/" ) {
      if ( gword[i].text == "+" || gword[i].text == "-" ) {
        if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
          i-- ;
          throw ( i ) ;
        } // if

        i++ ;
        if ( Term( i ) ) {

        } // if

        else {
          return false ;
        } // else


      } // if
      
      else if ( gword[i].text == "*" || gword[i].text == "/" ) {
        if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
          i-- ;
          throw ( i ) ;
        } // if

        i++ ;
        if ( Factor( i ) ) {
  
        } // if

        else {
          return false ;
        } // else

      
      } // else if
  
    } // while

  } // if
  
  if ( BooleanOperator( i ) ) {
    if ( ArithExp( i ) ) {
  
    } // if

    else {
      return false ;
    } // else 

  } // if
  
  return true ;
  
} // IDlessArithExpOrBexp()

bool Command( int & i, bool & quit ) {

  if ( gword[i].text == "quit" ) {
    quit = true ;
    return false ;
  } // if


  else if ( gword[i].type == "IDENT" ) {
    for ( int j = 0 ; j < glist.size() ; j++ ) {
      if ( gword[i].text == glist[j].id ) {
        gword[i].value = glist[j].value ;
        gword[i].type = glist[j].type ; 
        gword[i].defined = true ;       
      } // if 
      
    } // for


    i++ ;
    if ( gword[i].text == ":=" ) {
      i++ ;
      if ( ArithExp( i ) ) {
          
      } // if
  
      else {
        Error( i ) ;
        return false ;
      } // else

    } // if
  
    else if ( IDlessArithExpOrBexp( i ) ) {

    } // else if
    
    else {
      Error( i ) ;
      return false ;
    } // else

  } // if
  
  else if ( NOT_ID_StartArithExpOrBexp( i ) ) {
    
  } // else if

  
  else {
    Error( i ) ;
    return false ;
  } // else

  if ( gword[i].text == ";" ) {
    if ( i-1 > 0 && gword[i-1].type == "IDENT" && gword[i-1].defined == false ) {
      i-- ;
      throw ( i ) ;
    } // if

    i++ ;
  } // if

  else {
    Error( i ) ;
    return false ;
  } // else

  
  return true ;
  
} // Command()

int main() {
  vector<string> input ;

  Read( input ) ;
  bool quit = false ;
  int i = 0 ;
  Gettoken( input ) ;
  int start = 0 ;
  int test = 0 ;
  cout << "Program starts..." << endl ;
  while ( i < gword.size() && quit == false ) {
    start = i ;
    cout << "> " ;
    try {
      if ( Command( i, quit ) ) {
        Execution( start, i-1 ) ;
      } // if
      
    } // try

    catch ( int pop ) {
      i = pop ;
      cout << "Undefined identifier : '" << gword[i].text << "'" << endl ;
      i++ ;
      while ( gword[i].firstrow == gword[pop].firstrow ) i++ ;
    } // catch

    gunid = false ;
    gerror3 = 0 ;

  } // while

  cout << "Program exits..."  ;
  
} // main()


