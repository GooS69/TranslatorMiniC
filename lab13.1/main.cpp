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
		T.startTranslate();
	}
	catch (TranslationException exception) {
		std::cout << exception.what();
	}
}

