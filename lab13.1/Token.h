#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class LexemType {
	num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
	semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt,
	opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile,
	kwfor, kwreturn, kwin, kwout, eof, error
};
string lexemToString(LexemType type);

class Token
{
private:
	LexemType _type;
	int _value = 0;
	string _str;

public:
	Token(LexemType type);
	Token(int value);
	Token(LexemType type, const string& str);
	Token(char c);
	Token();


	LexemType type();
	int value();
	string str();


	string toString();
	void print(ostream& stream);

};