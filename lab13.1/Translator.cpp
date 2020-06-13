#include "Translator.h"

TranslationExeption::TranslationExeption(std::string message) {
	_message = message;
}

const char* TranslationExeption::what()const noexcept {
	return _message.c_str();
}


Translator::Translator(std::istream& is) :_scanner(Scanner(is)){
	_symbolTable = SymbolTable();
	_stringTable = StringTable();
	_label_counter = 0;
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