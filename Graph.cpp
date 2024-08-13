#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

vector<vector<int>> MatrixToList(const vector<vector<int>>& matrix)
{
	int elementCount = matrix.size();
	vector<vector<int>> list (elementCount);
	for (int i = 0; i < elementCount; i++)
	{
		//vector<int> tmp;
		for (int j = 0; j < elementCount; j++)
		{
			if (matrix[i][j] == 1)
			{
				list[i].push_back(j);
			}
		}
	}
	return list;
}

void printList(const vector<vector<int>>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < list[i].size(); j++)
		{
			cout << list[i][j] << " ";	
		}	
		cout << endl;
	}
}

vector<vector<int>> ListToMatrix(const vector<vector<int>>& list)
{
	int elementCount = list.size();
	vector<vector<int>> matrix(elementCount, vector<int>(elementCount, 0)); 
	
	// generate matrix
	for (int i = 0; i < elementCount; i++)
	{
		for (int j : list[i])
		{
			matrix[i][j] = 1;
		}
	}
	
	return matrix;
}

void printMatrix(const vector<vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";	
		}	
		cout << endl;
	}
}

bool isDirectedM(const vector<vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] != matrix[j][i])
				return true;
		}	
	}	
	return false;
}

void countVertexAndEdgesM(const vector<vector<int>>& matrix, int& countVertex, int& countEdges)
{
	countVertex = matrix.size();
	countEdges = 0;
	for (int i = 0; i < countVertex; i++)
	{
		for (int j = 0; j < countVertex; j++)
		{
			if (matrix[i][j] == 1) countEdges++;
		}
	}
	if (!isDirectedM(matrix)) countEdges /= 2;
}

vector<int> BFS(const vector<vector<int>>& matrix, int start) // start is the index
{
	int numOfElements = matrix.size();
	vector<bool> visited (numOfElements, false);
	vector<int> bfs;
	queue<int> q;
	
	q.push(start);
	visited[start] = true;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		bfs.push_back(cur);
		
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[cur][j] == 1 && !visited[j])
			{
				q.push(j);
				visited[j] = true;
			}
		}
	}
	
	return bfs;
}

vector<int> DFS(const vector<vector<int>>& matrix, int start) // start is the index
{
	int numOfElements = matrix.size();
	vector<bool> visited (numOfElements, false);
	vector<int> dfs;
	stack<int> s;
	
	s.push(start);
	visited[start] = true;
	while (!s.empty())
	{
		int cur = s.top();
		s.pop();
		dfs.push_back(cur);
		
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[cur][j] == 1 && !visited[j])
			{
				s.push(j);
				visited[j] = true;
			}
		}
	}
	
	return dfs;
}

bool hasCycle_fromAPoint(const vector<vector<int>>& matrix, int start)
{
	int numOfElements = matrix.size();
	vector<bool> visited (numOfElements, false);
	stack<int> s;
	vector<int> parent (numOfElements, -1);
	
	s.push(start);
	visited[start] = true;
	
	while (!s.empty())
	{
		int cur = s.top();
		s.pop();
		
		for (int j = 0; j < matrix.size(); j++)
		{
		if (matrix[cur][j] == 1)
            {
                if (visited[j] && j != parent[cur])
                {
                    return true;
                }
                else if (!visited[j])
                {
                    s.push(j);
                    visited[j] = true;
                    parent[j] = cur;
                }
            }
		}
	}
	
	return false;
}

bool hasCycle_arrayOfPoints(const vector<vector<int>>& matrix, const vector<int>& element)
{
	map<int, bool> visited;
	map<int, int> parent;
	for (int x : element)
	{
		visited[x] = false;
		parent[x] = -1;
	}
	stack<int> s;
	
	s.push(element[0]);
	visited[element[0]] = true;
	
	while (!s.empty())
	{
		int i = s.top();
		s.pop();
		
		for (int j : element)
		{
			if (matrix[i][j] == 1)
			{
				if (visited[j] && j != parent[i])
					return true;
				else if (!visited[j])
				{
					s.push(j);
					visited[j] = true;
					parent[j] = i;
				}
			}
		}
	}
	
	return false;
}

vector<int> degreeVerticeM(int n, vector<vector<int>> matrix)
{
	vector<int> result;
	if (isDirectedM(matrix))
	{
		int in_degree = 0;
		int out_degree = 0;
		for (int i = 0; i < matrix[n].size(); i++)
		{
			if(matrix[n][i] == 1) out_degree++;
			if (matrix[i][n] == 1) in_degree++;
		}
		result.push_back(in_degree);
		result.push_back(out_degree);
	}
	else
	{
	
		int cnt = 0;
		for (int i = 0; i < matrix[n].size(); i++)
		{
			if (matrix[n][i] == 1) cnt++;
		}
		result.push_back(cnt);
	}
	return result;
}

vector<int> isolatedElementM(const vector<vector<int>>& matrix)
{
	vector<int> list;
	
	for (int i = 0; i < matrix.size(); i++)
	{
		bool isConnected = true;
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] == 1 || matrix[j][i] == 1)
			{
				isConnected = false;
				break;
			}
		}
		if (!isConnected) list.push_back(i);
	}
	
	return list;
}



struct Edge
{
	int from;
	int to;
	int cost;	
};
	
bool comparator(Edge a, Edge b)
{
	if (a.cost != b.cost)
		return a.cost < b.cost;
	else
		return a.from < b.from;
}

vector<vector<int>> minimumSpanningTree_kruskal(const vector<vector<int>>& matrix)
{
	
	// check if the tree is connected
	vector<Edge> edgeMap;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] != 0)
			{
				Edge newEdge;
				newEdge.from = i;
				newEdge.to = j;
				newEdge.cost = matrix[i][j];
				edgeMap.push_back(newEdge);
			}
		}
	}
	
	sort(edgeMap.begin(), edgeMap.end(), comparator);
	
	vector<bool> visited (matrix.size(), false);
	vector<vector<int>> minimumST (matrix.size(), vector<int>(matrix.size(), 0));
	
	visited[edgeMap[0].from] = true;
	for (Edge cur : edgeMap)
	{
		if (!visited[cur.to])
		{
			minimumST[cur.from][cur.to] = cur.cost;
			visited[cur.to] = true;
		}
	}
	
	return minimumST;
}



vector<vector<int>> minimumSpanningTree_prim(const vector<vector<int>>& matrix)
{
	vector<vector<int>> minimumST (matrix.size(), vector<int>(matrix.size(), 0));
	vector<bool> visited (matrix.size(), false);
	vector<int> list;
	
	int cur = 0;
	visited[0] = true;
	list.push_back(0);
	
	for (int move = 0; move < matrix.size() - 1; move++)
	{
		int minVal = INT_MAX;
		int minSrc;
		int minDes;
		
		// find next minimum move
		for (int i : list)
		{
			for (int j = 0; j < matrix.size(); j++)
			{
				if (!visited[j] && matrix[i][j] != 0 && matrix[i][j] < minVal)
				{
					minVal = matrix[i][j];
					minSrc = i;
					minDes = j;
				}		
			}
		}
		
		visited[minDes] = true;
		minimumST[minSrc][minDes] = minVal;
		minimumST[minDes][minSrc] = minVal;
		list.push_back(minDes);
	}
	
	return minimumST;
}

int main()
{
		
}