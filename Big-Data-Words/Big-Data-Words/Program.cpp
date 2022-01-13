#include "Program.h"
#include <fstream>

void Program::Run(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Input files not detected. Exiting program.\n";
		isRunning = false;
	}
	else {
		std::string line;
		std::ifstream file1(argv[1]), file2(argv[2]);
		if (file1.is_open())
		{
			std::cout << "Successfully opened the first file. Getting data.\n";
			while (!file1.eof())
			{
				std::string* word = new std::string;
				file1 >> *word;
				first.add(*word);
				delete word;
				
			}
			file1.close();
			std::cout << "Successfully got the data.\n";
		}

		else {
			std::cout << "Unable to open first file. Terminating program.\n";
			isRunning = false;
		}
		
		if (file2.is_open())
		{
			std::cout << "Successfully opened the second file. Getting data.\n";
			while (!file2.eof())
			{
				std::string* word = new std::string;
				file2 >> *word;
				second.add(*word);
				delete word;
			}
			file2.close();
			std::cout << "Successfully got the data.\n";
		}


		else {
			std::cout << "Unable to open second file. Terminating program.\n";
			isRunning = false;
		}
		

	}
	if(isRunning) {
		std::cout << "Data loaded and being processed...\n";
		size_t wordsSizeFirst = 0, wordsFoundInSecond = 0;
		size_t wordsSizeSecond = 0, wordsFoundInFirst = 0;
		std::multiset<std::string> words1 = first.getUniqueWords();
		std::multiset<std::string> words2 = second.getUniqueWords();
		for (auto& a : words1) {
			size_t count = first.countOf(a);
			wordsSizeFirst += count;
			if (second.contains(a)) {
				size_t count2 = second.countOf(a);
				if (count <= count2) wordsFoundInSecond += count;
				else {
					wordsFoundInSecond += count - (count - count2);
				}
			}				
		}
		for (auto& a : words2) {
			size_t count = second.countOf(a);
			wordsSizeSecond += count;
			if (first.contains(a)) {
				size_t count2 = first.countOf(a);
				if (count <= count2) wordsFoundInFirst += count;
				else {
					wordsFoundInFirst += count - (count - count2);
				}
			}
		}
		double percentage1, percentage2;
		percentage1 = (wordsFoundInSecond / (double)wordsSizeFirst) * 100;
		percentage2 = (wordsFoundInFirst / (double)wordsSizeSecond) * 100;
		std::cout << "First file contains " << wordsSizeFirst << " words and " << wordsFoundInSecond << " of them are in the second file. (" << percentage1 << "%)\n";
		std::cout << "First file contains " << wordsSizeSecond << " words and " << wordsFoundInFirst << " of them are in the second file. (" << percentage2 << "%)\n";
	}

	std::cout << "Goodbye.\n";
}