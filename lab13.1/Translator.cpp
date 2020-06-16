#include "Translator.h"

TranslationException::TranslationException(std::string message) {
	_message = message;
}

const char* TranslationException::what()const noexcept {
	return _message.c_str();
}


Translator::Translator(std::istream& is) :_scanner(Scanner(is)){
	_symbolTable = SymbolTable();
	_stringTable = StringTable();
	_label_counter = 0;
}


void Translator::startTranslate() {
	E(GlobalScope);
	if (_currentLexem.type() != LexemType::eof) {
		syntaxError("expected operation(there are still tokens)");
	}
	printAtoms(std::cout);
	std::cout << std::endl << "Symbol table" << std::endl;
	_symbolTable.print(std::cout);
}


void Translator::getNextLexem() {
	if (_epsilonFlag) {
		_epsilonFlag = false;
		return;
	}
	else {
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error) {
			lexicalError(_currentLexem.str());
		}
		_tokens.push_back(_currentLexem);
	}
}


void Translator::printAtoms(std::ostream& stream) {
	for (auto it = _atoms.begin(); it != _atoms.end();it++) {
		Scope scope = it->first;
		std::vector <std::shared_ptr<Atom>> &atoms = it->second;
		for (int i = 0; i < atoms.size(); i++) {
			stream << std::to_string(scope) << " " << atoms[i]->toString() << std::endl;
		}
	}
}


void Translator::printSymbolTable(std::ostream& stream) {
	_symbolTable.print(stream);
}


void Translator::generateAtom(Scope scope, std::shared_ptr<Atom> atom) {
	_atoms.emplace(scope, std::vector<std::shared_ptr<Atom>>{});
	_atoms[scope].push_back(atom);
}


std::shared_ptr<LabelOperand> Translator::newLabel() {
	return std::make_shared<LabelOperand>(LabelOperand(_label_counter++));
}


void Translator::syntaxError(const std::string& message) {
	throw TranslationException(message);
}


void Translator::lexicalError(const std::string& message) {
	std::string out;
	for (int i = _tokens.size() - 1; i >= _tokens.size() -3 && i >= 0; i--) {
		out = _tokens[i].toString()+ " " + out;
	}
	out += "\n" + message;
	throw TranslationException(out);
}


std::shared_ptr<RValue> Translator::E(Scope scope) {								// ������� 1.1
	//std::cout << "E";
	auto q = E7(scope);
	if (!q) {
		syntaxError("E7 at E return nullptr");
	}
	return q;
}


std::shared_ptr<RValue> Translator::E7(Scope scope) {								// ������� 2.1
	//std::cout << "E7";
	auto q = E6(scope);
	if (!q) {
		syntaxError("E6 at E7 return nullptr");
	}
	auto s = E7_(scope, q);
	if (!s) {
		syntaxError("E7_ at E7 return nullptr");
	}

	return s;
}


std::shared_ptr<RValue> Translator::E7_(Scope scope, std::shared_ptr<RValue> p) {
	//std::cout << "E7_";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opor) {						// ������� 3.1
		auto r = E6(scope);
		if (!r) {
			syntaxError("E6 at E7_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E7_ return nullptr");
		}
		generateAtom(scope ,std::make_shared<BinaryOpAtom>(BinaryOpAtom("OR", p, r, s)));
		auto t = E7_(scope, s);
		if (!t) {
			syntaxError("E7_ at E7_ return nullptr");
		}
		return t;
	}
	else {
		_epsilonFlag = true;											// ������� 4.1
		return p;
	}
}


std::shared_ptr<RValue> Translator::E6(Scope scope) {								// ������� 5.1
	//std::cout << "E6";
	auto q = E5(scope);
	if (!q) {
		syntaxError("E5 at E6 return nullptr");
	}
	auto s = E6_(scope, q);
	if (!s) {
		syntaxError("E6_ at E6 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E6_(Scope scope, std::shared_ptr<RValue> p) {
	//std::cout << "E6_";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opand) {						// ������� 6.1
		auto r = E5(scope);
		if (!r) {
			syntaxError("E5 at E6_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E6_ return nullptr");
		}
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("AND", p, r, s)));
		auto t = E6_(scope, s);
		if (!t) {
			syntaxError("E6_ at E6_ return nullptr");
		}
		return t;
	}
	else {
		_epsilonFlag = true;											// ������� 7.1
		return p;
	}
}


std::shared_ptr<RValue> Translator::E5(Scope scope) {								// ������� 8.1
	//std::cout << "E5";
	auto q = E4(scope);
	if (!q) {
		syntaxError("E4 at E5 return nullptr");
	}
	auto s = E5_(scope, q);
	if (!s) {
		syntaxError("E5_ at E5 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E5_(Scope scope, std::shared_ptr<RValue> p) {
	//std::cout << "E5_";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opeq) {						// ������� 9.1
		auto r = E4(scope);
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("EQ", p, r, l)));
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(scope, std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::opne) {						// ������� 10.1
		auto r = E4(scope);
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("NE", p, r, l)));
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(scope, std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::opgt) {						// ������� 11.1
		auto r = E4(scope);
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("GT", p, r, l)));
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(scope, std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::oplt) {						// ������� 12.1
		auto r = E4(scope);
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("LT", p, r, l)));
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(scope, std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::ople) {						// ������� 13.1
		auto r = E4(scope);
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("LE", p, r, l)));
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(scope, std::make_shared<LabelAtom>(l));
		return s;
	}
	_epsilonFlag = true;												// ������� 14.1
	return p;
}


std::shared_ptr<RValue> Translator::E4(Scope scope) {								// ������� 15.1
	//std::cout << "E4";
	auto q = E3(scope);
	if (!q) {
		syntaxError("E3 at E4 return nullptr");
	}
	auto s = E4_(scope, q);
	if (!s) {
		syntaxError("E4_ at E4 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E4_(Scope scope, std::shared_ptr<RValue> p) {
	//std::cout << "E4_"<<"("<<_currentLexem.toString()<<")";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opplus) {					// ������� 16.1
		auto r = E3(scope);
		if (!r) {
			syntaxError("E3 at E4_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E4_ return nullptr");
		}
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", p, r, s)));
		auto t = E4_(scope, s);
		if (!t) {
			syntaxError("E4_ at E4_ return nullptr");
		}
		return t;
	}
	if (_currentLexem.type() == LexemType::opminus) {					// ������� 17.1
		auto r = E3(scope);
		if (!r) {
			syntaxError("E3 at E4_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E4_ return nullptr");
		}
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("SUB", p, r, s)));
		auto t = E4_(scope, s);
		if (!t) {
			syntaxError("E4_ at E4_ return nullptr");
		}
		return t;
	}
	_epsilonFlag = true;												// ������� 18.1
	return p;
}


std::shared_ptr<RValue> Translator::E3(Scope scope) {								// ������� 19.1
	//std::cout << "E3";
	auto q = E2(scope);
	if (!q) {
		syntaxError("E2 at E3 return nullptr");
	}
	auto s = E3_(scope, q);
	if (!s) {
		syntaxError("E3_ at E3 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E3_(Scope scope, std::shared_ptr<RValue> p) {
	//std::cout << "E3_";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opmult) {					// ������� 20.1
		auto r = E2(scope);
		if (!r) {
			syntaxError("E2 at E3_ return nullptr");
		}
		auto s = _symbolTable.alloc(scope);
		if (!s) {
			syntaxError("alloc at E3_ return nullptr");
		}
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", p, r, s)));
		auto t = E3_(scope, s);
		if (!t) {
			syntaxError("E3_ at E3_ return nullptr");
		}
		return t;
	}
	else {																// ������� 21.1
		_epsilonFlag = true;
		return p;
	}
}


std::shared_ptr<RValue> Translator::E2(Scope scope) {
	//std::cout << "E2";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opnot) {						// ������� 22.1
		auto q = E1(scope);
		if (!q) {
			syntaxError("E1 at E2 return nullptr");
		}
		auto r = _symbolTable.alloc(scope);
		if (!r) {
			syntaxError("alloc at E2 return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("NOT", q, r)));
		return r;
	}
	else {																// ������� 23.1
		_epsilonFlag = true;
		auto q = E1(scope);
		if (!q) {
			syntaxError("E1 at E2 return nullptr");
		}
		return q;
	}
}


std::shared_ptr<RValue> Translator::E1(Scope scope) {
	//std::cout << "E1";
	getNextLexem();
	if (_currentLexem.type() == LexemType::lpar) {						//������� 24.1
		auto q = E(scope);
		if (!q) {
			syntaxError("E at E1 return nullptr");
		}
		getNextLexem();
		if (_currentLexem.type() != LexemType::rpar) {
			syntaxError("expected ) at E1");
		}
		return q;
	}
	if (_currentLexem.type() == LexemType::num) {						//������� 25.1
		return std::make_shared<NumberOperand>(_currentLexem.value());
	}
	if (_currentLexem.type() == LexemType::chr) {						// ������� 26.1
		return std::make_shared<NumberOperand>(_currentLexem.value());
	}	
	if (_currentLexem.type() == LexemType::opinc) {						// ������� 27.1
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at E1");
		}
		std::string name = _currentLexem.str();
		auto q = _symbolTable.checkVar(scope, name);
		if (!q) {
			syntaxError("add at E1 return nullptr");
		}
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", q, std::make_shared<NumberOperand>(NumberOperand(1)), q)));
		return q;
	}
	if (_currentLexem.type() == LexemType::id) {						// ������� 28.1
		std::string name = _currentLexem.str();
		auto s = E1_(scope, name);
		if (!s) {
			syntaxError("E1_ at E1 return nullptr");
		}
		return s;
	}
	syntaxError("expected ( num char ++ id at E1");
}


std::shared_ptr<RValue> Translator::E1_(Scope scope, std::string p) {				// ������� 29.1
	//std::cout << "E1_";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opinc) {
		auto s = _symbolTable.checkVar(scope, p);
		if (!s) {
			syntaxError("add at E1_ return nullptr");
		}
		auto r = _symbolTable.alloc(scope);
		if (!r) {
			syntaxError("alloc at E1_ return nullptr");
		}
		generateAtom(scope, std::make_shared<UnaryOpAtom>("MOV", s, r));
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", s, std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		return r;
	}
	if (_currentLexem.type() == LexemType::lpar) {						// ������� 30.1
		int n = ArgList(scope);
		auto s = _symbolTable.checkFunc(p, n);
		if (!s) {
			syntaxError("checkFunl at E1_ return nullptr");
		}
		auto r = _symbolTable.alloc(scope);
		if (!r) {
			syntaxError("alloc at E1_ return nullptr");
		}
		generateAtom(scope, std::make_shared<CallAtom>(CallAtom(s, r)));
		return r;
	}
	_epsilonFlag = true;												// ������� 31.1
	auto q = _symbolTable.checkVar(scope, p);
	if (!q) {
		syntaxError("add at E1_ return nullptr");
	}
	return q;
}


int Translator::ArgList(Scope scope) {
	getNextLexem();
	_epsilonFlag = true;												// ������� 32.1
	if (_currentLexem.type() == LexemType::opnot || _currentLexem.type() == LexemType::lpar || _currentLexem.type() == LexemType::num
		|| _currentLexem.type() == LexemType::chr || _currentLexem.type() == LexemType::opinc || _currentLexem.type() == LexemType::id) {
		auto p = E(scope);
		if (!p) {
			syntaxError("E at ArgList return nullptr");
		}
		int m = ParamList_(scope);
		generateAtom(scope, std::make_shared<ParamAtom>(ParamAtom(p)));
		return ++m;
	}
	return 0;															// ������� 33.1
}


int Translator::ArgList_(Scope scope) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::comma) {						// ������� 34.1
		auto p = E(scope);
		if (!p) {
			syntaxError("E at ArgList_ return nullptr");
		}
		int m = ArgList_(scope);
		generateAtom(scope, std::make_shared<ParamAtom>(ParamAtom(p)));
		return ++m;
	}
	_epsilonFlag = true;												// ������� 35.1
	return 0;					
}

//------------------------------------------------------------------------------------------//



void Translator::DeclareStmt(Scope scope) {								// ������� 1.2
	TableRecord::RecordType p = Type(scope);
	getNextLexem();
	if (_currentLexem.type() == LexemType::id) {
		std::string name = _currentLexem.str();
		DeclareStmt_(scope, p, name);
		return;
	}
	else {
		syntaxError("expected id in DeclareStmt");
		return;
	}
}


void Translator::DeclareStmt_(Scope scope, TableRecord::RecordType p, std::string q) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::lpar) {						// ������� 2.2
		if (scope > -1) {
			syntaxError("Scope > -1 at DeclareStmt_");
		}
		std::shared_ptr<MemoryOperand> c_ = _symbolTable.addFunc(q, p, 0);
		int n = ParamList(c_->index());
		_symbolTable.changeLen(c_->index(), n);
		getNextLexem();
		if (_currentLexem.type() != LexemType::rpar) {
			syntaxError("expected ) at DeclareStmt_");
		}
		getNextLexem();
		if (_currentLexem.type() != LexemType::lbrace) {
			syntaxError("expected { at DeclareStmt_");
		}
		StmtList(c_->index());
		getNextLexem();
		if (_currentLexem.type() != LexemType::rbrace) {
			syntaxError("expected } at DeclareStmt_");
		}
		generateAtom(c_->index(),std::make_shared<RetAtom>(RetAtom(std::make_shared<NumberOperand>(NumberOperand(0)))));
		return;
	}
	if (_currentLexem.type() == LexemType::opassign) {					// ������� 3.2
		getNextLexem();
		if (_currentLexem.type() != LexemType::num) {
			syntaxError("expected num at DeclareStmt_");
		}
		_symbolTable.addVar(q, scope, p, _currentLexem.value());
		DeclVarList_(scope, p);
		getNextLexem();
		if (_currentLexem.type() != LexemType::semicolon) {
			syntaxError("expected ; at DeclareStmt_");
		}
		return;
	}
	_epsilonFlag = true;
	_symbolTable.addVar(q, scope, p);									// ������� 4.2
	DeclVarList_(scope, p);
	return;
}


TableRecord::RecordType Translator::Type(Scope scope) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::kwchar) {					// ������� 5.2
		return TableRecord::RecordType::chr;
	}
	if (_currentLexem.type() == LexemType::kwint) {						// ������� 6.2
		return TableRecord::RecordType::integer;
	}
	syntaxError("expected kwchar kwint at Type");
	return TableRecord::RecordType::unknown;
}


void Translator::DeclVarList_(Scope scope, TableRecord::RecordType p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::comma) {						// ������� 7.2
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at DeclVarList_");
		}
		InitVar(scope, p, _currentLexem.str());
		DeclVarList_(scope, p);
		return;
	}
	_epsilonFlag = true;												// ������� 8.2
	return;
}


void Translator::InitVar(Scope scope, TableRecord::RecordType p, std::string q) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opassign) {					// ������� 9.2
		getNextLexem();
		if (_currentLexem.type() != LexemType::chr && _currentLexem.type() != LexemType::num) {
			syntaxError("expected chr num at DeclVarList_");
		}
		_symbolTable.addVar(q, scope, p, _currentLexem.value());
		return;
	}
	_symbolTable.addVar(q, scope, p);									// ������� 10.2
	_epsilonFlag = true;
	return;
}


int Translator::ParamList(Scope scope) {
	getNextLexem();
	_epsilonFlag = true;
	if (_currentLexem.type() == LexemType::kwchar || _currentLexem.type() == LexemType::kwint) {	// ������� 11.2
		TableRecord::RecordType q = Type(scope);
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at ParamList");
		}
		_symbolTable.addVar(_currentLexem.str(), scope, q);
		int s = ParamList_(scope);
		return ++s;
	}
	return 0;																// ������� 12.2
}


int Translator::ParamList_(Scope scope) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::comma) {							// ������� 13.2
		TableRecord::RecordType q = Type(scope);
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at ParamList_");
		}
		_symbolTable.addVar(_currentLexem.str(), scope, q);
		int s = ParamList_(scope);
		return ++s;
	}
	_epsilonFlag = true;													// ������� 14.2
	return 0;
}


void Translator::StmtList(Scope scope) {
	return;																	// ������� 16.2
}
