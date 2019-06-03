#include "Writer.h"

void write(Instructions & instructions, Variables & variables, Labels & labels, string name)
{
	string regs[] = { "", "$t0", "$t1", "$t2", "$t3", "$t4" };
	ofstream of(name);

	if (of) {
		of << ".globl main" << endl;
		of << endl << ".data" << endl;
		for (auto var = variables.begin(); var != variables.end(); var++) {
			if ((*var)->getType() == Variable::MEM_VAR) {
				of << (*var)->getName() << ": .word " << (*var)->getValue() << endl;
			}
		}
		of << ".text" << endl;

		for (auto inst = instructions.begin(); inst != instructions.end(); inst++) {
			for (auto lab = labels.begin(); lab != labels.end(); lab++) {
				if ((*lab)->get_position() == (*inst)->get_position()) {
					of << (*lab)->get_name() << ":" << endl;
				}
			}

			string instString = (*inst)->get_text();
			int commandPos = 0;

			while (instString.find("'d") != string::npos) {
				commandPos = instString.find("'d");
				instString.replace(commandPos, 2, regs[(*inst)->get_dst().front()->getAssignment()]);
			}
			while (instString.find("'s") != string::npos) {
				commandPos = instString.find("'s");

				instString.replace(commandPos, 2, (*inst)->get_src().front()->getType() == Variable::VariableType::MEM_VAR ? (*inst)->get_src().front()->getName() : regs[(*inst)->get_src().front()->getAssignment()]);
				(*inst)->get_src().remove((*inst)->get_src().front());
			}
			while (instString.find("'l") != string::npos) {
				commandPos = instString.find("'l");
				instString.replace(commandPos, 2, (*inst)->get_label()->get_name());
			}
			while (instString.find("'n") != string::npos) {
				commandPos = instString.find("'n");
				instString.replace(commandPos, 2, to_string((*inst)->get_number()));
			}

			of << instString << endl;
		}
	}
	else {
		throw WrongOutputFileName();
	}
	of.close();
}
