#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Symbol.h"

using namespace std;

class SymbolTable
{
public:
	vector<Symbol> symbolTable;

	// Constructor
	SymbolTable();

	// Allocate and initialize the Symbol table and PRINT it
	void BuildSymbolTable(string choice);

	// Add symbol, kind, and value to the symbol table, automatically sets type variable
	int AddSymbol(string symbol, string kind, int value);
	int AddSymbol(string symbol, string kind, double value);
    int AddSymbol(string symbol, string kind, string value);

	// Returns the index where symbol is found, or -1s if not in the table
	int LookupSymbol(string symbol);

	// Return kind, data type, and value fields stored at index
	Symbol GetSymbol(int index);
	
	// Update Symbol at existing index
	void UpdateSymbol(int index, string kind, int value);
	void UpdateSymbol(int index, string kind, double value);
	void UpdateSymbol(int index, string kind, string value);
	
	// Prints the utilized rows of the symbol table
	void PrintSymbolTable();
};
