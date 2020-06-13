#include "Token.h"

//==========================================================

Token::Token(LexemType type)
{
	_type = type;
}


Token::Token(int value)
{
	_type = LexemType::num;
	_value = value;
}


Token::Token(LexemType type, const string& str)
{
	_type = type;
	_str = str;
}


Token::Token(char c)
{
	_type = LexemType::chr;
	_value = int(c);
}


Token::Token() {
	_type = LexemType::error;
}

//==========================================================

LexemType Token::type()
{
	return _type;
}


int Token::value()
{
	return _value;
}


string Token::str()
{
	return _str;
}

//==========================================================

string Token::toString()
{
	string s;
	switch (_type)
	{
	case LexemType::num:
		return s + lexemToString(_type) + ", " + to_string(_value);
	case LexemType::chr:
		return s + lexemToString(_type) + ", '" + (char)_value + "'";
	case LexemType::str:
	case LexemType::error:
	case LexemType::id:
		return s + lexemToString(_type) + ", " + "\""  + _str + "\"";
	default:
		if (!_str.empty())
		{
			return s + lexemToString(_type) + ", " + "\"" + _str + "\"";
		}
		else
		{
			return s + lexemToString(_type);
		}
	}
}


void Token::print(ostream& stream)
{
	stream << "[" << toString() << "]" << std::endl;
}