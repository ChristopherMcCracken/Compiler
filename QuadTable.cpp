#include "QuadTable.h"
#include "Globals.h"

QuadTable::QuadTable()
{
}

void QuadTable::BuildQuads(string choice)
{
	PrintQuadTable();
}

int QuadTable::NextQuad()
{
	return quadTable.size(); // translates to index of next quad
}

void QuadTable::AddQuad(int opcode, int op1, int op2, int op3)
{
	vector<int> quad = { opcode, op1, op2, op3 };
	quadTable.push_back(quad);
}

vector<int> QuadTable::GetQuad(int index) // Deviates from pdf
{
	return quadTable[index];
}

string QuadTable::GetMnemonic(int opcode)
{
	return InstructionMnemonicReserveTable.LookupCode(opcode);
}

void QuadTable::SetQuad(int index, int opcode, int op1, int op2, int op3)
{
	quadTable[index] = { opcode, op1, op2, op3 };
}

void QuadTable::PrintQuadTable()
{
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl
		 << "Quad Table" << endl
		 << setw(40) << "OPCODE" << setw(40) << "OP1" << setw(40) << "OP2" << setw(40) << "OP3" << endl
	     << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < quadTable.size(); i++) 
	{
		for (int j = 0; j < quadTable[i].size(); j++)
		{
			if (j == 0)
			{
				cout << setw(40) << left << Quads.GetMnemonic(quadTable[i][j]);
			}
			else
			{
				if (quadTable[i][j] > Symbols.symbolTable.size())
				{
					cout << setw(40) << left << quadTable[i][j];
				}
				else
				{
					string data = "[" + to_string(quadTable[i][j]) + "]" + Symbols.symbolTable[quadTable[i][j]].symbol;
					cout << setw(40) << left << data;
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}
