#include "RBTree.h"

RBTNode::RBTNode(const std::string& data, size_t count)
{
	this->data = data;
	this->count = count;
	parent = left = right = nullptr;
	color = RED;
}

RBTNode::RBTNode(const std::string data, const int& color, size_t count)
{
	this->data = data;
	this->color = color;
	this->count = count;
	parent = left = right = nullptr;
}

bool RBTNode::operator<(const RBTNode& rhs) const noexcept {
	return this->data < rhs.data;
}

RBTNode::~RBTNode() {
	delete left;
	delete right;
}

void RBTNode::setColor(const int color)
{
	this->color = color;
}

int RBTNode::getColor() const
{
	return color;
}

const std::string RBTNode::getData() const
{
	return data;
}

void RBTNode::setData(std::string data)
{
	this->data = data;
}

void RBTNode::setCount(size_t count) {
	this->count = count;
}

size_t RBTNode::getCount() const {
	return count;
}


RBTNode* BSTInsert(RBTNode* root, RBTNode* node)
{
	if (root == nullptr)
		return node;
	if (root->getData() > node->getData())
	{
		root->left = BSTInsert(root->left, node);
		root->left->parent = root;
	}
	else if (root->getData() < node->getData())
	{
		root->right = BSTInsert(root->right, node);
		root->right->parent = root;
	}

	return root;

}


RedBlackTree::RedBlackTree(const std::string& data)
{
	root = new RBTNode(data);
	root->setColor(BLACK);
}

RedBlackTree::RedBlackTree()
{
	this->root = nullptr;
}

RedBlackTree::~RedBlackTree() {
	if(this != nullptr)
	delete root;
}

RBTNode* RedBlackTree::getRoot()
{
	if (root == nullptr) return nullptr;
	return root;
}


void RedBlackTree::swapNodeColor(RBTNode* nodeA, RBTNode* nodeB)
{
	int tempColor = nodeA->getColor();
	nodeA->setColor(nodeB->getColor());
	nodeB->setColor(tempColor);

}

RBTNode* RedBlackTree::getMaxValueNode(RBTNode* root)
{
	if (root == nullptr)
		return nullptr;
	else if (root->right == nullptr)
		return root;
	else
		return getMaxValueNode(root->right);
}


RBTNode* RedBlackTree::getGrandParent(RBTNode* node)
{
	if ((node != nullptr) && (node->parent != nullptr))
		return node->parent->parent;
	return nullptr;

}

RBTNode* RedBlackTree::getUncle(RBTNode* node)
{
	RBTNode* grandParent = getGrandParent(node);

	if (grandParent == nullptr)
		return nullptr;
	if (node->parent == grandParent->left)
		return grandParent->right;
	if (node->parent == grandParent->right)
		return grandParent->left;

}

void RedBlackTree::rotateLeft(RBTNode*& node)
{
	RBTNode* rightNode = node->right;
	RBTNode* nodeParent = node->parent;
	node->right = rightNode->left;

	if (node->right != nullptr)
		node->right->parent = node;

	rightNode->parent = nodeParent;

	if (node->parent == nullptr)
		this->root = rightNode;
	else if (node == node->parent->left)
		node->parent->left = rightNode;
	else
		node->parent->right = rightNode;

	rightNode->left = node;
	node->parent = rightNode;
}

void RedBlackTree::rotateRight(RBTNode*& node)
{
	RBTNode* nodeLeft = node->left;
	node->left = nodeLeft->right;

	if (node->left != nullptr)
		node->left->parent = node;


	nodeLeft->parent = node->parent;

	if (node->parent == nullptr)
		this->root = nodeLeft;
	else if (node == node->parent->left)
		node->parent->left = nodeLeft;
	else
		node->parent->right = nodeLeft;

	nodeLeft->right = node;
	node->parent = nodeLeft;


}


void RedBlackTree::fixInsertViolation(RBTNode*& node)
{

	RBTNode* parentNode = nullptr;
	RBTNode* grandParentNode = nullptr;


	while ((node != root) && (node->getColor() != BLACK) && (node->parent->getColor() == RED))
	{

		parentNode = node->parent;
		grandParentNode = getGrandParent(node);

		/*  Case : A
			Parent of node is left child of Grand-parent of node */
		if (parentNode == grandParentNode->left)
		{

			RBTNode* uncleNode = grandParentNode->right;

			/* Case : 1
			   The uncle of node is also red
			   Only Recoloring required */
			if (uncleNode != nullptr && uncleNode->getColor() == RED)
			{
				grandParentNode->setColor(RED);
				parentNode->setColor(BLACK);
				uncleNode->setColor(BLACK);
				node = grandParentNode;
			}

			else
			{
				/* Case : 2
				   node is right child of its parent
				   Left-rotation required */
				if (node == parentNode->right)
				{
					rotateLeft(parentNode);

					node = parentNode;
					parentNode = node->parent;
				}

				/* Case : 3
				   node is left child of its parent
				   Right-rotation required */
				rotateRight(grandParentNode);
				swapNodeColor(parentNode, grandParentNode);
				node = parentNode;
			}
		}

		/* Case : B
		   Parent of node is right child of Grand-parent of node */
		else
		{
			RBTNode* uncleNode = grandParentNode->left;

			/*  Case : 1
				The uncle of node is also red
				Only Recoloring required */
			if ((uncleNode != nullptr) && (uncleNode->getColor() == RED))
			{
				grandParentNode->setColor(RED);
				parentNode->setColor(BLACK);
				uncleNode->setColor(BLACK);
				node = grandParentNode;
			}
			else
			{
				/* Case : 2
				   node is left child of its parent
				   Right-rotation required */
				if (node == parentNode->left)
				{
					rotateRight(parentNode);
					node = parentNode;
					parentNode = node->parent;
				}

				/* Case : 3
				   node is right child of its parent
				   Left-rotation required */
				rotateLeft(grandParentNode);
				swapNodeColor(parentNode, grandParentNode);
				node = parentNode;
			}
		}
	}

	root->setColor(BLACK);
}

void RedBlackTree::insertNode(std::string data, size_t count)
{
	RBTNode* newNode = new RBTNode(data, count);

	this->root = BSTInsert(this->root, newNode);

	fixInsertViolation(newNode);

}

RBTNode* RedBlackTree::getNodeToDeletePosition(RBTNode* root, std::string key)
{
	if (root == nullptr)
		return root;
	if (key < root->getData())
		return getNodeToDeletePosition(root->left, key);
	else if (key > root->getData())
		return getNodeToDeletePosition(root->right, key);

	if (root->left == nullptr or root->right == nullptr)
		return root;

	RBTNode* temp = getMaxValueNode(root->left);
	root->setData(temp->getData());
	return getNodeToDeletePosition(root->left, temp->getData());
}

void RedBlackTree::fixDeleteViolation(RBTNode* node)
{
	if (node == nullptr)
		return;

	if (node == root)
	{
		root = nullptr;
		return;
	}

	if (node->getColor() == RED || node->left->getColor() == RED || node->right->getColor() == RED)
	{
		RBTNode* child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left)
		{
			node->parent->left = child;
			if (child != nullptr)
			{
				child->parent = node->parent;
				child->setColor(BLACK);
			}
			delete (node);
		}
		else
		{
			node->parent->right = child;
			if (child != nullptr)
			{
				child->parent = node->parent;
				child->setColor(BLACK);
			}
			delete (node);
		}
	}
	else
	{
		RBTNode* sibling = nullptr;
		RBTNode* parent = nullptr;
		RBTNode* ptr = node;
		ptr->setColor(DOUBLE_BLACK);
		while (ptr != root && ptr->getColor() == DOUBLE_BLACK)
		{
			parent = ptr->parent;
			if (ptr == parent->left)
			{
				sibling = parent->right;

				if (!sibling->right)
				{
					sibling->right = new RBTNode("", BLACK);
					sibling->right->parent = sibling;
				}
				if (!sibling->left)
				{
					sibling->left = new RBTNode("", BLACK);
					sibling->left->parent = sibling;
				}
				//If sibling is red
				//Make sibling black
				//Make parent red
				//Rotate parent left
				if (sibling->getColor() == RED)
				{
					sibling->setColor(BLACK);
					parent->setColor(RED);
					rotateLeft(parent);

				}
				//If sibling is black
				else
				{
					//If both children of sibling are black
					//Make sibling red
					//If parent is red, make it black
					//If parent is black,make it double black
					if (sibling->left->getColor() == BLACK && sibling->right->getColor() == BLACK)
					{
						sibling->setColor(RED);
						if (parent->getColor() == RED)
							parent->setColor(BLACK);
						else
							parent->setColor(DOUBLE_BLACK);
						ptr = parent;
					}
					else
					{
						if (sibling->right->getColor() == BLACK) {
							sibling->left->setColor(BLACK);
							sibling->setColor(RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						sibling->setColor(parent->getColor());
						parent->setColor(BLACK);
						sibling->right->setColor(BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else
			{
				sibling = parent->left;
				if (!sibling->right)
				{
					sibling->right = new RBTNode("", BLACK);
					sibling->right->parent = sibling;
				}
				if (!sibling->left)
				{
					sibling->left = new RBTNode("", BLACK);
					sibling->left->parent = sibling;
				}
				if (sibling->getColor() == RED) {
					sibling->setColor(BLACK);
					parent->setColor(RED);
					rotateRight(parent);
				}
				else {
					if (sibling->left->getColor() == BLACK && sibling->right->getColor() == BLACK) {
						sibling->setColor(RED);
						if (parent->getColor() == RED)
							parent->setColor(BLACK);
						else
							parent->setColor(DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (sibling->left->getColor() == BLACK) {
							sibling->right->setColor(BLACK);
							sibling->setColor(RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						sibling->setColor(parent->getColor());
						parent->setColor(BLACK);
						sibling->left->setColor(BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
		delete(node);
		root->setColor(BLACK);
	}

}
void RedBlackTree::deleteNode(std::string data)
{
	RBTNode* nodeToDelete = getNodeToDeletePosition(this->root, data);
	if (!nodeToDelete->right)
	{
		nodeToDelete->right = new RBTNode("", BLACK);
		nodeToDelete->right->parent = nodeToDelete;
	}
	if (!nodeToDelete->left)
	{
		nodeToDelete->left = new RBTNode("", BLACK);
		nodeToDelete->left->parent = nodeToDelete;
	}
	fixDeleteViolation(nodeToDelete);
}

void RedBlackTree::inorderTraversal(RBTNode* root)
{
	if (root != nullptr)
	{
		inorderTraversal(root->left);
		std::cout << root->getData() << " ";
		inorderTraversal(root->right);
	}
}


void RedBlackTree::preorderTraversal(RBTNode* root)
{
	if (root != nullptr)
	{
		std::cout << root->getData() << " ";
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

RBTNode* RedBlackTree::getNode(const std::string& key, RBTNode* root)
{
	if (root == nullptr) return nullptr;
	if (root->getData() == key) return root;
	if (root->getData() < key) getNode(key, root->right);
	else getNode(key, root->left);
}

void RedBlackTree::getNodesHelp(std::multiset<RBTNode*>& nodes, RBTNode* root) const {
	if (root != nullptr)
	{
		getNodesHelp(nodes, root->left);
		nodes.insert(root);
		getNodesHelp(nodes, root->right);
	}
}

std::multiset<RBTNode*> RedBlackTree::getNodes() const {
	std::multiset<RBTNode*> nodes;
	getNodesHelp(nodes, root);
	return nodes;
}
