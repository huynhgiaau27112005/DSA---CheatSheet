#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/* STRUCT */
struct Pokemon
{
	string Name, Type1, Type2; 
	vector<string> Abilities;
	string Tier;
	int HP, Attack, Defense, SpecialAttack, SpecialDefense, Speed; 
	vector<string> NextEvolution; // fix: string -> vector<string>
	vector<string> Moves;
};

struct NODE
{
	Pokemon data;
	NODE* pNext;
	NODE* pPrev;
};

struct List
{
	NODE* pHead;
	NODE* pTail;
};

/* SAVE FILE INTO VECTOR<POKEMON> */
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
			tmp.erase(0, 2);
			tmp.pop_back();
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

vector<Pokemon> readFile_vector(string fileName)
{
	fstream f;
	f.open(fileName.c_str());
	if (!f.is_open()) return {};
	
	string tmp_name = "";
	string tmp_types;
	string tmp_abilities;
	string tmp_tier;
	int tmp_hp;
	int tmp_attack;
	int tmp_defense;
	int tmp_speAttack;
	int tmp_speDefense;
	int tmp_speed;
	string tmp_nextEvolution;
	string tmp_moves;
	
	Pokemon tmp;
	vector<Pokemon> ans;
	
	string firstLine;
	getline(f, firstLine);
	
	while (!f.eof())
	{
		getline(f, tmp_name, ',');
		if (tmp_name == "") break;
		getline(f, tmp_types, ',');
		getline(f, tmp_abilities, ',');
		getline(f, tmp_tier, ',');
		f >> tmp_hp;
		f.ignore();
		f >> tmp_attack;
		f.ignore();
		f >> tmp_defense;
		f.ignore();
		f >> tmp_speAttack;
		f.ignore();
		f >> tmp_speDefense;
		f.ignore();
		f >> tmp_speed;
		f.ignore();
		getline(f, tmp_nextEvolution, ',');
		//cout << tmp_types << ", " << tmp_nextEvolution << endl;
		//cout << tmp_types << endl;
		getline(f, tmp_moves, '\n');
		
		tmp.Name = tmp_name;
		vector<string> vectorType = getInfos(tmp_types);
		tmp.Type1 = vectorType[0];
		if (vectorType.size() == 1) tmp.Type2 = "";
		else tmp.Type2 = vectorType[1];
		tmp.Abilities = getInfos(tmp_abilities);
		tmp.Tier = tmp_tier;
		tmp.HP = tmp_hp;
		tmp.Attack = tmp_attack;
		tmp.Defense = tmp_defense;
		tmp.SpecialAttack = tmp_speAttack;
		tmp.SpecialDefense = tmp_speDefense;
		tmp.Speed = tmp_speed;
		tmp.NextEvolution = getInfos(tmp_nextEvolution);
		tmp.Moves = getInfos(tmp_moves);
		
		ans.push_back(tmp);
	}
	f.close();
	return ans;
}

/* SAVE POKEMONS TO DOUBLY LINKED LIST */
void addTail(List& list, Pokemon pokemon)
{
	if (list.pHead == nullptr)
	{
		list.pHead = new NODE;
		list.pHead->data = pokemon;
		list.pHead->pPrev = nullptr;
		list.pHead->pNext = nullptr;
		list.pTail = list.pHead;
		return;
	}
	NODE* newNode = new NODE;
	newNode->data = pokemon;
	newNode->pNext = nullptr;
	newNode->pPrev = list.pTail;
	list.pTail->pNext = newNode;
	list.pTail = newNode;
}

List readFile_linkedlist(vector<Pokemon> pokemons)
{
	List list;
	list.pHead = nullptr;
	list.pTail = nullptr;
	for (Pokemon p : pokemons)
	{
		addTail(list, p);
	}
	return list;
}

/* SAVE POKEMON TO STRUCT*** */
Pokemon*** readFile_struct(vector<Pokemon> pokemons, int m, int n, int p)
{
	int index = 0;
	Pokemon*** ans = new Pokemon**[m];
	for (int i = 0; i < m; i++)
	{
		ans[i] = new Pokemon*[n];
		for (int j = 0; j < n; j++)
		{
			ans[i][j] = new Pokemon[p];
			for (int k = 0; k < p; k++)
			{
				if (index == pokemons.size()) return ans;
				ans[i][j][k] = pokemons[index++];
			}
		}
	}
	return ans;
}


// without vector
Pokemon*** readFile_struct_novector(string fileName, int m, int n, int p)
{
	fstream f;
	f.open(fileName.c_str());
	if (!f.is_open()) 
	{
		return nullptr;
		/*Pokemon*** errorPtr = new Pokemon**[1];
		errorPtr[0] = new Pokemon*[1];
		errorPtr[0][0] = new Pokemon[1];
		return errorPtr;*/	
	}
	
	string tmp_name = "";
	string tmp_types;
	string tmp_abilities;
	string tmp_tier;
	int tmp_hp;
	int tmp_attack;
	int tmp_defense;
	int tmp_speAttack;
	int tmp_speDefense;
	int tmp_speed;
	string tmp_nextEvolution;
	string tmp_moves;
	
	Pokemon tmp;
	
	string firstLine;
	getline(f, firstLine);
	
	Pokemon* pokemons = new Pokemon[m * n * p + 1];
	int index = 0;
	while (!f.eof())
	{
		if (index == m * n * p) break;
		getline(f, tmp_name, ',');
		if (tmp_name == "") break;
		getline(f, tmp_types, ',');
		getline(f, tmp_abilities, ',');
		getline(f, tmp_tier, ',');
		f >> tmp_hp;
		f.ignore();
		f >> tmp_attack;
		f.ignore();
		f >> tmp_defense;
		f.ignore();
		f >> tmp_speAttack;
		f.ignore();
		f >> tmp_speDefense;
		f.ignore();
		f >> tmp_speed;
		f.ignore();
		getline(f, tmp_nextEvolution, ',');
		//cout << tmp_types << ", " << tmp_nextEvolution << endl;
		//cout << tmp_types << endl;
		getline(f, tmp_moves, '\n');
		
		tmp.Name = tmp_name;
		vector<string> vectorType = getInfos(tmp_types);
		tmp.Type1 = vectorType[0];
		if (vectorType.size() == 1) tmp.Type2 = "";
		else tmp.Type2 = vectorType[1];
		tmp.Abilities = getInfos(tmp_abilities);
		tmp.Tier = tmp_tier;
		tmp.HP = tmp_hp;
		tmp.Attack = tmp_attack;
		tmp.Defense = tmp_defense;
		tmp.SpecialAttack = tmp_speAttack;
		tmp.SpecialDefense = tmp_speDefense;
		tmp.Speed = tmp_speed;
		tmp.NextEvolution = getInfos(tmp_nextEvolution);
		tmp.Moves = getInfos(tmp_moves);
		
		pokemons[index++] = tmp;
		}
	f.close();
	
	Pokemon*** ans = new Pokemon**[m];
	index = 0;
	for (int i = 0; i < m; i++)
	{
		ans[i] = new Pokemon*[n];
		for (int j = 0; j < n; j++)
		{
			ans[i][j] = new Pokemon[p];
			for (int k = 0; k < p; k++)
			{
				ans[i][j][k] = pokemons[index++];
			}
		}
	}
	
	return ans;
}

void printPokemon(Pokemon p)
{
	cout << p.Name << ", " << p.Type1 << ", " << p.Type2 << ", " << p.Abilities.back()
			<< ", " << p.Tier << ", " << p.HP << ", " << p.Attack << ", " << p.Defense
			<< ", " << p.SpecialAttack << ", " << p.SpecialDefense << ", " << p.Speed
			<< ", " << ((p.NextEvolution.size() != 0) ? p.NextEvolution.back() : "") << ", " << p.Moves.back() << endl;
}

/* SORTING POKEMONS */
bool comparator(Pokemon a, Pokemon b)
{
	return a.Name > b.Name;	
}

void sortEx(vector<Pokemon>& pokemons)
{
	sort(pokemons.begin(), pokemons.end(), comparator);
}

/* DELETE 2 NODES WITH CONDITION...*/
bool comparatorB(NODE* a, NODE* b)
{
	return (a->data.Name[0] == b->data.Name[0]);	
}

void removeNodeEx(List& list)
{
	if (list.pHead == nullptr) return;
	for (NODE* pCur = list.pHead->pNext; pCur != nullptr; )
	{
		if (comparatorB(pCur->pPrev, pCur))
		{
			if (pCur->pNext == nullptr)
			{
				NODE* tmp = pCur;
				pCur = pCur->pPrev;
				pCur->pNext = nullptr;
				list.pTail = pCur;
				delete tmp;
				continue;
			}
			NODE* pTmp = pCur;
			pCur->pPrev->pNext = pCur->pNext;
			pCur->pNext->pPrev = pCur->pPrev;
			pCur = pCur->pNext;
			delete pTmp;
		}
		else
		{
			pCur = pCur->pNext;
		}		
	}
}

/* FIND SUB MATRIX */
// Find submatrix with exact ** size in *** 
bool boolForSubMatrix(Pokemon p)
{
	return p.Name[0] == 'B'; 
}

Pokemon** submatrix_Ex1(Pokemon*** pokemons, int m, int n, int p)
{
	int maxVal = 0, maxID = 0;
	for (int i = 0; i < m; i++)
	{
		int curVal = 0;
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				if (boolForSubMatrix(pokemons[i][j][k])) curVal++;
			}
		}
		if (curVal > maxVal)
		{
			maxVal = curVal;
			maxID = i;
		}
	}
	
	// Init
	Pokemon** ans = new Pokemon*[n];
	for (int j = 0; j < n; j++)
	{
		ans[j] = new Pokemon[p];
		for (int k = 0; k < p; k++)
		{
			ans[j][k] = pokemons[maxID][j][k];
		}
	}
	return ans;
}


int main()
{
	vector<Pokemon> pokemons = readFile_vector("pokemon_temp.csv");
	int cnt = 1;

	/*for (Pokemon p : pokemons)
	{
		cout << cnt++ << ". ";
		printPokemon(p);
	}*/
	
	/*List list = readFile_linkedlist(pokemons);
	removeNodeEx(list);
	for (NODE* cur = list.pHead; cur != nullptr; cur = cur->pNext)
	{
		cout << cnt++ << ". ";
		printPokemon(cur->data);
	}*/
	
	int m = 5, n = 5, p = 5;
	//Pokemon*** ans = readFile_struct(pokemons, m, n, p);
	Pokemon*** ans = readFile_struct_novector("pokemon_temp.csv", m, n, p);
	//Pokemon** submatrix = submatrix_Ex1(ans, m, n, p);
	/*for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < p; k++)
		{
			cout << cnt++ << ". ";
			printPokemon(submatrix[j][k]);
		}
	}*/
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				cout << cnt++ << ". ";
				printPokemon(ans[i][j][k]);
			}
		}
	}
	
	return 0;
}

// fix: there are more than 1 next evolutions -> string or vector<string>?