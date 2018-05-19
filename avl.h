class BinarySearchNode
{
public:
	BinarySearchNode(int value);
	void setValue(int value);
	void setLeft(BinarySearchNode* node);
	void setRight(BinarySearchNode* node);
	int getValue();
	BinarySearchNode* getLeft();
	BinarySearchNode* getRight();
private:
	int storedValue;
	BinarySearchNode* childLeft;
	BinarySearchNode* childRight;
};


class AVLSearchTree
{
public:
	AVLSearchTree(int value);
	BinarySearchNode* rotateWithLeftChild(BinarySearchNode* node);
	BinarySearchNode* doubleWithLeftChild(BinarySearchNode* node);
	BinarySearchNode* rotateWithRightChild(BinarySearchNode* node);
	BinarySearchNode* doubleWithRightChild(BinarySearchNode* node);
	void insert(int value, BinarySearchNode* node);
	BinarySearchNode* remove(int value, BinarySearchNode* t);
	BinarySearchNode* balanceTree(BinarySearchNode* root);
	BinarySearchNode* getRoot();
	int find(int value, BinarySearchNode* node);
	int findMin(BinarySearchNode node);
	int getHeight(BinarySearchNode* node, int initialheight);
private:
	BinarySearchNode* root;
};