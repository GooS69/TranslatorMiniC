#pragma once
#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include "Scanner.h"
#include <map>



class TranslationException :public std::exception {
protected:
	std::string _message;
public:
	TranslationException(std::string message);
	const char* what()const noexcept override;
};


class Translator {
protected:
	std::map<Scope, std::vector<std::shared_ptr<Atom>>> _atoms;
	SymbolTable _symbolTable;
	StringTable _stringTable;
	Scanner _scanner;
	Token _currentLexem;
	
	int _label_counter;
	bool _epsilonFlag = false;
	std::vector<Token> _tokens;

	std::shared_ptr<RValue> E(Scope scope);
	std::shared_ptr<RValue> E7(Scope scope);
	std::shared_ptr<RValue> E7_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E6(Scope scope);
	std::shared_ptr<RValue> E6_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E5(Scope scope);
	std::shared_ptr<RValue> E5_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E4(Scope scope);
	std::shared_ptr<RValue> E4_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E3(Scope scope);
	std::shared_ptr<RValue> E3_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E2(Scope scope);
	std::shared_ptr<RValue> E1(Scope scope);
	std::shared_ptr<RValue> E1_(Scope scope, std::string p);
public:
	Translator(std::istream& is);
	void startTranslate();
	void getNextLexem();
	void printAtoms(std::ostream& stream);
	void printSymbolTable(std::ostream& stream);
	void generateAtom(Scope scope,std::shared_ptr<Atom> atom);
	std::shared_ptr<LabelOperand> newLabel();
	void syntaxError(const std::string& message);
	void lexicalError(const std::string& message);
};