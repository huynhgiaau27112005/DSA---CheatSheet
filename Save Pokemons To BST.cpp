#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

/* STRUCT */
struct pokemon
{
	string Name;
	string Type1, Type2;
	vector<string> Abi;
	int HP, Atk, Def, SpAtk, SpDef, Spd;
	string nextEv;
	vector<string> Moves;
};

struct NODE
{
	pokemon key;
	NODE* left;
	NODE* right;
};
void printPokemon(pokemon p);

// helper functions============================================================================
// create node
NODE* createNode(pokemon data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

// insert node
bool stopMoveCondition(pokemon root, pokemon x)
{
	return (x.HP == root.HP) && (x.Name == root.Name);
}

bool movetoRightCondition(pokemon root, pokemon x)
{
	if (x.HP != root.HP)
		return x.HP > root.HP;
	else
		return x.Name > root.Name;
}

bool movetoLeftCondition(pokemon root, pokemon x)
{
	if (x.HP != root.HP)
		return x.HP < root.HP;
	else
		return x.Name < root.Name;
}

void insertNode(NODE*& pRoot, pokemon x)
{
	if (pRoot == nullptr)
	{
		pRoot = createNode(x);
		return;
	}
	if (stopMoveCondition(pRoot->key, x)) return;
	else if (movetoLeftCondition(pRoot->key, x)) insertNode(pRoot->left, x);
	else if (movetoRightCondition(pRoot->key, x)) insertNode(pRoot->right, x);
}


// save Pokemon to Binary Search Tree ====================================================================================
vector<string> getInfos(string s)
{
	if (s == "[]") return {};
	if (s[0] == '\"')
	{
		s.erase(0, 1);
		s.pop_back();
	}
	if (s[0] == '[')
	{
		s.erase(0, 1);
		s.pop_back();
	}
	stringstream ss (s);
	vector<string> info;
	string tmp;
	while (ss.good())
	{
		getline(ss, tmp, ';');
		if (tmp[0] == ' ') tmp.erase(0, 1);
		if (tmp[0] == '\"')
		{
			tmp.erase(0, 1);
			tmp.pop_back();
		}
		else if (tmp[0] == '\'')
		{
			tmp.erase(0, 1);
			tmp.pop_back();
		}
		info.push_back(tmp);
	}
	return info;
}

NODE* saveFileToBST(string fileName)
{
	fstream f;
	f.open(fileName.c_str());
	if (!f.is_open())
	{
		cout << "Can not open file";
		return nullptr;
	}
	
	string tmp_name = "";
	string tmp_types;
	string tmp_Abi;
	int tmp_hp;
	int tmp_Atk;
	int tmp_Def;
	int tmp_speAtk;
	int tmp_speDef;
	int tmp_Spd;
	string tmp_nextEvolution;
	string tmp_moves;
	
	pokemon tmp;
	//vector<pokemon> ans;
	NODE* pRoot = nullptr;
	
	string firstLine;
	getline(f, firstLine);
	
	int index = 0;
	while (!f.eof())
	{
		getline(f, tmp_name, ',');
		if (tmp_name == "") break;
		getline(f, tmp_types, ',');
		getline(f, tmp_Abi, ',');
		f >> tmp_hp;
		f.ignore();
		f >> tmp_Atk;
		f.ignore();
		f >> tmp_Def;
		f.ignore();
		f >> tmp_speAtk;
		f.ignore();
		f >> tmp_speDef;
		f.ignore();
		f >> tmp_Spd;
		f.ignore();
		getline(f, tmp_nextEvolution, ',');
		getline(f, tmp_moves, '\n');
		
		tmp.Name = tmp_name;
		vector<string> vectorType = getInfos(tmp_types);
		tmp.Type1 = vectorType[0];
		if (vectorType.size() == 1) tmp.Type2 = "";
		else tmp.Type2 = vectorType[1];
		tmp.Abi = getInfos(tmp_Abi);
		tmp.HP = tmp_hp;
		tmp.Atk = tmp_Atk;
		tmp.Def = tmp_Def;
		tmp.SpAtk = tmp_speAtk;
		tmp.SpDef = tmp_speDef;
		tmp.Spd = tmp_Spd;
		tmp.nextEv = tmp_nextEvolution;
		tmp.Moves = getInfos(tmp_moves);
		
		insertNode(pRoot, tmp);
	}
	f.close();
	
	return pRoot;
}

// Work with BST function=============================================================================================
// remove node (delete node) - remove all nodes with given condition
NODE* findMinRightSuccessor(NODE* pRoot)
{
	while (pRoot->left != nullptr)
	{
		pRoot = pRoot->left;
	}
	return pRoot;
}

void removeNode_minRight(NODE*& pRoot, pokemon x)
{
	if (pRoot == nullptr) return;
	if (stopMoveCondition(pRoot->key, x)) // change this condition
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
		if (movetoLeftCondition(pRoot->key, x)) removeNode_minRight(pRoot->left, x);
		else if (movetoRightCondition(pRoot->key, x)) removeNode_minRight(pRoot->right, x);
	}
}

bool shouldbeRemoved(pokemon x)
{
	return x.SpAtk > 90;
}

NODE* searchNodeToDelete_LNR(NODE* pRoot)
{
	if (pRoot == nullptr) return nullptr;
	if (shouldbeRemoved(pRoot->key)) return pRoot;
	
	NODE* findLeft = searchNodeToDelete_LNR(pRoot->left);
	if (findLeft != nullptr) return findLeft;
	NODE* findRight = searchNodeToDelete_LNR(pRoot->right);
	if (findRight != nullptr) return findRight;
	
	return nullptr;
}

void deleteNode_searchLNR(NODE*& pRoot)
{
	NODE* pDelete = nullptr;
	while ((pDelete = searchNodeToDelete_LNR(pRoot)) != nullptr)
	{
		//cout << "Delete: "; printPokemon(pDelete->key);
		removeNode_minRight(pRoot, pDelete->key);
	}
}

// find highest subtree (in height) that ensures given condition
bool nodeCondition(pokemon x)
{
	return x.HP > 50;
}
bool checkSubtree(NODE* pRoot)
{
	if (pRoot == nullptr) return false;

    std::queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();
        
        if (!nodeCondition(current->key)) return false;
        
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    return true;
}
int Height(NODE* pRoot)
{
	if (pRoot == nullptr) return 0;
	int leftHeight = 1 + Height(pRoot->left);
	int rightHeight = 1 + Height(pRoot->right);
	return max(leftHeight, rightHeight);
}
NODE* findSubtree(NODE* pRoot) // Use BFS browsing
{
	if (pRoot == nullptr) return nullptr;

    std::queue<NODE*> q;
    q.push(pRoot);
	
	int highestHeight = INT_MIN;
	NODE* highestSubtree = nullptr;
    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();
        
        if (checkSubtree(current))
        {
        	int currentHeight = Height(current);
        	if (currentHeight > highestHeight)
        	{
        		highestSubtree = current;
        		highestHeight = currentHeight;
			}
		}
        
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    return highestSubtree;
}

// TEST ==============================================================================================================
int stt = 1;
void printPokemon(pokemon p)
{
	cout << stt++ << ". ";
	cout << p.SpAtk << " - " << p.HP << " - " << p.Name << " | ";
	cout << p.Name << ", " << p.Type1 << ", " << p.Type2 << ", " << p.Abi.back()
			<< ", " << p.HP << ", " << p.Atk << ", " << p.Def
			<< ", " << p.SpAtk << ", " << p.SpDef << ", " << p.Spd
			<< ", " << p.nextEv << ", " << p.Moves.back() << endl;
}

void LNR(NODE* pRoot)
{
	if (pRoot == nullptr) return;
	LNR(pRoot->left);
	printPokemon(pRoot->key);
	LNR(pRoot->right);
}

int main()
{
	NODE* pRoot = saveFileToBST("data.csv");
	//deleteNode_searchLNR(pRoot);
	NODE* ans = findSubtree(pRoot);
	LNR(ans);
	return 0;
}
