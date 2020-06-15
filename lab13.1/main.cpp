#include <iostream>
#include <fstream>
#include "StringTable.h"
#include "SymbolTable.h"
#include "Translator.h"

int main()
{
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	try {
		t.syntaxError("There is no second |");
	}
	catch(TranslationException exception){
		std::cout << exception.what();
	}
}

