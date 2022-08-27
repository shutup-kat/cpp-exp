#include <iostream>
#include <bits/stdc++.h>
#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;


class Edge 
{
  public:
    int source, destination, weight;
};

class Graph 
{
  public:
    int V, E;
    int nodes;
    Edge* edge;
    map<int,vector<int>> adjacencyList;
    int greatestEdgeSize = 0;
};

Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;

	graph->edge = new Edge[E];

	return graph;
}

//CRITERIA 1:



//CRITERIA 2:
class subset 
{
  public:
    int parent;
    int rank;
};

int find(subset subsets[], int i)
{
	if(subsets[i].parent != i)
    {
		subsets[i].parent = find(subsets, subsets[i].parent);
    }

	return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if(subsets[xroot].rank < subsets[yroot].rank)
    {
		subsets[xroot].parent = yroot;
    }
	else if(subsets[xroot].rank > subsets[yroot].rank)
    {
		subsets[yroot].parent = xroot;
    }
	else 
    {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

int myComp(const void* a, const void* b)
{
	Edge* a1 = (Edge*)a;
	Edge* b1 = (Edge*)b;
	return a1->weight > b1->weight;
}

int Kruskal(Graph* graph)
{
	int V = graph->V;
	Edge result[V]; 
	int e = 0;
	int i = 0;

	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

	subset* subsets = new subset[(V * sizeof(subset))];

	for(int v = 0; v < V; ++v) 
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while(e < V - 1 && i < graph->E) 
	{
		Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.source);
		int y = find(subsets, next_edge.destination);

		if(x != y) 
        {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
	}

	//cout << "Following are the edges in the constructed "
			//"MST\n";

	int minimumCost = 0;

	for(i = 0; i < e; ++i) 
	{
		cout << result[i].source << " -- " << result[i].destination << " == " << result[i].weight << endl;
		minimumCost = minimumCost + result[i].weight;
	}

	cout << "Minimum Cost Spanning Tree: " << minimumCost << endl;
  return minimumCost;
}


bool Criteria1(Graph* graph, int maxVertices, vector<int>& val1,vector<int>& val2, vector<int>& weight)
{
  map<int, bool> connectedIndicator;
  stack<int> currentStack;
  //fill out the adjacent map
  for(int i = 0; i < val1.size(); i++)
  {
      graph->adjacencyList[val1[i]].push_back(val2[i]);
      graph->adjacencyList[val2[i]].push_back(val1[i]);
      if(i < maxVertices)
      {
        connectedIndicator[i] = false;
      }
  }

    
    //start the stack with 0;
    currentStack.push(0);
    connectedIndicator[0] = true;
    while(!currentStack.empty())
    {
      int tempVal = currentStack.top();
      currentStack.pop();
      for(auto val: graph->adjacencyList[tempVal])
      {
        if(connectedIndicator[val] != true)
        {
          connectedIndicator[val] = true;
          currentStack.push(val);
        }
      }
    }

    for(auto i : connectedIndicator)
    {
      
      if (i.second == false)
        return false;
    }

  return true;
}

bool Criteria2(Graph* graph)
{
  //Eulers Map Theory
  vector<int> mapSize;
  //iterate through the adjacent map
   // option 1: range-based loops
   graph->greatestEdgeSize = 0;
   for( const auto& pair : graph->adjacencyList)
    {
      mapSize.push_back(pair.second.size());
      if(pair.second.size() > graph->greatestEdgeSize)
      {
        graph->greatestEdgeSize = pair.second.size();
      }
    }

    
    for(auto i : mapSize)
    {
      if((i%2) == 0)
      {
        return true;
      }
    }
    return false;
}

string Criteria4(Graph* graph)
{
  string returnString = "";
  for(auto pair: graph->adjacencyList)
  {
    if(pair.second.size() == graph->greatestEdgeSize)
    {
      //loop through
      if(returnString != "")
      {
        returnString += ", " + to_string(pair.first) + "<-{";
      }else{
        returnString += to_string(pair.first) + "<-{";
      }

      for(int i = 0; i < pair.second.size(); i++)
      {
        if(i != pair.second.size()-1)
        {
          cout << pair.second[i] <<endl;
          returnString+= to_string(pair.second[i]) + ',';
        }else{
          cout << pair.second[i] <<endl;
          returnString+= to_string(pair.second[i]);
        }
      }

      returnString += "}";
    }
  }

  if(returnString == "") return "None";

  return returnString;
}

//main function to test Kruskal
int main(int argc, char *argv[])
{ 
    //Get Input File
    ArgumentManager am(argc, argv);
    string inputFile = am.get("input");
    string outputFile = am.get("output");
    ifstream read_input(inputFile);
    ofstream write_output(outputFile);

    int currentInt= 0;
    int maxVertices = 0;
    read_input >> currentInt;
    maxVertices = currentInt;
    
    
    
    vector <int> currentVertice, currentVertice2, currentWeight;
  

    //Determining whether it is fully connected
    while(read_input >> currentInt)
    {
        currentVertice.push_back(currentInt);
        if(read_input >> currentInt)
        currentVertice2.push_back(currentInt);
        if(read_input >> currentInt)
        currentWeight.push_back(currentInt);

        //need to update the array linked table
    }

    
    //Perform Criteria 2
    Graph* graph = createGraph(maxVertices, currentVertice.size());
    //add values to adjacencyList
    bool criteria1 = Criteria1(graph, maxVertices, currentVertice, currentVertice2, currentWeight);
    

    if(criteria1 == false)
    {
      write_output << "1. No" << endl;
      write_output << "Bad" << endl;
      read_input.close();
      write_output.close();
      return 0;
    }else{
      write_output << "1. Yes" << endl;
    }

    
    bool criteria2 = Criteria2(graph);
    cout << "Criteria 2: " << criteria2 << endl;
    (criteria2) ? write_output << "2. Yes" << endl :  write_output << "2. No" << endl;

    for(int i= 0; i < currentVertice.size(); i++)
    {
      graph->edge[i].source = currentVertice[i];
      graph->edge[i].destination = currentVertice2[i];
      graph->edge[i].weight = currentWeight[i];
    }

    int mimimumSpan = Kruskal(graph);
    write_output << "3. " << mimimumSpan <<endl;

  string criteria4 = Criteria4(graph);
  cout << "Criteria 4: " << criteria4 << endl;
  write_output << "4. " << criteria4 <<endl;

  if(criteria1 == true && criteria2 == true && criteria4 != "None")
  {
    write_output << "Good" << endl;
  }else{
    write_output << "Fair" << endl;
  }

  read_input.close();
  write_output.close();
  return 0;
}
