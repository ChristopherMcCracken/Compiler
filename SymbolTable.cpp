#include "SymbolTable.h"

SymbolTable::SymbolTable()
{

}

void SymbolTable::BuildSymbolTable(string choice)
{
    // Factorial Quads
    if (choice == "factorial")
    {
        AddSymbol("n", "VAR", 0);
        AddSymbol("prod", "VAR", 0);
        AddSymbol("count", "VAR", 0);
        AddSymbol("fact", "VAR", 0);
        AddSymbol("5", "CONST", 10);
        AddSymbol("5", "CONST", 1);
        AddSymbol("1", "CONST", 5);
    }

    // Sumnation Symbols
    if (choice == "sumnation")
    {
        AddSymbol("n", "VAR", 10);
        AddSymbol("total", "VAR", 0);
        AddSymbol("one", "VAR", 1);
    }
    PrintSymbolTable();
}

int SymbolTable::AddSymbol(string symbol, string kind, int value)
{
    Symbol tempSymbol(INT, symbol, kind, value);
    symbolTable.push_back(tempSymbol);
    return symbolTable.size();
}

int SymbolTable::AddSymbol(string symbol, string kind, double value)
{
    Symbol tempSymbol(DOUBLE, symbol, kind, value);
    symbolTable.push_back(tempSymbol);
    return symbolTable.size();
}

int SymbolTable::AddSymbol(string symbol, string kind, string value)
{
    Symbol tempSymbol(STRING, symbol, kind, value);
    symbolTable.push_back(tempSymbol);
    return symbolTable.size();
}

int SymbolTable::LookupSymbol(string symbol)
{
    for (int i = 0; i < symbolTable.size(); i++)
    {
        if (symbolTable[i].symbol == symbol)
        {
            return i;
        }
    }
    return -1;
}

Symbol SymbolTable::GetSymbol(int index)
{
    return symbolTable[index];
}
    
void SymbolTable::UpdateSymbol(int index, string kind, int value)
{
    Symbol tempSymbol(INT, symbolTable[index].symbol, kind, value);
    symbolTable[index] = tempSymbol;
}

void SymbolTable::UpdateSymbol(int index, string kind, double value)
{
    Symbol tempSymbol(DOUBLE, symbolTable[index].symbol, kind, value);
    symbolTable[index] = tempSymbol;
}

void SymbolTable::UpdateSymbol(int index, string kind, string value)
{
    Symbol tempSymbol(STRING, symbolTable[index].symbol, kind, value);
    symbolTable[index] = tempSymbol;
}

void SymbolTable::PrintSymbolTable()
{
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl
        << "Symbol Table" << endl
        << setw(40) << left << "Index & Lexeme"
        << setw(40) << left << "Kind"
        << setw(40) << left << "Type"
        << setw(40) << left << "Value" << endl
        << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
    string index;
    for (int i = 0; i < symbolTable.size(); i++) {
        switch (symbolTable[i].type) 
        {
        case INT:
            index = "[" + to_string(i) + "] ";
            std::cout << index << setw(40-index.length()) << left << symbolTable[i].symbol <<
                         setw(40) << left << symbolTable[i].kind <<
                         setw(40) << left << "INT" <<
                         setw(40) << left << get<int>(symbolTable[i].value) << endl;
            break;
        case DOUBLE:
            index = "[" + to_string(i) + "] ";
            std::cout << index << setw(40 - index.length()) << left << symbolTable[i].symbol <<
                         setw(40) << left << symbolTable[i].kind <<
                         setw(40) << left << "FLOT" <<
                         setw(40) << left << get<double>(symbolTable[i].value) << endl;
            break;
        case STRING:
            index = "[" + to_string(i) + "] ";
            std::cout << index << setw(40 - index.length()) << left << symbolTable[i].symbol <<
                         setw(40) << left << symbolTable[i].kind <<
                         setw(40) << left << "STRING" <<
                         setw(40) << left << get<string>(symbolTable[i].value) << endl;
            break;
        }
    }
    std::cout << endl;
}
