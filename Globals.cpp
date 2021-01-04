#include "Globals.h"

ReserveTable InstructionReserveTable("Instructions");
ReserveTable InstructionMnemonicReserveTable("Instructions Mnemonic");
ReserveTable LexicalReserveTable("Lexical");
ReserveTable MnemonicReserveTable("Mnemonic");
SymbolTable Symbols;
QuadTable Quads;
bool Verbose;
bool EndFile = false;
string NextToken;
int TokenCode;
string Buffer;
int BufferLine;
int BufferIndex;
map<string, int> LabelUpdates; // keep track of goto label quads that need to know the location of where label is placed