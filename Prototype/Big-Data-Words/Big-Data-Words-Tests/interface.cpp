#include "interface.h"


void WordsMultiset::add(const std::string& word, size_t times) {
	if (times > 0) {
		auto search = m.find(word);
		if (search != m.end()) {
			size_t time = m[word] + times;
			m.insert_or_assign(word, time);
		}
		else {
			std::pair<std::string, size_t> newItem;
			newItem.first = word;
			newItem.second = times;
			m.insert(newItem);
		}
	}		
	else {
		throw std::exception("Can't add a word negative times or 0 times");
	}
}

bool WordsMultiset::contains(const std::string& word) const {
	return (m.find(word) != m.end());
}

size_t WordsMultiset::countOf(const std::string& word) const
{
	size_t count = 0;
	if (m.find(word) != m.end()) count = m.at(word);
	return count;
}

size_t WordsMultiset::countOfUniqueWords() const
{
	size_t num = 0;
	for (auto kv : m) {
		//for(size_t i = 0; i < kv.second; i++)
			num++;
	}
	return num;
}

std::multiset<std::string> WordsMultiset::words() const
{
	std::multiset<std::string> words;
	for (auto kv : m) {
		for(size_t i = 0; i < kv.second; i++)
			words.insert(kv.first);
	}
	return words;
}

std::multiset<std::string> WordsMultiset::getUniqueWords() const
{
	std::multiset<std::string> words;
	for (auto kv : m) 
			words.insert(kv.first);
	
	return words;
}

void WordsMultiset::getWords(std::istream& stream) {

	std::string word;
	if (stream.good())
	{
		while (stream >> word)
		{
			this->add(word);
		}
	}

	else {
		throw std::exception("Bad stream");
	}
}

ComparisonReport Comparator::compare(std::istream& a, std::istream& b) {
	WordsMultiset first, second;
	ComparisonReport report;
	first.getWords(a);
	second.getWords(b);
	for (auto& a : first.getUniqueWords()) {		
		if (second.contains(a)) {
			size_t count = first.countOf(a);
			size_t count2 = second.countOf(a);
			if (count <= count2)   
				for(size_t i = 0; i < count; i++) 
					report.commonWords.add(a);
			else {
				report.commonWords.add(a, (count - count2));
				count = count - (count - count2);
				report.uniqueWords[0].add(a, count);
			}
		}
		else {
			report.uniqueWords[0].add(a);
		}
	}
	for (auto& a : second.getUniqueWords()) {
		if (first.contains(a)) {
			size_t count = second.countOf(a);
			size_t count2 = first.countOf(a);
			if (count > count2) {
				count = count - count2;
				report.uniqueWords[1].add(a, count);
			}				
		}
		else {
			report.uniqueWords[1].add(a);
		}
	}
	
	return report;
}

