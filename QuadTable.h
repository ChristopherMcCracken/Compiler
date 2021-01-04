#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

// Holds sequence of quadcode instructions and helper functions
class QuadTable
{
public:
	vector<vector<int>> quadTable;

	// Create a new, empty QuadTable ready for data to be added, with the specified number of rows(size).
	QuadTable();

	// Allocate and initialize contents of Quad table
	void BuildQuads(string choice);

	// Returns the index of the next open slot in the QuadTable
	int NextQuad();

	// Append new quadcode entry
	void AddQuad(int opcode, int op1, int op2, int op3);

	// Returns the quadcode located at index
	vector<int> GetQuad(int index);

	// Returns the mnemonic string associated with the opcode parameter
	// Used during interpreter ‘TRACE’ mode to print out the stored opcodes legibly
	string GetMnemonic(int opcode);

	// Changes the contents of the existing quad at index.Used only when backfilling
	// jump addresses later, during code generation, and very important
	void SetQuad(int index, int opcode, int op1, int op2, int op3);

	// Prints the currently used contents of the Quad table in neat tabular format
	void PrintQuadTable();
};

