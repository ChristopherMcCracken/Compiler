#include "ReserveTable.h"
#include "LexicalAnalyzer.h"
#include <algorithm>

ReserveTable::ReserveTable(string type)
{
    if (type == "Lexical")
    {
        Add("GOTO", 0);
        Add("INTEGER", 1);
        Add("TO", 2);
        Add("DO", 3);
        Add("IF", 4);
        Add("THEN", 5);
        Add("ELSE", 6);
        Add("FOR", 7);
        Add("OF", 8);
        Add("WRITELN", 9);
        Add("READLN", 10);
        Add("BEGIN", 11);
        Add("END", 12);
        Add("VAR", 13);
        Add("WHILE", 14);
        Add("UNIT", 15);
        Add("LABEL", 16);
        Add("REPEAT", 17);
        Add("UNTIL", 18);
        Add("PROCEDURE", 19);
        Add("DOWNTO", 20);
        Add("FUNCTION", 21);
        Add("RETURN", 22);
        Add("REAL", 23);
        Add("STRING", 24);
        Add("ARRAY", 25);
        Add("/", 30);
        Add("*", 31);
        Add("+", 32);
        Add("-", 33);
        Add("(", 34);
        Add(")", 35);
        Add(";", 36);
        Add(":=", 37);
        Add(">", 38);
        Add("<", 39);
        Add(">=", 40);
        Add("<=", 41);
        Add("=", 42);
        Add("<>", 43);
        Add(",", 44);
        Add("[", 45);
        Add("]", 46);
        Add(":", 47);
        Add(".", 48);
        Add("IDENTIFIERS", 50); // todo
        Add("INTEGERS", 51); // todo
        Add("FLOT", 52); // todo
        Add("STRING CONSTANTS", 53); // todo
        Add("UNDEFINED", 99);
    }
    if (type == "Mnemonic")
    {
        Add("GOTO", 0);
        Add("INTG", 1);
        Add("TO__", 2);
        Add("DO__", 3);
        Add("IF__", 4);
        Add("THEN", 5);
        Add("ELSE", 6);
        Add("FOR_", 7);
        Add("OF__", 8);
        Add("WRIT", 9);
        Add("READ", 10);
        Add("BEGN", 11);
        Add("END_", 12);
        Add("VAR_", 13);
        Add("WHIL", 14);
        Add("UNIT", 15);
        Add("LABL", 16);
        Add("REPT", 17);
        Add("UNTL", 18);
        Add("PROC", 19);
        Add("DWTO", 20);
        Add("FUNC", 21);
        Add("RETN", 22);
        Add("REAL", 23);
        Add("STRG", 24);
        Add("ARRY", 25);
        Add("DIVI", 30);
        Add("MULT", 31);
        Add("PLUS", 32);
        Add("SUBT", 33);
        Add("LPAR", 34);
        Add("RPAR", 35);
        Add(";___", 36);
        Add(":=__", 37);
        Add(">___", 38);
        Add("<___", 39);
        Add(">=__", 40);
        Add("<=__", 41);
        Add("=___", 42);
        Add("<>__", 43);
        Add(",___", 44);
        Add("[___", 45);
        Add("]___", 46);
        Add(":___", 47);
        Add(".___", 48);
        Add("IDEN", 50); // todo
        Add("INTS", 51); // todo
        Add("FLOT", 52); // todo
        Add("SCON", 53); // todo
        Add("UNDF", 99);
    }
    if (type == "Instructions")
    {
        Add("STOP", 0);
        Add("DIV", 1);
        Add("MUL", 2);
        Add("SUB", 3);
        Add("ADD", 4);
        Add("MOV", 5);
        Add("STI", 6);
        Add("LDI", 7);
        Add("BNZ", 8);
        Add("BNP", 9);
        Add("BNN", 10);
        Add("BZ", 11);
        Add("BP", 12);
        Add("BN", 13);
        Add("BR", 14);
        Add("BINDR", 15);
        Add("PRINT", 16);
    }
    if (type == "Instructions Mnemonic")
    {
        Add("STOP", 0);
        Add("DIV_", 1);
        Add("MUL_", 2);
        Add("SUB_", 3);
        Add("ADD_", 4);
        Add("MOV_", 5);
        Add("STI_", 6);
        Add("LDI_", 7);
        Add("BNZ_", 8);
        Add("BNP_", 9);
        Add("BNN_", 10);
        Add("BZ__", 11);
        Add("BP__", 12);
        Add("BN__", 13);
        Add("BR__", 14);
        Add("BNDR", 15);
        Add("PRNT", 16);
    }
}

int ReserveTable::Add(string name, int code)
{
    // Place pair
    OpCodes.insert({ name, code });

    // Return code since this is also its index
    return code;
}

int ReserveTable::LookupName(string name)
{
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    if (OpCodes.find(name) != OpCodes.end())
    {
        return OpCodes[name];
    }
    else
    {
        return 99;
    }
}

string ReserveTable::LookupCode(int code)
{
    for (auto &i : OpCodes)
    {
        if (i.second == code)
        {
            return i.first;
        }
    }
    return "";
}

void ReserveTable::PrintReserveTable()
{
    cout << "Reserve Table" << endl;
    for (auto& i : OpCodes)
    {
        cout << setw(40) << left << i.first << setw(40) << left << i.second << endl;
    }
    cout << endl;
}
