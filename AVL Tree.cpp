#include <iostream>

using namespace std;

struct NODE{ 
	int key;
	NODE* left;
	NODE* right;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

int Height(NODE* node)
{
	if (node == nullptr) return 0;
	int leftHeight = Height(node->left);
	int rightHeight = Height(node->right);
	return 1 + max(leftHeight, rightHeight);
}

void leftRotate(NODE*& node)
{
	NODE* newRoot = node->right;
	node->right = newRoot->left;
	newRoot->left = node;
	node = newRoot;	
}

void rightRotate(NODE*& node)
{
	NODE* newRoot = node->left;
	node->left = newRoot->right;
	newRoot->right = node;
	node = newRoot;
}

int getBalance(NODE* node)
{
	if (node == nullptr) return 0;
	return Height(node->left) - Height(node->right);
}

void selfBalancing(NODE*& node)
{
	if (node == nullptr) return;
	
	//selfBalancing(node->left);
	//selfBalancing(node->right);
	
	int balance = getBalance(node);
	if (balance > 1)
	{
		if (getBalance(node->left) < 0) // left right unbalanced
		{
			leftRotate(node->left);
		}
		rightRotate(node);
	}
	else if (balance < -1)
	{
		if (getBalance(node->right) > 0) // right left unbalanced
		{
			rightRotate(node->right);
		}
		leftRotate(node);
	}
}

void Insert(NODE*& pRoot, int x)
{
	if (pRoot == nullptr)
	{
		pRoot = createNode(x);
		return;
	}
	
	if (x == pRoot->key) return;
	else if (x < pRoot->key) Insert(pRoot->left, x);
	else if (x > pRoot->key) Insert(pRoot-key>right, x);
	
	selfBalancing(pRoot);
}

void Remove(NODE*& pRoot, int x) // same as BST, but add selfBalancing(root) at the end of function
{
	// bonus later
}

bool isAVL(NODE* pRoot)
{
	// necessary?
}