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
	StmtList(GlobalScope);
	//if (_currentLexem.type() != LexemType::eof) {
	//	syntaxError("expected operation(there are still tokens)");
	//}
	printAtoms(std::cout);
	std::cout << std::endl << "Symbol table" << std::endl;
	_symbolTable.print(std::cout);
}

void Translator::startTranslate_withoutTable() {
	StmtList(GlobalScope);
	//if (_currentLexem.type() != LexemType::eof) {
	//	syntaxError("expected operation(there are still tokens)");
	//}
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
		std::cout << "*" << _currentLexem.toString() << "*";
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


std::shared_ptr<RValue> Translator::E(Scope scope) {								// Правило 1.1
	//std::cout << "E";
	auto q = E7(scope);
	if (!q) {
		syntaxError("E7 at E return nullptr");
	}
	return q;
}


std::shared_ptr<RValue> Translator::E7(Scope scope) {								// Правило 2.1
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
	if (_currentLexem.type() == LexemType::opor) {						// Правило 3.1
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
		_epsilonFlag = true;											// Правило 4.1
		return p;
	}
}


std::shared_ptr<RValue> Translator::E6(Scope scope) {								// Правило 5.1
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
	if (_currentLexem.type() == LexemType::opand) {						// Правило 6.1
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
		_epsilonFlag = true;											// Правило 7.1
		return p;
	}
}


std::shared_ptr<RValue> Translator::E5(Scope scope) {								// Правило 8.1
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
	if (_currentLexem.type() == LexemType::opeq) {						// Правило 9.1
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
	if (_currentLexem.type() == LexemType::opne) {						// Правило 10.1
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
	if (_currentLexem.type() == LexemType::opgt) {						// Правило 11.1
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
	if (_currentLexem.type() == LexemType::oplt) {						// Правило 12.1
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
	if (_currentLexem.type() == LexemType::ople) {						// Правило 13.1
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
	_epsilonFlag = true;												// Правило 14.1
	return p;
}


std::shared_ptr<RValue> Translator::E4(Scope scope) {								// Правило 15.1
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
	if (_currentLexem.type() == LexemType::opplus) {					// Правило 16.1
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
	if (_currentLexem.type() == LexemType::opminus) {					// Правило 17.1
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
	_epsilonFlag = true;												// Правило 18.1
	return p;
}


std::shared_ptr<RValue> Translator::E3(Scope scope) {								// Правило 19.1
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
	if (_currentLexem.type() == LexemType::opmult) {					// Правило 20.1
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
	else {																// Правило 21.1
		_epsilonFlag = true;
		return p;
	}
}


std::shared_ptr<RValue> Translator::E2(Scope scope) {
	//std::cout << "E2";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opnot) {						// Правило 22.1
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
	else {																// Правило 23.1
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
	if (_currentLexem.type() == LexemType::lpar) {						//Правило 24.1
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
	if (_currentLexem.type() == LexemType::num) {						//Правило 25.1
		return std::make_shared<NumberOperand>(_currentLexem.value());
	}
	if (_currentLexem.type() == LexemType::chr) {						// Правило 26.1
		return std::make_shared<NumberOperand>(_currentLexem.value());
	}	
	if (_currentLexem.type() == LexemType::opinc) {						// Правило 27.1
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
	if (_currentLexem.type() == LexemType::id) {						// Правило 28.1
		std::string name = _currentLexem.str();
		auto s = E1_(scope, name);
		if (!s) {
			syntaxError("E1_ at E1 return nullptr");
		}
		return s;
	}
	syntaxError("expected ( num char ++ id at E1");
}


std::shared_ptr<RValue> Translator::E1_(Scope scope, std::string p) {				// Правило 29.1
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
	if (_currentLexem.type() == LexemType::lpar) {						// Правило 30.1
		int n = ArgList(scope);
		auto s = _symbolTable.checkFunc(p, n);
		if (!s) {
			syntaxError("checkFunl at E1_ return nullptr");
		}
		auto r = _symbolTable.alloc(scope);
		if (!r) {
			syntaxError("alloc at E1_ return nullptr");
		}
		getNextLexem();
		if (_currentLexem.type() != LexemType::rpar) {
			syntaxError("expected ) at E1_");
		}
		generateAtom(scope, std::make_shared<CallAtom>(CallAtom(s, r)));
		return r;
	}
	_epsilonFlag = true;												// Правило 31.1
	auto q = _symbolTable.checkVar(scope, p);
	if (!q) {
		syntaxError("add at E1_ return nullptr");
	}
	return q;
}


int Translator::ArgList(Scope scope) {
	getNextLexem();
	_epsilonFlag = true;												// Правило 32.1
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
	return 0;															// Правило 33.1
}


int Translator::ArgList_(Scope scope) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::comma) {						// Правило 34.1
		auto p = E(scope);
		if (!p) {
			syntaxError("E at ArgList_ return nullptr");
		}
		int m = ArgList_(scope);
		generateAtom(scope, std::make_shared<ParamAtom>(ParamAtom(p)));
		return ++m;
	}
	_epsilonFlag = true;												// Правило 35.1
	return 0;					
}

//------------------------------------------------------------------------------------------//



void Translator::DeclareStmt(Scope scope) {								// Правило 1.2
	std::cout << "DeclareStmt " ;
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
	std::cout << "DeclareStmt_ " ;
	getNextLexem();
	if (_currentLexem.type() == LexemType::lpar) {						// Правило 2.2
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
	if (_currentLexem.type() == LexemType::opassign) {					// Правило 3.2
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
	_symbolTable.addVar(q, scope, p);									// Правило 4.2
	DeclVarList_(scope, p);
	getNextLexem();
	if (_currentLexem.type() != LexemType::semicolon) {
		syntaxError("expected ; at DeclareStmt_");
	}
	return;
}


TableRecord::RecordType Translator::Type(Scope scope) {
	std::cout << "Type " ;
	getNextLexem();
	if (_currentLexem.type() == LexemType::kwchar) {					// Правило 5.2
		return TableRecord::RecordType::chr;
	}
	if (_currentLexem.type() == LexemType::kwint) {						// Правило 6.2
		return TableRecord::RecordType::integer;
	}
	syntaxError("expected kwchar kwint at Type");
	return TableRecord::RecordType::unknown;
}


void Translator::DeclVarList_(Scope scope, TableRecord::RecordType p) {
	std::cout << "DeclVarList_ " ;
	getNextLexem();
	if (_currentLexem.type() == LexemType::comma) {						// Правило 7.2
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at DeclVarList_");
		}
		InitVar(scope, p, _currentLexem.str());
		DeclVarList_(scope, p);
		return;
	}
	_epsilonFlag = true;												// Правило 8.2
	return;
}


void Translator::InitVar(Scope scope, TableRecord::RecordType p, std::string q) {
	std::cout << "InitVar " ;
	getNextLexem();
	if (_currentLexem.type() == LexemType::opassign) {					// Правило 9.2
		getNextLexem();
		if (_currentLexem.type() != LexemType::chr && _currentLexem.type() != LexemType::num) {
			syntaxError("expected chr num at DeclVarList_");
		}
		_symbolTable.addVar(q, scope, p, _currentLexem.value());
		return;
	}
	_symbolTable.addVar(q, scope, p);									// Правило 10.2
	_epsilonFlag = true;
	return;
}


int Translator::ParamList(Scope scope) {
	std::cout << "ParamList " ;
	getNextLexem();
	_epsilonFlag = true;
	if (_currentLexem.type() == LexemType::kwchar || _currentLexem.type() == LexemType::kwint) {	// Правило 11.2
		TableRecord::RecordType q = Type(scope);
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at ParamList");
		}
		_symbolTable.addVar(_currentLexem.str(), scope, q);
		int s = ParamList_(scope);
		return ++s;
	}
	return 0;																// Правило 12.2
}


int Translator::ParamList_(Scope scope) {
	std::cout << "ParamList_ " ;
	getNextLexem();
	if (_currentLexem.type() == LexemType::comma) {							// Правило 13.2
		TableRecord::RecordType q = Type(scope);
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at ParamList_");
		}
		_symbolTable.addVar(_currentLexem.str(), scope, q);
		int s = ParamList_(scope);
		return ++s;
	}
	_epsilonFlag = true;													// Правило 14.2
	return 0;
}


void Translator::StmtList(Scope scope) {
	std::cout << "StmtList ";
	getNextLexem();
	_epsilonFlag = true;
	if (_currentLexem.type() == LexemType::kwchar || _currentLexem.type() == LexemType::kwint ||
		_currentLexem.type() == LexemType::id || _currentLexem.type() == LexemType::kwwhile ||
		_currentLexem.type() == LexemType::kwfor || _currentLexem.type() == LexemType::kwif ||
		_currentLexem.type() == LexemType::lbrace || _currentLexem.type() == LexemType::kwin ||
		_currentLexem.type() == LexemType::kwreturn || _currentLexem.type() == LexemType::semicolon) {
		Stmt(scope);														// Правило 15.2							
		StmtList(scope);
	}
	return;																	// Правило 16.2
}



void Translator::Stmt(Scope scope) {
	std::cout << "Stmt " ;
	getNextLexem();
	if (_currentLexem.type() == LexemType::kwchar || _currentLexem.type() == LexemType::kwint){	
		_epsilonFlag = true;												// Правило 17.2
		DeclareStmt(scope);
		return;
	}
	if (_currentLexem.type() == LexemType::id) {							// Правило 18.2
		_epsilonFlag = true;
		AssignOrCallOp(scope);
		return;
	}
	if (_currentLexem.type() == LexemType::kwwhile) {						// Правило 19.2
		_epsilonFlag = true;
		WhileOp(scope);
		return;
	}
	if (_currentLexem.type() == LexemType::kwfor) {							// Правило 20.2
		_epsilonFlag = true;
		ForOp(scope);
		return;
	}
	if (_currentLexem.type() == LexemType::kwif) {							// Правило 21.2
		_epsilonFlag = true;
		IfOp(scope);
		return;
	}

	//if (_currentLexem.type() == LexemType::kwswitch) {							// Правило 22.2
	//	_epsilonFlag = true;
	//	SwitchOp(scope);
	//	return;
	//}

	if (_currentLexem.type() == LexemType::kwin) {							// Правило 23.2
		_epsilonFlag = true;
		IOp(scope);
		return;
	}

	if (_currentLexem.type() == LexemType::kwout) {							// Правило 24.2
		_epsilonFlag = true;
		OOp(scope);
		return;
	}


	if (_currentLexem.type() == LexemType::lbrace) {						// Правило 25.2
		StmtList(scope);
		getNextLexem();
		if (_currentLexem.type() != LexemType::rbrace) {
			syntaxError("expected } at Stmt");
		}
		return;
	}
	if (_currentLexem.type() == LexemType::kwreturn) {						// Правило 26.2
		auto p = E(scope);
		generateAtom(scope, std::make_shared<RetAtom>(RetAtom(p)));
		getNextLexem();
		if (_currentLexem.type() != LexemType::semicolon) {
			syntaxError("expected ; at Stmt");
		}
		return;
	}

	if (_currentLexem.type() == LexemType::semicolon) {						// Правило 27.2
		return;
	}


}


void Translator::AssignOrCallOp(Scope scope) {								// Правило 28.2
	std::cout << "AssignOrCallOp " ;
	AssignOrCall(scope);
	getNextLexem();
	if (_currentLexem.type() != LexemType::semicolon) {
		syntaxError("expected ; at AssignOrCallOp");
	}
	return;
}


void Translator::AssignOrCall(Scope scope) {								// Правило 29.2
	std::cout << "AssignOrCall " ;
	getNextLexem();
	if (_currentLexem.type() != LexemType::id) {
		syntaxError("expected id at AssignOrCall");
	}
	AssignOrCall_(scope, _currentLexem.str());
	return;
}


void Translator::AssignOrCall_(Scope scope, std::string p) {
	std::cout << "AssignOrCall_ ";
	getNextLexem();
	if (_currentLexem.type() == LexemType::opassign) {						// Правило 30.2
		auto r = _symbolTable.checkVar(scope, p);
		auto q = E(scope);
		generateAtom(scope, std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", q, r)));
		return;
	}
	if (_currentLexem.type() == LexemType::lpar) {							// Правило 31.2
		int n = ArgList(scope);
		auto q = _symbolTable.checkFunc(p, n);
		auto r = _symbolTable.alloc(scope);
		getNextLexem();
		if (_currentLexem.type() != LexemType::rpar) {
			syntaxError("expected ) at AssignOrCall_");
		}
		generateAtom(scope, std::make_shared<CallAtom>(CallAtom(q, r)));
		return;
	}
	syntaxError("expected = ( at AssignOrCall_");
	return;
}


void Translator::WhileOp(Scope scope) {										// Правило 32.2
	std::cout << "WhileOp ";
	getNextLexem();
	if (_currentLexem.type() != LexemType::kwwhile) {
		syntaxError("expected while at WhileOp");
	}
	auto l1 = newLabel();
	auto l2 = newLabel();
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l1)));
	getNextLexem();
	if (_currentLexem.type() != LexemType::lpar) {
		syntaxError("expected ( at WhileOp");
	}
	auto p = E(scope);
	getNextLexem();
	if (_currentLexem.type() != LexemType::rpar) {
		syntaxError("expected ) at WhileOp");
	}
	generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("EQ", p, std::make_shared<NumberOperand>(NumberOperand(0)),l2)));
	Stmt(scope);
	generateAtom(scope, std::make_shared<JumpAtom>(JumpAtom(l1)));
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l2)));
	return;
}


void Translator::ForOp(Scope scope) {											// Правило 33.2
	std::cout << "ForOp ";
	getNextLexem();
	if (_currentLexem.type() != LexemType::kwfor) {
		syntaxError("expected for at ForOp");
	}
	getNextLexem();
	if (_currentLexem.type() != LexemType::lpar) {
		syntaxError("expected ( at ForOp");
	}
	auto l1 = newLabel();
	auto l2 = newLabel();
	auto l3 = newLabel();
	auto l4 = newLabel();
	ForInit(scope);
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l1)));
	auto p = ForExp(scope);
	getNextLexem();
	if (_currentLexem.type() != LexemType::semicolon) {
		syntaxError("expected ; at ForOp");
	}
	generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("EQ", p, std::make_shared<NumberOperand>(NumberOperand(0)), l4)));
	generateAtom(scope, std::make_shared<JumpAtom>(JumpAtom(l3)));
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l2)));
	ForLoop(scope);
	generateAtom(scope, std::make_shared<JumpAtom>(JumpAtom(l1)));
	getNextLexem();
	if (_currentLexem.type() != LexemType::rpar) {
		syntaxError("expected ) at ForOp");
	}
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l3)));
	Stmt(scope);
	generateAtom(scope, std::make_shared<JumpAtom>(JumpAtom(l2)));
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l4)));
	return;
}


void Translator::ForInit(Scope scope) {
	std::cout << "ForInit ";
	getNextLexem();
	_epsilonFlag = true;
	if (_currentLexem.type() == LexemType::id) {									// Правило 34.2
		AssignOrCallOp(scope);
		return;
	}
	return;																			// Правило 35.2
}


std::shared_ptr<RValue> Translator::ForExp(Scope scope) {
	std::cout << "ForExp ";
	getNextLexem();
	_epsilonFlag = true;
	if (_currentLexem.type() == LexemType::opnot || _currentLexem.type() == LexemType::lpar || _currentLexem.type() == LexemType::num
		|| _currentLexem.type() == LexemType::chr || _currentLexem.type() == LexemType::opinc || _currentLexem.type() == LexemType::id) {
		auto q = E(scope);															// Правило 36.2
		return q;
	}
	return std::make_shared<NumberOperand>(NumberOperand(1));						// Правило 37.2
}


void Translator::ForLoop(Scope scope) {
	std::cout << "ForLoop ";
	getNextLexem();
	if (_currentLexem.type() == LexemType::id) {									// Правило 38.2
		_epsilonFlag = true;
		AssignOrCallOp(scope);
		return;
	}
	if (_currentLexem.type() == LexemType::opinc) {									// Правило 39.2
		getNextLexem();
		if (_currentLexem.type() != LexemType::id) {
			syntaxError("expected id at ForLoop");
		}
		auto p = _symbolTable.checkVar(scope, _currentLexem.str());
		generateAtom(scope, std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", p, std::make_shared<NumberOperand>(NumberOperand(1)), p)));
		return;
	}
	_epsilonFlag = true;															// Правило 40.2
	return;
}


void Translator::IfOp(Scope scope) {												// Правило 41.2
	std::cout << "IfOp ";
	getNextLexem();
	if (_currentLexem.type() != LexemType::kwif) {
		syntaxError("expected if at IfOp");
	}
	getNextLexem();
	if (_currentLexem.type() != LexemType::lpar) {
		syntaxError("expected ( at IfOp");
	}
	auto l1 = newLabel();
	auto l2 = newLabel();
	auto p = E(scope);
	getNextLexem();
	if (_currentLexem.type() != LexemType::rpar) {
		syntaxError("expected ) at IfOp");
	}
	generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("EQ", p, std::make_shared<NumberOperand>(NumberOperand(0)), l1)));
	Stmt(scope);
	generateAtom(scope, std::make_shared<JumpAtom>(JumpAtom(l2)));
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l1)));
	ElsePart(scope);
	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(l2)));
	return;
}


void Translator::ElsePart(Scope scope) {
	std::cout << "ElsePart ";
	getNextLexem();
	std::cout << "?????????????";
	if (_currentLexem.type() == LexemType::kwelse) {									// Правило 42.2
		std::cout << "?????????????";
		Stmt(scope);
		return;
	}
	_epsilonFlag = true;																// Правило 43.2
	return;
}

//void Translator::SwitchOp(Scope scope) {												// Правило 44.2
//	getNextLexem();
//	if (_currentLexem.type() != LexemType::kwswitch) {
//		syntaxError("expected switch at SwitchOp");
//	}
//	getNextLexem();
//	if (_currentLexem.type() != LexemType::lpar) {
//		syntaxError("expected ( at SwitchOp");
//	}
//	auto p = E(scope);
//	getNextLexem();
//	if (_currentLexem.type() != LexemType::rpar) {
//		syntaxError("expected ) at SwitchOp");
//	}
//
//	getNextLexem();
//	if (_currentLexem.type() != LexemType::lbrace) {
//		syntaxError("expected { at SwitchOp");
//	}
//	auto end = newLabel();
//	Cases(scope, p, end);
//	getNextLexem();
//	if (_currentLexem.type() != LexemType::rbrace) {
//		syntaxError("expected } at SwitchOp");
//	}
//	generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(end)));
//	return;
//}


//void Translator::Cases(Scope scope, std::shared_ptr<RValue> p, std::shared_ptr<LabelOperand> end) {
//	auto def1 = ACase(scope, p, end);													// Правило 45.2
//	Cases_(scope, p, end, def1);
//	return;
//}


//std::shared_ptr<LabelOperand> Translator::ACase(Scope scope, std::shared_ptr<RValue> p, std::shared_ptr<LabelOperand> end) {
//	getNextLexem();
//	if (_currentLexem.type() == LexemType::kwcase) {									// Правило 48.2
//		getNextLexem();
//		if (_currentLexem.type() != LexemType::num) {
//			syntaxError("expected num at ACase");
//		}
//		int val = _currentLexem.value();
//		auto next = newLabel();
//		generateAtom(scope, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("NE", p, std::make_shared<NumberOperand>(NumberOperand(val)), next)));
//		getNextLexem();
//		if (_currentLexem.type() != LexemType::colon) {
//			syntaxError("expected : at ACase");
//		}
//		Stmt(scope);
//		generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(end)));
//		generateAtom(scope, std::make_shared<LabelAtom>(LabelAtom(next)));
//		return;
//	}
//	if (_currentLexem.type() == LexemType::kwdefault) {									// Правило 49.2
//
//		return;
//	}
//	syntaxError("expected case default at ACase");
//	return;
//}


void Translator::IOp(Scope scope) {														// Правило 50.2
	getNextLexem();
	if (_currentLexem.type() != LexemType::kwin) {
		syntaxError("expected in at IOp");
	}
	getNextLexem();
	if (_currentLexem.type() != LexemType::id) {
		syntaxError("expected id at IOp");
	}
	std::string name = _currentLexem.str();
	getNextLexem();
	if (_currentLexem.type() != LexemType::semicolon) {
		syntaxError("expected ; at IOp");
	}
	auto p = _symbolTable.checkVar(scope, name);
	generateAtom(scope, std::make_shared<InAtom>(InAtom(p)));
	return;
}


void Translator::OOp(Scope scope) {														// Правило 51.2
	getNextLexem();
	if (_currentLexem.type() != LexemType::kwout) {
		syntaxError("expected out at OOp");
	}
	OOp_(scope);
	if (_currentLexem.type() != LexemType::semicolon) {
		syntaxError("expected ; at OOp");
	}
	return;
}


void Translator::OOp_(Scope scope) {
	getNextLexem();																		// Правило 52.2
	if (_currentLexem.type() == LexemType::opnot || _currentLexem.type() == LexemType::lpar || _currentLexem.type() == LexemType::num
		|| _currentLexem.type() == LexemType::chr || _currentLexem.type() == LexemType::opinc || _currentLexem.type() == LexemType::id) {
		auto p = E(scope);
		generateAtom(scope, std::make_shared<OutAtom>(OutAtom(p)));
		return;
	}
	if (_currentLexem.type() == LexemType::str) {										// Правило 53.2
		auto s = _stringTable.add(_currentLexem.str());
		generateAtom(scope, std::make_shared<OutAtom>(OutAtom(s)));
		return;
	}
}