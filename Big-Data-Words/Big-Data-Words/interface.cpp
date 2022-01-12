#include "interface.h"


void WordsMultiset::add(const std::string& word, size_t times) {

}

bool WordsMultiset::contains(const std::string& word) const {
	return true;
}

size_t WordsMultiset::countOf(const std::string& word) const
{
	return size_t();
}

size_t WordsMultiset::countOfUniqueWords() const
{
	return 0;
}

std::multiset<std::string> WordsMultiset::words() const
{
	return std::multiset<std::string>();
}

