/*
Chris McCracken
CS 4100, Compilers
Fall 2020
Brouillette/Your Majesty
*/

#include <iostream>
#include <fstream>
#include <variant>
#include "Interpreter.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Globals.h"

using namespace std;

int main()
{
	Symbols.AddSymbol("NULL", "NULL", 0);
	Symbols.AddSymbol("PLUS1INDEX", "CONST", 1);
	Symbols.AddSymbol("MINUS1INDEX", "CONST", -1);

	string codeFile = "CS4100FinalProjGOODMinimumFA20.txt";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		 << "OPENING: " << codeFile << endl
		 << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	LexicalAnalyzer::OpenFile(codeFile);
	SyntaxAnalyzer::AnalyzeSyntax(false); // Also does quad generation 

	cout << endl;
	Symbols.PrintSymbolTable();
	Quads.PrintQuadTable();

	Interpreter::InterpretQuads(true);
	//Interpreter::InterpretQuads(false);

	Symbols.PrintSymbolTable();

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		 << "CLOSING: " << codeFile << endl
		 << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	LexicalAnalyzer::CloseFile();
}