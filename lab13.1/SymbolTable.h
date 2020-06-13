#pragma once
#include <iostream>
#include <string>
#include <vector>
#include"Atoms.h"

class SymbolTable {
	struct TableRecord
	{
		std::string _name;
		bool operator == (const TableRecord& other) const;
		TableRecord(const std::string& name);
	};

protected:
	std::vector<TableRecord> _records;
public:
	SymbolTable();
	const TableRecord& operator [](const int index) const;
	std::shared_ptr<MemoryOperand> add(const std::string& name);
};
