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
	EXPECT_EQ(table.add(str)->toString(), "S0");
	EXPECT_EQ(table[0], "Hello");
}

TEST(add_stringtab, two_elem) {
	StringTable table = StringTable();
	std::string str = "Hello";
	std::string str2 = "HelloWorld";
	EXPECT_EQ(table.add(str)->toString(), "S0");
	EXPECT_EQ(table.add(str2)->toString(), "S1");
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
	EXPECT_EQ(table.add(str)->toString(), "S0");
	EXPECT_EQ(table[0], "Hello");
	EXPECT_EQ(table.add(str2)->toString(), "S1");
	EXPECT_EQ(table[1], "HelloWorld");
	EXPECT_EQ(table.add(str3)->toString(), "S2");
	EXPECT_EQ(table[2], "HelloSpace");
	EXPECT_EQ(table.add(str4)->toString(), "S3");
	EXPECT_EQ(table[3], "OutSpace");
	EXPECT_EQ(table.add(str5)->toString(), "S4");
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
	EXPECT_EQ(table.add(str4)->toString(), "S1");
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
	EXPECT_EQ(table.add(str4)->toString(), "S0");
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
	EXPECT_EQ(table.add(str4)->toString(), "S2");
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
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	EXPECT_EQ(table.addVar(str, 1, type, 0)->toString(), "0");
	EXPECT_EQ(table[0]._name, "a");
}

TEST(add_symboltab, two_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	EXPECT_EQ(table.addVar(str, 1, type, 0)->toString(), "0");
	EXPECT_EQ(table.addVar(str2, 1, type, 0)->toString(), "1");
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
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	EXPECT_EQ(table.addVar(str, 1, type, 0)->toString(), "0");
	EXPECT_EQ(table[0], str);
	EXPECT_EQ(table.addVar(str2, 1, type, 0)->toString(), "1");
	EXPECT_EQ(table[1], str2);
	EXPECT_EQ(table.addVar(str3, 1, type, 0)->toString(), "2");
	EXPECT_EQ(table[2], str3);
	EXPECT_EQ(table.addVar(str4, 1, type, 0)->toString(), "3");
	EXPECT_EQ(table[3], str4);
	EXPECT_EQ(table.addVar(str5, 1, type, 0)->toString(), "4");
	EXPECT_EQ(table[4], str5);
}

TEST(add_symboltab, existing_elem_on_pos1) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "c";
	std::string str4 = "b";
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto t1 = table.addVar(str, 1, type, 0);
	auto t2 = table.addVar(str2, 1, type, 0);
	auto t3 = table.addVar(str3, 1, type, 0);
	EXPECT_EQ(table.checkVar(1, str4)->toString(), "1");
	EXPECT_EQ(table[1], str4);
}

TEST(add_symboltab, existing_elem_on_firstpos) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "c";
	std::string str4 = "a";
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto t1 = table.addVar(str, 1, type, 0);
	auto t2 = table.addVar(str2, 1, type, 0);
	auto t3 = table.addVar(str3, 1, type, 0);
	EXPECT_EQ(table.checkVar(1, str4)->toString(), "0");
	EXPECT_EQ(table[0], str4);
}

TEST(add_symboltab, existing_elem_on_lastpos) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "temp1";
	std::string str3 = "temp2";
	std::string str4 = "temp2";
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto t1 = table.addVar(str, 1, type, 0);
	auto t2 = table.addVar(str2, 1, type, 0);
	auto t3 = table.addVar(str3, 1, type, 0);
	EXPECT_EQ(table.checkVar(1, str4)->toString(), "2");
	EXPECT_EQ(table[2], str4);
}

TEST(op_squarebrackets_symboltab, returning_first_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto t1 = table.addVar(str, 1, type, 0);
	EXPECT_EQ(table[0], str);
}

TEST(op_squarebrackets_symboltab, returning_third_elem_from_5_elems) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	std::string str3 = "c";
	std::string str4 = "temp1";
	std::string str5 = "temp2";
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto t1 = table.addVar(str, 1, type, 0);
	auto t2 = table.addVar(str2, 1, type, 0);
	auto t3 = table.addVar(str3, 1, type, 0);
	auto t4 = table.addVar(str4, 1, type, 0);
	auto t5 = table.addVar(str5, 1, type, 0);
	EXPECT_EQ(table[2], str3);
}

TEST(binary_atoms, ADD) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	BinaryOpAtom add = BinaryOpAtom("ADD", a, b, result);
	EXPECT_EQ(add.toString(), "(ADD, 0, 1, 2)");
}

TEST(binary_atoms, SUB) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	BinaryOpAtom bin_atom = BinaryOpAtom("SUB", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(SUB, 0, 1, 2)");
}

TEST(binary_atoms, MUL) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	BinaryOpAtom bin_atom = BinaryOpAtom("MUL", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(MUL, 0, 1, 2)");
}

TEST(binary_atoms, DIV) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	BinaryOpAtom bin_atom = BinaryOpAtom("DIV", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(DIV, 0, 1, 2)");
}

TEST(binary_atoms, AND) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	BinaryOpAtom bin_atom = BinaryOpAtom("AND", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(AND, 0, 1, 2)");
}

TEST(binary_atoms, OR) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	BinaryOpAtom bin_atom = BinaryOpAtom("OR", a, b, result);
	EXPECT_EQ(bin_atom.toString(), "(OR, 0, 1, 2)");
}

TEST(unary_atoms, NEG) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	UnaryOpAtom unar_atom = UnaryOpAtom("NEG", a, result);
	EXPECT_EQ(unar_atom.toString(), "(NEG, 0,, 1)");
}

TEST(unary_atoms, NOT) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	UnaryOpAtom unar_atom = UnaryOpAtom("NOT", a, result);
	EXPECT_EQ(unar_atom.toString(), "(NOT, 0,, 1)");
}

TEST(unary_atoms, MOV) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	UnaryOpAtom unar_atom = UnaryOpAtom("MOV", a, result);
	EXPECT_EQ(unar_atom.toString(), "(MOV, 0,, 1)");
}

TEST(conditionaljamp_atoms, EQ) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("EQ", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(EQ, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, NE) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("NE", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(NE, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, GT) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("GT", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(GT, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, LT) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("LT", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(LT, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, GE) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	ConditionalJumpAtom cond_jamp_atom = ConditionalJumpAtom("GE", a, b, label);
	EXPECT_EQ(cond_jamp_atom.toString(), "(GE, 0, 1, 1)");
}

TEST(conditionaljamp_atoms, LE) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
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
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto input = table.addVar("input", 1, type, 0);
	EXPECT_EQ(InAtom(input).toString(), "(IN,,, 0)");
}

TEST(out_atom, OUT) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto result = table.addVar("res", 1, type, 0);
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
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto res = table.addVar("res", 1, type, 0);
	t.generateAtom(1, std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", a, b, res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (ADD, 0, 1, 2)\n");
}

TEST(generate_atoms, unary_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto res = table.addVar("res", 1, type, 0);
	t.generateAtom(1, std::make_shared<UnaryOpAtom>(UnaryOpAtom("NEG", a, res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (NEG, 0,, 1)\n");
}

TEST(generate_atoms, lbl_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	std::ostringstream ss;
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	t.generateAtom(1, std::make_shared<LabelAtom>(LabelAtom(label)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (LBL,,, 1)\n");
}

TEST(generate_atoms, condjump_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	std::shared_ptr<LabelOperand> label = std::make_shared<LabelOperand>(LabelOperand(1));
	t.generateAtom(1, std::make_shared<ConditionalJumpAtom>(ConditionalJumpAtom("NE", a, b, label)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (NE, 0, 1, 1)\n");
}

TEST(generate_atoms, in_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto input = table.addVar("input", 1, type, 0);
	t.generateAtom(1, std::make_shared<InAtom>(InAtom(input)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (IN,,, 0)\n");
}

TEST(generate_atoms, out_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto res = table.addVar("res", 1, type, 0);
	t.generateAtom(1, std::make_shared<OutAtom>(OutAtom(res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (OUT,,, 0)\n");
}

TEST(print_atoms, one_atom) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto res = table.addVar("res", 1, type, 0);
	t.generateAtom(1, std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", a, b, res)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (MUL, 0, 1, 2)\n");
}

TEST(print_atoms, three_atoms) {
	std::ifstream ifile("myprog.txt");
	Translator t = Translator(ifile);
	SymbolTable table = SymbolTable();
	std::ostringstream ss;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("b", 1, type, 0);
	auto res = table.addVar("res", 1, type, 0);
	auto res2 = table.addVar("res2", 1, type, 0);
	auto res3 = table.addVar("res3", 1, type, 0);
	t.generateAtom(1, std::make_shared<BinaryOpAtom>(BinaryOpAtom("MUL", a, b, res)));
	t.generateAtom(1, std::make_shared<UnaryOpAtom>(UnaryOpAtom("NEG", res, res2)));
	t.generateAtom(1, std::make_shared<BinaryOpAtom>(BinaryOpAtom("ADD", a, res2, res3)));
	t.printAtoms(ss);
	EXPECT_EQ(ss.str(), "1 (MUL, 0, 1, 2)\n1 (NEG, 2,, 3)\n1 (ADD, 0, 3, 4)\n");
}

TEST(alloc, only_alloc) {
	SymbolTable table = SymbolTable();
	auto t = table.alloc(1);
	EXPECT_EQ(table[0]._name, "temp0");
}

TEST(alloc, alloc_after_symb) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	auto t = table.alloc(1);
	EXPECT_EQ(table[1]._name, "temp0");
}

TEST(alloc, two_alloc) {
	SymbolTable table = SymbolTable();
	auto t = table.alloc(1);
	auto t1 = table.alloc(1);
	EXPECT_EQ(table[0]._name, "temp0");
	EXPECT_EQ(table[1]._name, "temp1");
}

TEST(alloc, alloc_after_symb_and_alloc) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto t = table.alloc(1);
	auto a = table.addVar("a", 1, type, 0);
	auto t1 = table.alloc(1);
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
		EXPECT_EQ(ss.str(), "\nunknown symbol");
	}
}

TEST(grammar_tests, int_) {
	std::istringstream s_in("int a;");
	std::ostringstream s_out;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		EXPECT_EQ(exception.what(), "");
	}
}

TEST(grammar_tests, char_) {
	std::istringstream s_in("char a;");
	std::ostringstream s_out;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		EXPECT_EQ(exception.what(), "");
	}
}

TEST(grammar_tests, inc_a_left) {
	std::istringstream s_in("int main(){int a;\na = ++a;}");
	std::ostringstream s_out;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (ADD, 1, '1', 1)\n0 (MOV, 1,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		EXPECT_EQ(exception.what(), "");
	}
}

TEST(grammar_tests, inc_a_right) {
	std::istringstream s_in("int main(){int a;\na = a++;}");
	std::ostringstream s_out;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MOV, 1,, 2)\n0 (ADD, 1, '1', 1)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		EXPECT_EQ(exception.what(), "");
	}
}

TEST(grammar_tests, inc_a_left_without_id) {
	std::istringstream s_in("int main(){int a;\na = ++}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected id at E1");
	}
}

TEST(grammar_tests, inc_int_left) {
	std::istringstream s_in("++8");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected id at E1");
	}
}

TEST(grammar_tests, inc_int_right) {
	std::istringstream s_in("8++");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected operation(there are still tokens)");
	}
}

TEST(grammar_tests, NOT_a) {
	std::istringstream s_in("int main(){int a;\na = !a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (NOT, 1,, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, NOT_a_without_exp) {
	std::istringstream s_in("!");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, MUL_a_a) {
	std::istringstream s_in("int main(){int a;\n a = a*a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MUL, 1, 1, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, MUL_a_b) {
	std::istringstream s_in("int main(){int a;\nint b;\nint c;\nc = a*b;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MUL, 1, 2, 4)\n0 (MOV, 4,, 3)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, MUL_a_int) {
	std::istringstream s_in("int main(){int a;\na = a*2;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MUL, 1, '2', 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, MUL_int_a) {
	std::istringstream s_in("int main(){int a;\na = 3*a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MUL, '3', 1, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, MUL_a_without_exp_right) {
	std::istringstream s_in("int main(){int a;\na = a*;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, MUL_a_without_exp_left) {
	std::istringstream s_in("int main(){int a;\na= *a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, SUB_a_a) {
	std::istringstream s_in("int main(){int a;\na = a - a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (SUB, 1, 1, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}
TEST(grammar_tests, SUB_a_b) {
	std::istringstream s_in("int main(){int a;\nint b;\nint c;\nc = a - b;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (SUB, 1, 2, 4)\n0 (MOV, 4,, 3)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, SUB_a_int) {
	std::istringstream s_in("int main(){int a;\na = a - 2;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (SUB, 1, '2', 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, SUB_int_a) {
	std::istringstream s_in("int main(){int W;\nW = 228 - W;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (SUB, '228', 1, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, SUB_a_without_exp_left) {
	std::istringstream s_in("- a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, SUB_a_without_exp_right) {
	std::istringstream s_in("a -");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}
TEST(grammar_tests, ADD_a_a) {
	std::istringstream s_in("int main(){int a;\na = a+a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (ADD, 1, 1, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, ADD_a_b) {
	std::istringstream s_in("int main(){int a;\nint b;\nint c;\nc = a+b;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (ADD, 1, 2, 4)\n0 (MOV, 4,, 3)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, ADD_a_int) {
	std::istringstream s_in("int main(){int a;\na=a+25565;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (ADD, 1, '25565', 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, ADD_int_a) {
	std::istringstream s_in("int main(){int a;\na=322+a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (ADD, '322', 1, 2)\n0 (MOV, 2,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, ADD_a_witout_exp_right) {
	std::istringstream s_in("322+");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, ADD_a_witout_exp_left) {
	std::istringstream s_in("+322");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, EQ_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a==a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (EQ, 1, 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, EQ_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a==69){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (EQ, 1, '69', 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, EQ_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(14==a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (EQ, '14', 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, EQ_int_int) {
	std::istringstream s_in("int main(){while(14==18){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 1)\n0 (EQ, '14', '18', 2)\n0 (MOV, '0',, 1)\n0 (LBL,,, 2)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, EQ_a_without_exp_left) {
	std::istringstream s_in("==a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, EQ_a_without_exp_right) {
	std::istringstream s_in("a==");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, EQ_int_without_exp_left) {
	std::istringstream s_in("==18");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, EQ_int_without_exp_right) {
	std::istringstream s_in("14==");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, NE_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a!=a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (NE, 1, 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, NE_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a!=69){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (NE, 1, '69', 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, NE_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(14!=a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (NE, '14', 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, NE_int_int) {
	std::istringstream s_in("int main(){while(14!=18){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 1)\n0 (NE, '14', '18', 2)\n0 (MOV, '0',, 1)\n0 (LBL,,, 2)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, NE_a_without_exp_left) {
	std::istringstream s_in("!=a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, NE_a_without_exp_right) {
	std::istringstream s_in("a!=");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, NE_int_without_exp_left) {
	std::istringstream s_in("!=18");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, NE_int_without_exp_right) {
	std::istringstream s_in("14!=");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, GT_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a>a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (GT, 1, 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, GT_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a>69){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (GT, 1, '69', 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, GT_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(14>a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (GT, '14', 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, GT_int_int) {
	std::istringstream s_in("int main(){while(14>18){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 1)\n0 (GT, '14', '18', 2)\n0 (MOV, '0',, 1)\n0 (LBL,,, 2)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, GT_a_without_exp_left) {
	std::istringstream s_in(">a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, GT_a_without_exp_right) {
	std::istringstream s_in("a>");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, GT_int_without_exp_left) {
	std::istringstream s_in(">18");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, GT_int_without_exp_right) {
	std::istringstream s_in("14>");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, LT_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a<a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (LT, 1, 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LT_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a<69){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (LT, 1, '69', 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LT_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(14<a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (LT, '14', 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LT_int_int) {
	std::istringstream s_in("int main(){while(14<18){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 1)\n0 (LT, '14', '18', 2)\n0 (MOV, '0',, 1)\n0 (LBL,,, 2)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LT_a_without_exp_left) {
	std::istringstream s_in("<a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, LT_a_without_exp_right) {
	std::istringstream s_in("a<");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, LT_int_without_exp_left) {
	std::istringstream s_in("<18");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, LT_int_without_exp_right) {
	std::istringstream s_in("14<");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, LE_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a<=a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (LE, 1, 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LE_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a<=69){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (LE, 1, '69', 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LE_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(14<=a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 2)\n0 (LE, '14', 1, 2)\n0 (MOV, '0',, 2)\n0 (LBL,,, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LE_int_int) {
	std::istringstream s_in("int main(){while(14<=18){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 1)\n0 (LE, '14', '18', 2)\n0 (MOV, '0',, 1)\n0 (LBL,,, 2)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, LE_a_without_exp_left) {
	std::istringstream s_in("<=a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected = ( at AssignOrCall_");
	}
}

TEST(grammar_tests, LE_a_without_exp_right) {
	std::istringstream s_in("a<=");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, LE_int_without_exp_left) {
	std::istringstream s_in("<=18");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, LE_int_without_exp_right) {
	std::istringstream s_in("14<=");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, AND_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a&&a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (AND, 1, 1, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, AND_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a&&8){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (AND, 1, '8', 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, AND_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(256&&a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (AND, '256', 1, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, AND_int_int) {
	std::istringstream s_in("int main(){while(325&&8){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (AND, '325', '8', 1)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, AND_a_without_exp_left) {
	std::istringstream s_in("&&a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, AND_a_without_exp_right) {
	std::istringstream s_in("a&&");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, AND_int_without_exp_left) {
	std::istringstream s_in("&&12");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, AND_int_without_exp_right) {
	std::istringstream s_in("56&&");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, OR_a_a) {
	std::istringstream s_in("int main(){int a;\nwhile(a||a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (OR, 1, 1, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, OR_a_int) {
	std::istringstream s_in("int main(){int a;\nwhile(a||8){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (OR, 1, '8', 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, OR_int_a) {
	std::istringstream s_in("int main(){int a;\nwhile(256||a){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (OR, '256', 1, 2)\n0 (EQ, 2, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, OR_int_int) {
	std::istringstream s_in("int main(){while(325||8){};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (OR, '325', '8', 1)\n0 (EQ, 1, '0', 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(grammar_tests, OR_a_without_exp_left) {
	std::istringstream s_in("||a");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, OR_a_without_exp_right) {
	std::istringstream s_in("a||");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "operator should be inside function");
	}
}

TEST(grammar_tests, OR_int_without_exp_left) {
	std::istringstream s_in("||12");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(grammar_tests, OR_int_without_exp_right) {
	std::istringstream s_in("56||");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "expected ( num char ++ id at E1");
	}
}

TEST(integrat_grammar_tests, one) {
	std::istringstream s_in("int main(){int a;\nint b;\nint c;\nc=a*b - a*a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MUL, 1, 2, 4)\n0 (MUL, 1, 1, 5)\n0 (SUB, 4, 5, 6)\n0 (MOV, 6,, 3)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, second) {
	std::istringstream s_in("int main(){int a;\nint b;\nb=a*25565 - 15;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MUL, 1, '25565', 3)\n0 (SUB, 3, '15', 4)\n0 (MOV, 4,, 2)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, while_inc) {
	std::istringstream s_in("int main(){int a=0;\nint b=3;\nwhile(a<b){a=a++;};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (LBL,,, 0)\n0 (MOV, '1',, 3)\n0 (LT, 1, 2, 2)\n0 (MOV, '0',, 3)\n0 (LBL,,, 2)\n0 (EQ, 3, '0', 1)\n0 (MOV, 1,, 4)\n0 (ADD, 1, '1', 1)\n0 (MOV, 4,, 1)\n0 (JMP,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, if_inc) {
	std::istringstream s_in("int main(){int a=0;\nint b=3;\nif(a>b){a=a++;};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MOV, '1',, 3)\n0 (GT, 1, 2, 2)\n0 (MOV, '0',, 3)\n0 (LBL,,, 2)\n0 (EQ, 3, '0', 0)\n0 (MOV, 1,, 4)\n0 (ADD, 1, '1', 1)\n0 (MOV, 4,, 1)\n0 (JMP,,, 1)\n0 (LBL,,, 0)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, for_inc) {
	std::istringstream s_in("int main(){int a=0;\nint b=3;\nint i;\nfor(i = 0; a<=b; ++i){a=a++;};}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MOV, '0',, 3)\n0 (LBL,,, 0)\n0 (MOV, '1',, 4)\n0 (LE, 1, 2, 4)\n0 (MOV, '0',, 4)\n0 (LBL,,, 4)\n0 (EQ, 4, '0', 3)\n0 (JMP,,, 2)\n0 (LBL,,, 1)\n0 (ADD, 3, '1', 3)\n0 (JMP,,, 0)\n0 (LBL,,, 2)\n0 (MOV, 1,, 5)\n0 (ADD, 1, '1', 1)\n0 (MOV, 5,, 1)\n0 (JMP,,, 1)\n0 (LBL,,, 3)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, in) {
	std::istringstream s_in("int main(){int a;\nin a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (IN,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, out_int) {
	std::istringstream s_in("int main(){int a = 10;\nout a;}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (OUT,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, out_str) {
	std::istringstream s_in("int main(){int a = 10;\nout \"Hello\";}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (OUT,,, S0)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}
TEST(integrat_grammar_tests, IF_1_else_2) {
	std::istringstream s_in("int main(){int a = 10;\nint b=0;if(a>5){b=1;}\nelse{b=2;}}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MOV, '1',, 3)\n0 (GT, 1, '5', 2)\n0 (MOV, '0',, 3)\n0 (LBL,,, 2)\n0 (EQ, 3, '0', 0)\n0 (MOV, '1',, 2)\n0 (JMP,,, 1)\n0 (LBL,,, 0)\n0 (MOV, '2',, 2)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, if_1_ELSE_2) {
	std::istringstream s_in("int main(){int a = 10;\nint b=0;\nif(a>15){b=1;}\nelse{b=2;}}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (MOV, '1',, 3)\n0 (GT, 1, '15', 2)\n0 (MOV, '0',, 3)\n0 (LBL,,, 2)\n0 (EQ, 3, '0', 0)\n0 (MOV, '1',, 2)\n0 (JMP,,, 1)\n0 (LBL,,, 0)\n0 (MOV, '2',, 2)\n0 (LBL,,, 1)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}

TEST(integrat_grammar_tests, switch_case1) {
	std::istringstream s_in("int main(){int a = 3;\nswitch(a){\ncase 1:\na=a+2;\ndefault:\na=a+5;}}");
	std::ostringstream s_out;
	std::ostringstream s_out2;
	Translator t = Translator(s_in);
	try {
		t.startTranslate_withoutTable();
		t.printAtoms(s_out);
		EXPECT_EQ(s_out.str(), "0 (NE, 1, '1', 1)\n0 (ADD, 1, '2', 2)\n0 (MOV, 2,, 1)\n0 (LBL,,, 0)\n0 (LBL,,, 1)\n0 (JMP,,, 2)\n0 (LBL,,, 3)\n0 (ADD, 1, '5', 3)\n0 (MOV, 3,, 1)\n0 (JMP,,, 0)\n0 (LBL,,, 2)\n0 (JMP,,, 3)\n0 (LBL,,, 0)\n0 (RET,,, '0')\n");
	}
	catch (TranslationException exception) {
		s_out2 << exception.what();
		EXPECT_EQ(s_out2.str(), "");
	}
}
TEST(symboltable, one_a) {
	SymbolTable table = SymbolTable();
	std::ostringstream os;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto a = table.addVar("a", 1, type, 0);
	table.print(os);
	std::ostringstream os2;
	os2 << "code\tname\tkind\ttype\tlen\tinit\tscope\toffset\n0\ta\tvar\tchar\t-1\t0\t1\t-1\n";
	EXPECT_EQ(os.str(), os2.str());
}

TEST(symboltable, two_a_int) {
	SymbolTable table = SymbolTable();
	std::ostringstream os;
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	TableRecord::RecordType type2 = TableRecord::RecordType::integer;
	auto a = table.addVar("a", 1, type, 0);
	auto b = table.addVar("8", 1, type2, 8);
	table.print(os);
	std::ostringstream os2;
	os2 << "code\tname\tkind\ttype\tlen\tinit\tscope\toffset\n0\ta\tvar\tchar\t-1\t0\t1\t-1\n1\t8\tvar\tint\t-1\t8\t1\t-1\n";
	EXPECT_EQ(os.str(), os2.str());
}

TEST(call_atom, call) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto f = table.addVar("func1", 1, type, 0);
	auto result = table.addVar("res", 1, type, 0);
	CallAtom atom = CallAtom(f, result);
	EXPECT_EQ(atom.toString(), "(CALL, 0,, 1)");
}

TEST(ret_atom, ret) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto result = table.addVar("res", 1, type, 0);
	RetAtom atom = RetAtom(result);
	EXPECT_EQ(atom.toString(), "(RET,,, 0)");
}

TEST(param_atom, param) {
	SymbolTable table = SymbolTable();
	TableRecord::RecordType type = TableRecord::RecordType::chr;
	auto param = table.addVar("p", 1, type, 0);
	ParamAtom atom = ParamAtom(param);
	EXPECT_EQ(atom.toString(), "(PARAM,,, 0)");
}