#pragma once

#include "SymbolTable.h"
#include "QuadTable.h"
#include "ReserveTable.h"

class Interpreter
{
public:
	// Run the interpreter with/without TRACE mode
	static void InterpretQuads(bool True);
};
