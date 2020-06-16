#include "SymbolTable.h"

SymbolTable::SymbolTable(){
	_temp_counter = 0; 
	_records = std::vector<TableRecord>{};
}

bool SymbolTable::TableRecord::operator == (const TableRecord& other)const {
	return _name == other._name;
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


std::shared_ptr<MemoryOperand> SymbolTable::alloc() {
	return this->add("temp" + std::to_string(_temp_counter++));
}


std::string SymbolTable::TableRecord::toString(RecordKind kind) {
	if (kind == RecordKind::unknown) {
		return "unknown";
	}
	else if (kind == RecordKind::var) {
		return "var";
	}
	else if (kind == RecordKind::func) {
		return "func";
	}
}


std::string SymbolTable::TableRecord::toString(RecordType type) {
	if (type == RecordType::unknown) {
		return "unknown";
	}
	else if (type == RecordType::integer) {
		return "int";
	}
	else if (type == RecordType::chr) {
		return "char";
	}
}


void SymbolTable::print(std::ostream& stream) {
	stream << "code\t" << "name\t" << "kind\t" << "type\t" << "len\t" << "init\t" << "scope\t" << "offset"<<std::endl;
	for (int i = 0; i < _records.size();i++) {
		stream << i << "\t" << _records[i]._name << "\t"<<_records[i].toString(_records[i]._kind) <<"\t"<<
		_records[i].toString(_records[i]._type) << "\t"<<std::to_string(_records[i]._len) << "\t"<< 
		std::to_string(_records[i]._init)<< "\t" << std::to_string(_records[i]._scope) << "\t"<< 
		std::to_string(_records[i]._offset)<<std::endl;
	}
}