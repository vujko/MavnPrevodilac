#include "IR.h"

Variable::VariableType Variable::getType()
{
	return m_type;
}

string Variable::getName()
{
	return m_name;
}

int Variable::getPosition()
{
	return m_position;
}

Regs Variable::getAssignment()
{
	return m_assignment;
}

int Variable::getValue()
{
	return m_value;
}

void Variable::set_type(VariableType var)
{
	m_type = var;
}

void Variable::set_name(string name_)
{
	m_name = name_;
}

void Variable::set_position(int pos)
{
	m_position = pos;
}

void Variable::set_assignment(Regs ass)
{
	m_assignment = ass;
}

void Variable::set_value(int val)
{
	m_value = val;
}

void Variable::check_name()
{
	//nisam testirao
	char prvo = *m_name.begin();

	if (prvo != 'm' && m_type == T_MEM) {
		throw NameNotValid(m_name);
	}
	else if (prvo != 'r' && m_type == T_REG) {
		throw  NameNotValid(m_name);
	}
	else {
		for (auto i = ++m_name.begin(); i != m_name.end(); i++) {
			if (isalpha(*i)) {
				throw NameNotValid(m_name);
			}
		}
	}

}




Label::Label()
{
}

Label::Label(int position, string name):position(position), name(name)
{
}

int Label::get_position()
{
	return position;
}

string Label::get_name()
{
	return name;
}

void Label::set_position(int pos_)
{
	position = pos_;
}

void Label::set_name(string name_)
{
	name = name_;
}

int Instruction::get_position()
{
	return m_position;
}

InstructionType Instruction::get_type()
{
	return m_type;
}

Label * Instruction::get_label()
{
	return m_lab;
}

string Instruction::get_text()
{
	return m_text;
}

int Instruction::get_number()
{
	return m_number;
}

Variables & Instruction::get_dst()
{
	return m_dst;
}

Variables & Instruction::get_src()
{
	return m_src;
}

Variables & Instruction::get_use()
{
	return m_use;
}

Variables & Instruction::get_def()
{
	return m_def;
}

Variables & Instruction::get_in()
{
	return m_in;
}

Variables & Instruction::get_out()
{
	return m_out;
}

list<Instruction*>& Instruction::get_succ()
{
	return m_succ;
}

list<Instruction*>& Instruction::get_pred()
{
	return m_pred;
}

void Instruction::set_position(int position)
{
	m_position = position;
}

void Instruction::set_type(InstructionType inst)
{
	m_type = inst;
}

void Instruction::set_label(Label* l)
{
	m_lab = l;
}

void Instruction::set_dst(Variables & dst)
{
	m_dst = dst;
}

void Instruction::set_src(Variables & src)
{
	m_src = src;
}

void Instruction::set_use(Variables & use)
{
	m_use = use;
}

void Instruction::set_def(Variables & def)
{
	m_def = def;
}

void Instruction::set_in(Variables & in)
{
	m_in = in;
}

void Instruction::set_out(Variables & out)
{
	m_out = out;
}

void Instruction::set_succ(list<Instruction*> succ)
{
	m_succ = succ;
}

void Instruction::set_pred(list<Instruction*> pred)
{
	m_pred = pred;
}

void Instruction::set_text(string text)
{
	m_text = text;
}

void Instruction::set_number(int number)
{
	m_number = number;
}

