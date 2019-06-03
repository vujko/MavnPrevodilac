#pragma once

#include "IR.h"
#include <stack>
#include "InterferenceGraph.h"
#include "Exception.h"
using namespace std;

typedef stack<Variable*> SimplificationStack;

SimplificationStack* doSimplification(InterferenceGraph ig, int degree);

void doSimplification(SimplificationStack& ss, InterferenceGraph* ig, int degree);

