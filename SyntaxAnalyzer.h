#pragma once

#include "Globals.h"
#include "LexicalAnalyzer.h"

class SyntaxAnalyzer
{
public:
	static int AnalyzeSyntax(bool verbose);
private:
	// Variables
	static int indent;
	static bool syntaxErrorFlag;

	// Nonterminals
	static int program();
	static int block();
	static int blockBody();
	static int labelDeclaration();
	static int variableDecSec();
	static int variableDeclaration();
	static int statement();
	static int variable();
	static int label();
	static int relExpression();
	static int relOp();
	static int simpleExpression();
	static int addOp();
	static int sign();
	static int term();
	static int mulOp();
	static int factor();
	static int type();
	static int simpleType();
	static int constant();
	static int unsignedConstant();
	static int unsignedNumber();
	static int identifier();
	static int stringConstant();

	// Auxillary
	static void syntaxError(string expected);
	static bool insensitiveCompare(string s1, string s2);
	static void debugParseTree(bool enter, string nonTerminal);
	static void resync();
	static int genSymbol();
	static int relOpToOpcode(int relOp);
};