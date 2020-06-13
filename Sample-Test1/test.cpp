#include "pch.h"
#include "..//lab13.1/StringTable.h"
#include "..//lab13.1/StringTable.cpp"
#include "..//lab13.1/SymbolTable.h"
#include "..//lab13.1/SymbolTable.cpp"
#include "..//lab13.1/Atoms.h"
#include "..//lab13.1/Atoms.cpp"

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
	EXPECT_EQ(table[0], str);
}

TEST(add_symboltab, two_elem) {
	SymbolTable table = SymbolTable();
	std::string str = "a";
	std::string str2 = "b";
	EXPECT_EQ(table.add(str)->toString(), "0");
	EXPECT_EQ(table.add(str2)->toString(), "1");
	EXPECT_EQ(table[0], str);
	EXPECT_EQ(table[1], str2);
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