#pragma once
#include "interface.h"
class Program {
private:
	WordsMultiset first, second;
	ComparisonReport report;
	bool isRunning = true;
public:
	void Run(int argc, char** argv);
};