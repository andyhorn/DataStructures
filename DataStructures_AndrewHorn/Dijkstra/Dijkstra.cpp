#include "Graph.h"
#include "Hashmap.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stack;
using std::vector;

static const int TABLE_SIZE = 21;
static const string FILENAME = "C:\\Users\\andyj\\Google Drive\\School\\OIT\\2017-2018\\Winter\\CST211 - Data Structures\\Labs\\Lab_04.txt";

int ReadFile(ifstream &file, Graph<string, string> &graph, HashMap<string, int> &hash, const string filename);
int Dijkstra(HashMap<string, int> &hash, vector<Vertex<string, string>> &nodes, vector<Edge<string, string>> &distance, vector<Vertex<string, string>> &predecessor);
int GetDirections(HashMap<string, int> &hash, vector<Vertex<string, string>> &nodes, vector<Edge<string, string>> &distance, vector<Vertex<string, string>>& predecessor, string start, string end);
bool Contains(vector<Edge<string, string>> &vector, string data);
bool Contains(vector<Vertex<string, string>> &vector, string data);
// "C:\\Users\\andyj\\Google Drive\\School\\OIT\\2017-2018\\Winter\\CST211 - Data Structures\\Labs\\Lab_04.txt"

int main()
{
	auto getIndex = [](string value)
	{
		int sum = 0;
		for (char c : value)
			sum += c;
		return sum % TABLE_SIZE;
	};

	// run Dijkstra's algorithm
	try
	{
		bool run = true;
		while (run)
		{
			vector<Edge<string, string>> distance;
			vector<Vertex<string, string>> predecessor;
			vector<Vertex<string, string>> nodes;
			stack<string> directions;
			HashMap<string, int> hash(TABLE_SIZE, getIndex);
			Graph<string, string> graph;
			ifstream file;
			string from, to;
			int numNodes = 0;
			numNodes = ReadFile(file, graph, hash, FILENAME); // read file data into graph
			nodes.resize(numNodes);
			distance.resize(numNodes);
			predecessor.resize(numNodes);

			auto addToVector = [&nodes, &hash](Vertex<string, string> vertex)
			{
				nodes[hash[vertex.GetData()]] = vertex;
			};
			graph.DepthFirst(addToVector);

			run = Dijkstra(hash, nodes, distance, predecessor);
		}
	}
	catch (Exception &e)
	{
		cout << e << endl;
	}
	return 0;
}

int GetDirections(HashMap<string, int> &hash, vector<Vertex<string, string>> &nodes, vector<Edge<string, string>> &distance, vector<Vertex<string, string>>& predecessor, string start, string end)
{
	string cur;
	stack<string> directions;
	char runAgain = '\0';
	cur = end;

	try
	{
		while (cur != start)
		{
			directions.push(cur);
			directions.push(distance[hash[cur]].GetData());
			try
			{
				cur = predecessor[hash[cur]].GetData();
			}
			catch (Exception &e)
			{
				cout << e << endl;
				cout << "From: " << start << endl
					<< "To: " << end << endl;
				throw Exception("Invalid parameter.");
			}
		}
		cout << "Directions from " << start << " to " << end << ":" << endl;
		cout << "Start: " << start << endl;
		while (!directions.empty())
		{
			cout << "Take " << directions.top();
			directions.pop();
			cout << " to " << directions.top() << endl;
			directions.pop();
		}
		cout << "Total distance: " << distance[hash[end]].GetWeight() << "mi." << endl;
	}
	catch (Exception &e)
	{
		cout << e << endl;
	}

	cout << "\n\nRun again? Y/N: ";
	cin >> runAgain;
	cin.ignore(100, '\n');
	if (tolower(runAgain) == 'y')
		return 1;
	else
		return 0;
}

int ReadFile(ifstream &file, Graph<string, string> &graph, HashMap<string, int> &hash, const string filename)
{
	size_t startNodes = 0, endNodes = 0;
	file.open(filename);
	if (file.is_open())
	{
		cout << "Reading file..." << endl;
		while (!file.eof())
		{
			char startNode[256] = { '\0' }, endNode[256] = { '\0' }, path[256] = { '\0' };
			int mileage = 0;
			file.getline(startNode, 256, ',');
			file.getline(endNode, 256, ',');
			file.getline(path, 256, ',');
			file >> mileage;
			file.ignore(256, '\n');

			try
			{
				graph.InsertVertex(startNode); // non-unique rejection
				hash.Insert(startNode, static_cast<int>(startNodes + endNodes)); // attempt to insert node
				startNodes++; // if a unique location (not rejected), increment index counter
			}
			catch (Exception) {}
			try
			{
				graph.InsertVertex(endNode); // non-unique rejection
				hash.Insert(endNode, static_cast<int>(startNodes + endNodes));
				endNodes++;
			}
			catch (Exception) {}
			try
			{
				graph.InsertEdge(startNode, endNode, path, mileage);
			}
			catch (Exception &e)
			{
				cout << e << endl;
			}
		}
		file.close();
		cout << "Success! File read." << endl;
	}
	else
		cout << "Unable to open file." << endl;

	return static_cast<int>(startNodes + endNodes); // should be total count of unique Vertex
}

int Dijkstra(HashMap<string, int> &hash, vector<Vertex<string, string>> &nodes, vector<Edge<string, string>> &distance, vector<Vertex<string, string>>& predecessor)
{
	bool finished = false;
	string start, end, cur;
	cout << "From: ";
	std::getline(cin, start, '\n');
	if (!Contains(nodes, start))
	{
		cout << "Place not present." << endl;
		return 1;
	}
	cout << "Destination: ";
	std::getline(cin, end, '\n');
	if (!Contains(nodes, end))
	{
		cout << "Place not present." << endl;
		return 1;
	}
	cur = start;

	try
	{
		// Since distance from starting vertex to itself is 0, update element in distance array
		//distance[hash[start]] = Edge<string, string>(start, nullptr, 0);
		while (!finished)
		{
			// Using the starting vertex and current vertex, update the distance array to adjacent vertices
			for (Vertex<string, string> &vertex : nodes)
			{
				if (vertex.GetData() == cur && !vertex.GetProcessed())
				{
					auto edge = vertex.GetEdges();
					while (edge != vertex.GetEdgesEnd())
					{
						bool update = false;
						if (distance[hash[edge->GetDestination()->GetData()]].GetWeight() == 0)
							update = true;
						else if ((edge->GetWeight() + distance[hash[cur]].GetWeight())
							< distance[hash[edge->GetDestination()->GetData()]].GetWeight())
							update = true;
						if (update && edge->GetDestination()->GetData() != vertex.GetData())
						{
							finished = false;
							distance[hash[edge->GetDestination()->GetData()]] = *edge;
							distance[hash[edge->GetDestination()->GetData()]].SetWeight(
								distance[hash[cur]].GetWeight() + edge->GetWeight());
							predecessor[hash[edge->GetDestination()->GetData()]] = vertex;
						}
						edge++;
					}

					vertex.SetProcessed(true);
					size_t tempDist = 0;
					string nextVertex = vertex.GetData();
					for (Edge<string, string> edge : distance)
					{
						if (edge.GetDestination() != nullptr)
							if ((tempDist == 0 || edge.GetWeight() != 0) && !(nodes[hash[edge.GetDestination()->GetData()]].GetProcessed()))
							{
								tempDist = edge.GetWeight();
								nextVertex = edge.GetDestination()->GetData();
							}
					}
					if (cur == "")
						throw Exception("Error: Next vertex null.");
					else if (cur != nextVertex)
						cur = nextVertex;
					else
						finished = true;
				}
			}
		}
	}
	catch (Exception &e)
	{
		cout << e << endl;
		return 1;
	}
	return GetDirections(hash, nodes, distance, predecessor, start, end);
}

bool Contains(vector<Vertex<string, string>> &vector, string data)
{
	bool contains = false;
	for (Vertex<string, string> vertex : vector)
		if (vertex.GetData() == data)
			contains = true;
	return contains;
}

bool Contains(vector<Edge<string, string>> &vector, string data)
{
	bool contains = false;
	for (Edge<string, string> edge : vector)
		if (edge.GetData() == data)
			contains = true;
	return contains;
}