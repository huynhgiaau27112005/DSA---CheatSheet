#include <iostream>
#include <queue>

using namespace std;

struct NODE
{
	int key;
	NODE* left;
	NODE* right;
};

// Ex 1: create node
NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

// Ex 2: insert node
void insertNode(NODE*& pRoot, int x)
{
	if (pRoot == nullptr)
	{
		pRoot = createNode(x);
		return;
	}
	if (pRoot->key == x) return;
	else if (x < pRoot->key) insertNode(pRoot->left, x);
	else if (x > pRoot->key) insertNode(pRoot->right, x);
}

// Ex 3: NLR
void NLR(NODE* pRoot)
{
	if (pRoot == nullptr) return;
	cout << pRoot->key << " ";
	NLR(pRoot->left);
	NLR(pRoot->right);
}

// Ex 4: LNR
void LNR(NODE* pRoot)
{
	if (pRoot == nullptr) return;
	LNR(pRoot->left);
	cout << pRoot->key << " ";
	LNR(pRoot->right);
}

// Ex 5: LRN
void LRN(NODE* pRoot)
{
	if (pRoot == nullptr) return;
	LNR(pRoot->left);
	LNR(pRoot->right);
	cout << pRoot->key << " ";
}

// Ex 6: level order - BFS
void LevelOrder(NODE* pRoot) {
    if (pRoot == nullptr) return;

    std::queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();
        
        std::cout << current->key << " ";
        
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

// Ex 7: count height of tree
int Height(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;
	int leftHeight = 1 + Height(pRoot->left);
	int rightHeight = 1 + Height(pRoot->right);
	return max(leftHeight, rightHeight);
}

// Ex 8: count node
int countNode(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;
	return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}

// Ex 9: sum node
int sumNode(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;
	return pRoot->key + sumNode(pRoot->left) + sumNode(pRoot->right);
}

// Ex 10: search node
NODE* searchNode(NODE* pRoot, int x)
{
	if (pRoot == nullptr) return nullptr;
	if (x == pRoot-> key) return pRoot;
	if (x < pRoot->key) return searchNode(pRoot->left, x);
	if (x > pRoot->key) return searchNode(pRoot->right, x);
}

// Ex 11.1: remove node in min right
NODE* findMinRightSuccessor(NODE* pRoot)
{
	while (pRoot->left != nullptr)
	{
		pRoot = pRoot->left;
	}
	return pRoot;
}

void removeNode_minRight(NODE*& pRoot, int x)
{
	if (pRoot == nullptr) return;
	if (pRoot->key == x)
	{
		// case 1: pRoot is leaf
		if (pRoot->left == nullptr && pRoot->right == nullptr)
		{
			delete pRoot;
			pRoot = nullptr;
			return;
		}
		
		// case 2: pRoot has one child
		else if (pRoot->left == nullptr)
		{
			NODE* pTemp = pRoot;
			pRoot = pRoot->right;
			delete pTemp;
			return;
		}
		else if (pRoot->right == nullptr)
		{
			NODE* pTemp = pRoot;
			pRoot = pRoot->left;
			delete pTemp;
			return;
		}
		
		// case 3: pRoot has 2 children
		else
		{
			NODE* pSuccessor = findMinRightSuccessor(pRoot->right);
			pRoot->key = pSuccessor->key;
			removeNode_minRight(pRoot->right, pSuccessor->key);
		}
	}
	else
	{
		if (x < pRoot->key) removeNode_minRight(pRoot->left, x);
		else if (x > pRoot->key) removeNode_minRight(pRoot->right, x);
	}
}

// Ex 11.2: remove node in max left
NODE* findMaxLeftSuccessor(NODE* pRoot)
{
	while (pRoot->right != nullptr)
	{
		pRoot = pRoot->right;
	}
	return pRoot;
}

void removeNode_maxLeft(NODE*& pRoot, int x)
{
	if (pRoot == nullptr) return;
	if (pRoot->key == x)
	{
		// case 1: pRoot is leaf
		if (pRoot->left == nullptr && pRoot->right == nullptr)
		{
			delete pRoot;
			pRoot = nullptr;
			return;
		}
		
		// case 2: pRoot has one child
		else if (pRoot->left == nullptr)
		{
			NODE* pTemp = pRoot;
			pRoot = pRoot->right;
			delete pTemp;
			return;
		}
		else if (pRoot->right == nullptr)
		{
			NODE* pTemp = pRoot;
			pRoot = pRoot->left;
			delete pTemp;
			return;
		}
		
		// case 3: pRoot has 2 children
		else
		{
			NODE* pSuccessor = findMaxLeftSuccessor(pRoot->left);
			pRoot->key = pSuccessor->key;
			removeNode_maxLeft(pRoot->left, pSuccessor->key);
		}
	}
	else
	{
		if (x < pRoot->key) removeNode_maxLeft(pRoot->left, x);
		else if (x > pRoot->key) removeNode_maxLeft(pRoot->right, x);
	}
}

// Ex 12: create tree
NODE* createTree(int a[], int n)
{
	NODE* pRoot = nullptr;
	for (int i = 0; i < n; i++)
	{
		insertNode(pRoot, a[i]);
	}
	return pRoot;
}

// Ex 13: remove tree
void removeTree(NODE*& pRoot)
{
	if (pRoot == nullptr) return;
	removeTree(pRoot->left);
	removeTree(pRoot->right);
	delete pRoot;
	pRoot = nullptr;
}

// Ex 14: find height of node (node height)
int heightNode(NODE* pRoot, int value)
{
	NODE* findNode = searchNode(pRoot, value);
	if (findNode == nullptr) return -1;
	else return Height(findNode);
}

// Ex 15: find level of node (node level)
int levelNode(NODE* pRoot, int p)
{
	if (pRoot == nullptr) return -1;
	if (pRoot->key == p) return 1;
	int level = (p < pRoot->key) ? levelNode(pRoot->left, p) : levelNode(pRoot->right, p);
	if (level == -1) return -1;
	return 1 + level;
}

// Ex 16: count leaves (number of leaf nodes)
int countLeaf(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;
	if (pRoot->left == nullptr && pRoot->right == nullptr) return 1;
	return countLeaf(pRoot->left) + countLeaf(pRoot->right);
}

// Ex 17: count the number of nodes less than the given value
int countLess(NODE* pRoot, int x)
{
	if (pRoot == nullptr) return 0;
	int countLeft = countLess(pRoot->left, x);
	int countRight = countLess(pRoot->right, x);
	int bonusCount = (pRoot->key < x) ? 1 : 0;
	return countLeft + countRight + bonusCount;
}


// Ex 18: count the number of nodes greater than the given value
//similar to ex 17

// Ex 19.1: is binary search tree -> optimized algorithm
bool isBST_helper(NODE* pRoot, int minRange = INT_MIN, int maxRange = INT_MAX)
{
	if (pRoot == nullptr) return true;
	if (pRoot->key <= minRange || pRoot->key >= maxRange)
		return false;
	else 
		return isBST_helper(pRoot->left, minRange, pRoot->key) && isBST_helper(pRoot->right, pRoot->key, maxRange);
}
bool isBST(NODE* pRoot)
{
	return isBST_helper(pRoot);
}

// Ex 19.2: is binary search tree -> do the LRN way (easier code interaction, more complexity)
/*
Scan through the Tree in LRN moves, save nodes in vector<int> values
A Binary Search Tree ensures values[i] < values[i + 1] with all values of i in range [0, values.size() - 2] 
*/

// Ex 20: is full binary search tree
bool isFullBST_helper(NODE* pRoot, int minRange = INT_MIN, int maxRange = INT_MAX)
{
    if (pRoot == nullptr) return true;
    if (pRoot->key <= minRange || pRoot->key >= maxRange) return false;

    bool isLeaf = (pRoot->left == nullptr && pRoot->right == nullptr);
    bool hasTwoChildren = (pRoot->left != nullptr && pRoot->right != nullptr);

    if (isLeaf || hasTwoChildren) 
        return isFullBST_helper(pRoot->left, minRange, pRoot->key) && isFullBST_helper(pRoot->right, pRoot->key, maxRange);
    else
        return false;
}
bool isFullBST(NODE* pRoot)
{
	return isFullBST_helper(pRoot);
}

// Others ==============================================================================================================
// Find max and min Node in general tree
int findMaxNode_GeneralTree(NODE* pRoot)
{
	if (pRoot == nullptr) return INT_MIN;
	int leftMax = findMaxNode_GeneralTree(pRoot->left);
	int rightMax = findMaxNode_GeneralTree(pRoot->right);
	int curVal = pRoot->key;
	return max(curVal, max(leftMax, rightMax)); 
}
int findMinNode_GeneralTree(NODE* pRoot)
{
	if (pRoot == nullptr) return INT_MAX;
	int leftMin = findMinNode_GeneralTree(pRoot->left);
	int rightMin = findMinNode_GeneralTree(pRoot->right);
	int curVal = pRoot->key;
	return min(curVal, min(leftMin, rightMin)); 
}


// Test ===================================================================================================================
int arr[] = {3, 5, 1, 2, 4};
int n = 5;
int main()
{
	//NODE* pRoot = createTree(arr, n);
	//NLR(pRoot);
    // Initialize tree
    NODE* root = new NODE{1, nullptr, nullptr};
    root->left = new NODE{2, nullptr, nullptr};
    root->right = new NODE{3, nullptr, nullptr};
    root->left->left = new NODE{4, nullptr, nullptr};
    root->left->right = new NODE{5, nullptr, nullptr};
    
    // Browsing through BST with BFS movement
    LevelOrder(root);
	cout << Height(root);
	
    // Deallocate
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

	return 0;
}