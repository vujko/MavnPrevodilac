#pragma once
#include "IR.h"
#include "Exception.h"
#include <fstream>
#include <sstream>

void write(Instructions& instructions, Variables& variables, Labels& labels, string name);