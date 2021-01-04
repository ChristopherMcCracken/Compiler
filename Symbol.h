#pragma once

#include <string>
#include <iostream>
#include <variant>

using namespace std;

// Allows type variable to be set more clearly
enum type {
	INT,
	DOUBLE,
	STRING
};

class Symbol
{
public:
	Symbol(int type = 0, string symbol = "", string kind = "", variant<int, double, string> value = INT)
	{
		this->type = type;
		this->symbol = symbol;
		this->kind = kind;
		this->value = value;
	}
	int type;
	string symbol;
	string kind;
	variant <int, double, string> value;
};