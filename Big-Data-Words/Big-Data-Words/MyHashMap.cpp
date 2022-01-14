#include "MyHashMap.h"



HashMapTrie::HashMapTrie() {
    table = new RedBlackTree * [HASH_SIZE]();
    for (int i = 0; i < HASH_SIZE; i++) {
        table[i] = new RedBlackTree();
    }

}

HashMapTrie::~HashMapTrie() {
    for (int i = 0; i < HASH_SIZE; ++i) {
        RedBlackTree* entry = table[i];
        if (entry != nullptr) entry->~RedBlackTree();
        table[i] = nullptr;
    }
    delete[] table;
}

bool HashMapTrie::get(const std::string& key, size_t& value) const {
    size_t hashValue = hashFunc(key);
    RedBlackTree* entry = table[hashValue];
    RBTNode* root = entry->getRoot();
    if (root != nullptr) {
        RBTNode* node = entry->getNode(key, root);
        if (node != nullptr) {
            value = node->getCount();
            return true;
        }
    }
    return false;
}

bool HashMapTrie::contains(const std::string& key) const {
    size_t hashValue = hashFunc(key);
    RedBlackTree* entry = table[hashValue];
    RBTNode* root = entry->getRoot();

    if (root != nullptr) {
        if (entry->getNode(key, root) != nullptr)
            return true;
    }
    return false;
}

void HashMapTrie::put(const std::string& key, const size_t& value) {
    size_t hashValue = hashFunc(key);
    RedBlackTree* entry = table[hashValue];
    RBTNode* root = entry->getRoot();
    if (root != nullptr) {
        RBTNode* searchNode = entry->getNode(key, root);
        if (searchNode != nullptr) {
            searchNode->setCount(searchNode->getCount() + 1);
        }
        else {
            entry->insertNode(key, value);
        }
    }
    else {
        entry->insertNode(key, value);
        LinkedList* newNode = new LinkedList();
        newNode->root = entry;
        newNode->next = nullptr;
        if (listRoots == nullptr) {
            listRoots = newNode;
        }
        else {
            LinkedList* temp = listRoots;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}

void HashMapTrie::remove(const std::string& key) {
    size_t hashValue = hashFunc(key);
    RedBlackTree* entry = table[hashValue];
    RBTNode* root = entry->getRoot();

    if (root != nullptr) {
        entry->deleteNode(key);
    }
    if (root == nullptr) {
        LinkedList* temp = listRoots;
        LinkedList* prev = listRoots;
        while (temp->next != nullptr) {
            if (temp->root == entry) {
                prev->next = temp->next;
                delete temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }
}

std::multiset<RBTNode> HashMapTrie::getKeysAndValues() const {
    std::multiset<RBTNode> keysValues;
    LinkedList* temp = listRoots;
    while (temp != nullptr) {
        RedBlackTree* root = temp->root;
        std::multiset<RBTNode*> nodes = root->getNodes();
        for (auto& a : nodes) {
            RBTNode newNode = RBTNode(a->getData(), a->getCount());
            keysValues.insert(newNode);

        }
        temp = temp->next;
    }
    return keysValues;
}