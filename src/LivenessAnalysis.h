#pragma once

#include "Types.h"
#include "Constants.h"
#include "IR.h"
class LivenessAnalysis {
public:

	LivenessAnalysis() {};
	~LivenessAnalysis() {};
	LivenessAnalysis(Instructions& i) : instructions(i) {};

	Instructions instructions;
	void livenessAnalysis();
	bool is_equal(list<Instruction>& temp);
};
