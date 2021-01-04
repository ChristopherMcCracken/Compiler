#pragma once

#include "ReserveTable.h"
#include "SymbolTable.h"
#include "QuadTable.h"

extern ReserveTable InstructionReserveTable;
extern ReserveTable InstructionMnemonicReserveTable;
extern ReserveTable LexicalReserveTable;
extern ReserveTable MnemonicReserveTable;
extern SymbolTable Symbols;
extern QuadTable Quads;
extern bool Verbose;
extern bool EndFile;
extern string NextToken;
extern int TokenCode;
extern string Buffer;
extern int BufferLine;
extern int BufferIndex;
extern map<string, int> LabelUpdates;
