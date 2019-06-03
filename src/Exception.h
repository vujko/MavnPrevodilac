#pragma once
#include <iostream>

class WrongMemoryName : public std::runtime_error
{
public:
	WrongMemoryName() : std::runtime_error("Wrong definition of memory loaction!") {}
};

class WrongRegistryName : public std::runtime_error
{
public:
	WrongRegistryName() : std::runtime_error("Wrong definistion of registry") {}
};

class LabelRedefined :public std::runtime_error
{
public:
	LabelRedefined() : std::runtime_error("Label has been already defined") {}
};

class VariableRedefined : public std::runtime_error
{
public:
	VariableRedefined() : std::runtime_error("Variable has been already defined!") {}
};

class WrongFunctionName : public std::runtime_error
{
public:
	WrongFunctionName() : std::runtime_error("Wrong definition of function!") {}
};

class UndefinedVariable : public std::runtime_error
{
public:
	UndefinedVariable() : std::runtime_error("Variable has not been defined!") {}
};

class UndefinedInstruction : public std::runtime_error
{
public:
	UndefinedInstruction() : std::runtime_error("Undefined instruction!!") {}
};

class WrongResourceManagement : std::runtime_error
{
public:
	WrongResourceManagement() : runtime_error("Error! Spill happened!") {}
};

class WrongOutputFileName : std::runtime_error
{
public:
	WrongOutputFileName() : runtime_error("\nException! Failed to open input file!\n") {}
};

class NotEnughRegisters : std::runtime_error {
public:
	NotEnughRegisters() : runtime_error("\nThere is not enough registers to complete the program!\n\n") {}
};

class AllocationFailed : runtime_error {
public:
	AllocationFailed() : runtime_error("\nException!Resource allocation failed!\n") {}
};