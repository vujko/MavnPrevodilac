#include "InterferenceGraph.h"

void InterferenceGraph::printInterferenceMatrix()
{
	if (matrix.size() == 0)
	{
		cout << "There is nothing to print!" << endl;
		return;
	}

	cout << endl << "Interference matrix:" << endl;
	cout << "==========================================" << endl;

	// print existing variables in order to mark rows and columns
	for (auto varIt = variables->begin(); varIt != variables->end(); varIt++)
	{
		cout << "\t" << (*varIt)->getName();
	}
	cout << endl;

	auto varIt = variables->begin();
	for (auto it1 = matrix.begin(); it1 != matrix.end(); it1++)
	{
		cout << (*varIt++)->getName();
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			cout << "\t" << *it2;
		}
		cout << endl;
	}
	cout << "==========================================" << endl;

}

void InterferenceGraph::makeInterferenceGraph(Instructions& instructions)
{
	
	matrix.resize(variables->size());

	for (auto iter = matrix.begin(); iter != matrix.end(); iter++) {
		iter->resize(variables->size(), __EMPTY__);
	}

	for (Instruction* inst : instructions) {

		for (Variable* a : inst->get_def()) {
			for (Variable* b : inst->get_out()) {
				if (a->getPosition() != b->getPosition() && a->getType() != Variable::VariableType::MEM_VAR && b->getType() != Variable::VariableType::MEM_VAR) {

					matrix[a->getPosition()][b->getPosition()] = __INTERFERENCE__;
					matrix[b->getPosition()][a->getPosition()] = __INTERFERENCE__;
					
				}
			}
		}
		
	}


}

Variables * InterferenceGraph::get_reg_variables(Variables & all_variables)
{
	Variables* var = new Variables();
	int position = 0;
	for (auto it = all_variables.begin(); it != all_variables.end(); it++)
	{
		if ((*it)->getType() == Variable::REG_VAR) {

			(*it)->set_position(position++);
			var->push_back(*it);
		}
	}

	return var;
}
