# include <string>
# include <iostream>
# include <vector>
# include <stdio.h>
# include <iomanip>
# include <math.h>
using namespace std ;


struct Token {
  int firstrow ; // token嚙踝蕭嚙練 
  int firstcolumn ; // token嚙瘠嚙踝蕭m
  int precedence ;
  string text ; // token嚙踝蕭嚙箴 
  string type ; // token嚙踝蕭嚙瞌 
  bool defined ;
  double value ; // 嚙緘嚙踝蕭嚙?
} ; // Token()

struct Varidata {
  string name ;
  string type ;
  string vindex ;
} ; // Varidata()

struct Vari {
  vector<Varidata> list ; 
} ; // Vari()

struct Func {
  string name ;
  vector<string> word ;
  vector<Token> t ;
} ; // Func()

vector<Vari> gvaritable ;
vector<Func> gfunctable ;
vector<string> gfivefunc ;
vector<Token> gword ; // TOKEN嚙踝蕭嚙誼查PASER 
bool ground2 = false ;

void User_input( int & i ) ;
bool Definition( int & i ) ;
bool Type_specifier( int & i ) ;
bool Function_definition_or_declarators( int & i ) ;
bool Rest_of_declarators( int & i ) ;
bool Function_definition_without_ID( int & i ) ;
bool Formal_parameter_list( int & i ) ;
bool Compound_statement( int & i ) ;
bool Declaration( int & i ) ;
bool Statement( int & i ) ;
bool Expression( int & i ) ;
bool Basic_expression( int & i ) ;
bool Rest_of_Identifier_started_basic_exp( int & i ) ;
bool Rest_of_PPMM_Identifier_started_basic_exp( int & i ) ;
bool Sign( int & i ) ;
bool Actual_parameter_list( int & i ) ;
bool Assignment_operator( int & i ) ;
bool Romce_and_romloe( int & i ) ;
bool Rest_of_maybe_logical_OR_exp( int & i ) ;
bool Maybe_logical_AND_exp( int & i ) ;
bool Rest_of_maybe_logical_AND_exp( int & i ) ;
bool Maybe_bit_OR_exp( int & i ) ;
bool Rest_of_maybe_bit_OR_exp( int & i ) ;
bool Maybe_bit_ex_OR_exp( int & i ) ;
bool Rest_of_maybe_bit_ex_OR_exp( int & i ) ;
bool Maybe_bit_AND_exp( int & i ) ;
bool Rest_of_maybe_bit_AND_exp( int & i ) ;
bool Maybe_equality_exp( int & i ) ;
bool Rest_of_maybe_equality_exp( int & i ) ;
bool Maybe_relational_exp( int & i ) ;
bool Rest_of_maybe_relational_exp( int & i ) ;
bool Maybe_shift_exp( int & i ) ;
bool Rest_of_maybe_shift_exp( int & i ) ;
bool Maybe_additive_exp( int & i ) ;
bool Rest_of_maybe_additive_exp( int & i ) ;
bool Maybe_mult_exp( int & i ) ;
bool Rest_of_maybe_mult_exp( int & i ) ;
bool Unary_exp( int & i ) ;
bool Signed_unary_exp( int & i ) ;
bool Unsigned_unary_exp( int & i ) ;
bool Checkdefine( string str ) ;


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
    str += ' ' ;
    input.push_back( str ) ;
    str = "\0" ;
  } // if()
  
  if ( !input.empty() ) input.erase( input.begin() ) ;

} // Read()

void Skipwhitespace( int & row, int & column, vector<string> input ) {
  if ( row < input.size() && column > input[row].length() ) {
    row++ ;
    column = 0 ;
  } // if
  
  while ( ( row < input.size() && column < input[row].length() ) && 
          ( input[row][column] == ' ' || input[row][column] == '\t' || input[row][column] == '\n' ) ) {

    if ( input[row][column] == '\n' ) {
      row += 1 ;
      column = 0 ;
    } // if 

    else column += 1 ;

  } // while()
  
} // Skipwhitespace()

void Gettoken( vector<string> input ) {
  Token temp ;
  temp.value = 0 ;
  temp.defined = false ;
  int row, column = 0 ;
  int dot = 0 ;
  bool quit = false ; 
  Skipwhitespace( row, column, input ) ;
  while ( row < input.size() && column < input[row].length() ) {
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

      if ( temp.text == "int" ) temp.type = "INT" ;
      if ( temp.text == "float" ) temp.type = "FLOAT" ;
      if ( temp.text == "char" ) temp.type = "CHAR" ;
      if ( temp.text == "bool" ) temp.type = "BOOL" ;
      if ( temp.text == "string" ) temp.type = "STRING" ;
      if ( temp.text == "void" ) temp.type = "VOID" ;
      if ( temp.text == "if" ) temp.type = "IF" ;
      if ( temp.text == "else" ) temp.type = "ELSE" ;
      if ( temp.text == "while" ) temp.type = "WHILE" ;
      if ( temp.text == "do" ) temp.type = "DO" ;
      if ( temp.text == "return" ) temp.type = "RETURN" ;
      if ( temp.text == "true" ) temp.type = "CTRUE" ;
      if ( temp.text == "false" ) temp.type = "CFALSE" ;

  
      gword.push_back( temp ) ;
    } // if

    else if ( ( input[row][column] >= '0' && input[row][column] <= '9' ) || 
              input[row][column] == '.' ) { // NUM
      temp.firstrow = row ;
      temp.firstcolumn = column ;
      if ( input[row][column] == '.' ) {
        dot++ ;
      } // if

      while ( ( ( input[row][column] >= '0' && input[row][column] <= '9' ) || input[row][column] == '.' ) && 
              dot < 2 && column < input[row].size() ) {

        temp.text += input[row][column] ;
        column += 1 ;
        if ( input[row][column] == '.' ) {
          dot++ ;
        } // if
  
      } // while

      if ( dot > 0 ) {
        temp.type = "CFLOAT" ;
      } // if
  
      else {
        temp.type = "CINT" ;
      } // else
  
      if ( temp.text == "." ) {
        temp.type = "ERROR1" ;
      } // if 
   
      gword.push_back( temp ) ;
    } // if

    else if ( input[row][column] == '\'' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "CCHAR" ;
      column++ ;
      if (  input[row][column] == '\\' ) {
        if ( input[row][column+1] == 'n' ) {
          temp.text += '\n' ;
          column += 2 ;
        } // if

        else if ( input[row][column+1] == 't' ) {
          temp.text += '\t' ;
          column += 2 ;
        } // if

        else if ( input[row][column+1] == '0' ) {
          temp.text += '\0' ;
          column += 2 ;
        } // if

        else if ( input[row][column+1] == '\"' ) {
          temp.text += '\"' ;
          column += 2 ;
        } // if

        else if ( input[row][column+1] == '\\' ) {
          temp.text += '\\' ;
          column += 2 ;
        } // if

      } // if

      else {
        temp.text += input[row][column] ;
        column++ ;
      } // else



      if ( input[row][column] == '\'' ) {
        column++ ;
      } // if

      gword.push_back( temp ) ;
    } // else if

    else if ( input[row][column] == '\"' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "CSTRING" ;
      column++ ;
      while ( input[row][column] != '\"' ) {
        temp.text += input[row][column] ;
        column++ ;
      } // while

      if ( input[row][column] == '\"' ) column++ ;
      gword.push_back( temp ) ;
    } // else if

    else if ( input[row][column] == '/' &&  input[row][column+1] == '/' ) {  
      row++ ;  
      column = 0 ;
  
    } // else if

    else if ( input[row][column] == '+' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 1 ;
      temp.type = "+" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;
      if ( column < input[row].size() && input[row][column] == '+' ) {
        temp.text += input[row][column] ;
        temp.type = "PP" ;
        if ( column < input[row].size() ) column += 1 ;
      } // if

      else if ( column < input[row].size() && input[row][column] == '=' ) {
        temp.text += input[row][column] ;
        temp.type = "PE" ;
        if ( column < input[row].size() ) column += 1 ;        
      } // else if

      gword.push_back( temp ) ;
    } // if

    else if ( input[row][column] == '-' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 1 ;
      temp.type = "-" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;
      if ( column < input[row].size() && input[row][column] == '-' ) {
        temp.text += input[row][column] ;
        temp.type = "MM" ;
        if ( column < input[row].size() ) column += 1 ;
      } // if

      else if ( column < input[row].size() && input[row][column] == '=' ) {
        temp.text += input[row][column] ;
        temp.type = "ME" ;
        if ( column < input[row].size() ) column += 1 ;        
      } // else if

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '*' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 2 ;
      temp.type = "*" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      if ( column < input[row].size() && input[row][column] == '=' ) {
        temp.text += input[row][column] ;
        temp.type = "TE" ;
        if ( column < input[row].size() ) column += 1 ;        
      } // else if

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '/' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 2 ;
      temp.type = "/" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      if ( column < input[row].size() && input[row][column] == '=' ) {
        temp.text += input[row][column] ;
        temp.type = "DE" ;
        if ( column < input[row].size() ) column += 1 ;        
      } // else if

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '%' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 2 ;
      temp.type = "%" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      if ( column < input[row].size() && input[row][column] == '=' ) {
        temp.text += input[row][column] ;
        temp.type = "RE" ;
        if ( column < input[row].size() ) column += 1 ;        
      } // else if

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '^' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.precedence = 2 ;
      temp.type = "^" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  


    else if ( input[row][column] == '=' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "=" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;
      if ( input[row][column] == '=' ) {
        temp.type = "EQ" ;
        temp.text += input[row][column] ;
        column++ ;
      } // if

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == ';' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = ";" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == ',' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "," ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '?' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "?" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '&' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "&" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;
      if ( input[row][column] == '&' ) {
        temp.type = "AND" ;
        temp.text += input[row][column] ;
        column++ ;
      } // if

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '|' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "|" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;
      if ( input[row][column] == '|' ) {
        temp.type = "OR" ;
        temp.text += input[row][column] ;
        column++ ;
      } // if

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

    else if ( input[row][column] == '[' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "[" ;
      temp.precedence = 0 ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // else if  

    else if ( input[row][column] == ']' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "]" ;
      temp.precedence = 0 ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // else if  

    else if ( input[row][column] == '{' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "{" ;
      temp.precedence = 0 ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '}' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "}" ;
      temp.precedence = 0 ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) column += 1 ;

      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '>' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = ">" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) {
        column += 1 ;
        if ( input[row][column] == '=' ) {
          temp.type = "GE" ;
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // if

        else if ( input[row][column] == '>' ) {
          temp.type = "RS" ;
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // else if

      } // if
  
      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '<' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "<" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) {
        column += 1 ;
        if ( input[row][column] == '=' ) {
          temp.type = "LE" ;
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // if

        else if ( input[row][column] == '<' ) {
          temp.type = "LS" ;
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // else if

      } // if
  
      gword.push_back( temp ) ;
    } // if  

    else if ( input[row][column] == '!' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = "!" ;
      temp.text += input[row][column] ;
      if ( column < input[row].size() ) {
        column += 1 ;
        if ( input[row][column] == '=' ) {
          temp.type = "NEQ" ;
          temp.text += input[row][column] ;
          if ( column < input[row].size() ) column += 1 ;
        } // if

      } // if
  
      gword.push_back( temp ) ;
    } // if  


    else if ( input[row][column] == ':' ) { 
      temp.firstcolumn = column ;
      temp.firstrow = row ;
      temp.type = ":" ;
      temp.text += input[row][column] ;
      column++ ;

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

    Skipwhitespace( row, column, input ) ;
    
  } // while
  
} // Gettoken()

bool Unsigned_unary_exp( int & i ) {
  if ( gword[i].type == "IDENT" ) {
    if ( !Checkdefine( gword[i].text ) ) throw ( i ) ;
    i++ ;
    if ( gword[i].text == "(" ) {
      i++ ;
      if ( Actual_parameter_list( i ) ) {

      } // if

      if ( gword[i].text == ")" ) {
        i++ ;
      } // if

      else {
        return false ;
      } // else

    } // if

    else if ( gword[i].text == "[" ) {
      i++ ;
      if ( Expression( i ) ) {
        if ( gword[i].text == "]" ) {
          i++ ;
          if ( gword[i].type == "PP" || gword[i].type == "MM" ) {
            i++ ;
          } // if

        } // if

        else {
          return false ;
        } // else

      } // if

      else {
        return false ;
      } // else

    } // else if

    else if ( gword[i].type == "PP" || gword[i].type == "MM" ) {
      i++ ;
    } // else if

  } // if

  else if ( gword[i].type == "CINT" || gword[i].type == "CCHAR" ||
            gword[i].type == "CSTRING" || gword[i].type == "CFLOAT" || 
            gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
    i++ ;    
  } // else if

  else if ( gword[i].text == "(" ) {
    i++ ;
    if ( Expression( i ) ) {
      if ( gword[i].text == ")" ) {
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

} // Unsigned_unary_exp()

bool Signed_unary_exp( int & i ) {
  if ( gword[i].type == "IDENT" ) {
    if ( !Checkdefine( gword[i].text ) ) throw ( i ) ;
    i++ ;
    if ( gword[i].text == "(" ) {
      i++ ;
      if ( Actual_parameter_list( i ) ) {

      } // if

      if ( gword[i].text == ")" ) {
        i++ ;
      } // if

      else {
        return false ;
      } // else

    } // if

    else if ( gword[i].text == "[" ) {
      i++ ;
      if ( Expression( i ) ) {
        if ( gword[i].text == "]" ) {
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

  } // if

  else if ( gword[i].type == "CINT" || gword[i].type == "CCHAR" || 
            gword[i].type == "CSTRING" || gword[i].type == "CFLOAT" || 
            gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
    i++ ;    
  } // else if

  else if ( gword[i].text == "(" ) {
    i++ ;
    if ( Expression( i ) ) {
      if ( gword[i].text == ")" ) {
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

} // Signed_unary_exp()

bool Unary_exp( int & i ) {
  if ( Sign( i ) ) {
    while ( Sign( i ) ) {

    } // while

    if ( Signed_unary_exp( i ) ) {

    } // if

    else {
      return false ;
    } // else

  } // if

  else if ( Unsigned_unary_exp( i ) ) {

  } // else if

  else if ( gword[i].type == "PP" || gword[i].type == "MM" ) {
    i++ ;
    if ( gword[i].type == "IDENT" ) {
      if ( !Checkdefine( gword[i].text ) ) throw ( i ) ;
      i++ ;
      if ( gword[i].text == "[" ) {
        i++ ;
        if ( Expression( i ) ) {
          if ( gword[i].text == "]" ) {
            i++ ;
          } // if

          else {
            return false ;
          } // else

        } // if

        else {
          return false ;
        } // else

      } // if

    } // if

    else {
      return false ;
    } // else

  } // else if

  else {
    return false ; 
  } // else

  return true ;

} // Unary_exp()

bool Rest_of_maybe_mult_exp( int & i ) {
  while ( gword[i].text == "*" || gword[i].text == "/" || gword[i].text == "%" ) {
    i++ ;
    if ( Unary_exp( i ) ) {

    } // if

    else {
      return false ;
    } // else

  } // while

  return true ;

} // Rest_of_maybe_mult_exp()

bool Maybe_mult_exp( int & i ) {
  if ( Unary_exp( i ) ) {
    if ( Rest_of_maybe_mult_exp( i ) ) {

    } // if

    else {
      return false ;
    } // else

  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_mult_exp()

bool Rest_of_maybe_additive_exp( int & i ) {
  if ( Rest_of_maybe_mult_exp( i ) ) {
    while ( gword[i].text == "+" || gword[i].text == "-" ) {
      i++ ;
      if ( Maybe_mult_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_additive_exp()

bool Maybe_additive_exp( int & i ) {
  if ( Maybe_mult_exp( i ) ) {
    while ( gword[i].text == "+" || gword[i].text == "-" ) {
      i++ ;
      if ( Maybe_mult_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_additive_exp()

bool Rest_of_maybe_shift_exp( int & i ) {
  if ( Rest_of_maybe_additive_exp( i ) ) {
    while ( gword[i].type == "LS" || gword[i].type == "RS" ) {
      i++ ;
      if ( Maybe_additive_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_shift_exp()

bool Maybe_shift_exp( int & i ) {
  if ( Maybe_additive_exp( i ) ) {
    while ( gword[i].type == "LS" || gword[i].type == "RS" ) {
      i++ ;
      if ( Maybe_additive_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_shift_exp()

bool Rest_of_maybe_relational_exp( int & i ) {
  if ( Rest_of_maybe_shift_exp( i ) ) {
    while ( gword[i].type == "LE" || gword[i].type == "GE" || 
            gword[i].text == ">" || gword[i].text == "<" ) {
      i++ ;
      if ( Maybe_shift_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_relational_exp()

bool Maybe_relational_exp( int & i ) {
  if ( Maybe_shift_exp( i ) ) {
    while ( gword[i].type == "LE" || gword[i].type == "GE" || 
            gword[i].text == ">" || gword[i].text == "<" ) {
      i++ ;
      if ( Maybe_shift_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_relational_exp()

bool Rest_of_maybe_equality_exp( int & i ) {
  if ( Rest_of_maybe_relational_exp( i ) ) {
    while ( gword[i].type == "EQ" || gword[i].type == "NEQ" ) {
      i++ ;
      if ( Maybe_relational_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_equality_exp()

bool Maybe_equality_exp( int & i ) {
  if ( Maybe_relational_exp( i ) ) {
    while ( gword[i].type == "EQ" || gword[i].type == "NEQ" ) {
      i++ ;
      if ( Maybe_relational_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_equality_exp()

bool Rest_of_maybe_bit_AND_exp( int & i ) {
  if ( Rest_of_maybe_equality_exp( i ) ) {
    while ( gword[i].text == "&" ) {
      i++ ;
      if ( Maybe_equality_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_bit_AND_exp()

bool Maybe_bit_AND_exp( int & i ) {
  if ( Maybe_equality_exp( i ) ) {
    while ( gword[i].text == "&" ) {
      i++ ;
      if ( Maybe_equality_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_bit_AND_exp()

bool Rest_of_maybe_bit_ex_OR_exp( int & i ) {
  if ( Rest_of_maybe_bit_AND_exp( i ) ) {
    while ( gword[i].text == "^" ) {
      i++ ;
      if ( Maybe_bit_AND_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_bit_ex_OR_exp()

bool Maybe_bit_ex_OR_exp( int & i ) {
  if ( Maybe_bit_AND_exp( i ) ) {
    while ( gword[i].text == "^" ) {
      i++ ;
      if ( Maybe_bit_AND_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_bit_ex_OR_exp()

bool Rest_of_maybe_bit_OR_exp( int & i ) {
  if ( Rest_of_maybe_bit_ex_OR_exp( i ) ) {
    while ( gword[i].text == "|" ) {
      i++ ;
      if ( Maybe_bit_ex_OR_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_bit_OR_exp()


bool Maybe_bit_OR_exp( int & i ) {
  if ( Maybe_bit_ex_OR_exp( i ) ) {
    while ( gword[i].text == "|" ) {
      i++ ;
      if ( Maybe_bit_ex_OR_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_bit_OR_exp()

bool Rest_of_maybe_logical_AND_exp( int & i ) {
  if ( Rest_of_maybe_bit_OR_exp( i ) ) {
    while ( gword[i].type == "AND" ) {
      i++ ;
      if ( Maybe_bit_OR_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_maybe_logical_AND_exp()

bool Maybe_logical_AND_exp( int & i ) {
  if ( Maybe_bit_OR_exp( i ) ) {
    while ( gword[i].type == "AND" ) {
      i++ ;
      if ( Maybe_bit_OR_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else

  return true ;

} // Maybe_logical_AND_exp()

bool Rest_of_maybe_logical_OR_exp( int & i ) {
  if ( Rest_of_maybe_logical_AND_exp( i ) ) {
    while ( gword[i].type == "OR" ) {
      i++ ;
      if ( Maybe_logical_AND_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while

  } // if

  else {
    return false ; 
  } // else

  return true ;

} // Rest_of_maybe_logical_OR_exp()

bool Romce_and_romloe( int & i ) {
  if ( Rest_of_maybe_logical_OR_exp( i ) ) {
    if ( gword[i].text == "?" ) {
      i++ ;
      if ( Basic_expression( i ) ) {
        if ( gword[i].text == ":" ) {
          i++ ;
          if ( Basic_expression( i ) ) {

          } // if

          else {
            return false ;
          } // else

        } // if

        else {
          return false ;
        } // else

      } // if

      else {
        return false ;
      } // else

    } // if

  } // if

  else {
    return false ;
  } // else

  return true ;


} // Romce_and_romloe()

bool Assignment_operator( int & i ) {
  if ( gword[i].text == "=" ) {
    i++ ;
  } // if

  else if ( gword[i].type == "TE" ) {
    i++ ;
  } // else if

  else if ( gword[i].type == "DE" ) {
    i++ ;
  } // else if
  else if ( gword[i].type == "RE" ) {
    i++ ;
  } // else if
  else if ( gword[i].type == "PE" ) {
    i++ ;
  } // else if
  else if ( gword[i].type == "ME" ) {
    i++ ;
  } // else if

  else {
    return false ;
  } // else

  return true ;

} // Assignment_operator()

bool Actual_parameter_list( int & i ) {
  if ( Basic_expression( i ) ) {
    while ( gword[i].text == "," ) {
      i++ ;
      if ( Basic_expression( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while

  } // if

  else {
    return false ;
  } // else

  return true ;

} // Actual_parameter_list()

bool Sign( int & i ) {
  if ( gword[i].text == "+" ) {
    i++ ;
  } // if

  else if ( gword[i].text == "-" ) {
    i++ ;
  } // else if

  else if ( gword[i].text == "!" ) {
    i++ ;
  } // else if

  else {
    return false ;
  } // else

  return true ;

} // Sign()


bool Rest_of_PPMM_Identifier_started_basic_exp( int & i ) {
  if ( gword[i].text == "[" ) {
    i++ ;
    if ( Expression( i ) ) {
      if ( gword[i].text == "]" ) {
        i++ ;
      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else

  } // if

  if ( Romce_and_romloe( i ) ) {

  } // if

  else {
    return false ;
  } // else 

  return true ;

} // Rest_of_PPMM_Identifier_started_basic_exp()

bool Rest_of_Identifier_started_basic_exp( int & i ) {
  if ( gword[i].text == "(" ) {
    i++ ;
    if ( Actual_parameter_list( i ) ) {

    } // if

    if ( gword[i].text == ")" ) {
      i++ ;
      if ( Romce_and_romloe( i ) ) {

      } // if

      else {
        return false ;
      } // else
    } // if

    else {
      return false ;
    } // else

    return true ;

  } // if

  else if ( gword[i].text == "[" ) {
    i++ ;
    if ( Expression( i ) ) {
      if ( gword[i].text == "]" ) {
        i++ ;
        if ( Assignment_operator( i ) ) {
          if ( Basic_expression( i ) ) {

          } // if

          else {
            return false ;
          } // else

        } // if

        else if ( gword[i].type == "PP" || gword[i].type == "MM" ) {
          i++ ;
          if ( Romce_and_romloe( i ) ) {

          } // if

          else {
            return false ;
          } // else

        } // else if

        else if ( Romce_and_romloe( i ) ) {

        } // else if

        else {
          return false ;
        } // else

      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( Assignment_operator( i ) ) {
    if ( Basic_expression( i ) ) {

    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( gword[i].type == "PP" || gword[i].type == "MM" ) {
    i++ ;
    if ( Romce_and_romloe( i ) ) {

    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( Romce_and_romloe( i ) ) {

  } // else if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_Identifier_started_basic_exp()


bool Basic_expression( int & i ) {
  if ( gword[i].type == "IDENT" ) {
    if ( !Checkdefine( gword[i].text ) ) throw ( i ) ;
    i++ ;
    if ( Rest_of_Identifier_started_basic_exp( i ) ) {

    } // if

    else {
      return false ;
    } // else

  } // if

  else if ( gword[i].type == "PP" || gword[i].type == "MM" ) {
    i++ ;
    if ( gword[i].type == "IDENT" ) {
      if ( !Checkdefine( gword[i].text ) ) throw ( i ) ;
      i++ ;
      if ( Rest_of_PPMM_Identifier_started_basic_exp( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else
    
  } // else if

  else if ( Sign( i ) ) {
    while ( Sign( i ) ) {

    } // while

    if ( Signed_unary_exp( i ) ) {
      if (  Romce_and_romloe( i ) ) {

      } // if

      else {
        return false; 
      } // else

    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( ( gword[i].type == "CINT" || gword[i].type == "CFLOAT" || gword[i].type == "CCHAR" || 
              gword[i].type == "CSTRING" || gword[i].type == "CTRUE" || gword[i].type == "CFALSE" )
            || gword[i].text == "("  ) {
    if ( gword[i].type == "CINT" || gword[i].type == "CFLOAT" ||  gword[i].type == "CCHAR" ||  
         gword[i].type == "CSTRING" || gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
      i++ ;
      if ( Romce_and_romloe( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // if

    else if ( gword[i].text == "(" ) {
      i++ ;
      if ( Expression( i ) ) {
        if ( gword[i].text == ")" ) {
          i++ ;
          if ( Romce_and_romloe( i ) ) {

          } // if

          else {
            return false ;
          } // else

        } // if

        else {
          return false ;
        } // else

      } // if

      else {
        return false ;
      } // else

    } // else if

  } // else if

  else {
    return false ;
  } // else

  return true ;

} // Basic_expression()

bool Expression( int & i ) {
  if ( Basic_expression( i ) ) {
    while ( gword[i].text == "," ) {
      i++ ;
      if ( Basic_expression( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // while


  } // if

  else {
    return false ;
  } // else


  return true ;

} // Expression()

bool Statement( int & i ) {
  if ( gword[i].text == ";" ) {
    i++ ;
  } // if

  else if ( Expression( i ) ) {
    if ( gword[i].text == ";" ) {
      i++ ;
    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( gword[i].type == "RETURN" ) {
    i++ ;
    if ( Expression( i ) ) {

    } // if

    if ( gword[i].text == ";" ) {
      i++ ;
 
    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( Compound_statement( i ) ) {

  } // else if 

  else if ( gword[i].type == "IF" ) {
    i++ ;
    if ( gword[i].text == "(" ) {
      i++ ;
      if ( Expression( i ) ) {
        if ( gword[i].text == ")" ) {
          i++ ;
          if ( Statement( i ) ) {

          } // if

          else {
            return false ;
          } // else

        } // if

        else {
          return false ;
        } // else

      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else

    if ( gword[i].type == "ELSE" ) {
      i++ ;
      if ( Statement( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // if

  } // else if

  else if ( gword[i].type == "WHILE" ) {
    i++ ;
    if ( gword[i].text == "(" ) {
      i++ ;
      if ( Expression( i ) ) {
        if ( gword[i].text == ")" ) {
          i++ ;
          if ( Statement( i ) ) {

          } // if

          else {
            return false ;
          } // else

        } // if

        else {
          return false ;
        } // else

      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else

  } // else if

  else if ( gword[i].type == "DO" ) {
    i++ ;
    if ( Statement( i ) ) {
      if ( gword[i].type == "WHILE" ) {
        i++ ;
        if ( gword[i].text == "(" ) {
          i++ ;
          if ( Expression( i ) ) {
            if ( gword[i].text == ")" ) {
              i++ ;
              if ( gword[i].text == ";" ) {
                i++ ;
              } // if

              else {
                return false ;
              } // else

            } // if

            else {
              return false ;
            } // else

          } // if

          else {
            return false;
          } // else

        } // if

        else {
          return false ;
        } // else

      } // if
      
      else {
        return false;
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

} // Statement()

bool Declaration( int & i ) {

  if ( Type_specifier( i ) ) {
    if ( gword[i].type == "IDENT" ) {
      i++ ;
      if ( Rest_of_declarators( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else

  } // if

  else {
    return false ;
  } // else

  return true ;

} // Declaration()

bool Compound_statement( int & i ) {
  Vari v2 ;
  v2.list.clear() ;
  int step = 0 ;

  if ( gword[i].text == "{" ) {
    gvaritable.push_back( v2 ) ;
    i++ ;
    step = i ;
    while ( Declaration( i ) || ( ( i == step ) && Statement( i ) ) ) {
      step = i ;
    } // while

    if ( step != i ) return false ;

    if ( gword[i].text == "}" ) {
      gvaritable.pop_back() ;
      i++ ;
    } // if

    else {
      return false ;
    } // else

  } // if


  else {
    return false ;
  } // else

  return true ;

} // Compound_statement()

bool Formal_parameter_list( int & i ) {
  Varidata vd1 ;
  vd1.name = "" ;
  vd1.type = "" ;
  vd1.vindex = "" ;
  Vari v1 ;
  v1.list.clear() ;
  gvaritable.push_back( v1 ) ;


  if ( Type_specifier( i ) ) {
    vd1.type = gword[i-1].text ;
    if ( gword[i].text == "&" ) {
      i++ ;
    } // if

    if ( gword[i].type == "IDENT" ) {
      vd1.name = gword[i].text ;
      i++ ;
      if ( gword[i].text == "[" ) {
        vd1.vindex = gword[i+1].text ;
        i++ ;
        if ( gword[i].type == "CINT" || gword[i].type == "CFLOAT" || gword[i].type == "CCHAR" || 
             gword[i].type == "CSTRING" || gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
          i++ ;
          if ( gword[i].text == "]" ) {
            i++ ;
          } // if
          else {
            return false ;
          } // else
        } // if

        else {
          return false ;
        } // else

      } // if
      
    } // if

    else {
      return false ;
    } // else

    gvaritable[gvaritable.size()-1].list.push_back( vd1 ) ;

    while ( gword[i].text == "," ) {
      i++ ;
      if ( Type_specifier( i ) ) {
        vd1.type = gword[i-1].text ;
        if ( gword[i].text == "&" ) {
          i++ ;
        } // if

        if ( gword[i].type == "IDENT" ) {
          vd1.name = gword[i].text ;
          i++ ;
          if ( gword[i].text == "[" ) {
            vd1.vindex = gword[i+1].text ;
            i++ ;
            if ( gword[i].type == "CINT" || gword[i].type == "CFLOAT" || gword[i].type == "CCHAR" || 
                 gword[i].type == "CSTRING" || gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
              i++ ;
              if ( gword[i].text == "]" ) {
                i++ ;
              } // if
              else {
                return false ;
              } // else
            } // if

            else {
              return false ;
            } // else 

          } // if
      
        } // if
 
        else {
          return false ;
        } // else
      } // if

      else {
        return false ;
      } // else

      gvaritable[gvaritable.size()-1].list.push_back( vd1 ) ;

    } // while

  } // if

  else {
    return false ;
  } // else



  return true ;

} // Formal_parameter_list()


bool Function_definition_without_ID( int & i ) {
  if ( gword[i].text == "(" ) { 
    i++ ;
    if ( gword[i].type == "VOID" ) {
      i++ ;
    } // if

    else if ( Formal_parameter_list( i ) ) {

    } // else if

    if ( gword[i].text == ")" ) {
      i++ ;
      if ( Compound_statement( i ) ) {

      } // if

      else {
        return false ;
      } // else

    } // if

    else {
      return false ;
    } // else

  } // if

  else {
    return false ;
  } // else


  return true ;

} // Function_definition_without_ID()


bool Rest_of_declarators( int & i ) {
  if ( gvaritable.size() > 1 ) {
    Varidata v3 ;
    v3.name = gword[i-1].text ;
    v3.type = gword[i-2].text ;
    v3.vindex = "" ;
    int step = i ;
    if ( gword[step].text == "[" ) {
      step++ ;
      if ( gword[step].type == "CINT" || gword[step].type == "CFLOAT" || gword[step].type == "CCHAR" || 
           gword[step].type == "CSTRING" || gword[step].type == "CTRUE" || 
           gword[step].type == "CFALSE" ) {
        v3.vindex = gword[step].text ;
        step++ ;
        if ( gword[step].text == "]" ) step++ ;
      } // if
    } // if

    gvaritable[gvaritable.size()-1].list.push_back( v3 ) ;

    while ( gword[step].text == "," ) {
      step++ ;
      if ( gword[step].type == "IDENT" ) {
        v3.name = gword[step].text ;
        if ( gword[step].text == "[" ) {
          step++ ;
          if ( gword[step].type == "CINT" || gword[step].type == "CFLOAT" || gword[step].type == "CCHAR" || 
               gword[step].type == "CSTRING" || gword[step].type == "CTRUE" || 
               gword[step].type == "CFALSE" ) {
            step++ ;
            if ( gword[step].text == "]" ) step++ ;
          } // if
        } // if

      } // if

      gvaritable[gvaritable.size()-1].list.push_back( v3 ) ;

    } // while

    

  } // if

  if ( gword[i].text == "[" ) {
    i++ ;
    if ( gword[i].type == "CINT" || gword[i].type == "CFLOAT" || gword[i].type == "CCHAR" || 
         gword[i].type == "CSTRING" || gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
      i++ ;
      if ( gword[i].text == "]" ) {
        i++ ;
      } // if
      else {
        return false ;
      } // else
    } // if

    else {
      return false ;
    } // else

  } // if

  while ( gword[i].text == "," ) {
    i++ ;
    if ( gword[i].type == "IDENT" ) {
      i++ ;
      if ( gword[i].text == "[" ) {
        i++ ;
        if ( gword[i].type == "CINT" || gword[i].type == "CFLOAT" || 
             gword[i].type == "CCHAR" || gword[i].type == "CSTRING" || 
             gword[i].type == "CTRUE" || gword[i].type == "CFALSE" ) {
          i++ ;
          if ( gword[i].text == "]" ) {
            i++ ;
          } // if
          else {
            return false ;
          } // else
        } // if

        else {
          return false ;
        } // else

      } // if

    } // if

    else {
      return false ;
    } // else

  } // while

  if ( gword[i].text == ";" ) {
    i++ ;
  } // if

  else {
    return false ;
  } // else

  return true ;

} // Rest_of_declarators()

bool Function_definition_or_declarators( int & i ) {

  if ( Function_definition_without_ID( i ) ) {

  } // if

  else if ( Rest_of_declarators( i ) ) {

  } // else if

  else {
    return false ;
  } // else

  return true ;

} // Function_definition_or_declarators()


bool Type_specifier( int & i ) {
  if ( gword[i].type == "INT" || gword[i].type == "CHAR" || gword[i].type == "FLOAT" || 
       gword[i].type == "STRING" || gword[i].type == "BOOL" ) {
    i++ ;
    return true ;
  } // if

  return false ;
} // Type_specifier()



bool Definition( int & i ) {
  if ( gword[i].type == "VOID" ) {
    i++ ;
    if ( gword[i].type == "IDENT" ) {
      i++ ;
      if ( Function_definition_without_ID( i ) ) {

      } // if

      else {
        return false ;
      } // else
    } // if

    else {
      return false ;
    } // else

  } // if

  else if ( Type_specifier( i ) ) {
    if ( gword[i].type == "IDENT" ) {
      i++ ;
      if ( Function_definition_or_declarators( i ) ) {

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
} // Definition()

bool Checkdefine( string str ) {
  
  for ( int j = 0 ; j < gfivefunc.size() ; j++ ) {
    if ( gfivefunc[j] == str ) return true ;
  } // for

  for ( int i = gvaritable.size()-1 ; i >= 0 ; i-- ) {
    for ( int j = 0 ; j < gvaritable[i].list.size() ; j++ ) {
      if ( str == gvaritable[i].list[j].name ) {
        return true ;
      } // if

    } // for

  } // for
  
  for ( int c = 0 ; c < gfunctable.size() ; c++ ) {
    if ( gfunctable[c].name == str ) return true ;
  } // for

  return false ;

} // Checkdefine()

bool Redefine_vari( string str ) {
  for ( int i = gvaritable.size()-1 ; i >= 0 ; i-- ) {
    for ( int j = 0 ; j < gvaritable[i].list.size() ; j++ ) {
      if ( str == gvaritable[i].list[j].name ) {
        gvaritable[i].list.erase( gvaritable[i].list.begin() + j ) ;
        return true ;
      } // if

    } // for

  } // for

  return false ;

} // Redefine_vari()

bool Redefine_func( string str ) {
  for ( int i = 0 ; i < gfunctable.size() ; i++ ) {
    if ( str == gfunctable[i].name ) {
      gfunctable.erase( gfunctable.begin() + i ) ;
      return true ;
    } // if

  } // for

  return false ;

} // Redefine_func()

void Error1( int & i, int start ) {
  int line = 0 ;
  if ( start == 0 ) line = gword[i].firstrow + 1 ;
  else line = gword[i].firstrow - gword[start-1].firstrow ;
  if ( gword[i].type == "ERROR1" ) {
    cout << "Line " << line << " : unrecognized token with first char : '" << gword[i].text << "'" << endl ;
  } // if 

  else {
    cout << "Line " << line << " : unexpected token : '" << gword[i].text << "'" << endl ;
  } // else 

} // Error1()

void ListAllVariables() {
  Varidata vd ;
  for ( int i = 0 ; i < gvaritable[0].list.size()-1 ; i++ ) {
    for ( int j = i+1 ; j < gvaritable[0].list.size() ; j++ ) {
      if (  gvaritable[0].list[i].name > gvaritable[0].list[j].name ) {
        vd.name = gvaritable[0].list[i].name ;
        vd.type = gvaritable[0].list[i].type ;
        vd.vindex = gvaritable[0].list[i].vindex ;
        gvaritable[0].list[i].name = gvaritable[0].list[j].name ;
        gvaritable[0].list[i].type = gvaritable[0].list[j].type ;
        gvaritable[0].list[i].vindex = gvaritable[0].list[j].vindex ;
        gvaritable[0].list[j].name = vd.name ;
        gvaritable[0].list[j].type = vd.type ;
        gvaritable[0].list[j].vindex = vd.vindex ;

      } // if

    } // for

  } // for

  for ( int k = 0 ; k < gvaritable[0].list.size() ; k++ ) {
    cout << gvaritable[0].list[k].name  << endl ;
  } // for

} // ListAllVariables()

void ListAllFunctions() {
  string f = "" ;

  vector<string> store ;
  for ( int a = 0 ; a <  gfunctable.size() ; a++ ) {
    store.push_back( gfunctable[a].name ) ;
  } // for
  
  for ( int i = 0 ; i < store.size()-1 ; i++ ) {
    for ( int j = i+1 ; j < store.size() ; j++ ) {
      if ( store[i] > store[j] ) {
        f = store[i] ;
        store[i] = store[j] ;
        store[j] = f ;
      } // if

    } // for

  } // for

  for ( int k = 0 ; k < store.size() ; k++ ) {
    cout << store[k] << "()" << endl ;
  } // for


} // ListAllFunctions() 

void ListVariable( string str ) {
  for ( int a = 0 ; a < gvaritable[0].list.size() ; a++ ) {
    if ( gvaritable[0].list[a].name == str ) {
      cout << gvaritable[0].list[a].type << " " << gvaritable[0].list[a].name  ;
      if ( gvaritable[0].list[a].vindex != "" ) cout << "[ " << gvaritable[0].list[a].vindex << " ]" ;
      cout << " ;" << endl;
      return ;
    } // if

  } // for

} // ListVariable()

void ListFunction( string str ) {
  bool find = false ;
  int s = 0 ;
  for ( int i = 0 ; i < gfunctable.size() && find == false ; i++ ) {
    if ( str == gfunctable[i].word[1] ) {
      s = i ;
      find = true ;
    } // if
  } // for

  cout << gfunctable[s].t[0].text << " " ;

  int j = 1 ;
  int space = 0 ;





  while ( j < gfunctable[s].t.size() - 1 ) {
    if ( gfunctable[s].t[j].type == "IDENT" ) {
      cout << gfunctable[s].t[j].text ;
      j++ ;
      if ( gfunctable[s].t[j].text == "(" || gfunctable[s].t[j].text == "++" || 
           gfunctable[s].t[j].text == "--" || gfunctable[s].t[j].text == "[" ) {
        cout << gfunctable[s].t[j].text << " " ;
        j++ ;
      } // if

      else {
        cout << " " ;
      } // else

    } // if

    else if ( gfunctable[s].t[j].text == ";" ) {
      if ( gfunctable[s].t[j+1].text == "}" ) space -= 2 ;
      cout <<  gfunctable[s].t[j].text << endl ;

      if ( space > 0 ) {
        for ( int p = space ; p > 0 ; p-- ) {
          cout << " " ;
        } // for

      } // if



      j++ ;
    } // else if

    else if ( gfunctable[s].t[j].text == "{" ) {
      space += 2 ;
      if ( gfunctable[s].t[j+1].text == "}" ) space -= 2 ;

      cout <<  gfunctable[s].t[j].text << endl ;
      if ( space > 0 ) {
        for ( int p = space ; p > 0 ; p-- ) {
          cout << " " ;
        } // for

      } // if



      j++ ;
    } // else if


    else if ( gfunctable[s].t[j].text == "}" ) {
      if ( gfunctable[s].t[j+1].text == "}" ) space -= 2 ;
      cout <<  gfunctable[s].t[j].text ;
      if ( j < gfunctable[s].t.size() ) cout << endl ;
      if ( space > 0 ) {
        for ( int p = space ; p > 0 ; p-- ) {
          cout << " " ;
        } // for

      } // if

      j++ ;
    } // else if

    else {
      cout << gfunctable[s].t[j].text << " " ;
      j++ ;
    } // else

  } // while

  cout << "}" << endl ;

} // ListFunction()

void User_input() {
  bool done = false ;
  gfunctable.clear() ;
  gvaritable.clear() ;
  int i = 0 ;
  int start = 0 ;
  int step = 0 ;
  int r = 0 ;
  Func ftemp ;
  Vari vtemp ;
  Varidata vdtemp ;
  vtemp.list.clear() ;
  gvaritable.push_back( vtemp ) ;
  vdtemp.name = "" ;
  vdtemp.type = "" ;
  vdtemp.vindex = "" ;

  Token t ;
  string str ;
  str = "Done" ;
  gfivefunc.push_back( str ) ;
  str = "ListAllVariables" ;
  gfivefunc.push_back( str ) ;
  str = "ListAllFunctions" ;
  gfivefunc.push_back( str ) ;
  str = "ListVariable" ;
  gfivefunc.push_back( str ) ;
  str = "ListFunction" ;
  gfivefunc.push_back( str ) ;
  str = "cin" ;
  gfivefunc.push_back( str ) ;
  str = "cout" ;
  gfivefunc.push_back( str ) ;

  cout << "Our-C running ..." << endl ;
  while ( i < gword.size() && done == false ) {
    cout << "> " ;
    start = i ;
    step = i ;
    try {
      if ( Definition( i ) ) { // 是定義嗎?
        if ( gword[start+2].text == "(" ) { // 是 且第三個字是'(' 是func定義  
          ftemp.name =  gword[start+1].text ; // 名稱
          while ( start < i ) {
            str = gword[start].text ;
            t.type = gword[start].type ;
            t.text = gword[start].text ;
            ftemp.t.push_back( t ) ;
            ftemp.word.push_back( str ) ;
            start++ ;
          } // while

          if ( Redefine_func( ftemp.name ) ) {
            cout << "New definition of " << ftemp.name << "() entered ..." << endl ;
          } // if

          else {
            cout << "Definition of " << ftemp.name << "() entered ..." << endl ;
          } // else

          gfunctable.push_back( ftemp ) ;
        } // if

        else { // 是 且是變數定義
          vdtemp.type = gword[start].text ;
          while ( start < i ) {
            if ( gword[start].type == "IDENT" ) {
              vdtemp.name = gword[start].text ;
              if ( gword[start+1].text == "[" ) {
                vdtemp.vindex = gword[start+2].text ;
                start = start + 4 ;
              } // if

              if ( Redefine_vari( vdtemp.name ) ) {
                cout << "New definition of " << vdtemp.name << " entered ..." << endl ;
              } // if

              else {
                cout << "Definition of " << vdtemp.name << " entered ..." << endl ;
              } // else

              gvaritable[0].list.push_back( vdtemp ) ; 
            } // if

            vdtemp.name = "" ;
            vdtemp.vindex = "" ;
            start++ ;             
          } // while

        } // else

      } // if 


      else if ( i == start && Statement( i ) ) {
        if ( gword[start].text == "Done" ) {
          done = true ;
        } // if

        else if ( gword[start].text == "ListAllVariables" ) {
          ListAllVariables() ;
          cout << "Statement executed ..." << endl ;
        } // else if

        else if ( gword[start].text == "ListAllFunctions" ) {
          ListAllFunctions() ;
          cout << "Statement executed ..." << endl ;
        } // else if

        else if ( gword[start].text == "ListVariable" ) {
          ListVariable( gword[start+2].text ) ;
          cout << "Statement executed ..." << endl ;
        } // else if

        else if ( gword[start].text == "ListFunction" ) {
          ListFunction( gword[start+2].text ) ;
          cout << "Statement executed ..." << endl ;
        } // else if

        else {
          cout << "Statement executed ..." << endl ;
        } // else


      } // else if


      else {
        Error1( i, start ) ;
        i++ ;
        while ( i < gword.size() && gword[i].firstrow == gword[i-1].firstrow ) i++ ;
      } // else
    } // try

    catch ( int jump ) {
      int l ;
      if ( start == 0 ) l = gword[jump].firstrow + 1 ;
      else l = gword[jump].firstrow - gword[start-1].firstrow ;
      cout << "Line " << l << " : undefined identifier : '" ; 
      cout << gword[jump].text << "'" << endl ;
      jump++ ;
      while ( jump < gword.size() && gword[jump].firstrow == gword[jump-1].firstrow ) jump++ ;
      i = jump ;
    } // catch

    vdtemp.name = "" ;
    vdtemp.type = "" ;
    vdtemp.vindex = "" ;
    ftemp.name = "" ;
    ftemp.word.clear() ;
    ftemp.t.clear() ;
    
    while ( gvaritable.size() > 1 ) {
      gvaritable.pop_back() ;
    } // while

  } // while
  

  cout << "Our-C exited ..." ;

} // User_input()


int main() {
  vector<string> input ;
  Read( input ) ;
  Gettoken( input ) ;
  User_input() ;
} // main()

