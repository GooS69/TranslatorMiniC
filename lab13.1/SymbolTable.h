#pragma once
#include <iostream>
#include <string>
#include <vector>
#include"Atoms.h"
typedef int Scope;
const Scope GlobalScope = -1;

class SymbolTable {
	struct TableRecord
	{
		enum class RecordKind { unknown, var, func };
		enum class RecordType { unknown, integer, chr };
		std::string _name;
		RecordKind _kind = RecordKind::unknown;
		RecordType _type = RecordType::unknown;
		int _len = -1;
		int _init = 0;
		Scope _scope = GlobalScope;
		int _offset = -1;
		bool operator == (const TableRecord& other) const;
		TableRecord(const std::string& name);
		std::string toString(RecordKind kind);
		std::string toString(RecordType type);
	};

protected:
	std::vector<TableRecord> _records;
	int _temp_counter;
public:
	SymbolTable();
	const TableRecord& operator [](const int index) const;
	std::shared_ptr<MemoryOperand> alloc(Scope scope);
	std::shared_ptr<MemoryOperand> addVar(const std::string& name, const Scope scope, const TableRecord::RecordType type, const int init = 0);
	std::shared_ptr<MemoryOperand> addFunc(const std::string& name, const TableRecord::RecordType type, const int len);
	std::shared_ptr<MemoryOperand> checkVar(const Scope scope, const std::string& name);
	std::shared_ptr<MemoryOperand> checkFunc(const std::string& name, int len);
	void print(std::ostream& stream);
};
