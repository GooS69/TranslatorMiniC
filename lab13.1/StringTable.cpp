#include "StringTable.h"

StringTable::StringTable() {
	_strings = std::vector<std::string>{};
}


const std::string& StringTable::operator [](const int index) const{
	return _strings[index];
}


std::shared_ptr<StringOperand> StringTable::add(const std::string name) {
	std::shared_ptr<StringOperand> StrOp;
	int i = 0;
	for (i; i < _strings.size(); i++) {
		if(_strings[i] == name) {
			StrOp = std::make_shared<StringOperand>(StringOperand(i,this));
			return StrOp;
		}
	}
	_strings.push_back(name);
	StrOp = std::make_shared<StringOperand>(StringOperand(i, this));
	return StrOp;
}


std::ostream& operator<<(std::ostream& os, StringTable& table) {
	for (int i = 0; i < table._strings.size();i++) {
		os << table[i] << std::endl;
	}
	return os;
}

void StringTable::print(std::ostream& stream) {
	stream << "code\t" << "string\t" << std::endl;
	for (int i = 0; i < _strings.size(); i++) {
		stream << i << "\t" << _strings[i] << std::endl;
	}
}