#include <iostream>
#include <fstream>
#include "StringTable.h"
#include "SymbolTable.h"
#include "Translator.h"

int main()
{
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	std::ofstream ofile("prog_atom.txt");
	try {
		t.startTranslate();
		t.printAtoms(ofile);
		ofile << std::endl<<"Symbol Table"<<std::endl;
		t.printSymbolTable(ofile);
		ofile << std::endl << "String Table" << std::endl;
		t.printStringTable(ofile);
	}
	catch(TranslationException exception){
		std::cout << exception.what();
	}
}

