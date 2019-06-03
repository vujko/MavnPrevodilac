#include "ResourceAllocation.h"

bool doResourceAllocation(SimplificationStack ss, InterferenceGraph ig)
{
	Variables colored;
	while (!ss.empty())
	{
		list<Regs> regs;
		regs.push_back(t0);
		regs.push_back(t1);
		regs.push_back(t2);
		regs.push_back(t3);
		regs.push_back(t4);

		Variable* var = ss.top();
		ss.pop();

		if (!colored.empty())
		{
			for (Variable* a : colored)
			{
				if (ig.matrix[var->getPosition()][a->getPosition()] == __INTERFERENCE__)
				{
					regs.remove(a->getAssignment());
				}
			}

		}

		if (!regs.empty())
		{
			var->set_assignment(regs.front());
			colored.push_back(var);
		}
		else {
			return false;
		}
	}
	return true;
}
