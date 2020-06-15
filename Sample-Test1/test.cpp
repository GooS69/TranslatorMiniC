#include <fstream>
#include <sstream>
#include <iostream>
#include "pch.h"
#include "..//lab13.1/StringTable.h"
#include "..//lab13.1/StringTable.cpp"
#include "..//lab13.1/SymbolTable.h"
#include "..//lab13.1/SymbolTable.cpp"
#include "..//lab13.1/Atoms.h"
#include "..//lab13.1/Atoms.cpp"
#include "..//lab13.1/Translator.h"
#include "..//lab13.1/Translator.cpp"
#include "..//lab13.1/Scanner.cpp"
#include "..//lab13.1/Lexemtostring.cpp"
#include "..//lab13.1/Token.cpp"
#include "..//lab13.1/Scanner.h"
#include "..//lab13.1/Token.h"

TEST(add_stringtab, one_elem) {
	StringTable table = StringTable();
	std::string str = "Hello";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table[0], "Hello");
}

TEST(add_stringtab, two_elem) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "HelloWorld";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table.add(str2)->toString(), "1");
	EXPECT_EQ(table[0], "Hello");
	EXPECT_EQ(table[1], "HelloWorld");
}

TEST(add_stringtab, five_elem) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "HelloWorld";
	std::string str3 = "HelloSpace";
	std::string str4 = "OutSpace";
	std::string str5 = "Goodbye";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table[0], "Hello");
	EXPECT_EQ(table.add(str2)->toString(), "1");
	EXPECT_EQ(table[1], "HelloWorld");
	EXPECT_EQ(table.add(str3)->toString(), "2");
	EXPECT_EQ(table[2], "HelloSpace");
	EXPECT_EQ(table.add(str4)->toString(), "3");
	EXPECT_EQ(table[3], "OutSpace");
	EXPECT_EQ(table.add(str5)->toString(), "4");
	EXPECT_EQ(table[4], "Goodbye");
}
TEST(add_stringtab, existing_elem_on_pos1) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "Hello2";
	std::string str3 = "Hello3";
	std::string str4 = "Hello2";
	table.add(str);
	table.add(str2);
	table.add(str3);
	EXPECT_EQ(table.add(str4)->toString(), "1");
	EXPECT_EQ(table[1], "Hello2");
}

TEST(add_stringtab, existing_elem_on_firstpos) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "Hello2";
	std::string str3 = "Hello3";
	std::string str4 = "Hello";
	table.add(str);
	table.add(str2);
	table.add(str3);
	EXPECT_EQ(table.add(str4)->toString(), "0");
	EXPECT_EQ(table[0], "Hello");
}

TEST(add_stringtab, existing_elem_on_lastpos) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "Hello2";
	std::string str3 = "Hello3";
	std::string str4 = "Hello3";
	table.add(str);
	table.add(str2);
	table.add(str3);
	EXPECT_EQ(table.add(str4)->toString(), "2");
	EXPECT_EQ(table[2], "Hello3");
}

TEST(op_squarebrackets_stringtab, returning_first_elem) {
	StringTable table = StringTable();
	std::string str = "Hello";
	table.add(str);
	EXPECT_EQ(table[0], "Hello");
}

TEST(op_squarebrackets_stringtab, returning_third_elem_from_5_elems) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "HelloWorld";
	std::string str3 = "HelloSpace";
	std::string str4 = "OutSpace";
	std::string str5 = "Goodbye";
	table.add(str);
	table.add(str2);
	table.add(str3);
	table.add(str4);
	table.add(str5);
	EXPECT_EQ(table[2], "HelloSpace");
}

TEST(add_symboltab, one_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table[0]._name, "a");
}

TEST(add_symboltab, two_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table.add(str2)->toString(), "1");
	EXPECT_EQ(table[0]._name, "a");
	EXPECT_EQ(table[1]._name, "b");
}

TEST(add_symboltab, five_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "temp1";
	std::string str4 = "temp2";
	std::string str5 = "temp3";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table[0], str);
	EXPECT_EQ(table.add(str2)->toString(), "1");
	EXPECT_EQ(table[1], str2);
	EXPECT_EQ(table.add(str3)->toString(), "2");
	EXPECT_EQ(table[2], str3);
	EXPECT_EQ(table.add(str4)->toString(), "3");
	EXPECT_EQ(table[3], str4);
	EXPECT_EQ(table.add(str5)->toString(), "4");
	EXPECT_EQ(table[4], str5);
}
TEST(add_symboltab, existing_elem_on_pos1) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "c";
	std::string str4 = "b";
	table.add(str);
	table.add(str2);
	table.add(str3);
	EXPECT_EQ(table.add(str4)->toString(), "1");
	EXPECT_EQ(table[1], str4);
}

TEST(add_symboltab, existing_elem_on_firstpos) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "c";
	std::string str4 = "a";
	table.add(str);
	table.add(str2);
	table.add(str3);
	EXPECT_EQ(table.add(str4)->toString(), "0");
	EXPECT_EQ(table[0], str4);
}

TEST(add_symboltab, existing_elem_on_lastpos) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "temp1";
	std::string str3 = "temp2";
	std::string str4 = "temp2";
	table.add(str);
	table.add(str2);
	table.add(str3);
	EXPECT_EQ(table.add(str4)->toString(), "2");
	EXPECT_EQ(table[2], str4);
}

TEST(op_squarebrackets_symboltab, returning_first_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	table.add(str);
	EXPECT_EQ(table[0], str);
}

TEST(op_squarebrackets_symboltab, returning_third_elem_from_5_elems) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "c";
	std::string str4 = "temp1";
	std::string str5 = "temp2";
	table.add(str);
	table.add(str2);
	table.add(str3);
	table.add(str4);
	table.add(str5);
	EXPECT_EQ(table[2], str3);
}

TEST(binary_atoms, ADD) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	auto result = table.add("res");
	BinaryOpAtom add = BinaryOpAtom("ADD", a, b, result);
	EXPECT_EQ(add.toString(), "(ADD, 0, 1, 2)");
}

TEST(binary_atoms, SUB) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	auto result = table.add("res");
	BinaryOpAtom bin_atom = BinaryOpAtom("SUB", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(SUB, 0, 1, 2)");
}

TEST(binary_atoms, MUL) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	auto result = table.add("res");
	BinaryOpAtom bin_atom = BinaryOpAtom("MUL", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(MUL, 0, 1, 2)");
}

TEST(binary_atoms, DIV) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	auto result = table.add("res");
	BinaryOpAtom bin_atom = BinaryOpAtom("DIV", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(DIV, 0, 1, 2)");
}

TEST(binary_atoms, AND) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	auto result = table.add("res");
	BinaryOpAtom bin_atom = BinaryOpAtom("AND", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(AND, 0, 1, 2)");
}

TEST(binary_atoms, OR) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	auto result = table.add("res");
	BinaryOpAtom bin_atom = BinaryOpAtom("OR", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(OR, 0, 1, 2)");
}

TEST(unary_atoms, NEG) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto result = table.add("res");
	UnaryOpAtom unar_atom = UnaryOpAtom("NEG", a, result);
	EXPECT_EQ(unar_atom.toString(), "(NEG, 0,, 1)");
}

TEST(unary_atoms, NOT) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto result = table.add("res");
	UnaryOpAtom unar_atom = UnaryOpAtom("NOT", a, result);
	EXPECT_EQ(unar_atom.toString(), "(NOT, 0,, 1)");
}

TEST(unary_atoms, MOV) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto result = table.add("res");
	UnaryOpAtom unar_atom = UnaryOpAtom("MOV", a, result);
	EXPECT_EQ(unar_atom.toString(), "(MOV, 0,, 1)");
}

TEST(conditionaljamp_atoms, EQ) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("EQ", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(EQ, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, NE) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("NE", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(NE, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, GT) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("GT", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(GT, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, LT) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("LT", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(LT, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, GE) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("GE", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(GE, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, LE) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("LE", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(LE, 0, 1, 1)");
}

TEST(jamp_atoms, JMP) {
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	JumpAtom cond_jamp_atom = JumpAtom(label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(JMP,,, 1)");
}

TEST(in_atom, IN) {
	SymbolTable table = SymbolTable();
	auto input = table.add("input");
	EXPECT_EQ(InAtom(input).toString(), "(IN,,, 0)");
}

TEST(out_atom, OUT) {
	SymbolTable table = SymbolTable();
	auto result = table.add("res");
	EXPECT_EQ(OutAtom(result).toString(), "(OUT,,, 0)");
}

TEST(label_atom, LBL) {
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	EXPECT_EQ(LabelAtom(label).toString(), "(LBL,,, 1)");
}

TEST(generate_atoms, bin_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto a = table.add("a");
	auto b = table.add("b");
	auto res = table.add("result");
	t.generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", a, b, res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(ADD, 0, 1, 2)\n");
}

TEST(generate_atoms, unary_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto a = table.add("a");
	auto res = table.add("result");
	t.generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("NEG", a, res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(NEG, 0,, 1)\n");
}

TEST(generate_atoms, lbl_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	std::ostringstream ss;
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	t.generateAtom(std::make_shared<LabelAtom>(LabelAtom(label)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(LBL,,, 1)\n");
}

TEST(generate_atoms, condjump_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto a = table.add("a");
	auto b = table.add("b");
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	t.generateAtom(std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("NE", a, b, label)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(NE, 0, 1, 1)\n");
}

TEST(generate_atoms, in_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto input = table.add("input");
	t.generateAtom(std::make_shared<InAtom>(InAtom(input)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(IN,,, 0)\n");
}

TEST(generate_atoms, out_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto res = table.add("result");
	t.generateAtom(std::make_shared<OutAtom>(OutAtom(res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(OUT,,, 0)\n");
}

TEST(print_atoms, one_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto a = table.add("a");
	auto b = table.add("b");
	auto res = table.add("result");
	t.generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", a, b, res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(MUL, 0, 1, 2)\n");
}

TEST(print_atoms, three_atoms) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	auto a = table.add("a");
	auto b = table.add("b");
	auto res = table.add("result");
	auto res2 = table.add("result2");
	auto res3 = table.add("result3");
	t.generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", a, b, res)));
	t.generateAtom(std::make_shared<UnaryOpAtom>(UnaryOpAtom("NEG", res, res2)));
	t.generateAtom(std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", a, res2, res3)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "(MUL, 0, 1, 2)\n(NEG, 2,, 3)\n(ADD, 0, 3, 4)\n");
}

TEST(alloc, only_alloc) {
	SymbolTable table = SymbolTable();
	auto t = table.alloc();
	EXPECT_EQ(table[0]._name, "temp0");
}

TEST(alloc, alloc_after_symb) {
	SymbolTable table = SymbolTable();
	auto a = table.add("a");
	auto t = table.alloc();
	EXPECT_EQ(table[1]._name, "temp0");
}

TEST(alloc, two_alloc) {
	SymbolTable table = SymbolTable();
	auto t = table.alloc();
	auto t1 = table.alloc();
	EXPECT_EQ(table[0]._name, "temp0");
	EXPECT_EQ(table[1]._name, "temp1");
}

TEST(alloc, alloc_after_symb_and_alloc) {
	SymbolTable table = SymbolTable();
	auto t = table.alloc();
	auto a = table.add("a");
	auto t1 = table.alloc();
	EXPECT_EQ(table[2]._name, "temp1");
}

TEST(newlabel, one_label) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	auto l = t.newLabel();
	EXPECT_EQ(l->toString(), "0");
}

TEST(newlabel, three_labels) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	auto l = t.newLabel();
	auto l2 = t.newLabel();
	auto l3 = t.newLabel();
	EXPECT_EQ(l->toString(), "0");
	EXPECT_EQ(l2->toString(), "1");
	EXPECT_EQ(l3->toString(), "2");
}

TEST(syntax_error, syntax_error) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	std::ostringstream ss;
	try {
		t.syntaxError("unexpected statement: expected ||");
	}
	catch (TranslationException exception) {
		ss << exception.what();
		EXPECT_EQ(ss.str(), "unexpected statement: expected ||");
	}
}

TEST(lexical_error, lexical_error) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	std::ostringstream ss;
	try {
		t.lexicalError("unknown symbol");
	}
	catch (TranslationException exception) {
		ss << exception.what();
		EXPECT_EQ(ss.str(), "unknown symbol");
	}
}