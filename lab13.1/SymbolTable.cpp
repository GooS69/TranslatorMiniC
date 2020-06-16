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


std::shared_ptr<MemoryOperand> SymbolTable::alloc(Scope scope) {
	return this->addVar("temp" + std::to_string(_temp_counter++), scope, TableRecord::RecordType::unknown);
}


std::shared_ptr<MemoryOperand> SymbolTable::addVar(const std::string& name, const Scope scope, const TableRecord::RecordType type, const int init) {
	std::shared_ptr<MemoryOperand> MemOp;
	int i = 0;
	for (i;i < _records.size();i++) {
		if (_records[i]._name == name && _records[i]._scope == scope) {
			return nullptr;
		}
	}
	_records.push_back(name);
	_records[i]._scope = scope;
	_records[i]._type = type;
	_records[i]._init = init;
	_records[i]._kind = TableRecord::RecordKind::var;
	return std::make_shared<MemoryOperand>(MemoryOperand(i, this));
}


std::shared_ptr<MemoryOperand> SymbolTable::addFunc(const std::string& name, const TableRecord::RecordType type, const int len) {
	int i = 0;
	for (i;i < _records.size();i++) {
		if (_records[i]._name == name) {
			return nullptr;
		}
	}
	std::shared_ptr<MemoryOperand> MemOp;
	_records.push_back(name);
	_records[i]._type = type;
	_records[i]._len = len;
	_records[i]._kind = TableRecord::RecordKind::func;
	return std::make_shared<MemoryOperand>(MemoryOperand(i, this));
}


std::shared_ptr<MemoryOperand> SymbolTable::checkVar(const Scope scope, const std::string& name) {
	int i = 0;
	for (i;i < _records.size();i++) {
		if (_records[i]._name == name && _records[i]._scope == scope && _records[i]._kind == TableRecord::RecordKind::var 
			&& _records[i]._type != TableRecord::RecordType::unknown) {
			return std::make_shared<MemoryOperand>(MemoryOperand(i, this));
		}
	}
	i = 0;
	for (i;i < _records.size();i++) {
		if (_records[i]._name == name && _records[i]._scope == GlobalScope && _records[i]._kind == TableRecord::RecordKind::var
			&& _records[i]._type != TableRecord::RecordType::unknown) {
			return std::make_shared<MemoryOperand>(MemoryOperand(i, this));
		}
	}
	return nullptr;
}


std::shared_ptr<MemoryOperand> SymbolTable::checkFunc(const std::string& name, int len) {
	int i = 0;
	for (i;i < _records.size();i++) {
		if (_records[i]._name == name && _records[i]._scope == GlobalScope && _records[i]._kind == TableRecord::RecordKind::func
			&& _records[i]._type != TableRecord::RecordType::unknown) {
			if (_records[i]._len == len) {
				return std::make_shared<MemoryOperand>(MemoryOperand(i, this));
			}
			else {
				return nullptr;
			}
		}
	}
	return nullptr;
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