#include <iostream>
#include <sstream>
#include "StringTable.h"
#include "SymbolTable.h"
#include "Translator.h"

int main()
{
	std::istringstream s_in("2&&2");
	Translator t = Translator(s_in);
	try {
		t.startTranslate();
	}
	catch (TranslationException exception) {
		std::cout << exception.what();
	}
}

