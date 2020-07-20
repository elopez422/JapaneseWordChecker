#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Eduardo Lopez Aguirre
// RE:((([dwyzj]|[bmkhprgn]y?|ts?|sh?|ch)?[aeiouIE]+n?)
// +(([dwyzj]|[bmkhprg]y?|ts?|sh?|ch)[aeiouIE]+n?)*)+
bool word (string s)
{

  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      if (state == 0 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if ((state == 0|| state == 1) && (s[charpos] == 'd'||s[charpos] == 'w'||
          s[charpos] == 'z'||s[charpos] == 'y'||s[charpos] == 'j')){
        state = 2;}
      else
      if ((state == 0) && (s[charpos] == 'b'||s[charpos] == 'm'||
          s[charpos] == 'k'||s[charpos] == 'n'||s[charpos] == 'h'||
          s[charpos] == 'p'||s[charpos] == 'r'||s[charpos] == 'g')){
        state = 3;}
      else
      if ((state == 0|| state == 1)&& s[charpos] == 't')
        state = 4;
      else
      if ((state == 0|| state == 1) && s[charpos] == 's')
        state = 5;
      else
      if ((state == 0|| state == 1) && s[charpos] == 'c')
        state = 6;
      else
      if ((state == 0|| state == 1)&& s[charpos] == 'n')
        state = 0;
      else
      if (state == 1 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if ((state == 1) && (s[charpos] == 'b'||s[charpos] == 'm'||
          s[charpos] == 'k' ||s[charpos] == 'h'|| s[charpos] == 'p'||
          s[charpos] == 'r'||s[charpos] == 'g')){
          state = 3;}
      else
      if (state == 2 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 3 && s[charpos] == 'y')
        state = 2;
      else
      if (state == 3 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 4 && s[charpos] == 's')
        state = 2;
      else
      if (state == 4 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 5 && s[charpos] == 'h')
        state = 2;
      else
      if (state == 5 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 6 && s[charpos] == 'h')
        state = 2;
      else
        {
          return(false);
        }
      charpos++;
    }//end of while

    // where did I end up????
  if (state == 0)
    return(true);
  else
  if (state == 1)
      return(true); // end in a final state
  else
    return(false);
}// end of wordtoken


// PERIOD DFA
// Done by: Eduardo Lopez Aguirre
bool period (string s)
{

  if(s == ".")
    return true;
  else
    return false;

}


// ------ Three  Tables -------------------------------------

// TABLES Done by: Eduardo Lopez Aguirre

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {WORD1, WORD2, PERIOD, ERROR, VERB, VERBNEG,
                VERBPAST, VERBPASTNEG, IS, WAS, OBJECT,
                SUBJECT, DESTINATION, PRONOUN,
                CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG",
                        "VERBPAST","VERBPASTNEG", "IS", "WAS", "OBJECT",
                        "SUBJECT", "DESTINATION", "PRONOUN",
                         "CONNECTOR", "EOFM"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
string reservedWords[18] = {"masu", "masen", "mashita", "masendeshita", "desu",
                            "deshita", "o", "wa", "ni","watashi", "anata",
                            "kare", "kanojo", "sore", "mata", "soshite",
                            "shikashi", "dakara"};
tokentype reservedType[18] = {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS,
                            WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, PRONOUN,
                            PRONOUN, PRONOUN, PRONOUN, CONNECTOR, CONNECTOR,
                            CONNECTOR,CONNECTOR};

int scanner(tokentype& , string& );  // to be called by main
// ------------ Scaner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Eduardo Lopez Aguirre
int scanner(tokentype& tt, string& w){

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.

  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */
    fin >> w;
    cout << "Scanner called using word: " << w << endl;

    if(w == "eofm")
      tt = EOFM;
    else
    if(word(w)){
      bool reserved = false;
      for(int i = 0; i<18; i++)
      {
        if(w == reservedWords[i])
        {
          tt = reservedType[i];
          reserved = true;
          break;
        }
      }
      if(reserved == false)
      {
        if(w[w.size()-1] == 'I' || w[w.size()-1] == 'E')
          tt = WORD2;
        else
          tt = WORD1;
      }
    }
    else
    if(period(w))
      tt = PERIOD;
    else{
      tt = ERROR; }

    return 0; //Why is return type int??
}//the end of scanner

//----- Prototypes for Parser Story--------------------------------------------
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();
//translator functions
void getEword();
void gen(string);

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

//Parser Globals
//global vars are intialized to 0 (i.e. false for bool) by compiler
tokentype  saved_token;
string saved_lexeme;
string saved_E_word; //for translator
bool token_available;
bool traceFlag;

// Type of error: Syntax error 1 expected a different token
// Done by: Eduardo Lopez Aguirre
void syntaxerror1(tokentype expected, string lexeme){
  cout << "\nSYNTAX ERROR: expected " << tokenName[expected]
       << " but found " << lexeme << endl;
  exit(1);
}
// Type of error: syntax error 2. Unexpected lexeme
// Done by: Eduardo Lopez Aguirre
void syntaxerror2( string lexeme, string parserFunction ) {
  cout << "\nSYNTAX ERROR: unexpected " << lexeme << " found in "
       << parserFunction << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: THe purpose of this function is to check the next token
//          and return the token type
// Done by: Eduardo Lopez Aguirre
tokentype next_token(){

  string lexeme;

	if (token_available == false)
	{
		scanner(saved_token, lexeme);
		if (saved_token == ERROR) {
			cout << "\nLexical Error: " << lexeme << " is not a valid token" << endl;
		}
		token_available = true;
		saved_lexeme = lexeme; //I think I can just pass saved_lexeme by reference to scanner

	}
	return saved_token;    // return the saved token
}

// Purpose: The purpose of this function is to determine whether the next token
//          matched the grammar rule returning true if it does and false
//          if it does not
// Done by: Eduardo Lopez Aguirre
bool match(tokentype expected) {
	if (next_token() != expected)  // mismatch has occurred with the next token
	{ // generate a syntax error message here
	  // do error handling here if any
		syntaxerror1(expected, saved_lexeme);
		return false;
	}
	else  // match has occurred
	{
    if(traceFlag)
		  cout << "Matched " << tokenName[expected] << endl; // say there was a match
		token_available = false;  // eat up the token
		return true;
	}
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// 1 <story> ::= <s> { <s> }
// Done by: Eduardo Lopez Aguirre
void story()
{
  if(traceFlag)
	  cout << "Processing <story>" << endl << endl;
	s();
	while (true)
	{
		switch (next_token()) // look ahead
		{
      case CONNECTOR: s();
			   break;
		  case WORD1: s();
			   break;
		  case PRONOUN: s();
			   break;
		  default:{
        if(traceFlag)
          cout << "\nSuccessfully parsed <story>.\n" << endl;
        return;  // loop stops
      }
		}//end switch
	}//end loop
}


//2 <s>  ::= [CONNECTOR #getEword# #gen(“CONNECTOR”)#] <noun> #getEword# SUBJECT
// #gen(“ACTOR”)# <after subject>
// Done by: Eduardo Lopez Aguirre
void s()
{
  if(traceFlag)
	 cout << "Processing <s>" << endl;
	if(next_token() == CONNECTOR){
		match(saved_token);
    getEword();
    gen("CONNECTOR");
  }

	noun();
  getEword();
	match(SUBJECT);
  gen("ACTOR");
	afterSubject();
}

// 3 <afterSubject> ::= <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)#
// PEROD | <noun> #getEword# <after noun>
// Done by: Eduardo Lopez Aguirre
void afterSubject()
{
  if(traceFlag)
	 cout << "Processing <afterSubject>" << endl;

	switch (next_token())
   {
  	case WORD2: //Verb
  		verb();
      getEword();
      gen("ACTION");
  		tense();
      gen("TENSE");
  		match(PERIOD);
      gen(".");
  		break;

    case WORD1: //Noun
    case PRONOUN: //Pronoun
      noun();
      getEword();
      afterNoun();
      break;

  	default:
  		syntaxerror2(saved_lexeme, "afterSubject");
	 }

}

// 4 <afterNoun> :: = <be> #gen(“DESCRIPTION”)#  #gen(“TENSE”)# PEROD
//| DESTINATION #gen(“TO”)# <verb> #getEword# <tense> #gen(“TENSE”)# PERIOD
//| OBJECT #gen(“OBJECT”)# <after object>
// Done by: Eduardo Lopez Aguirre
void afterNoun()
{
  if(traceFlag)
	 cout << "Processing <afterNoun>" << endl;
	switch (next_token())
	{
	case IS:
	case WAS:
		be();
    gen("DESCRIPTION");
    gen("TENSE");
		match(PERIOD);
    gen(".");
		break;

	case DESTINATION:
		match(DESTINATION);
    gen("TO");
		verb();
    getEword();
		tense();
    gen("TENSE");
		match(PERIOD);
    gen(".");
		break;

	case OBJECT:
		match(OBJECT);
    gen("OBJECT");
		afterObject();
		break;

	default:
		syntaxerror2(saved_lexeme, "afterNoun");
	}
}

// 5 <afterObject> ::= <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)#
//PEROD |<noun> #getEword# DESTINATION #gen(“TO”)# <verb> #getEword#
//#gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD
// Done by: Eduardo Lopez Aguirre
void afterObject()
{
  if(traceFlag)
	 cout << "Processing <afterObject>" << endl;
	switch (next_token())
	{
    case WORD2:
    	verb();
      getEword();
      gen("ACTION");
    	tense();
      gen("TENSE");
    	match(PERIOD);
      gen(".");
    	break;

    case WORD1:
    case PRONOUN:
    	noun();
      getEword();
    	match(DESTINATION);
      gen("TO");
    	verb();
      getEword();
      gen("ACTION");
    	tense();
      gen("TENSE");
    	match(PERIOD);
      gen(".");
    	break;

    default:
    	syntaxerror2(saved_lexeme, "afterObject");
	}
}

// 6 <noun> :: = WORD1 | PRONOUN
// Done by: Eduardo Lopez Aguirre
void noun()
{
  if(traceFlag)
	 cout << "Processing <noun>" << endl;
	switch (next_token())
	{
	case WORD1:
		match(WORD1);
		break;

	case PRONOUN:
		match(PRONOUN);
		break;

	default:
		syntaxerror2(saved_lexeme, "noun");
	}
}

// 7 <verb> ::= WORD2
// Done by: Eduardo Lopez Aguirre
void verb()
{
  if(traceFlag)
	 cout << "Processing <verb>" << endl;
	match(WORD2);
}

// 8 <be> :: = IS | WAS
// Done by: Eduardo Lopez Aguirre
void be()
{
  if(traceFlag)
	 cout << "Processing <be>" << endl;
	switch (next_token())
	{
	case IS:
		match(IS);
		break;

	case WAS:
		match(WAS);
		break;

	default:
		syntaxerror2(saved_lexeme, "be");
	}
}

// 9 <tense> : = VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Eduardo Lopez Aguirre
void tense()
{
  if(traceFlag)
	 cout << "Processing <tense>" << endl;
	switch (next_token())
	{
    case VERBPAST:
		match(VERBPAST);
		break;

	case VERBPASTNEG:
		match(VERBPASTNEG);
		break;

	case VERB:
		match(VERB);
		break;

	case VERBNEG:
		match(VERBNEG);
		break;

	default:
		syntaxerror2(saved_lexeme, "tense");
	}
}

//----------- Parser Utility ---------------------------
//Turns tracing messages on if user enters 'y' by setting tracing flag to true.
//Tracing flag is a global variable which is initialized to 0 or false by the
//compiler so this function sets the flag to true if the user wants traces.
//Done by: Eduardo Lopez Aguirre
void toggleTraces()
{
  char in;
  cout << "Would you like to see traces? Y/n: ";
  cin >> in;
  cout << endl;
  if(toupper(in) == 'Y')
    traceFlag = true;
}


//=================================================
// File translator.cpp written by Group Number: 5
//=================================================
ofstream fout;
// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt
//  Done by: Eduardo Lopez Aguirre
struct lexEntry{
  string japanesWord;
  string englishWord;
};

//Lexicon is an aray of 27 vectors. Each array index coresponds to a letter in
//the alphabet a = 0, z = 26. Vectors at each inex of the array are of type
//lexEntry.A Japanes word that start with "a" and its coresponding english word
// will be located in one of the lexEntrys in the vector at location 0
vector<lexEntry> Lexicon[27];

// Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result
//                 in saved_E_word
//  Done by: Eduardo Lopez Aguirre

void getEword(){
  int lexIndex = saved_lexeme[0] - 'a';
  for(int i = 0; i < Lexicon[lexIndex].size(); i ++)
    if(Lexicon[lexIndex][i].japanesWord == saved_lexeme){
      saved_E_word = Lexicon[lexIndex][i].englishWord;
      return;
    }
  saved_E_word = saved_lexeme;
}


// gen(line_type) - using the line type,sends a line of an IR to translated.txt
//(saved_E_word or saved_token is used)
//  Done by: Lopez Aguirre
void gen(string line_type){
  if(line_type == "."){
        fout << endl;
        return;
  }
  fout << line_type << ": ";
  if(line_type == "TENSE"){
    fout << tokenName[saved_token] << endl;
  }
  else{
    fout << saved_E_word << endl;
  }
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar
//    rule with semantic routine calls
//    above each non-terminal function

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------
// The final test driver to start the translator
// Done by:  Eduardo Lopez Aguirre
int main()
{
  // opens the lexicon.txt file and reads it into Lexicon
  fin.open("lexicon.txt");
  int lexIndex;
  lexEntry entry;
  while(fin >> entry.japanesWord >> entry.englishWord){
    lexIndex = entry.japanesWord[0] - 'a';
    Lexicon[lexIndex].push_back(entry);
  }
  //closes lexicon.txt
  fin.close();


  //opens the output file translated.txt
  fout.open("translated.txt");

  //get input file
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //ask user if they want to see treces
  toggleTraces();
  //calls the <story> to start parsing
  story();
  //closes the input file
  fin.close();
  //** closes traslated.txt
  fout.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
