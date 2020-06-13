#pragma once
#include <string>
class StringTable;
class SymbolTable;


class Operand {
public:
	Operand() {};
	virtual std::string toString() const = 0;
};


class RValue: public Operand {
public:
	RValue() {};
};


class MemoryOperand : public RValue {
protected:
	int _index;
	const SymbolTable* _symbolTable;
public:
	MemoryOperand(int index, const SymbolTable* symbolTable);
	std::string toString() const override;
};


class NumberOperand :public RValue {
protected:
	int _value;
public:
	NumberOperand(int value);
	std::string toString() const override;
};


class StringOperand : public Operand {
protected:
	int _index;
	const StringTable* _stringTable;
public:
	StringOperand(int index, const StringTable* stringTable);
	std::string toString() const override;
};


class LabelOperand :public Operand {
protected:
	int _labelID;
public: 
	LabelOperand(int labelID);
	std::string toString() const override;
};


class Atom {
public:
	Atom() {};
	virtual std::string toString() const = 0;
};

class BinaryOpAtom :public Atom {
protected:
	std::string _name;
	std::shared_ptr<RValue> _left;
	std::shared_ptr<RValue> _right;
	std::shared_ptr<MemoryOperand> _result;
public:
	BinaryOpAtom(const std::string& name, std::shared_ptr<RValue> left, std::shared_ptr<RValue> right, std::shared_ptr<MemoryOperand> result);
	std::string toString() const override;
};


class UnaryOpAtom : public Atom {
protected:
	std::string _name;
	std::shared_ptr<RValue> _operand;
	std::shared_ptr<MemoryOperand> _result;
public:
	UnaryOpAtom(const std::string& name, std::shared_ptr<RValue> operand, std::shared_ptr<MemoryOperand> result);
	std::string toString() const override;
};


class ConditionalJumpAtom :public Atom {
protected:
	std::string _condition;
	std::shared_ptr<RValue> _left;
	std::shared_ptr<RValue> _right;
	std::shared_ptr<LabelOperand> _label;
public:
	ConditionalJumpAtom(const std::string& condition, std::shared_ptr<RValue> left, std::shared_ptr<RValue> right, std::shared_ptr<LabelOperand> label);
	std::string toString() const override;
};


class JumpAtom :public Atom {
protected:
	std::shared_ptr<LabelOperand> _label;
public:
	JumpAtom(std::shared_ptr<LabelOperand> label);
	std::string toString() const override;
};


class LabelAtom : public Atom {
protected:
	std::shared_ptr<LabelOperand> _label;
public:
	LabelAtom(std::shared_ptr<LabelOperand> label);
	std::string toString() const override;
};


class InAtom :public Atom {
protected:
	std::shared_ptr<MemoryOperand> _result;
public:
	InAtom(std::shared_ptr<MemoryOperand> result);
	std::string toString() const override;
};


class OutAtom :public Atom {
protected:
	std::shared_ptr<Operand> _value;
public:
	OutAtom(std::shared_ptr<Operand> value);
	std::string toString() const override;
};
