#include "interface.h"


void WordsMultiset::add(const std::string& word, size_t times) {
	if (times > 0) {
		size_t val = 1;
		if (m.get(word,val)) {
			size_t time = val + times;
			m.put(word, time);
		}
		else {
			m.put(word, times);
		}
	}		
	else {
		throw std::exception("Can't add a word negative times or 0 times");
	}
}

bool WordsMultiset::contains(const std::string& word) const{
	return m.contains(word);
}

size_t WordsMultiset::countOf(const std::string& word) const
{
	size_t count = 0;
	if (m.get(word, count)) return count;
	return count;
}

size_t WordsMultiset::countOfUniqueWords() const
{
	size_t num = 0;
	
	std::multiset<RBTNode> keyValues = m.getKeysAndValues();
	num = keyValues.size();

	
	return num;
}

std::multiset<std::string> WordsMultiset::words() const
{
	std::multiset<RBTNode> keyValues = m.getKeysAndValues();
	std::multiset<std::string> words;
	for (auto& kv : keyValues) {
		for (int i = 0; i < kv.getCount(); ++i)
			words.insert(kv.getData());
	}
	
	return words;
}

std::multiset<std::string> WordsMultiset::getUniqueWords() const
{
	std::multiset<RBTNode> keyValues = m.getKeysAndValues();
	std::multiset<std::string> words;
	for (auto& kv : keyValues) {
			words.insert(kv.getData());
	}

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
	ComparisonReport* report = new ComparisonReport();
	first.getWords(a);
	second.getWords(b);
	for (auto& a : first.getUniqueWords()) {
		if (second.contains(a)) {
			size_t count = first.countOf(a);
			size_t count2 = second.countOf(a);
			if (count <= count2)
				for (size_t i = 0; i < count; i++)
					report->commonWords.add(a);
			else {
				report->commonWords.add(a, (count - count2));
				count = count - (count - count2);
				report->uniqueWords[0].add(a, count);
			}
		}
		else {
			report->uniqueWords[0].add(a);
		}
	}
	for (auto& a : second.getUniqueWords()) {
		if (first.contains(a)) {
			size_t count = second.countOf(a);
			size_t count2 = first.countOf(a);
			if (count > count2) {
				count = count - count2;
				report->uniqueWords[1].add(a, count);
			}
		}
		else {
			report->uniqueWords[1].add(a);
		}
	}

	return *report;
}

