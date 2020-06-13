#pragma once
#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include "Scanner.h"


class TranslationExeption :public std::exception {
protected:
	std::string _message;
public:
	TranslationExeption(std::string message);
	const char* what()const noexcept override;
};


class Translator {
protected:
	std::vector<std::shared_ptr<Atom>> _atoms;
	SymbolTable _symbolTable;
	StringTable _stringTable;
	Scanner _scanner;
	Token _currentLexem;
	
	int _label_counter;
public:
	Translator(std::istream& is);
	void printAtoms(std::ostream& stream);
	void generateAtom(std::shared_ptr<Atom> atom);
	std::shared_ptr<LabelOperand> newLabel();
	void syntaxError(const std::string& message);
	void lexicalError(const std::string& message);
};