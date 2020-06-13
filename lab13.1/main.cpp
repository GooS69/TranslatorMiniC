#include <iostream>
#include <fstream>
#include "StringTable.h"
#include "SymbolTable.h"
#include "Translator.h"

int main()
{







	std::ifstream ifile("myprog.txt");
	Translator T(ifile);
	try {
		SymbolTable S = SymbolTable();
		auto R = S.add("in memory");
		std::shared_ptr<BinaryOpAtom> A = std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADDDDD", R, R, R));
		//std::cout << A.toString();
		T.generateAtom(A);
		T.printAtoms(std::cout);
	}
	catch (TranslationException exception) {
		std::cout << exception.what();
	}
}

