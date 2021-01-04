#include "Interpreter.h"
#include "Globals.h"
#include <iostream>

void Interpreter::InterpretQuads(bool trace)
{
	int programCounter = 0;
	int lastInstructionIndex = Quads.quadTable.size() - 1;
	// Optional Tracing
	if (trace)
	{
		//cout << "PC " << programCounter << ": " << Quads.GetMnemonic(opCode) << ", " << op1Index << ", " << op2Index << ", " << op3Index << endl;
		cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl
			<< "Code Generation" << endl
			<< setw(40) << "PC & OPCODE" << setw(40) << "OP1" << setw(40) << "OP2" << setw(40) << "OP3" << endl
			<< "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	while (programCounter <= lastInstructionIndex)
	{
		// Breakdown quad
		vector<int> quad = Quads.GetQuad(programCounter);
		int opCode = quad[0];
		int op1Index = quad[1];
		int op2Index = quad[2];
		int op3Index = quad[3];

		// Optional Tracing
		if (trace)
		{
			//cout << "PC " << programCounter << ": " << Quads.GetMnemonic(opCode) << ", " << op1Index << ", " << op2Index << ", " << op3Index << endl;
			if (op3Index < Symbols.symbolTable.size())
			{
				string out1, out2, out3, out4;
				out1 = "PC " + to_string(programCounter) + ": " + Quads.GetMnemonic(opCode);
				out2 = '[' + to_string(op1Index) + ']' + Symbols.symbolTable[op1Index].symbol;
				out3 = '[' + to_string(op2Index) + ']' + Symbols.symbolTable[op2Index].symbol;
				out4 = '[' + to_string(op3Index) + ']' + Symbols.symbolTable[op3Index].symbol;
				cout << setw(40) << left << out1 << setw(40) << left << out2 << setw(40) << left << out3 << setw(40) << left << out4 << endl;
			}
			else
			{
				cout << "PC " << programCounter << ": " << Quads.GetMnemonic(opCode) << ", " << Symbols.symbolTable[op1Index].symbol << ", " << Symbols.symbolTable[op2Index].symbol << ", " << op3Index << endl;
			}
		}

		// Check if opCode is valid, then execute instruction
		if (InstructionReserveTable.LookupCode(opCode) != "")
		{
			switch (opCode)
			{
			case 0: // STOP - Terminate Program
				exit(0);
			case 1: // DIV - Place op1/op2 into op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<int>(Symbols.symbolTable[op1Index].value) / get<int>(Symbols.symbolTable[op2Index].value));
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<double>(Symbols.symbolTable[op1Index].value) / get<double>(Symbols.symbolTable[op2Index].value));
					break;
				case STRING:
					break;
				}
				break;
			case 2: // MUL - Place op1*op2 into op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<int>(Symbols.symbolTable[op1Index].value) * get<int>(Symbols.symbolTable[op2Index].value));
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<double>(Symbols.symbolTable[op1Index].value) * get<double>(Symbols.symbolTable[op2Index].value));
					break;
				case STRING:
					break;
				}
				break;
			case 3: // SUB - Place op1-op2 into op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<int>(Symbols.symbolTable[op1Index].value) - get<int>(Symbols.symbolTable[op2Index].value));;
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<double>(Symbols.symbolTable[op1Index].value) - get<double>(Symbols.symbolTable[op2Index].value));
					break;
				case STRING:
					break;
				}
				break;
			case 4: // ADD - Place op1+op2 into op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<int>(Symbols.symbolTable[op1Index].value) + get<int>(Symbols.symbolTable[op2Index].value));
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<double>(Symbols.symbolTable[op1Index].value) + get<double>(Symbols.symbolTable[op2Index].value));
					break;
				case STRING:
					break;
				}
				break;
			case 5: // MOV - Place op1 into op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<int>(Symbols.symbolTable[op1Index].value));
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<double>(Symbols.symbolTable[op1Index].value));
					break;
				case STRING:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<string>(Symbols.symbolTable[op1Index].value));
					break;
				}
				break;
			case 6: // STI - Store indexed - Assign the value of op1 into op2 + offset op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op1Index,
						Symbols.symbolTable[op1Index].kind,
						get<int>(Symbols.symbolTable[op2Index + op3Index].value));					
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op1Index,
						Symbols.symbolTable[op1Index].kind,
						get<double>(Symbols.symbolTable[op2Index + op3Index].value));
					break;
				case STRING:
					Symbols.UpdateSymbol(op1Index,
						Symbols.symbolTable[op1Index].kind,
						get<string>(Symbols.symbolTable[op2Index + op3Index].value));
					break;
				}
				break;
			case 7: // LDI - Load indexed - Assign the value of op1 + offset op2, into op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<int>(Symbols.symbolTable[op1Index + op2Index].value));
					break;
				case DOUBLE:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<double>(Symbols.symbolTable[op1Index + op2Index].value));
					break;
				case STRING:
					Symbols.UpdateSymbol(op3Index,
						Symbols.symbolTable[op3Index].kind,
						get<string>(Symbols.symbolTable[op1Index + op2Index].value));
					break;
				}
				break;
			case 8: // BNZ (Branch Not Zero) - If op1 <> 0, set program counter to op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					if (get<int>(Symbols.symbolTable[op1Index].value) != 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case DOUBLE:
					if (get<double>(Symbols.symbolTable[op1Index].value) != 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case STRING:
					break;
				}
			case 9: // BNP (Branch Not Positive) If op1 <= 0, set program counter to op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					if (get<int>(Symbols.symbolTable[op1Index].value) <= 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case DOUBLE:
					if (get<double>(Symbols.symbolTable[op1Index].value) <= 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case STRING:
					break;
				}
				break;
			case 10: // BNN (Branch Not Negative) - If op1 >= 0, set program counter to op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					if (get<int>(Symbols.symbolTable[op1Index].value) >= 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case DOUBLE:
					if (get<double>(Symbols.symbolTable[op1Index].value) >= 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case STRING:
					break;
				}
				break;
			case 11: // BZ (Branch Zero) - If op1 = 0, set program counter to op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					if (get<int>(Symbols.symbolTable[op1Index].value) == 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case DOUBLE:
					if (get<double>(Symbols.symbolTable[op1Index].value) == 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case STRING:
					break;
				}
				break;
			case 12: // BP (Branch Positive) - If op1 > 0, set program counter to op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					if (get<int>(Symbols.symbolTable[op1Index].value) > 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case DOUBLE:
					if (get<double>(Symbols.symbolTable[op1Index].value) > 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case STRING:
					break;
				}
				break;
			case 13: // BN (Branch Negative) - If op1 < 0, set program counter to op3
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT:
					if (get<int>(Symbols.symbolTable[op1Index].value) < 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case DOUBLE:
					if (get<double>(Symbols.symbolTable[op1Index].value) < 0)
					{
						programCounter = op3Index;
						continue;
					}
					break;
				case STRING:
					break;
				}
				break;
			case 14: // BR (Branch unconditional) - Set program counter to op3
				programCounter = op3Index;
				continue;
			case 15: // BINDR (Branch unconditional indirect) - Set program counter to op3 value contents
				switch (Symbols.symbolTable[op1Index].type)
				{
				case INT: // Shoould only be used for integer values
					programCounter = get<int>(Symbols.symbolTable[op3Index].value);
					continue;
				case DOUBLE:
					break;
				case STRING:
					continue;
				}
				break;
			case 16: // PRINT - Write symbol table name and value of op 1
				switch (Symbols.symbolTable[op3Index].type) // endls were added for output legibility for grader, actual implementation would have no endls
				{
				case INT:
					cout << endl << get<int>(Symbols.symbolTable[op3Index].value) << endl << endl;
					break;
				case DOUBLE:
					cout << endl << get<double>(Symbols.symbolTable[op3Index].value) << endl << endl;
					break;
				case STRING:
					cout << endl << get<string>(Symbols.symbolTable[op3Index].value) << endl << endl;
					break;
				}
				break;
			}			
		}
		programCounter++;
	} // end while
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
}
