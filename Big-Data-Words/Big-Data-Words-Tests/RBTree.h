#include <string>
#include <set>
#include <iostream>
#define BLACK 0
#define RED 1
#define DOUBLE_BLACK 2

//Red Black Tree Node
class RBTNode
{

	int color = -1;
	std::string data{};
	size_t count = 0;

public:
	RBTNode* parent = nullptr;
	RBTNode* left = nullptr;
	RBTNode* right = nullptr;

	RBTNode(const std::string& data, size_t count = 1);

	RBTNode(const std::string data, const int& color, size_t count = 1);

	bool operator<(const RBTNode& rhs) const noexcept;

	~RBTNode();

	void setColor(const int color);

	int getColor() const;

	const std::string getData() const;

	void setData(std::string data);
	
	void setCount(size_t count);

	size_t getCount() const;

};


//Red Black Tree class
class RedBlackTree
{

	RBTNode* root = nullptr;

public:
	RedBlackTree(const std::string& data);

	RedBlackTree();

	~RedBlackTree();

	RBTNode* getRoot();

	//Swapping colors of two nodes
	void swapNodeColor(RBTNode* nodeA, RBTNode* nodeB);
	
	RBTNode* getMaxValueNode(RBTNode* root);

	RBTNode* getGrandParent(RBTNode* node);

	RBTNode* getUncle(RBTNode* node);

	void rotateLeft(RBTNode*& node);

	void rotateRight(RBTNode*& node);

	//Fixes Red Black Tree propertied after inserting a node	
	void fixInsertViolation(RBTNode*& node);

	void insertNode(std::string data, size_t count);

	RBTNode* getNodeToDeletePosition(RBTNode* root, std::string key);

	void fixDeleteViolation(RBTNode* node);

	void deleteNode(std::string data);

	void inorderTraversal(RBTNode* root);

	void preorderTraversal(RBTNode* root);

	RBTNode* getNode(const std::string& key, RBTNode* root);

	void getNodesHelp(std::multiset<RBTNode*>& nodes, RBTNode* root) const;

	std::multiset<RBTNode*> getNodes() const;


};

