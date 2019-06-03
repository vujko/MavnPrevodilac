#include "SimplificationStack.h"
bool in_removed(vector<int> vec, int position) {
	for (auto i = vec.begin(); i < vec.end(); i++) {
		if ((*i) == position) {
			return true;
		}
	}
	return false;

}
void doSimplification(SimplificationStack& ss, InterferenceGraph* ig, int degree)
{
	int maxPosition = -1;
	int numberOfNeighbourss = -1;
	int size = ig->variables->size();
	int counter;
	vector<int> removed_positions;

	while (size > 0) {
		maxPosition = -1;
		numberOfNeighbourss = -1;
		for (int i = 0; i < ig->matrix.size(); i++) {
			if (in_removed(removed_positions, i))
				continue;
			counter = 0;
			// za svaku variablu trazim onu sa kojom je ona u sukobu inkrementuj counter te varijable 
			for (int j = 0; j < ig->matrix.size(); j++) {
				if (ig->matrix[i][j] == __INTERFERENCE__ && !in_removed(removed_positions, j))
					counter++;
			}
			// brojac ne sme da bude veci od broja resursa 
			if (counter > numberOfNeighbourss && counter < degree)
			{
				// kada se naidje na do sada  najveci 
				numberOfNeighbourss = counter;
				maxPosition = i;
			}

		}

		// ako mu je broj komsija manji od nula baci gresku ,
		// najmanji broj komsija je nula ( viseci cvor )
		if (numberOfNeighbourss < 0) {
			
		}

		for (auto it = ig->variables->begin(); it != ig->variables->end(); it++)
		{
			if ((*it)->getPosition() == maxPosition) {
				ss.push(*it);
			}
		}
		removed_positions.push_back(maxPosition);

		size--;
	}

}