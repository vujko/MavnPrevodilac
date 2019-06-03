#pragma once

#include "Types.h"
#include <iostream>
#include <string>

using namespace std;
/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	//Variable(string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign) {}
	Variable(string name, VariableType type) : m_type(type), m_name(name), m_position(0) , m_assignment(no_assign){
		check_name();
	}
	Variable(std::string name, int pos, VariableType vt) : m_type(vt), m_name(name), m_position(pos), m_assignment(no_assign) {}


	VariableType getType();
	string getName();
	int getPosition();
	Regs getAssignment();
	int getValue();

	void set_type(VariableType);
	void set_name(string );
	void set_position(int);
	void set_assignment(Regs);
	void set_value(int);

	//throw VariableExists(currentToken.getValue());
	struct NameNotValid : std::runtime_error {
		NameNotValid(string s) : runtime_error("\n\nName not valid!\n\n") {}
	};

private:
	VariableType m_type;
	string m_name;
	int m_position;
	Regs m_assignment;
	int m_value;

	void check_name();
};


/**
 * This type represents list of variables from program code.
 */
typedef list<Variable*> Variables;


class Label {

	int position;
	string name;

public:
	Label();
	Label(int position, string name);

	int get_position();
	string get_name();

	void set_position(int pos_);
	void set_name(string name_);

	bool operator==(Label& l) {
		return !strcmp(l.name.c_str(), this->name.c_str());
	}

};

typedef list<Label*> Labels;

/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}

	Instruction(InstructionType instr) : m_position(0), m_type(instr) {}


	int get_position();
	InstructionType get_type();
	Label* get_label();
	string get_text();
	int get_number();

	Variables& get_dst();
	Variables& get_src();

	Variables& get_use();
	Variables& get_def();
	Variables& get_in();
	Variables& get_out();

	list<Instruction*>& get_succ();
	list<Instruction*>& get_pred();


	void set_position(int position);
	void set_type(InstructionType inst);
	void set_label(Label* l);

	void set_dst(Variables& dst);
	void set_src(Variables& src);

	void set_use(Variables& use);
	void set_def(Variables& def);
	void set_in(Variables& in);
	void set_out(Variables& out);

	void set_succ(list<Instruction*> succ);
	void set_pred(list<Instruction*> pred);
	void set_text(string text);
	void set_number(int number);





private:
	int m_position;
	InstructionType m_type;
	Label* m_lab;
	string m_text;
	int m_number;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	list<Instruction*> m_succ;
	list<Instruction*> m_pred;

	
};


/**
 * This type represents list of instructions from program code.
 */
typedef list<Instruction*> Instructions;
