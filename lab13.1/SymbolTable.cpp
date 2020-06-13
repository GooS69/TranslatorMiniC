#include "SymbolTable.h"

bool SymbolTable::TableRecord::operator == (const TableRecord& other)const {
	return _name == other._name;
}

SymbolTable::SymbolTable() {
	_records = std::vector<TableRecord>{};
}

SymbolTable::TableRecord::TableRecord(const std::string& name) {
	_name = name;
}

const SymbolTable::TableRecord& SymbolTable::operator [](const int index) const {
	return _records[index];
}

std::shared_ptr<MemoryOperand> SymbolTable::add(const std::string& name) {
	std::shared_ptr<MemoryOperand> MemOp;
	int i = 0;
	for (i; i < _records.size(); i++) {
		if (_records[i]._name == name) {
			MemOp = std::make_shared<MemoryOperand>(MemoryOperand(i,this));
			return MemOp;
		}
	}
	_records.push_back(name);
	MemOp = std::make_shared<MemoryOperand>(MemoryOperand(i, this));
	return MemOp;
}