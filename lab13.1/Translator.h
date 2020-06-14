#pragma once
#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include "Scanner.h"


class TranslationException :public std::exception {
protected:
	std::string _message;
public:
	TranslationException(std::string message);
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
	bool _epsilonFlag = false;

	std::shared_ptr<RValue> E();
	std::shared_ptr<RValue> E7();
	std::shared_ptr<RValue> E7_(std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E6();
	std::shared_ptr<RValue> E6_(std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E5();
	std::shared_ptr<RValue> E5_(std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E4();
	std::shared_ptr<RValue> E4_(std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E3();
	std::shared_ptr<RValue> E3_(std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E2();
	std::shared_ptr<RValue> E1();
	std::shared_ptr<RValue> E1_(std::string p);
public:
	Translator(std::istream& is);
	void startTranslate();
	void getNextLexem();
	void printAtoms(std::ostream& stream);
	void generateAtom(std::shared_ptr<Atom> atom);
	std::shared_ptr<LabelOperand> newLabel();
	void syntaxError(const std::string& message);
	void lexicalError(const std::string& message);


	


};