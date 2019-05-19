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

	InterferenceGraph(Variables* v) : variables(v) {}

	void setMatrix(InterferenceMatrix* mat) { matrix = *mat; }

	void printInterferenceMatrix();

	InterferenceMatrix getMatrix();

	Variables getVars();

};


InterferenceGraph makeInterferenceGraph();

#endif