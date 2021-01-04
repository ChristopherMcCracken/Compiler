#include "SyntaxAnalyzer.h"

int SyntaxAnalyzer::indent = 0;
bool SyntaxAnalyzer::syntaxErrorFlag = false;

int SyntaxAnalyzer::AnalyzeSyntax(bool inVerbose = false)
{
	Verbose = inVerbose;
	LexicalAnalyzer::GetNextToken(Verbose);
	program();
	return 0;
}

// <program> -> $UNIT <identifier> $SEMICOLON <block> $PERIOD
int SyntaxAnalyzer::program()
{
	debugParseTree(true, "Program");
	if (TokenCode != 15)
	{
		syntaxError("UNIT");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	identifier();
	if (NextToken == ";")
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		block();
		if (NextToken == ".")
		{
			LexicalAnalyzer::GetNextToken(Verbose);
		}
		else
		{
			syntaxError(".");
		}
	}
	else
	{
		syntaxError(";");
	}
	debugParseTree(false, "Program");
	return 1;
}

// <block> -> [<label-declaration>]{<variable - dec - sec>}* <block - body>
int SyntaxAnalyzer::block()
{
	debugParseTree(true, "Block");
	if (TokenCode == 16) // Label
	{
		labelDeclaration();
	}
	while (TokenCode == 13) // VAR
	{
		if (syntaxErrorFlag) return 1;
		variableDecSec();
	}
	blockBody();
	while (syntaxErrorFlag && !EndFile)
	{
		resync();
		syntaxErrorFlag = false;
		while (!syntaxErrorFlag && !EndFile)
		{
			statement();
			LexicalAnalyzer::GetNextToken(Verbose);
		}
	}
	debugParseTree(true, "Block");
	return 1;
}

// <block-body> $BEGIN <statement> {$SCOLN <statement>} $END
int SyntaxAnalyzer::blockBody()
{
	debugParseTree(true, "Block Body");
	if (TokenCode == 11) // BEGIN
	{
		do
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			statement();
		} 
		while (NextToken == ";");
		if (TokenCode != 12) // END
		{
			syntaxError("END");
		}
	}
	else
	{
		syntaxError("BEGIN");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Block Body");
	return 1;
}

//<label-declaration> -> $LABEL <identifier> {$COMMA <identifier>}* $SEMICOLON
int SyntaxAnalyzer::labelDeclaration()
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Label Declaration");
	if (TokenCode != 16) // LABEL
	{
		syntaxError("LABEL");
	}
	do
	{
		if (syntaxErrorFlag) return 1;
		LexicalAnalyzer::GetNextToken(Verbose);
		Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind = "UNUSEDDECLABEL"; // We now know that this identifier is meant to be a label, not a var, update it's kind from var to declared label
		identifier();
	}
	while (NextToken == ",");
	if (NextToken != ";")
	{
		syntaxError("SEMICOLON");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Label Declaration");
	return 1;
}

// <variable-dec-sec> -> $VAR <variable-declaration>
int SyntaxAnalyzer::variableDecSec()
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Variable Dec Sec");
	if (TokenCode != 13) // VAR
	{
		syntaxError("VAR");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	variableDeclaration();
	debugParseTree(false, "Variable Dec Sec");
	return 1;
}

// <variable - declaration> -> {<identifier> {$COMMA <identifier>}* $COLON <type> $SEMICOLON}+
int SyntaxAnalyzer::variableDeclaration()
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Variable Declaration");
	Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind = "DECVAR";
	identifier();
	while (NextToken == ",")
	{
		if (syntaxErrorFlag) return 1;
		LexicalAnalyzer::GetNextToken(Verbose);
		Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind = "DECVAR";
		identifier();
	}
	if (NextToken == ":")
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		type();
		if (NextToken != ";")
		{
			syntaxError("SEMICOLON");
		}
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	if (TokenCode == 50) // IDENTIFIERS
	{
		variableDeclaration();
	}
	debugParseTree(false, "Variable Declaration");
	return 1;
}

//<statement>-> {<label> $COLON}*
//[
//	<variable> $ASSIGN (<simple expression> | <string constant>) |
//	<block - body> |
//	$IF <relexpression> $THEN <statement> [$ELSE <statement>] |
//	$WHILE <relexpression> $DO <statement> |
//	$REPEAT <statement> $UNTIL <relexpression> |
//	$FOR <variable> $ASSIGN <simple expression>	$TO <simple expression> $DO <statement> |
//	$GOTO <label> |	$WRITELN $LPAR(<simple expression> | <identifier> |	<stringconst>) $RPAR
//]+
int SyntaxAnalyzer::statement()
{
	debugParseTree(true, "Statement"); 
	int left, right;
	// {<label> $COLON}* // label
	while (Symbols.LookupSymbol(NextToken) != -1 &&
		  (Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind == "UNUSEDDECLABEL" || 
		   Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind == "USEDDECLABEL"))
	{
		if (syntaxErrorFlag) return 1;
		int labelSymbolLocation = label();
		Symbols.symbolTable[labelSymbolLocation].value = Quads.NextQuad();
		if (!LabelUpdates.empty()) // if there is a GOTO label quad that needs the location updated now that 
		{
			map<string, int>::iterator it;
			it = LabelUpdates.find(Symbols.symbolTable[labelSymbolLocation].symbol);
			if (it != LabelUpdates.end())
			{
				Quads.SetQuad(it->second, InstructionReserveTable.LookupName("BR"), 0, 0, get<int>(Symbols.symbolTable[labelSymbolLocation].value)); // jump to value of label, note that value of label is set to quad following label
			}
		}
		if (NextToken != ":")
		{
			syntaxError(":");
		}
		LexicalAnalyzer::GetNextToken(Verbose);
	}

	//	<variable> $ASSIGN (<simple expression> | <string constant>) |
	if (TokenCode == 50) // IDENTIFIERS
	{
		left = variable(); // returns var index
		if (NextToken == ":=")
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			right = simpleExpression(); // returns result index
			Quads.AddQuad(InstructionReserveTable.LookupName("MOV"), right, 0, left); // MOV, 2, 0, 1 == a:=b
		}
		else if (TokenCode == 53) // STRING CONSTANTS
		{
			stringConstant();
		}
		else
		{
			syntaxError("Simple Expression/String Constant");
		}
	}

	//	<block - body> |
	else if (TokenCode == 11) // BEGIN
	{
		blockBody();
	}

	//	$IF <relexpression> $THEN <statement> [$ELSE <statement>] |
	else if (TokenCode == 4) // IF
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		int branchQuad = relExpression();
		if (TokenCode == 5) // THEN
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			statement();
			if (TokenCode == 6) // ELSE
			{
				LexicalAnalyzer::GetNextToken(Verbose);
				int patchElse = Quads.NextQuad(); // Save backfill quad to jump around ELSE body, target is not known yet
				Quads.AddQuad(InstructionReserveTable.LookupName("BR"), 0, 0, 0); // Branch, backfill the FALSE IF branch jump
				Quads.SetQuad(branchQuad, Quads.quadTable[branchQuad][0], Quads.quadTable[branchQuad][1], Quads.quadTable[branchQuad][2], Quads.NextQuad()); // conditional jump //op1index
				statement(); // gen ELSE body quads, fill in end of ELSE part
				Quads.SetQuad(patchElse, Quads.quadTable[patchElse][0], Quads.quadTable[patchElse][1], Quads.quadTable[patchElse][2], Quads.NextQuad());
			}
			else
			{
				Quads.SetQuad(branchQuad, Quads.quadTable[branchQuad][0], Quads.quadTable[branchQuad][1], Quads.quadTable[branchQuad][2], Quads.NextQuad()); // no ELSE encountered, fix IF branch
			}
		}
		else
		{
			syntaxError("THEN");
		}
	}

	//	$WHILE <relexpression> $DO <statement> |
	else if (TokenCode == 14) // WHILE
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		int saveTop = Quads.NextQuad(); // Before generating code, save top of loop where unconditional branch will jump
		int branchQuad = relExpression(); // Tells where branchTarget to be set
		if (TokenCode == 3) // DO
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			statement();
			Quads.AddQuad(InstructionReserveTable.LookupName("BR"), 0, 0, saveTop);// jump to top of loop, backfill the forward branch
			Quads.SetQuad(branchQuad, Quads.quadTable[branchQuad][0], Quads.quadTable[branchQuad][1],Quads.quadTable[branchQuad][2], Quads.NextQuad());// conditional jumps nextQuad	
		}
		else
		{
			syntaxError("DO");
		}
	}

	//	$REPEAT <statement> $UNTIL <relexpression> |
	else if (TokenCode == 17) // REPEAT
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		int branchTarget = Quads.NextQuad();
		statement();
		if (TokenCode == 18) // UNTIL
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			int branchQuad = relExpression();
			Quads.SetQuad(branchQuad, Quads.quadTable[branchQuad][0], Quads.quadTable[branchQuad][1], Quads.quadTable[branchQuad][2], branchTarget);// conditional jumps nextQuad		
		}
		else
		{
			syntaxError("UNTIL");
		}
	}

	//	$FOR <variable> $ASSIGN <simple expression>	$TO <simple expression> $DO <statement> | 
	else if (TokenCode == 7) // FOR
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		int left = variable();
		if (TokenCode == 37) // :=
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			int right = simpleExpression();
			Quads.AddQuad(InstructionReserveTable.LookupName("MOV"), right, 0, left); // loopVariable stored is stored in left
			if (TokenCode == 2) // TO
			{
				LexicalAnalyzer::GetNextToken(Verbose);
				int saveTop = Quads.NextQuad(); // Before generating code, save top of loop where unconditional branch will jump
				int right = simpleExpression();
				int temp = genSymbol(); // create temp var in symbol table
				Quads.AddQuad(3, left, right, temp); //compare
				int branchQuad = Quads.NextQuad(); // save q index where branch will be
				Quads.AddQuad(relOpToOpcode(41), temp, 0, 0); // target set later <=
				if (TokenCode == 3) // DO
				{
					LexicalAnalyzer::GetNextToken(Verbose);
					statement();
					Quads.AddQuad(InstructionReserveTable.LookupName("ADD"), left, Symbols.LookupSymbol("PLUS1INDEX"), left); // incremement loopVariable
					Quads.AddQuad(InstructionReserveTable.LookupName("BR"), 0, 0, saveTop); // jump to top of loop, backfill the forward branch
					Quads.SetQuad(branchQuad, Quads.quadTable[branchQuad][0], Quads.quadTable[branchQuad][1], Quads.quadTable[branchQuad][2], Quads.NextQuad());// conditional jumps nextQuad	
				}
				else
				{
					syntaxError("DO");
				}
			}
			else
			{
				syntaxError("TO");
			}
		}
		else
		{
			syntaxError("ASSIGN");
		}
	}

	//	$GOTO <label> |
	else if (TokenCode == 0) // GOTO
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		int symbolTableIndex = label();
		Quads.AddQuad(InstructionReserveTable.LookupName("BR"), 0, 0, get<int>(Symbols.symbolTable[symbolTableIndex].value)); // jump to value of label, note that value of label is set to quad following label		
		if (get<int>(Symbols.symbolTable[symbolTableIndex].value) == 0) // if the label has not yet been placed, we need to store this quad index into memory, and when it is later placed, we will access this memory and set the proper op3 for this quad
		{
			LabelUpdates.insert({ Symbols.symbolTable[symbolTableIndex].symbol, Quads.NextQuad() - 1 });
		}
	}

	//	$WRITELN $LPAR(<identifier> | <stringconst> | <simple expression> ) $RPAR
	else if (TokenCode == 9)
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		if (TokenCode == 34) // (
		{
			LexicalAnalyzer::GetNextToken(Verbose);
			if (TokenCode == 50) // IDENTIFIERS
			{
				Quads.AddQuad(16, 0, 0, identifier());
			}
			else if (TokenCode == 53) // STRING CONSTANTS
			{
				Quads.AddQuad(16, 0, 0, stringConstant());
			}
			else
			{
				simpleExpression();
			}
			if (TokenCode != 35) // )
			{
				syntaxError(")");
			}
		}
		else
		{
			syntaxError("(");
		}
		LexicalAnalyzer::GetNextToken(Verbose);
	}
	debugParseTree(false, "Statement");
	return 1;
}

//<variable> -> <identifier>[$LBRACK <simple expression> $RBRACK]
int SyntaxAnalyzer::variable()
{
	int retVal = -2;
	if (syntaxErrorFlag) return retVal;
	debugParseTree(true, "Variable");
	if (Symbols.LookupSymbol(NextToken) != -1 && Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind != "DECVAR")
	{
		cout << "Warning: Use of underclared identifier: " << NextToken << endl;
	}
	retVal = identifier();
	if (NextToken == "[")
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		simpleExpression();
		if (NextToken == "]")
		{
			LexicalAnalyzer::GetNextToken(Verbose);
		}
		else
		{
			syntaxError("]");
		}
	}	
	debugParseTree(false, "Variable");
	return retVal;
}

//<label> -> <identifier> Must check that the identifier has been declared as type ‘label’ in order to differentiate from a variable in <statement>
int SyntaxAnalyzer::label()
{
	int retVal = 1;
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Label");
	if (Symbols.LookupSymbol(NextToken) != -1 && Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind == "UNUSEDDECLABEL")
	{
		Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind = "USEDDECLABEL";
	}
	retVal = identifier(); // returns symboltable index of the label
	debugParseTree(false, "Label");
	return retVal;
}

//<relexpression> -> <simple expression> <relop> <simple expression>
int SyntaxAnalyzer::relExpression() 
{
	if (syntaxErrorFlag) return 1;
	int left, right, saveRelOp, result, temp;
	left = simpleExpression(); // get the left operand, our 'A'
	saveRelOp = relOp(); // returns TokenCode of rel operator
	right = simpleExpression(); // right operand, our 'B'
	temp = genSymbol(); // create temp var in symbol table
	Quads.AddQuad(3, left, right, temp); //compare
	result = Quads.NextQuad(); // save q index where branch will be
	Quads.AddQuad(relOpToOpcode(saveRelOp), temp, 0, 0); // target set later
	return result;
}

//<relop>->$EQ | $LSS | $GTR | $NEQ | $LEQ | $GEQ
int SyntaxAnalyzer::relOp()
{
	int retVal = -1;
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Rel Op");
	if (!(38 <= TokenCode <= 43))
	{
		syntaxError("Rel Op");
	}
	retVal = TokenCode;
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Rel Op");
	return retVal;
}

// <simple expression> -> [<sign>] <term> {<addop> <term>}*
int SyntaxAnalyzer::simpleExpression()
{
	int left, right, signVal=0, temp, opCode;
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Simple Expression");
	if (TokenCode == 32 || TokenCode == 33) // + -
	{
		signVal = sign();
	}
	left = term();
	if (signVal == -1) // Add a negation quad
	{
		Quads.AddQuad(InstructionReserveTable.LookupName("MUL"), left, Symbols.LookupSymbol("MINUS1INDEX"), left); // Minus1Index will be preloaded into symbol table as a constant
	}
	while (TokenCode == 32 || TokenCode == 33) // + -
	{
		if (syntaxErrorFlag) return 1;
		if (TokenCode == 32)
		{
			opCode = InstructionReserveTable.LookupName("ADD");
		}
		else
		{
			opCode = InstructionReserveTable.LookupName("SUB");
		}
		addOp(); // checks and moves ahead
		right = term(); // index of term result
		temp = genSymbol(); // genSymbol adds a specially-named temp variable to the symbol table and returns its index
		Quads.AddQuad(opCode, left, right, temp);
		left = temp; // now leftmost term is the last result
	}
	debugParseTree(false, "Simple Expression");
	return left;
}

// <addop> -> $PLUS | $MINUS
int SyntaxAnalyzer::addOp()
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Add Op");
	if (TokenCode != 32 && TokenCode != 33)
	{
		syntaxError("$PLUS | $MINUS");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Add Op");
	return 1;
}

// <sign>-> $PLUS | $MINUS
int SyntaxAnalyzer::sign()
{
	int result = 1;
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Sign");
	if (TokenCode == 32) // +
	{
		// do nothing
	}
	else if (TokenCode == 33) // -
	{
		result = -1;
	}
	else
	{
		syntaxError("Sign");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Sign");
	return result;
}

// <term> -> <factor> {<mulop> <factor>}*
int SyntaxAnalyzer::term()
{
	int left, right, temp, opCode;
	debugParseTree(true, "Term");
	left = factor();
	while (TokenCode == 30 || TokenCode == 31) // / *
	{
		if (syntaxErrorFlag) return 1;
		if (TokenCode == 30)
		{
			opCode = InstructionReserveTable.LookupName("DIV");
		}
		else
		{
			opCode = InstructionReserveTable.LookupName("MUL");
		}
		mulOp(); // checks and moves ahead
		right = factor(); // index of term result
		temp = genSymbol(); // genSymbol adds a specially-named temp variable to the symbol table and returns its index
		Quads.AddQuad(opCode, left, right, temp);
		left = temp; // now leftmost term is the last result
	}
	debugParseTree(false, "Term");
	return left;
}

// <mulop>->$MULTIPLY | $DIVIDE
int SyntaxAnalyzer::mulOp()
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Mul Op");
	if (TokenCode != 30 && TokenCode != 31)
	{
		syntaxError("$MULTIPLY | $DIVIDE");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Mul Op");
	return 1;
}

// <factor> -> <unsigned constant> | <variable> | $LPAR <simple expression> $RPAR
int SyntaxAnalyzer::factor()
{
	int retVal = -2;
	if (syntaxErrorFlag) return retVal;
	debugParseTree(true, "Factor");
	if (TokenCode == 33) // skip minus
	{
		LexicalAnalyzer::GetNextToken(Verbose);
	}
	if (TokenCode == 51 || TokenCode == 52) 
	{
		retVal = unsignedConstant(); 
	}	
	else if (TokenCode == 50)
	{
		retVal = variable();
	}
	else if (TokenCode == 34) // (
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		retVal = simpleExpression();
		if (TokenCode != 35) // )
		{
			syntaxError(")");
		}
		Symbols.LookupSymbol(NextToken);
		LexicalAnalyzer::GetNextToken(Verbose);
	}
	else
	{
		syntaxError("Factor");
	}
	debugParseTree(false, "Factor");
	return retVal;
}

//<type> -> <simple type> | $ARRAY $LBRACK $INTTYPE $RBRACK $OF $INTEGER
int SyntaxAnalyzer::type() 
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Type");
	if (NextToken == "ARRAY")
	{
		LexicalAnalyzer::GetNextToken(Verbose);
		if (NextToken == "[")
		{
			LexicalAnalyzer::GetNextToken(Verbose);			
			if (Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].type == 0)
			{
				LexicalAnalyzer::GetNextToken(Verbose);
				if (NextToken == "]")
				{
					LexicalAnalyzer::GetNextToken(Verbose);
					if (NextToken == "OF")
					{
						LexicalAnalyzer::GetNextToken(Verbose);
						if (NextToken == "INTEGER")
						{
							LexicalAnalyzer::GetNextToken(Verbose);
						}
					}
				}
			}
		}
		syntaxError("Type");
	}
	else
	{
		simpleType();
	}
	debugParseTree(false, "Type");
	return 1;
}

//<simple type>-> $INTEGER | $FLOAT | $STRING
int SyntaxAnalyzer::simpleType() 
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Simple Type");
	if (TokenCode != 1 && TokenCode != 23 && TokenCode != 24)
	{
		syntaxError("Simple Type");
	}
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Simple Type");
	return 1;
}

//<constant> -> [<sign>] <unsigned constant>
int SyntaxAnalyzer::constant()
{
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Constant");
	if (TokenCode == 32 || TokenCode == 33) // since it's optional, check it will pass before we add to tree
	{
		sign();
	}
	unsignedConstant();
	debugParseTree(false, "Constant");
	return 1;
}

// <unsigned constant> -> <unsigned number>
int SyntaxAnalyzer::unsignedConstant()
{
	int retVal = -2;
	if (syntaxErrorFlag) return 1;
	debugParseTree(true, "Unsigned Constant");
	retVal = unsignedNumber();
	debugParseTree(false, "Unsigned Constant");
	return retVal;
}

//<unsigned number>-> $FLOATTYPE | $INTTYPE Token codes 52 or 51
int SyntaxAnalyzer::unsignedNumber()
{
	int retVal = -2;
	if (syntaxErrorFlag) return retVal;
	debugParseTree(true, "Unsigned Number");
	if (TokenCode != 51 && TokenCode != 52)
	{
		syntaxError("Unsigned Number");
	}
	retVal = Symbols.LookupSymbol(NextToken);
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Unsigned Number");
	return retVal;
}

//<identifier>-> $IDENTIFIER **note: <letter> {<letter> |<digit> | $ | _ }*
int SyntaxAnalyzer::identifier()
{
	int retVal = -1;
	if (syntaxErrorFlag) return retVal;
	debugParseTree(true, "Identifier");
	if (TokenCode != 50)
	{
		syntaxError("IDENTIFIER");
	}
	retVal = Symbols.LookupSymbol(NextToken);
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "Identifier");
	return retVal;
}

//<stringconst>-> $STRINGTYPE Token code 53
int SyntaxAnalyzer::stringConstant()
{
	int retVal = -1;
	if (syntaxErrorFlag) return retVal;
	debugParseTree(true, "String Constant");
	if (TokenCode != 53)
	{
		syntaxError("String Constant");
	}
	retVal = Symbols.LookupSymbol(NextToken);
	LexicalAnalyzer::GetNextToken(Verbose);
	debugParseTree(false, "String Constant");
	return retVal;
}

void SyntaxAnalyzer::syntaxError(string expected)
{
	cout << "Line: " << BufferLine << ", Index: " << BufferIndex << endl
		<< "Error: expected: " << expected << ", but " << NextToken << " was received." << endl;
	syntaxErrorFlag = true;
	//	exit(0);
}

bool SyntaxAnalyzer::insensitiveCompare(string s1, string s2)
{
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1 == s2)
	{
		return true;
	}
	return false;
}

void SyntaxAnalyzer::debugParseTree(bool enter, string nonTerminal)
{		
	if (Verbose)
	{
		if (enter)
		{
			cout << setw(2*indent++) << "" << "Entering: " << nonTerminal << endl;
		}
		else
		{
			cout << setw(2*--indent) << "" << "Exiting: " << nonTerminal << endl;
		}
	}
}

void SyntaxAnalyzer::resync()
{
	while (((Symbols.LookupSymbol(NextToken) != -1 && Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind == "USEDDECLABEL") ||
		    (Symbols.LookupSymbol(NextToken) != -1 && Symbols.symbolTable[Symbols.LookupSymbol(NextToken)].kind == "UNUSEDDECLABEL") ||
		    (TokenCode == 50) || // IDENTIFIERS
		    (TokenCode == 11) || // BEGIN
		    (TokenCode == 4)  || // IF
		    (TokenCode == 14) || // WHILE
		    (TokenCode == 17) || // REPEAT
		    (TokenCode == 7)  || // FOR
		    (TokenCode == 0)  || // GOTO
		    (TokenCode == 9)) && // WRITELN
		    (!EndFile))
	{
		LexicalAnalyzer::GetNextToken(Verbose);
	}
}

// genSymbol adds a specially-named temp variable to the symbol table and returns its index
int SyntaxAnalyzer::genSymbol()
{
	static int tempCounter = 0;
	string TempSymbolName = "TEMP" + to_string(tempCounter++);
	Symbols.AddSymbol(TempSymbolName, "INT", 0);
	return Symbols.LookupSymbol(TempSymbolName);
}

int SyntaxAnalyzer::relOpToOpcode(int relop)
{
    int result = 0; // 38 - 43
    switch (relop)
    {
    case 38: // greater than, BNP
		result = InstructionReserveTable.LookupName("BNP");
  	    break;
    case 39: // less than <, BNN
  	    result = InstructionReserveTable.LookupName("BNN");
  	    break;
    case 40: // greater than or equal to >=, BN
  		result = InstructionReserveTable.LookupName("BN");
  		break;
    case 41: // less than or equal <=, BP
  		result = InstructionReserveTable.LookupName("BP");
  		break;
    case 42: // equal =, BNZ
  	    result = InstructionReserveTable.LookupName("BNZ");
  	    break;
    case 43: // not equal <>, BZ
  	    result = InstructionReserveTable.LookupName("BZ");
  	    break;
	// default error maybe
    }
    return result;
}
