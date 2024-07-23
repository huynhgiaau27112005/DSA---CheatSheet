#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct pokemon
{
	string Name;
	string Type1, Type2;
	vector<string> Abi;
	int HP, Atk, Def, SpAtk, SpDef, Spd;
	string nextEv;
	vector<string> Moves;
};


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

vector<pokemon> readFile_vector(string fileName)
{
	fstream f;
	f.open(fileName.c_str());
	if (!f.is_open()) return {};
	
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
	vector<pokemon> ans;
	
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
		//cout << tmp_types << ", " << tmp_nextEvolution << endl;
		//cout << tmp_types << endl;
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
		
		ans.push_back(tmp);
	}
	f.close();
	
	return ans;
}

pokemon*** readFile(string filename, int m, int n, int p)
{
	vector<pokemon> pokemons = readFile_vector(filename);
	int cnt = pokemons.size();
	int index = cnt - m * n * p;
	pokemon*** ans = new pokemon**[m];
	for (int i = 0; i < m; i++)
	{
		ans[i] = new pokemon*[n];
		for (int j = 0; j < n; j++)
		{
			ans[i][j] = new pokemon[p];
			for (int k = 0; k < p; k++)
			{
				ans[i][j][k] = pokemons[index++];
			}
		}
	}
	
	return ans;
}

void print3D(pokemon*** P, int m, int n, int p)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				cout << P[i][j][k].Name << " - " << P[i][j][k].Type1;
				if (P[i][j][k].Type2 != "") cout << " - " << P[i][j][k].Type2;
				cout << endl;
			}
		}
	}
}

void printPokemon(pokemon p)
{
	cout << p.Name << ", " << p.Type1 << ", " << p.Type2 << ", " << p.Abi.back()
			<< ", " << p.HP << ", " << p.Atk << ", " << p.Def
			<< ", " << p.SpAtk << ", " << p.SpDef << ", " << p.Spd
			<< ", " << p.nextEv << ", " << p.Moves.back() << endl;
}

struct pokeNode
{
	pokemon data;
	pokeNode* pNext;
	pokeNode* pPrev;	
};

struct pokeList
{
	pokeNode* head;
	pokeNode* tail;
};

void addTail(pokeList& list, pokemon pokemon)
{
	if (list.head == nullptr)
	{
		list.head = new pokeNode;
		list.head->data = pokemon;
		list.head->pPrev = nullptr;
		list.head->pNext = nullptr;
		list.tail = list.head;
		return;
	}
	pokeNode* newNode = new pokeNode;
	newNode->data = pokemon;
	newNode->pNext = nullptr;
	newNode->pPrev = list.tail;
	list.tail->pNext = newNode;
	list.tail = newNode;
}

pokeList readFile(string filename)
{
	pokeList list;
	list.head = nullptr;
	list.tail = nullptr;
	vector<pokemon> getData = readFile_vector(filename);
	for (pokemon p : getData)
	{
		if (p.Type2 != "") addTail(list, p);
	}
	return list;
}

pokeList test_strange1(string filename)
{
	pokeList list;
	list.head = nullptr;
	list.tail = nullptr;
	vector<pokemon> getData = readFile_vector(filename);
	int cnt = 0;
	for (pokemon p : getData)
	{
		if (cnt++ < 1) addTail(list, p);
		if (p.nextEv == "[]") addTail(list, p);
	}
	return list;
}

void printList(pokeList P)
{
	for (pokeNode* pCur = P.head; pCur != nullptr; pCur = pCur->pNext)
	{
		cout << pCur->data.Name << " - " << pCur->data.Type1 << " - " << pCur->data.Type2 << " - " << pCur->data.nextEv << endl;
	}
}

bool comparator(pokemon a, pokemon b)
{
	if (a.nextEv == "[]" && b.nextEv == "[]") return true;
	else return false;
}

void removeP(pokeList &P)
{
	if (P.head == nullptr) return;
	for (pokeNode* pCur = P.head->pNext; pCur != nullptr; )
	{
		if (P.head == P.tail) break;
		if (comparator(pCur->pPrev->data, pCur->data))
		{
			if (pCur->pNext == nullptr)
			{
				pokeNode* tmp = pCur;
				pCur = pCur->pPrev;
				pCur->pNext = nullptr;
				P.tail = pCur;
				delete tmp;
				continue;
			}
			pokeNode* pTmp = pCur;
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

pokemon*** speedUp(pokemon*** P, int& size, int m, int n, int p, int t)
{
	int cnt = 0;
	vector<int> index;
	for (int i = 0; i < m; i++)
	{
		int sum = 0;
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				sum += P[i][j][k].Spd;
			}
		}
		if (sum > t)
		{
			cnt++;
			index.push_back(i);
		}
	}
	cout << cnt << endl;
	pokemon*** ans = new pokemon**[cnt];
	for (int i = 0; i < cnt; i++)
	{
		ans[i] = new pokemon*[n];
		for (int j = 0; j < n; j++)
		{
			ans[i][j] = new pokemon[p];
			for (int k = 0; k < p; k++)
			{
				ans[i][j][k] = P[index[i]][j][k];
			}
		}
	}
	size = cnt;
	return ans;
}

int main()
{
	//vector<pokemon> pokemons = readFile_vector("pokemon.csv");
	int cnt = 1;
	
	int m = 5, n = 5, p = 5;
	pokemon*** pokemons = readFile("pokemon.csv", m, n, p);
	/*for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				cout << cnt++ << ". ";
				printPokemon(ans[i][j][k]);
			}
		}
	}*/
	print3D(pokemons, m, n, p);
	
	///pokeList list = readFile("pokemon.csv");
	//removeP(list);
	//printList(list);
	
	//int size;
	//pokemon*** ans = speedUp(pokemons, size, m, n, p, 1500);
	//print3D(ans, size, n, p);
	//cout << size << endl;
	return 0;
}
