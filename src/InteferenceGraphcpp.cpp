#include "InterferenceGraph.h"
//#include "Test.h"

#include <iostream>
#include <vector>

using namespace std;

static InterferenceGraph ig;

//InterferenceGraph& buildInterferenceGraph(Instructions& instructions)
//{
//
//	//ig.variables = &getVariables();
//
//	//ig.matrix.resize(ig.variables->size());
//
//	//for (auto iter = ig.matrix.begin(); iter != ig.matrix.end(); iter++)
//	//	it->resize(ig.variables->size(), __EMPTY__);
//
//	//for (Instruction* inst : instructions)
//	//	if (inst->type != InstructionType::move)
//	//		for (Variable* a : inst->def)
//	//			for (Variable* b : inst->out)
//	//				if (a->pos != b->pos)
//	//				{
//	//					ig.matrix[a->pos][b->pos] = __INTERFERENCE__;
//	//					ig.matrix[b->pos][a->pos] = __INTERFERENCE__;
//	//				}
//
//	//return ig;
//}


void printInterferenceMatrix()
{
	if (ig.matrix.size() == 0)
	{
		cout << "There is nothing to print!" << endl;
		return;
	}

	cout << "==========================================" << endl;
	cout << "Interference matrix:" << endl;
	cout << "==========================================" << endl;

	// print existing variables in order to mark rows and columns
	for (auto varIt = ig.variables->begin(); varIt != ig.variables->end(); varIt++)
	{
		cout << "\t" << (*varIt)->getName();
	}
	cout << endl;

	auto varIt = ig.variables->begin();
	for (auto it1 = ig.matrix.begin(); it1 != ig.matrix.end(); it1++)
	{
		cout << (*varIt++)->getName();
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			char i = (*it2 == 32 || *it2 == 120) ? (char)*it2 : 120;
			cout << "\t" << i;
		}
		cout << endl;
	}
	cout << "==========================================" << endl;
}
