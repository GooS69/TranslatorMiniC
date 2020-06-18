#pragma once
#include <map>
#include <istream>
#include "Token.h"


static std::map<char, LexemType> punctuation
{
	{'[', LexemType::lbracket},
	{']', LexemType::rbracket},
	{'(', LexemType::lpar},
	{')', LexemType::rpar},
	{'{', LexemType::lbrace},
	{'}', LexemType::rbrace},
	{';', LexemType::semicolon},
	{',', LexemType::comma},
	{':', LexemType::colon}
};


static std::map<std::string, LexemType> keywords
{
	{"return", LexemType::kwreturn},
	{"int",    LexemType::kwint},
	{"char",   LexemType::kwchar},
	{"if",     LexemType::kwif},
	{"else",   LexemType::kwelse},
	{"switch", LexemType::kwswitch},
	{"case",   LexemType::kwcase},
	{"default",LexemType::kwdefault},
	{"while",  LexemType::kwwhile},
	{"for",    LexemType::kwfor},
	{"in",     LexemType::kwin},
	{"out",    LexemType::kwout}
};


class Scanner {
private:
	int integerValue = 0;  //�������� ��������
	char characterValue = '\0'; //������
	std::string stringValue = ""; //������
	int currentState = 0; //������� ���������
	char currentCharacter = '\0'; //������� ������
	bool stopped = false; // ���� ��������� ������������ (���� ������ ���� ����� ����)
	bool stopAtCurrent = false;  //���� ��������� (����� ���� ��� ������)
	bool negativeValue = false;  //������������� �����
	Token stoppedAtToken = Token(LexemType::eof); //����� ������
	std::istream& inputStream;

public:
	Scanner(std::istream& inputStream);
	Token getNextToken();

};

Scanner& operator>>(Scanner& scanner, Token& token);
