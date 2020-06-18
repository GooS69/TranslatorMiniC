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
	int ArgList(Scope scope);
	int ArgList_(Scope scope);

	void DeclareStmt(Scope scope);
	void DeclareStmt_(Scope scope, TableRecord::RecordType p, std::string q);
	TableRecord::RecordType Type(Scope scope);
	void DeclVarList_(Scope scope, TableRecord::RecordType p);
	void InitVar(Scope scope, TableRecord::RecordType p, std::string q);
	int ParamList(Scope scope);
	int ParamList_(Scope scope);
	void StmtList(Scope scope);
	void Stmt(Scope scope);
	void AssignOrCallOp(Scope scope);
	void AssignOrCall(Scope scope);
	void AssignOrCall_(Scope scope, std::string p);
	void WhileOp(Scope scope);
	void ForOp(Scope scope);
	void ForInit(Scope scope);
	std::shared_ptr<RValue> ForExp(Scope scope);
	void ForLoop(Scope scope);
	void IfOp(Scope scope);
	void ElsePart(Scope scope);
	void IOp(Scope scope);
	void OOp(Scope scope);
	void OOp_(Scope scope);
	void SwitchOp(Scope scope);
	void Cases(Scope scope, std::shared_ptr<RValue> p, std::shared_ptr<LabelOperand> end);
	std::shared_ptr<LabelOperand> ACase(Scope scope,std::shared_ptr<RValue> p, std::shared_ptr<LabelOperand> end);
	void Cases_(Scope scope, std::shared_ptr<RValue> p, std::shared_ptr<LabelOperand> end, std::shared_ptr<LabelOperand> def);

public:
	Translator(std::istream& is);
	void startTranslate();
	void startTranslate_withoutTable();
	void getNextLexem();
	void printAtoms(std::ostream& stream);
	void printSymbolTable(std::ostream& stream);
	void printStringTable(std::ostream& stream);
	void generateAtom(Scope scope,std::shared_ptr<Atom> atom);
	std::shared_ptr<LabelOperand> newLabel();
	void syntaxError(const std::string& message);
	void lexicalError(const std::string& message);
};