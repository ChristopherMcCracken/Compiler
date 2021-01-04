#include "LexicalAnalyzer.h"

ifstream fin;
bool echoOn;

void LexicalAnalyzer::OpenFile(string file)
{
	fin.open(file);
}

void LexicalAnalyzer::CloseFile()
{
	EndFile = false;
	BufferLine = 0;
	BufferLine = 0;
	fin.close();
}

void LexicalAnalyzer::GetNextToken(bool echo)
{	
	echoOn = echo;
	NextToken = "";
	TokenCode = -1;
	BuildToken();
	if (TokenCode == -1) // If it's not been set already
	{
		TokenCode = LexicalReserveTable.LookupName(NextToken);
	}
	if (echoOn)
	{
		LexicalAnalyzer::PrintToken();
	}
}

void LexicalAnalyzer::BuildToken()
{
	char nextChar = GetNextChar();

	if (EndFile)
	{
		return;
	}

	if (IsWhitespace(nextChar))
	{		
		BuildToken(); // skips blanks
	}
	else if (IsComment(nextChar))
	{
		HandleComment(nextChar);
		BuildToken();
	}
	else if (IsDigit(nextChar))
	{
		HandleDigit(nextChar);
		return;
	}
	else if (IsLetter(nextChar))
	{
		HandleLetter(nextChar);
		return;
	}
	else if (nextChar == '"')
	{
		HandleString(nextChar);
		return;
	}
	else
	{
		HandleOther(nextChar, NextToken);
		return;
	}
}

void LexicalAnalyzer::PrintToken()
{
	if (!EndFile)
	{
		cout << left << setw(40) << NextToken << left << 
			setw(40) << TokenCode << left << 
			setw(40) << MnemonicReserveTable.LookupCode(TokenCode) << left << 
			setw(40) << Symbols.LookupSymbol(NextToken) << endl;
	}
}

void LexicalAnalyzer::GetNextLine()
{	
	BufferIndex = 0;
	do 
	{
		if (fin.eof())
		{
			EndFile = true;
			return;
		}
		getline(fin, Buffer);
		BufferLine++; // Keep track of line number
		if (BufferLine == 1 && Verbose)
		{
			cout << left << setw(40) << "Lexeme" << left << setw(40) << "Token Code" << left << setw(40) << "Mnemonic" << left << setw(40) << "ST Index" << endl;
		}
		if (Verbose)
		{
			cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		cout << "Line: " << BufferLine << ": " << Buffer << endl;
	}
	while (Buffer.length() == 0);
}

char LexicalAnalyzer::GetNextChar()
{
	if (BufferIndex > Buffer.length())
	{
		GetNextLine();
	}
	return Buffer[BufferIndex++];
}
 
bool LexicalAnalyzer::IsComment(char nextChar)
{
	return (nextChar == '{') || (nextChar == '(' && Buffer[BufferIndex] == '*');
}

void LexicalAnalyzer::HandleComment(char nextChar)
{
	if (nextChar == '{')
	{
		while (nextChar != '}')
		{
			if (EndFile)
			{
				cout << "Warning: Unterminated Comment" << endl;
				return;
			}
			nextChar = GetNextChar();
		}
	}
	else
	{
		while (!(nextChar == '*' && GetNextChar() == ')'))
		{
			if (EndFile)
			{
				cout << "Warning: Unterminated Comment" << endl;
				return;
			}
			nextChar = GetNextChar();
		}
	}
}

bool LexicalAnalyzer::IsWhitespace(char nextChar)
{
	return (nextChar == ' ' || nextChar == '\n' || nextChar == '\0' || nextChar == '\t' || nextChar == '\v' || nextChar == '\f' || nextChar == '\r');
}

bool LexicalAnalyzer::IsLetter(char nextChar)
{
	if (nextChar == '^' || nextChar == '_' || nextChar == '[' || nextChar == ']') // cant get a regex to work with these, look into this later
	{
		return false;
	}
	string checkMe;
	checkMe.push_back(nextChar);
	regex re("[a-zA-z]+"); // alpha
	return regex_match(checkMe, re);
}

void LexicalAnalyzer::HandleLetter(char nextChar)
{
	while (IsLetter(nextChar) || IsDigit(nextChar) || nextChar == '_') // todo other than _ what else is allowed?
	{
		NextToken += nextChar;
		nextChar = GetNextChar();
	}
	BufferIndex--;
	if (LexicalReserveTable.LookupName(NextToken) != 99)
	{
		return; // It's something in the table
	}
	if (NextToken.length() > 30)
	{
		cout << "Warning: Identifier name too long, truncating to 30." << endl;
		NextToken = NextToken.substr(0, 30);
	}
	if (Symbols.LookupSymbol(NextToken) == -1)
	{
		Symbols.AddSymbol(NextToken, "VAR", 0);
	}
	TokenCode = 50;
	return; // It's a variable name
}

bool LexicalAnalyzer::IsDigit(char nextChar)
{
	string checkMe;
	checkMe.push_back(nextChar);
	regex re("[[:d:]]+"); // digit
	if (nextChar == '-')
	{
		return (regex_match(checkMe + Buffer[BufferIndex], re));
	}
	else
	{
		return regex_match(checkMe, re);		
	}
}

void LexicalAnalyzer::HandleDigit(char nextChar)
{
	NextToken += nextChar;
	regex re("(\\-)?" // -
		"[[:d:]]+"    // digit
		"(\\.)?"      // .
		"[[:d:]]?"    // digit
		"(\\E|e)?"    // E
		"(\\-)?"      // -
		"[[:d:]]*");  // digit		
	while (regex_match(NextToken, re))
	{
		nextChar = GetNextChar();
		NextToken += nextChar;
	}
	// Remove failed regex_match 
	if (NextToken.length() > 1)
	{
		NextToken.pop_back();
		BufferIndex--;
	}
	if (NextToken.length() > 10)
	{
		cout << "Warning: Numeric constant too long, truncating to 10." << endl;
		NextToken = NextToken.substr(0, 10);
	}
	//if (Symbols.LookupSymbol(NextToken) == -1) // todo decide if needed
	//{
	regex hasDot("(\\.)+");
	if (regex_search(NextToken, hasDot))
	{
		TokenCode = 52; // Flot
		Symbols.AddSymbol(NextToken, "CONST", stod(NextToken));
	}
	else
	{
		TokenCode = 51; // Integer
		Symbols.AddSymbol(NextToken, "CONST", stoi(NextToken));
	}
	//}
	return;
}

void LexicalAnalyzer::HandleString(char nextChar)
{
	nextChar = GetNextChar();
	while (nextChar != '"')
	{
		if (BufferIndex == Buffer.length())
		{
			cout << "Warning: Unterminated String found, terminating string at end of line" << endl;
			break;
		}
		if (EndFile)
		{
			cout << "Warning: Unterminated String found, terminating string at end of file" << endl;
			break;
		}
		NextToken += nextChar;
		nextChar = GetNextChar();
	}
	if (Symbols.LookupSymbol(NextToken) == -1)
	{
		Symbols.AddSymbol(NextToken, "CONST", NextToken);
	}
	TokenCode = 53;
	return;
}

void LexicalAnalyzer::HandleOther(char nextChar, string &NextToken)
{
	NextToken += nextChar;
	while(LexicalReserveTable.LookupName(NextToken) != 99)
	{
		nextChar = GetNextChar();
		NextToken += nextChar;
	}
	// Undo operations done during last loop
	if (NextToken.length() > 1)
	{
		NextToken.pop_back();
		BufferIndex--;
	}
	TokenCode = LexicalReserveTable.LookupName(NextToken);
	return;
}