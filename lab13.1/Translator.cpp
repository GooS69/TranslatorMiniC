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
	E();
	printAtoms(std::cout);
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
	for (int i = 0; i < _atoms.size(); i++) {
		stream << _atoms[i]->toString() << std::endl;
	}
}


void Translator::generateAtom(std::shared_ptr<Atom> atom) {
	_atoms.push_back(atom);
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


std::shared_ptr<RValue> Translator::E() {								// Правило 1.1
	auto q = E7();
	if (!q) {
		syntaxError("E7 at E return nullptr");
	}
	return q;
}


std::shared_ptr<RValue> Translator::E7() {								// Правило 2.1
	auto q = E6();
	if (!q) {
		syntaxError("E6 at E7 return nullptr");
	}
	auto s = E7_(q);
	if (!s) {
		syntaxError("E7_ at E7 return nullptr");
	}

	return s;
}


std::shared_ptr<RValue> Translator::E7_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opor) {						// Правило 3.1
		auto r = E6();
		if (!r) {
			syntaxError("E6 at E7_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E7_ return nullptr");
		}
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("OR", p, r, s)));
		auto t = E7_(s);
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


std::shared_ptr<RValue> Translator::E6() {								// Правило 5.1
	auto q = E5();
	if (!q) {
		syntaxError("E5 at E6 return nullptr");
	}
	auto s = E6_(q);
	if (!s) {
		syntaxError("E6_ at E6 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E6_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opand) {						// Правило 6.1
		auto r = E5();
		if (!r) {
			syntaxError("E5 at E6_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E6_ return nullptr");
		}
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("AND", p, r, s)));
		auto t = E6_(s);
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


std::shared_ptr<RValue> Translator::E5() {								// Правило 8.1
	auto q = E4();
	if (!q) {
		syntaxError("E4 at E5 return nullptr");
	}
	auto s = E5_(q);
	if (!s) {
		syntaxError("E5_ at E5 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E5_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opeq) {						// Правило 9.1
		auto r = E4();
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("EQ", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::opne) {						// Правило 10.1
		auto r = E4();
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("NE", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::opgt) {						// Правило 11.1
		auto r = E4();
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("GT", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::oplt) {						// Правило 12.1
		auto r = E4();
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("LT", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::ople) {						// Правило 13.1
		auto r = E4();
		if (!r) {
			syntaxError("E4 at E5_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E5_ return nullptr");
		}
		auto l = newLabel();
		if (!l) {
			syntaxError("newLabel at E5_ return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("LE", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	_epsilonFlag = true;												// Правило 14.1
	return p;
}


std::shared_ptr<RValue> Translator::E4() {								// Правило 15.1
	auto q = E3();
	if (!q) {
		syntaxError("E3 at E4 return nullptr");
	}
	auto s = E4_(q);
	if (!s) {
		syntaxError("E4_ at E4 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E4_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opplus) {					// Правило 16.1
		auto r = E3();
		if (!r) {
			syntaxError("E3 at E4_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E4_ return nullptr");
		}
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", p, r, s)));
		auto t = E4_(s);
		if (!t) {
			syntaxError("E4_ at E4_ return nullptr");
		}
		return t;
	}
	if (_currentLexem.type() == LexemType::opminus) {					// Правило 17.1
		auto r = E3();
		if (!r) {
			syntaxError("E3 at E4_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E4_ return nullptr");
		}
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("SUB", p, r, s)));
		auto t = E4_(s);
		if (!t) {
			syntaxError("E4_ at E4_ return nullptr");
		}
		return t;
	}
	_epsilonFlag = true;												// Правило 18.1
	return p;
}


std::shared_ptr<RValue> Translator::E3() {								// Правило 19.1
	auto q = E2();
	if (!q) {
		syntaxError("E2 at E3 return nullptr");
	}
	auto s = E3_(q);
	if (!s) {
		syntaxError("E3_ at E3 return nullptr");
	}
	return s;
}


std::shared_ptr<RValue> Translator::E3_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opmult) {					// Правило 20.1
		auto r = E2();
		if (!r) {
			syntaxError("E2 at E3_ return nullptr");
		}
		auto s = _symbolTable.alloc();
		if (!s) {
			syntaxError("alloc at E3_ return nullptr");
		}
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", p, r, s)));
		auto t = E3_(s);
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


std::shared_ptr<RValue> Translator::E2() {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opnot) {						// Правило 22.1
		auto q = E1();
		if (!q) {
			syntaxError("E1 at E2 return nullptr");
		}
		auto r = _symbolTable.alloc();
		if (!r) {
			syntaxError("alloc at E2 return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("NOT", q, r)));
		return r;
	}
	else {																// Правило 23.1
		_epsilonFlag = true;
		auto q = E1();
		if (!q) {
			syntaxError("E1 at E2 return nullptr");
		}
		return q;
	}
}


std::shared_ptr<RValue> Translator::E1() {
	getNextLexem();
	if (_currentLexem.type() == LexemType::lpar) {						//Правило 24.1
		auto q = E();
		if (!q) {
			syntaxError("E at E1 return nullptr");
		}
		getNextLexem();
		if (_currentLexem.type() != LexemType::rpar) {
			syntaxError("expected )");
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
			syntaxError("expected id");
		}
		std::string name = _currentLexem.str();
		auto q = _symbolTable.add(name);
		if (!q) {
			syntaxError("add at E1 return nullptr");
		}
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", q, std::make_shared<NumberOperand>(NumberOperand(1)), q)));
		return q;
	}
	if (_currentLexem.type() == LexemType::id) {						// Правило 28.1
		std::string name = _currentLexem.str();
		auto s = E1_(name);
		if (!s) {
			syntaxError("E1_ at E1 return nullptr");
		}
		return s;
	}
	syntaxError("expected ( num char ++ id");
}


std::shared_ptr<RValue> Translator::E1_(std::string p) {				// Правило 29.1
	getNextLexem();
	if (_currentLexem.type() == LexemType::opinc) {
		auto s = _symbolTable.add(p);
		if (!s) {
			syntaxError("add at E1_ return nullptr");
		}
		auto r = _symbolTable.alloc();
		if (!r) {
			syntaxError("alloc at E1_ return nullptr");
		}
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", s, r));
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", s, std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		return r;
	}
	_epsilonFlag = true;												// Правило 31.1
	auto q = _symbolTable.add(p);
	if (!q) {
		syntaxError("add at E1_ return nullptr");
	}
	return q;
}


