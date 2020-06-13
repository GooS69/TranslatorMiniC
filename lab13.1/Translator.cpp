#include "Translator.h"

Translator::Translator(std::istream& is) :_scanner(Scanner(is)){
	_symbolTable = SymbolTable();
	_stringTable = StringTable();
}


void Translator::printAtoms(std::ostream& stream) {
	for (int i = 0; i < _atoms.size(); i++) {
		stream << _atoms[i] << std::endl;
	}
}