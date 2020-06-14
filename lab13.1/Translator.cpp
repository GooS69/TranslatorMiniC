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
	throw TranslationException(message);
}


std::shared_ptr<RValue> Translator::E() {
	auto q = E7();
	return q;
}


std::shared_ptr<RValue> Translator::E7() {
	auto q = E6();
	auto s = E7_(q);
	return s;
}


std::shared_ptr<RValue> Translator::E7_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opor) {						// Правило 3.1
		auto r = E6();
		auto s = _symbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("OR", p, r, s)));
		auto t = E7_(s);
		return t;
	}
	else {
		_epsilonFlag = true;											// Правило 4.1
		return p;
	}
}


std::shared_ptr<RValue> Translator::E6() {								// Правило 5.1
	auto q = E5();
	auto s = E6_(q);
	return s;
}


std::shared_ptr<RValue> Translator::E6_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opand) {						// Правило 6.1
		auto r = E5();
		auto s = _symbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("AND", p, r, s)));
		auto t = E6_(s);
		return t;
	}
	else {
		_epsilonFlag = true;											// Правило 7.1
		return p;
	}
}


std::shared_ptr<RValue> Translator::E5() {								// Правило 8.1
	auto q = E4();
	auto s = E5_(q);
	return s;
}


std::shared_ptr<RValue> Translator::E5_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opeq) {						// Правило 9.1
		auto r = E4();
		auto s = _symbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("EQ", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::opne) {						// Правило 10.1
		auto r = E4();
		auto s = _symbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("NE", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::opgt) {						// Правило 11.1
		auto r = E4();
		auto s = _symbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("GT", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::oplt) {						// Правило 12.1
		auto r = E4();
		auto s = _symbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("LT", p, r, l)));
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("MOV", std::make_shared<NumberOperand>(NumberOperand(0)), s)));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	if (_currentLexem.type() == LexemType::ople) {						// Правило 13.1
		auto r = E4();
		auto s = _symbolTable.alloc();
		auto l = newLabel();
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
	auto s = E4_(q);
	return s;
}


std::shared_ptr<RValue> Translator::E4_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opplus) {					// Правило 16.1
		auto r = E3();
		auto s = _symbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", p, r, s)));
		auto t = E4_(s);
		return t;
	}
	if (_currentLexem.type() == LexemType::opminus) {					// Правило 17.1
		auto r = E3();
		auto s = _symbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("SUB", p, r, s)));
		auto t = E4_(s);
		return t;
	}
	_epsilonFlag = true;												// Правило 18.1
	return p;
}


std::shared_ptr<RValue> Translator::E3() {								// Правило 19.1
	auto q = E2();
	auto s = E3_(q);
	return s;
}


std::shared_ptr<RValue> Translator::E3_(std::shared_ptr<RValue> p) {
	getNextLexem();
	if (_currentLexem.type() == LexemType::opmult) {					// Правило 20.1
		auto r = E2();
		auto s = _symbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", p, r, s)));
		auto t = E3_(s);
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
		auto r = _symbolTable.alloc();
		generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("NOT", q, r)));
		return r;
	}
	else {																// Правило 23.1
		_epsilonFlag = true;
		auto q = E1();
		return q;
	}
}


std::shared_ptr<RValue> Translator::E1() {
	getNextLexem();
	if (_currentLexem.type() == LexemType::lpar) {						//Правило 24.1
		auto q = E();
		if (!q) {
			syntaxError("dfhzdgn");
		}
		getNextLexem();
		if (_currentLexem.type() != LexemType::rpar) {
			syntaxError("sdgers");
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
			syntaxError("sdgers");
		}
		std::string name = _currentLexem.str();
		auto q = _symbolTable.add(name);
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", q, std::make_shared<NumberOperand>(NumberOperand(1)), q)));
		return q;
	}
	if (_currentLexem.type() == LexemType::id) {						// Правило 28.1
		std::string name = _currentLexem.str();
		auto s = E1_(name);
		return s;
	}
	syntaxError("sdgers");
}


std::shared_ptr<RValue> Translator::E1_(std::string p) {				// Правило 29.1
	getNextLexem();
	if (_currentLexem.type() == LexemType::opinc) {
		auto s = _symbolTable.add(p);
		auto r = _symbolTable.alloc();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", s, r));
		generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", s, std::make_shared<NumberOperand>(NumberOperand(1)), s)));
		return r;
	}
	_epsilonFlag = true;												// Правило 31.1
	auto q = _symbolTable.add(p);
	return q;
}


