#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;

struct graphNode
{
	int number = 0;
	string name = "";
	int numAdjNodes = 0;
	vector< tuple<int, double> > adjNodesList;
};


fstream openFile();
vector<graphNode> createGraph();
void printGraph(vector<graphNode> graph);
double calcDist(const vector<graphNode> graph, double d[], int p[], int s, int t);
tuple<int, double> extractMin(vector<int>& list, const double dist[]);
void printPath(double d[], int p[], int s, int t);
void createMST(const vector<graphNode> graph, double d[], int p[], int s);
bool isContained(vector<int> q, int t);
void printMST(vector<graphNode> graph, double d[], int p[], int s);


int main()
{
	auto graph = createGraph();
	double d[15];
	int p[15];
	int s = 1;
	int t = 2;
	char quit = ' ';

	createMST(graph, d, p, s);

	printMST(graph, d, p, s);

	/*
	cout << "Would you like to calculate a path? (y for yes, q for no)" << endl;
	cin >> quit;

	while (quit != 'q')
	{
		cout << "Please enter a starting location (1 - 15)" << endl;
		cin >> s;
		cout << "Please enter a target location (1 - 15)" << endl;
		cin >> t;

		calcDist(graph, d, p, s, t);

		printPath(d, p, s, t);

		cout << "Would you like to calculate a path? (y for yes, q for no)" << endl;
		cin >> quit;
	}
	*/
	

	return 0;
}

fstream openFile()
{
	fstream graphData;
	graphData.open("C:\\Users\\quint\\source\\repos\\CSCE_A311_Hw4_P1\\CSCE_A311_Hw4_P1\\GraphData.txt");

	if (!graphData)
	{
		cout << "Unable to open file";
		exit(1);
	}
		
	return graphData;
}

vector<graphNode> createGraph()
{
	fstream outFile = openFile();

	int numNodes;
	outFile >> numNodes;

	vector<graphNode> graph;

	for (int i = 0; i < numNodes; ++i)
	{
		graphNode temp;
		outFile >> temp.number;
		getline(outFile, temp.name);
		getline(outFile, temp.name);
		outFile >> temp.numAdjNodes;
		for (int j = 0; j < temp.numAdjNodes; ++j)
		{
			tuple<int, double> tmp(0, 0);

			// string test;
			// outFile >> test;

			// getline(outFile, test);
			// int a = stoi(test);

			int a = 0;
			outFile >> a;

			double b = 0;
			outFile >> b;
			
			tmp = { a, b };
			temp.adjNodesList.push_back(tmp);
		}

		graph.push_back(temp);
		temp.adjNodesList.clear();
	}

	outFile.close();

	return graph;
}

void printGraph(vector<graphNode> graph)
{
	for (int i = 0; i < 15; ++i)
	{
		cout << graph[i].number << endl;
		cout << graph[i].name << endl;
		cout << graph[i].numAdjNodes << endl;
		for (int j = 0; j < graph[i].numAdjNodes; ++j)
		{
			cout << get<0>(graph[i].adjNodesList[j]) << ' ';
			cout << get<1>(graph[i].adjNodesList[j]) << endl;
		}
	}
}

void printMST(vector<graphNode> graph, double d[], int p[], int s)
{
	double total = 0;
	for (int i = 0; i < graph.size(); ++i)
	{
		cout << "Vertex " << i + 1 << " is connected to vertex " << p[i] << " weight " << d[i] << endl;
		total += d[i];
	}
	cout << "The total distance is " << total << endl;
}

double calcDist(const vector<graphNode> graph, double d[], int p[], int s, int t)
{
	fill_n(d, 15, 1000000);
	fill_n(p, 15, 0);
	vector<int> q;
	d[s - 1] = 0;

	for (int i = 0; i < 15; ++i)	// Initialize q with all vector numbers and distances
	{
		q.push_back(graph[i].number);
	}

	while (!q.empty())
	// for (int j = 0; j < 5; ++j)
	{
		tuple<int, double> u = extractMin(q, d);
		// tuple<int, int> u = { j + 1, j * 2 };

		int uIndex = get<0>(u) - 1;	// Index of current node

		for (int i = 0; i < graph[uIndex].numAdjNodes; ++i)	// Iterates through adj nodes
		{
			int vIndex = get<0>(graph[uIndex].adjNodesList[i]) - 1;	// Index of current adj node
			double b = get<1>(graph[uIndex].adjNodesList[i]) + d[uIndex];	// Weight of adj node path + distance of current node

			if (d[vIndex] > b)
			{
				d[vIndex] = b;	// Set distance
				p[vIndex] = uIndex + 1;	// Set parent
			}
		}
	}

	return d[t - 1];	// Distance to target from source
}

tuple<int, double> extractMin(vector<int>& list,const double dist[])
{
	int mindex = 0;	// Initialize min to distance of first vector
	double min = dist[list[mindex] - 1];

	for (int i = 1; i < list.size(); ++i)
	{
		if (dist[(list[i] - 1)] < min)	// If distance of vector is less than distance of current min
		{
			mindex = i;
			min = dist[mindex];
		}
	}

	tuple<int, double> temp = { list[mindex], min };

	list.erase(list.begin() + mindex);
	return temp;
}

void printPath(double d[], int p[], int s, int t)
{
	vector<int> path;

	path.insert(path.begin(), t);

	int i = t - 1;
	while (p[i] != s)	// While the parent of the current node is not the starting node
	{
		path.insert(path.begin(), p[i]);
		i = p[i] - 1;
	}

	path.insert(path.begin(), p[i]);

	cout << "The shortest path from Site " << s << " to Site " << t << " is as follows : " << endl;
	
	for (int i = 0; i < path.size() - 1; ++i)
	{
		cout << "Site " << path[i] << " --> ";
	}
	cout << "Site " << path[path.size() - 1] << endl;

	cout << "The total distance is " << d[t - 1];
}

void createMST(const vector<graphNode> graph, double d[], int p[], int s)
{
	fill_n(d, 15, 1000000);
	fill_n(p, 15, 0);
	vector<int> q;
	d[s - 1] = 0;

	for (int i = 0; i < 15; ++i)	// Initialize q with all vector numbers
	{
		q.push_back(graph[i].number);
	}


	while (!q.empty())
	{
		tuple<int, double> u = extractMin(q, d);

		int uIndex = get<0>(u) - 1;	// Index of current node

		for (int i = 0; i < graph[uIndex].numAdjNodes; ++i)	// Iterates through adj nodes
		{
			int vIndex = get<0>(graph[uIndex].adjNodesList[i]) - 1;	// Index of current adj node
			double b = get<1>(graph[uIndex].adjNodesList[i]);	// Weight of adj node path

			if ( isContained(q, graph[vIndex].number) && (b < d[vIndex]))
			{
				d[vIndex] = b;	// Set distance
				p[vIndex] = uIndex + 1;	// Set parent
			}
		}
	}
}

bool isContained(vector<int> q, int t)
{
	for (int i = 0; i < q.size(); ++i)
	{
		if (q[i] == t)
			return true;
	}
	return false;
}