#include "LivenessAnalysis.h"

void LivenessAnalysis::livenessAnalysis()
{

	list<Instruction> temp;

	do {
		temp.clear();
		for (auto it = instructions.rbegin(); it != instructions.rend(); ++it) {
			Instruction* instr = *it;
			temp.push_back(*instr);

			for (Instruction* s : instr->get_succ()) {
				for (Variable* var : s->get_in()) {
					instr->get_out().push_back(var);
				}
			}

			instr->get_out().sort();
			instr->get_out().unique();

			for (Variable* var : instr->get_use()) {
				instr->get_in().push_back(var);
			}
			for (Variable* var : instr->get_out()) {
				if (find(instr->get_def().begin(), instr->get_def().end(), var) == instr->get_def().end())
					instr->get_in().push_back(var);
			}
			instr->get_in().sort();
			instr->get_in().unique();
		}
	} while (!is_equal(temp));
}

bool LivenessAnalysis::is_equal(list<Instruction>& instructions_copy)
{
	for (Instruction* instr1 : instructions) {
		for (Instruction& instr2 : instructions_copy) {
			if (instr1->get_position() == instr2.get_position() &&
				(instr1->get_in().size() != instr2.get_in().size()
					|| instr1->get_out().size() != instr2.get_out().size()))
				return false;
		}
	}
	return true;
}
