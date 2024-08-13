#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <map>

using namespace std;

struct Flight
{
	string FlightId;
	int business, economy, hour, minutes = 0;
};

struct Data
{
	pair<string, string> Nation;
	Flight F;
};


Data encryptionData(string s)
{
	// erase { at first and } at end
	s.pop_back();
	s.erase(0, 1);
	
	stringstream ss (s);
	Data newData;
	
	string getNations;
	getline(ss, getNations, ':');
	getNations.erase(0, 1); // erase " "
	getNations.pop_back();
	stringstream nationStream (getNations);
	getline(nationStream, newData.Nation.first, ','); // get nation source
	getline(nationStream, newData.Nation.second); // get nation dest
	
	string flightInfo;
	getline(ss, flightInfo);
	flightInfo.erase(0, 1); // delete ' ['
	flightInfo.erase(0, 1);
	flightInfo.pop_back(); // delete ]
	
	stringstream flightStream (flightInfo);
	string flightID, business, economy, time, hour, minutes;
	
	getline(flightStream, flightID, ',');
	flightID.erase(0, 1); //delete "
	flightID.pop_back();
	newData.F.FlightId = flightID;
	
	getline(flightStream, business, ',');
	business.erase(0, 1); // delete space + "
	business.erase(0, 1);
	int spacePos = business.find(' ');
	business.erase(spacePos);
	newData.F.business = stoi(business);
	
	getline(flightStream, economy, ',');
	economy.erase(0, 1); // delete space
	economy.pop_back(); // delete "
	spacePos = economy.find(' ');
	economy.erase(spacePos);
	newData.F.economy = stoi(economy);
	
	getline(flightStream, time);
	if (time.find(',') != std::string::npos)
	{
		stringstream timeStream (time);
		getline(timeStream, hour, ',');
		hour.erase(0, 1); // delete space + "
		hour.erase(0, 1);
		spacePos = hour.find(' ');
		hour.erase(spacePos);
		newData.F.hour = stoi(hour);
		
		getline(timeStream, minutes);
		minutes.erase(0, 1); // delete space
		minutes.pop_back(); // delete "
		spacePos = minutes.find(' ');
		minutes.erase(spacePos);
		newData.F.minutes = stoi(minutes);
	}
	else
	{
		newData.F.hour = 0;
		
		stringstream timeStream (time);
		getline(timeStream, minutes);
		minutes.erase(0, 1); // delete space + "
		minutes.erase(0, 1);
		minutes.pop_back(); // delete "
		spacePos = minutes.find(' ');
		minutes.erase(spacePos);
		newData.F.minutes = stoi(minutes);
	}
	
	return newData;
	
}

vector<Data> readFile_vectorData(string fileName, map<string, int>& Vertex)
{
	vector<Data> dataList;
	fstream fs(fileName.c_str());
	if (!fs.is_open())
	{
		cout << "Can not open file.\n";
		return dataList;
	}
	
	string information;
	while (getline(fs, information))
	{
		if (information == "") break;
		
		Data newData = encryptionData(information);		
		dataList.push_back(newData);
		
		string src = newData.Nation.first;
		string des = newData.Nation.second;
		
		if (Vertex.find(src) == Vertex.end())
			Vertex[src] = Vertex.size();

		if (Vertex.find(des) == Vertex.end())
			Vertex[des] = Vertex.size();
	}
	fs.close();
	return dataList;
}

vector<vector<Flight>> getMatrix(const vector<Data>& dataList, map<string,int>& Vertex)
{
	Flight nullFlight;
	nullFlight.FlightId = "";
	vector<vector<Flight>> matrix (Vertex.size(), vector<Flight>(Vertex.size(), nullFlight));
	for (Data curData : dataList)
	{
		if (!(curData.F.hour < 10)) continue;
		int src = Vertex[curData.Nation.first];
		int des = Vertex[curData.Nation.second];
		matrix[src][des] = curData.F;	
		matrix[des][src] = curData.F;	
	}	
	return matrix;
}

void printFlight(const vector<vector<Flight>>& matrix)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << (matrix[i][j].FlightId != "") << " ";
		}
		cout << endl;
	}
}


int countDevelopedRegion(string nation1, string nation2, const vector<vector<Flight>>& matrix, map<string, int>& Vertex) // return the number of region
{
	vector<string> vertexList (Vertex.size());
	for (auto x : Vertex)
	{
		vertexList[x.second] = x.first;
	}
	
	int countRegion = 0;
	vector<int> ind {Vertex[nation1], Vertex[nation2]};
	if (matrix[ind[0]][ind[1]].FlightId == "" || matrix[ind[0]][ind[1]].FlightId == "") return 0;
	
	for (int i = 0; i < vertexList.size(); i++)
	{
		if (i == ind[0] || i == ind[1]) continue;
		if (matrix[i][ind[0]].FlightId == "" || matrix[ind[0]][i].FlightId == "") continue;
		if (matrix[i][ind[1]].FlightId == "" || matrix[ind[1]][i].FlightId == "") continue;
		ind.push_back(i);
		
		for (int j = i + 1; j < vertexList.size(); j++)
		{
			if (j == ind[0] || j == ind[1]) continue;
			if (matrix[j][ind[0]].FlightId == "" || matrix[ind[0]][j].FlightId == "") continue;
			if (matrix[j][ind[1]].FlightId == "" || matrix[ind[1]][j].FlightId == "") continue;
			if (matrix[j][ind[2]].FlightId == "" || matrix[ind[2]][j].FlightId == "") continue;
			ind.push_back(j);
			countRegion++;
			
			// print out
			for (int x = 0; x < 3; x++)
				cout << vertexList[ind[x]] << " - ";
			cout << vertexList[ind[3]] << endl;
			
			ind.pop_back();
		}
		ind.pop_back();
	}
	
	return countRegion;
}

int main()
{
	map<string, int> Vertex;
	vector<Data> dataList = readFile_vectorData("flight.txt", Vertex);
	vector<vector<Flight>> matrix = getMatrix(dataList, Vertex);
	/*int cnt = 0;
	for (Data x : dataList)
	{
		cout << ++cnt << ". " << x.Nation.first << " -> " << x.Nation.second << " | " << x.F.FlightId << ", "
		<< x.F.business << ", " << x.F.economy << ", " << x.F.hour << ", " << x.F.minutes << endl;
	}
	
	cnt = 0;
	for (auto x : Vertex)
	{
		cout << ++cnt << ". " << x.first << " - " << x.second << endl;
	}*/
	//printFlight(matrix);
	//cout << "start" << endl;
	cout << countDevelopedRegion("Myanmar", "Vietnam", matrix, Vertex);
	
	/*int cnt = 0;
	vector<string> vertexList (Vertex.size());
	for (auto x : Vertex)
	{
		vertexList[x.second] = x.first;
	}
	for (string x : vertexList) cout << ++cnt << ". " << x << endl;*/
	
	/*cout << matrix[205][205].FlightId << endl;
	for (int i = 0; i < Vertex.size(); i++)
	{
		for (int j = 0; j < Vertex.size(); j++)
		{
			if (matrix[i][j].FlightId != "" && matrix[j][i].FlightId != "") cout << i << ", " << j << endl;
		}
	}
	cout << "No country\n";*/
	//printFlight(matrix);
	return 0;
}