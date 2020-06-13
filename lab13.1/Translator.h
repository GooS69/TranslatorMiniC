#pragma once
#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include "Scanner.h"


class Translator {
protected:
	std::vector<std::shared_ptr<Atom>> _atoms;
	SymbolTable _symbolTable;
	StringTable _stringTable;
	Scanner _scanner;
	Token _currentLexem;
public:
	Translator(std::istream& is);
	void printAtoms(std::ostream& stream);
	void generateAtom(std::shared_ptr<Atom> atom);

};