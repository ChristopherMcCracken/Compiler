#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

// This is a lookup table ADT used for the opcode lookup
class ReserveTable
{
public:
	map <string, int> OpCodes;

	// Constructor
	ReserveTable();
	ReserveTable(string type);
	
	// Append parameters to end of list
	int Add(string name, int code);
	
	// Returns the code associated with name, else returns 99
	int LookupName(string name);
	
	// Returns the associated name to code, else an empty string
	string LookupCode(int code);

	// Prints the notable contents of the Reserve table
	void PrintReserveTable();
};
