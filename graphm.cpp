/* ----------------------     graphm.cpp     ----------------------
// Christopher Hovsepian CSS 343
// Started 23 July 2020
// Last Modified: 1 August 2020
//
// add data31.txt and data32.txt
// g++ -std=c++11 graphl.h graphl.cpp graphm.h graphm.cpp nodedata.h nodedata.cpp myDriver.cpp    
// g++ -std=c++11 graphl.h graphl.cpp graphm.h graphm.cpp nodedata.h nodedata.cpp driver.cpp     
//
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
// ------------------------------------------------------------------*/

#include "graphm.h"
#include <iomanip>

// ------------------------     GraphM     -------------------------
// Description:     This makes an empty adjacency matrix
// precondition:    x
// postcondition:   You have an empty adjacency matrix
// ------------------------------------------------------------------
GraphM::GraphM()
{
	size = 0;
	for (int i = 1; i < MAX_NODES; i++)
	{
		for (int j = 1; j < MAX_NODES; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}
	}// end double for loop
}


// ------------------------     ~GraphM     -------------------------
// Description:     Destructor
// precondition:    x
// postcondition:   You free up memory
// ------------------------------------------------------------------
GraphM::~GraphM() {}


// ----------------------     buildGraph     ------------------------
// Description:     This reades data from the ifstream (a text file) 
//					and places it in the 2D array matrix
// precondition:    You need the file to read
// postcondition:   makes the adjacency matrix
// ------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile) 
{
	infile >> size;
	string s = "";
	getline(infile, s);
	int from, to, dist;

	if (size >= INT_MAX)
	{
		size = 0;
		return;
	}
	if (infile.eof())
	{
		return;
	}
	for (int i = 1; i <= size; ++i) 
	{
		data[i].setData(infile);
	}
	while (true)
	{
		infile >> from >> to >> dist;

		if (from == 0 && to == 0)
		{
			return;
		}
		insertEdge(from, to, dist);
	}
}


// ----------------------     insertEdge     ------------------------
// Description:     This is a helper function for buildGraph by	
//					setting the distance between 2 nodes
// precondition:    You need a matrix with values to check
// postcondition:   returnes true if it sets a distance
// ------------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int dist) 
{
	if (size == 0)
	{
		return false;
	}

	if (from > size || to > size)
	{
		return false;
	}

	if (from < 1 || to < 1 || dist < 1)
	{
		return false;
	}

	if (from == to)
	{
		return false;
	}
	C[from][to] = dist;
	return true;
}


// -------------------     findShortestPath     ---------------------
// Description:     Dijkstra's algorithm finds the shortest path from 
//					node to node
// precondition:    You need a matrix to search	
// postcondition:   You find the distance and shortest path from
//					each node to the other nodes
// ------------------------------------------------------------------
void GraphM::findShortestPath() 
{
	int v = 1;

	for (int source = 1; source <= size; source++) 
	{
		T[source][source].dist = 0;
		
		for (int i = 1; i<= size; i++) 
		{
			v = smallestNode(source);
			T[source][v].visited = true;
			if (v != 0)
			{
				for (int w = 1; w <= size; w++)
				{
					if (C[v][w] != INT_MAX && T[source][w].visited == false)
					{
						if (T[source][v].dist + C[v][w] < T[source][w].dist)
						{
							T[source][w].path = v;
						}
						T[source][w].dist = min(T[source][w].dist, (T[source][v].dist + C[v][w]));
					}
				}//for
			}
		}//for
	}//for
}// end find shortest path



// ---------------------     smallestNode     -----------------------
// Description:     This is a findShortestPath helper function
// precondition:    You need a matrix to search
// postcondition:   returnes the smallest number / distance to 
//					help findShortestPath
// ------------------------------------------------------------------
int GraphM::smallestNode(int i) 
{
	int min = INT_MAX;
	int small = 0;

	for (int j = 1; j <= size; j++)
	{
		if (T[i][j].dist != INT_MAX && T[i][j].visited == false)
		{
			if (T[i][j].dist < min)
			{
				 min = T[i][j].dist;
				 if (min != INT_MAX)
				 {
					 small = j;
				 }
			}
		}
	}
	if (min == INT_MAX)
	{
		return 0;
	}
	return small;
}


// ----------------------     removeEdge     ------------------------
// Description:     This removes an edge
// precondition:    You need an edge to remove
// postcondition:   Returnes true if the edge is removed
// ------------------------------------------------------------------
bool GraphM::removeEdge(int from, int to) 
{
	insertEdge(from, to, INT_MAX);
	removeHelper();
	return true;
}


// ---------------------     removeHelper     -----------------------
// Description:     This is a helper function for ermoveEdge
// precondition:    You need an edge to remove
// postcondition:   Clears out the data
// ------------------------------------------------------------------
void GraphM::removeHelper()
{
	for (int i = 0; i < MAX_NODES; i++)
	{
		for (int j = 0; j < MAX_NODES; j++)
		{
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}
	}
}



// ----------------------     displayAll     ------------------------
// Description:     This prints out the name of the nodes, which other
//					nodes they are attached to, the distance, and path.
// precondition:    You need a matrix to display
// postcondition:   It prints out the graph
// ------------------------------------------------------------------
void GraphM::displayAll() const 
{
	cout << "Description" << setw(20) << "From_node" << setw(11)
	<< "To_node" << setw(14) << "Dijstra's" << setw(10) << "Path\n";

	for (int from = 1; from <= size; from++)
	{
		cout << data[from] << endl;
		for (int to = 1; to <= size; to++)
		{
			if (T[from][to].dist != 0)
			{ 
				cout << setw(27) << from << setw(11) << to;
				if (T[from][to].dist == INT_MAX)
				{
					cout << setw(15) << "----\n"; // this means a path
				}								 //  does not exist
				else
				{
					cout << setw(13) << T[from][to].dist << setw(10);
					displayPath(from, to);
					cout << endl;
				}
			}
		}//end for
	}//end for
}


// ------------------------     display     -------------------------
// Description:     This is a displayAll helper function
// precondition:    Needs the from and to passed to it
// postcondition:   Displays data from the node
// ------------------------------------------------------------------
void GraphM::display(int from, int to) const 
{
	if ((from > size || from < 0) || (to > size || to < 0))
	{
		cout << setw(10) << from << setw(10) << to << setw(10)
		<< "---\n";
		return;
	}
	cout << setw(10) << from << setw(10) << to;

	if (T[from][to].dist != INT_MAX)
	{
		cout << setw(10) << T[from][to].dist << setw(10);
        displayPath(from, to); 
        cout << endl;
        displayData(from, to);
	}
	else
	{
		cout << setw(10) << "---" << endl;
	}
	cout << endl;
}


// ----------------------     displayPath     -----------------------
// Description:     This is a recursive helper function for display
// precondition:    Needs from and to pased to it, so it know where
//					to go
// postcondition:   Walk along the path (edge) printing the path values
// ------------------------------------------------------------------
void GraphM::displayPath(int from, int to) const
{
	if (T[from][to].path == INT_MAX)
	{
		return;
	}
	if (from == to)
	{
		cout << to << " ";
		return;
	}
	int keeper = to;
	displayPath(from, to = T[from][to].path);
	cout << keeper << " ";
}


// ----------------------     displayData     -----------------------
// Description:     This is a recursive helper function for display
// precondition:    Needs from and to pased to it, so it know where
//					to go
// postcondition:   Walk along the path (edge) printing the data values
// ------------------------------------------------------------------
void GraphM::displayData(int from, int to) const
{
	if (to != 0)
	{
		displayData(from, T[from][to].path);
		cout << data[to] << endl;
	}
}
