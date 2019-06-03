#pragma once
#ifndef INTERFERENCE_GRAPH
#define INTERFERENCE_GRAPH

#include "IR.h"

extern Variables variables;
extern Instructions instructions;

typedef std::vector<std::vector<int>> InterferenceMatrix;

class InterferenceGraph {
public:
	Variables * variables;		// all variables from instructions
	InterferenceMatrix matrix;	// interference matrix

	InterferenceGraph() {}

	InterferenceGraph(Variables v, Instructions& instructions) : variables(get_reg_variables(v)) {
		makeInterferenceGraph(instructions);
	}

	void setMatrix(InterferenceMatrix* mat) { matrix = *mat; }

	void printInterferenceMatrix();

	InterferenceMatrix getMatrix() { return matrix; }

	Variables getVars() { return *variables; }
	void makeInterferenceGraph(Instructions& instructions);

private:

	Variables * get_reg_variables(Variables& all_variables);

};




#endif