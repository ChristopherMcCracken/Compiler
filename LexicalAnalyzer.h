#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>
#include "LexicalAnalyzer.h"
#include "ReserveTable.h"
#include "Globals.h"

using namespace std;

class LexicalAnalyzer
{
public:
	// GetNextToken must be based directly on the DFA state diagram which is to be handed in with the program
	// GetNextToken must print each unmodified input line as it is read from the file, before processing the raw text
	// a) Reading new lines of input as needed, and immediately echo printing them as selected by echoOn
	// b) Recognizing the next token in the input, placing the lexeme in the globally accessible string nextToken
	// c) Determining the corrrect integer tokenCode for the new token, which will be referenced by main, making calls to
	//    lookup reserve words as needed.
	// d) Placing each identifier or numeric constant into the SymbolTable only once, making the entries case-insensitive. 
	//    Identifiers which are reserved words must not be added to the symbol table, but should be identified by finding them 
	//    in a pre - constructed ReservedWord table.Note that within the lexical analyzer program, there should be virtually 
	//    NO INTEGER LITERALS in the code; instead, use named symbolic constants declared in a centrally accessible location.
	// e) Setting a globally accessible boolean variable or function ENDFILE set to TRUE when the input file data is exhausted, 
	//    so that the main program can check this in its loop stop condition.
	// f) GetNextToken must utilize well - designed auxiliary procedures to make it more readable and understandable. At a minimum, 
	//    GetNextChar, SkipBlanks, IsLetter, IsDigit, IsWhitespace functions should be used to make the code clear.
	// GetNextToken should generate a warning messageand take actions for the following non - fatal errors :
	// a) Identifier is longer than 30 characters; print warning messageand truncate.
	// b) Numeric constant is longer than 30 characters; print warningand truncate.
	// c) Unclosed comment(only happens when end of file is reached before comment termination) : print
	//    a warning message, ‘End of file found before comment terminated.’; no other action needed.
	// d) Unterminated string(end of line or end of file reached before a “ was found) : print a warning
	//    message, “Unterminated string found.”
	// e) Invalid character in file; return the character as an undefined token(code 99), with no additional
	//    warning message needed.
	static void OpenFile(string file);
	static void CloseFile();

	static void GetNextToken(bool echoOn);

	static void BuildToken();

	// Print neatly:
	// 1) Lexeme
	// 2) Token Code
	// 3) Table-Looked-Up 4-Character Mnemonic for code (use ReserveTable Instance)
	// 4) For identifiers and literals added to the SymbolTable, the SymbolTable location index of the token
	static void PrintToken();

	static void GetNextLine();

	// g) GetNextChar must always return the next character available, including the start of whitespace, calling functions when needed 
	//    to get the next line of input from the file(via GetNextLine probably, which will handle echoing the line when requested).
	static char GetNextChar();

	static bool IsComment(char nextChar);

	static void HandleComment(char nextChar);

	static bool IsLetter(char nextChar);

	static void HandleLetter(char nextChar);

	static bool IsDigit(char nextChar);

	static void HandleDigit(char nextChar);

	static bool IsWhitespace(char nextChar);

	static void HandleString(char nextChar);

	static void HandleOther(char nextChar, string &nextToken);
};

