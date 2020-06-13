#pragma once
#include <iostream>
#include <string>
#include <vector>
#include"Atoms.h"


class StringTable {
protected:
	std::vector<std::string> _strings;
public:
	StringTable();
	const std::string& operator [](const int index) const;
	std::shared_ptr<StringOperand> add(const std::string name);
	friend std::ostream& operator<<(std::ostream& os, StringTable& table);

};