#include "avl.h"

BinarySearchNode::BinarySearchNode(int num)
{
	storedValue = num;
	childLeft = nullptr;
	childRight = nullptr;
}

void BinarySearchNode::setValue(int num)
{
	storedValue = num;
}

void BinarySearchNode::setLeft(BinarySearchNode* node)
{
	childLeft = node;
}

void BinarySearchNode::setRight(BinarySearchNode* node)
{
	childRight = node;
}

BinarySearchNode* BinarySearchNode::getLeft()
{
	return childLeft;
}

BinarySearchNode* BinarySearchNode::getRight()
{
	return childRight;
}

int BinarySearchNode::getValue()
{
	return storedValue;
}

AVLSearchTree::AVLSearchTree(int value)
{
	root = new BinarySearchNode(value);
}

void AVLSearchTree::insert(int num, BinarySearchNode* node)
{
	//num is less than current node, go to left child node
	if (num < (*node).getValue())
	{
		if ((*node).getLeft() != nullptr)
		{
			insert(num, (*node).getLeft());
			(*node).setLeft(balanceTree((*node).getLeft()));
			if (node == root)
				balanceTree(node);
		}
		else
		{
			BinarySearchNode* newNode = new BinarySearchNode(num);
			(*node).setLeft(newNode);

		}
	}
	//num is greater than current node, go to right child node
	else if (num > (*node).getValue())
	{
		if ((*node).getRight() != nullptr)
		{
			insert(num, (*node).getRight());
			(*node).setRight(balanceTree((*node).getRight()));
			if (node == root)
				balanceTree(node);
		}
		else
		{
			BinarySearchNode* newNode = new BinarySearchNode(num);
			(*node).setRight(newNode);
		}
	}
	//else num is already in tree, do nothing
}

BinarySearchNode* AVLSearchTree::remove(int num, BinarySearchNode* t)
{
	if (t == nullptr)
		return t; // Not Found
	if (num < (*t).getValue())
	{
		(*t).setLeft(remove(num, (*t).getLeft()));
		if ((*t).getLeft() != nullptr)
			(*t).setLeft(balanceTree((*t).getLeft()));
		if (t == root)
			balanceTree(t);
	}
	else if (num > (*t).getValue())
	{
		(*t).setRight(remove(num, (*t).getRight()));
		if ((*t).getRight() != nullptr)
			(*t).setRight(balanceTree((*t).getRight()));
		if (t == root)
			balanceTree(t);
	}
	// Two children
	else if ((*t).getLeft() != nullptr && (*t).getRight() != nullptr)
	{ 
		(*t).setValue(findMin((*(*t).getRight()).getValue()));
		(*t).setRight(remove((*t).getValue(), (*t).getRight()));
	}
	// None or One child
	else  
		t = ((*t).getLeft() != nullptr) ? (*t).getLeft() : (*t).getRight();
	return t;
}

BinarySearchNode* AVLSearchTree::balanceTree(BinarySearchNode* node)
{
	//Left subtree is more than one higher than right subtree, so imbalance is in left subtree
	if (getHeight((*node).getLeft(), 0) - getHeight((*node).getRight(), 0) > 1)
	{
		BinarySearchNode* temp = (*node).getLeft();
		//the left subtree height of temp node is greater than the right, imbalance is in the left subtree of temp requiring one rotation
		if (getHeight((*temp).getLeft(), 0) > getHeight((*temp).getRight(), 0))
			node = rotateWithLeftChild(node);
		//imbalance is in right subtree of temp requiring 2 rotations to restore balance
		else
			node = doubleWithLeftChild(node);
	}
	//Right subtree is more than one higher than left subtree, so imbalance is in right subtree
	else if (getHeight((*node).getRight(), 0) - getHeight((*node).getLeft(), 0) > 1)
	{
		BinarySearchNode* temp = (*node).getRight();
		//the right subtree height of temp node is greater than the left, imbalance is in the right subtree of temp requiring one rotation
		if (getHeight((*temp).getLeft(), 0) < getHeight((*temp).getRight(), 0))
			node = rotateWithRightChild(node);
		//imbalance is in left subtree of temp requiring 2 rotations to restore balance
		else
			node = doubleWithRightChild(node);
	}
	return node;
}

//Returns value if it is found or -1 if it is not in the tree
int AVLSearchTree::find(int value, BinarySearchNode* node)
{
	if (node == nullptr)
		return -1;
	else if (value < (*node).getValue())
		find(value, (*node).getLeft());
	else if (value >(*node).getValue())
		find(value, (*node).getRight());
	else
		return value;
}

int AVLSearchTree::findMin(BinarySearchNode current)
{
	if (current.getLeft() != nullptr)
	{
		current = *current.getLeft();
		findMin(current);
	}
	else
	{
		return current.getValue();
	}
}


int AVLSearchTree::getHeight(BinarySearchNode* node, int initialHeight)
{
	if (node == nullptr)
		return initialHeight;
	else if ((*node).getLeft() != nullptr && (*node).getRight() != nullptr)
	{
		initialHeight++;
		int temp1 = getHeight((*node).getLeft(), initialHeight);
		int temp2 = getHeight((*node).getRight(), initialHeight);
		return ((temp1 > temp2) ? temp1 : temp2);
	}
	else if ((*node).getLeft() != nullptr)
	{
		initialHeight++;
		int temp = getHeight((*node).getLeft(), initialHeight);
		return temp;
	}
	else if ((*node).getRight() != nullptr)
	{
		initialHeight++;
		int temp = getHeight((*node).getRight(), initialHeight);
		return temp;
	}
	else
	{
		initialHeight++;
		return initialHeight;
	}
}

BinarySearchNode* AVLSearchTree::getRoot()
{
	return root;
}

BinarySearchNode* AVLSearchTree::rotateWithLeftChild(BinarySearchNode* node1)
{
	BinarySearchNode* node2 = (*node1).getLeft();
	(*node1).setLeft((*node2).getRight());
	(*node2).setRight(node1);
	if (node1 == root)
		root = node2;
	return node2;
}

BinarySearchNode* AVLSearchTree::doubleWithLeftChild(BinarySearchNode* node)
{
	(*node).setLeft(rotateWithRightChild((*node).getLeft()));
	return rotateWithLeftChild(node);
}

BinarySearchNode* AVLSearchTree::rotateWithRightChild(BinarySearchNode* node1)
{
	BinarySearchNode* node2 = (*node1).getRight();
	(*node1).setRight((*node2).getLeft());
	(*node2).setLeft(node1);
	if (node1 == root)
		root = node2;
	return node2;
}

BinarySearchNode* AVLSearchTree::doubleWithRightChild(BinarySearchNode* node)
{
	(*node).setRight(rotateWithLeftChild((*node).getRight()));
	return rotateWithRightChild(node);
}
