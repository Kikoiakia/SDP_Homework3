#pragma once
#include "RBTree.h"

struct KeyHash {
    size_t operator()(const std::string& key, const int& hashSize = 2) const
    {
        return std::hash<std::string>() (key) % hashSize;
    }
};

struct LinkedList {
    RedBlackTree* root = nullptr;
    LinkedList* next = nullptr;
};



class HashMapTrie {
private:
    RedBlackTree** table;
    KeyHash hashFunc;
    LinkedList* listRoots{};

public:
    HashMapTrie();

    ~HashMapTrie();

    bool get(const std::string& key, size_t& value) const;

    bool contains(const std::string& key) const;

    void put(const std::string& key, const size_t& value = 0);

    void remove(const std::string& key);

    std::multiset<RBTNode> getKeysAndValues() const;

};