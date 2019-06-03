#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "SimplificationStack.h"
#include "ResourceAllocation.h"
#include "Writer.h"
#include <iostream>
#include <exception>

using namespace std;

void main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		string outputFile = ".\\..\\examples\\simpleOut.s";
		bool retVal = false;

		LexicalAnalysis lex;
		
		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");
		
		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}


		///
		SyntaxAnalysis syntax(lex);

		retVal = syntax.Do();

		if (retVal)
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}

		syntax.create_succ_pred();
		syntax.print_instructions(&syntax.instructions);
		LivenessAnalysis la = LivenessAnalysis(syntax.instructions);
		la.livenessAnalysis();


		cout << endl;
		cout << "==========================================" << endl;
		cout << "Instruction list after LIVENESS ANALYSIS:" << endl;
		cout << "==========================================" << endl;
		syntax.print_instructions(&syntax.instructions);

		InterferenceGraph ig(syntax.variables, syntax.instructions);
		ig.printInterferenceMatrix();

		SimplificationStack ss;
		doSimplification(ss, &ig, __REG_NUMBER__);
		bool resourceSuccessful = doResourceAllocation(ss, ig);
		if (resourceSuccessful) {
			cout << endl;
			cout << "==========================================" << endl;
			cout << "Resource allocation finished successfuly  " << endl;
			cout << "==========================================" << endl;

		}
		else {
			throw AllocationFailed();
		}
		cout << endl;
		cout << "==========================================" << endl;
		cout << "Instruction list after RESOURCE ALLOCATION:" << endl;
		cout << "==========================================" << endl;
		syntax.print_instructions(&syntax.instructions);

		write(syntax.instructions, syntax.variables, syntax.labels, outputFile);
	}	
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
}