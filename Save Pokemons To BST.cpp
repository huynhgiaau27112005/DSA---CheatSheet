#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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
	return x.Name == root.Name;
}

bool movetoRightCondition(pokemon root, pokemon x)
{
	return x.Name > root.Name;
}

bool movetoLeftCondition(pokemon root, pokemon x)
{
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


// save Pokemon to Binary Search Tree
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
	if (!f.is_open()) return nullptr;
	
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

int main()
{
	
}
