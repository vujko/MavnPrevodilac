#include "SyntaxAnalysis.h"
#include <iostream>
#include "Exception.h"

using namespace std;


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex) : instructionPosition(0), lexicalAnalysis(lex), errorFound(false), regPosition(0)
{
	tokenIterator = lexicalAnalysis.getTokenList().begin();
}


bool SyntaxAnalysis::Do()
{
	// get the first token
	currentToken = getNextToken();
	// begin analysis from start nonterminal symbol
	q();

	// check if anything has been analyzed:
	if (--tokenIterator == lexicalAnalysis.getTokenList().begin())
		return false;
	else
		return !errorFound;
}


void SyntaxAnalysis::printSyntaxError(Token& token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (currentToken.getType() == t)
	{
		currentToken.printTokenValue();
		if (t != T_END_OF_FILE)
			currentToken = getNextToken();
	}
	else
	{
		printSyntaxError(currentToken);
		errorFound = true;
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *tokenIterator++;
}


void SyntaxAnalysis::q()
{
	if (errorFound) {
		return;
	}
	s();
	eat(T_SEMI_COL);
	l();
}


void SyntaxAnalysis::s()
{
	Variable* var;
	Label* label;
	if (errorFound) {
		return;
	}
	TokenType current = currentToken.getType();
	switch (current) {
	case T_MEM:
		eat(T_MEM);
		var = new Variable(currentToken.getValue(), Variable::VariableType::MEM_VAR);

		eat(T_M_ID);
		var->set_value(atoi(currentToken.getValue().c_str()));
		if (VariableExists(var))
		{
			errorFound = true;
			throw VariableRedefined();
		}
		variables.push_back(var);

		eat(T_NUM);
		break;
	case T_REG:
		eat(T_REG);
		var = new Variable(currentToken.getValue(), Variable::VariableType::REG_VAR);
		var->set_position(regPosition++);
		if (VariableExists(var))
		{
			errorFound = true;
			throw VariableRedefined();
		}
		
		variables.push_back(var);

		eat(T_R_ID);
		break;

	case T_FUNC:
		eat(T_FUNC);

		check_function_name(currentToken.getValue());

		label = new Label(instructionPosition, currentToken.getValue());
		labels.push_back(label);

		eat(T_ID);
		break;
	case T_ID:
		label = new Label(instructionPosition, currentToken.getValue());
		if (LabelExists(label))
		{
			errorFound = true;
			throw LabelRedefined();
		}
		labels.push_back(label);
		eat(T_ID);		
		eat(T_COL);
		e();
		break;
	default:
		e();
	}
	
}


void SyntaxAnalysis::l()
{
	if (errorFound) {
		return;
	}
	TokenType current = currentToken.getType();
	switch (current) {
	case T_END_OF_FILE:
		eat(T_END_OF_FILE);
		break;
	default:
		q();
	}

}


void SyntaxAnalysis::e()
{
	Instruction* ins;
	if (errorFound) {
		return;
	}
	TokenType current = currentToken.getType();
	switch (current) {
	case T_ADD:
		eat(T_ADD);
		ins = new Instruction(I_ADD);
		addVariablesInInstruction(ins, false, true);

		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);

		ins->set_text("add \t\t 'd, 's, 's");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_ADDI:
		eat(T_ADDI);
		ins = new Instruction(I_ADDI);

		addVariablesInInstruction(ins, false, true);

		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_COMMA);

		ins->set_number(atoi(currentToken.getValue().c_str()));
		eat(T_NUM);

		ins->set_position(instructionPosition++);
		ins->set_text("addi \t\t 'd, 's, 'n");
		instructions.push_back(ins);
		break;

	case T_SUB:

		eat(T_SUB);
		ins = new Instruction(I_SUB);
		addVariablesInInstruction(ins, false, true);

		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);

		ins->set_text("sub \t\t 'd, 's, 's");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_LA:
		
		eat(T_LA);
		ins = new Instruction(I_LA);

		addVariablesInInstruction(ins, false, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, false);
		eat(T_M_ID);
		ins->set_text("la \t\t 'd, 's");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_LW:

		eat(T_LW);
		ins = new Instruction(I_LW);

		addVariablesInInstruction(ins, false, true);
		eat(T_R_ID);
		eat(T_COMMA);

		ins->set_number(atoi(currentToken.getValue().c_str()));
		eat(T_NUM);
		eat(T_L_PARENT);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_R_PARENT);
		ins->set_text("lw \t\t 'd, 'n('s)");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_LI:

		eat(T_LI);
		ins = new Instruction(I_LI);

		addVariablesInInstruction(ins, false, true);
		eat(T_R_ID);
		eat(T_COMMA);

		ins->set_number(atoi(currentToken.getValue().c_str()));
		eat(T_NUM);

		ins->set_text("li \t\t 'd, 'n");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_SW:

		eat(T_SW);
		ins = new Instruction(I_SW);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_COMMA);

		ins->set_number(atoi(currentToken.getValue().c_str()));
		eat(T_NUM);
		eat(T_L_PARENT);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_R_PARENT);

		ins->set_text("sw \t\t 's, 'n('s)");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_B:

		eat(T_B);
		ins = new Instruction(I_B);

		addLabelToInstruction(ins);
		eat(T_ID);

		ins->set_text("b \t\t 'l");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_BLTZ:

		eat(T_BLTZ);
		ins = new Instruction(I_BLTZ);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addLabelToInstruction(ins);
		eat(T_ID);

		ins->set_text("blitz \t\t 's, 'l");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_NOP:
		eat(T_NOP);
		ins = new Instruction(I_NOP);
		ins->set_text("nop");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_NEG:
		eat(T_NEG);
		ins = new Instruction(I_NEG);

		addVariablesInInstruction(ins, false, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);

		ins->set_text("neg \t\t 'd, 's");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_NEGU:
		eat(T_NEGU);
		ins = new Instruction(I_NEGU);

		addVariablesInInstruction(ins, false, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, true);
		eat(T_R_ID);

		ins->set_text("negu \t\t 'd, 's");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);
		break;

	case T_LHU:

		eat(T_LHU);
		ins = new Instruction(I_LHU);

		addVariablesInInstruction(ins, false, true);
		eat(T_R_ID);
		eat(T_COMMA);

		addVariablesInInstruction(ins, true, false);
		eat(T_M_ID);

		ins->set_text("lhu \t\t 'd, 's");
		ins->set_position(instructionPosition++);
		instructions.push_back(ins);

		break;
	default:
		errorFound = true;
		throw UndefinedInstruction();
	}
}

bool SyntaxAnalysis::VariableExists(Variable * var)
{
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if (!strcmp((*it)->getName().c_str(), var->getName().c_str()) && (*it)->getType() == var->getType()) {
			return true;
		}
	}
	return false;
}

bool SyntaxAnalysis::LabelExists(Label * l)
{
	for(auto it = labels.begin(); it != labels.end(); it++){
		if (*l == *(*it)) {
			return true;
		}
	}
	return false;
}

void SyntaxAnalysis::addVariablesInInstruction(Instruction * inst, bool isSource, bool isReg)
{

	Variable* var = new Variable();
	var->set_name(currentToken.getValue());

	if (isReg) {
		var->set_type(Variable::VariableType::REG_VAR);
	}
	else {
		var->set_type(Variable::VariableType::MEM_VAR);
	}

	if (!VariableExists(var)) {
		errorFound = true;
		throw UndefinedVariable();
	}

	if (isSource) {
		inst->get_src().push_back(get_variable(var));
		inst->get_use().push_back(get_variable(var));
	}
	else {
		inst->get_def().push_back(get_variable(var));
		inst->get_dst().push_back(get_variable(var));
	}
	
}

Variable* SyntaxAnalysis::get_variable(Variable* temp)
{
	for (auto it = variables.begin(); it != variables.end(); it++)
	{
		if ((*it)->getName() == temp->getName())
			return *it;
	}
}

void SyntaxAnalysis::create_succ_pred()
{
	for (Instruction* in1 : instructions) {

		if (in1->get_type() == InstructionType::I_B) {
			for (Instruction* in2 : instructions) {
				
				if (in2->get_position() == in1->get_label()->get_position()) {
					in1->get_succ().push_back(in2);
					in2->get_pred().push_back(in1);
				}

			}
		}
		else {

			for (Instruction* in2 : instructions) {
				if (in1->get_position() + 1 == in2->get_position()) {
					in1->get_succ().push_back(in2);
					in2->get_pred().push_back(in1);
				}

				else if (in1->get_type() == InstructionType::I_BLTZ) {
					if (in1->get_label()->get_position() == in2->get_position()) {
						in1->get_succ().push_back(in2);
						in2->get_pred().push_back(in1);
					}
					

				}
			}

		}

	}
}

void SyntaxAnalysis::addLabelToInstruction(Instruction * inst)
{

	if (LabelExists(new Label(-1, currentToken.getValue()))) {

		for (auto i = labels.begin(); i != labels.end(); i++)
		{
			if (!strcmp(currentToken.getValue().c_str(), (*i)->get_name().c_str())) {
				(*inst).set_label(*i);
			}
		}
	}

}

void SyntaxAnalysis::check_function_name(string name)
{
	for (int i = 0; i < name.length(); i++)
	{
		if ((i == 0 && !isalpha(name[i])) || i > 0 && !isalnum(name[i]))
		{
			errorFound = true;
			throw WrongFunctionName();
		}
	}
}

void SyntaxAnalysis::print_instructions(Instructions* instruc)
{
	char *InstType[] = { "NO_TYPE", "ADD", "ADDI", "SUB", "LA", "LI", "LW", "SW", "BLTZ", "B", "NOP", "NEG", "NEGU","LHU" };

	for (Instructions::iterator it = instruc->begin(); it != instruc->end(); it++) {

		int counter = 1;
		std::cout << "Type: " << InstType[(*it)->get_type()] << "	Pos: " << (*it)->get_position() << std::endl;
		std::cout << "------------------------------------------" << std::endl;
		for (Variables::iterator i = (*it)->get_dst().begin(); i != (*it)->get_dst().end(); i++)
		{
			std::cout << "Dest" << counter++ << ":	Naziv: " << (*i)->getName() << ",  Pos: " << (*i)->getPosition()
				<< ",  Assignment: " << (*i)->getAssignment() << std::endl;
		}
		counter = 1;
		for (Variables::iterator i = (*it)->get_src().begin(); i != (*it)->get_src().end(); i++)
		{
			std::cout << "Src" << counter++ << ":	Naziv: " << (*i)->getName() << ",  Pos: " << (*i)->getPosition()
				<< ",  Assignment: " << (*i)->getAssignment() << std::endl;
		}
		std::cout << "------------------------------------------" << std::endl;
		std::cout << "PRED:	";

		for (Instruction* itt : (*it)->get_pred()) {
			cout << itt->get_position() << " ";
		}
		std::cout << std::endl;
		std::cout << "SUCC:	";

		for (Instruction* itt : (*it)->get_succ()) {
			cout << itt->get_position() << " ";
		}
		std::cout << std::endl;
		std::cout << "USE:	";
		for (Variables::iterator i = (*it)->get_use().begin(); i != (*it)->get_use().end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				std::cout << (*i)->getName() << '\t';
		}
		std::cout << std::endl;
		std::cout << "DEF:	";
		for (Variables::iterator i = (*it)->get_def().begin(); i != (*it)->get_def().end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				std::cout << (*i)->getName() << '\t';
		}
		std::cout << std::endl;
		std::cout << "IN:	";
		for (Variables::iterator i = (*it)->get_in().begin(); i != (*it)->get_in().end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				std::cout << (*i)->getName() << '\t';
		}
		std::cout << std::endl;
		std::cout << "Out:	";
		for (Variables::iterator i = (*it)->get_out().begin(); i != (*it)->get_out().end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				std::cout << (*i)->getName() << '\t';
		}
		std::cout << std::endl << "==========================================" << std::endl;
		std::cout << "==========================================" << std::endl;
	}
}

