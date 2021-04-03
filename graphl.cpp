/* ----------------------     graphl.cpp     ----------------------
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

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>	// needed
#include "graphl.h"	// needed


// ------------------------     GraphL     --------------------------
// Description:     This is the default constructor 
// precondition:    x
// postcondition:   It makes an empty array of graph nodes
// ------------------------------------------------------------------
GraphL::GraphL()
{
	size = 0;
	for (int i = 0; i < MAX_NODE_DATA; i++)
	{
		arrayGraphNodes[i].edgeHead = NULL;
		arrayGraphNodes[i].visited = false;
		arrayGraphNodes[i].data = NULL;
	}
}


// ------------------------     ~GraphL     -------------------------
// Description:     Destructor
// precondition:    You need a GraphL to deallocate
// postcondition:   This frees up memory
// ------------------------------------------------------------------
GraphL::~GraphL()
{
	makeEmpty();
}	


//----------------------     buildGraph     ------------------------
//Description:		This reades the txt file and places it in a 
//					string, which is placed in a node in the graph
//precondition:		You need ifstream to read a text file with data
//postcondition:	It makes a graph
//------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile2) 
{
	int from, to;
	string s;
	infile2 >> size;
	getline(infile2, s);
	stringstream line(s);
	for (int i = 1; i <= size; ++i)
	{
		getline(infile2, s);
		NodeData* cur = new NodeData(s);
		arrayGraphNodes[i].data = cur;
	}
	while (true)
	{
		if (infile2.eof()) 
		{	
			return;	
		}
		infile2 >> from >> to;
		if (from == 0)
		{
			break;
		}
		if (arrayGraphNodes[from].edgeHead == NULL)
		{
			EdgeNode* EN = new EdgeNode;
			EN->adjGraphNode = to;
			arrayGraphNodes[from].edgeHead = EN;
			arrayGraphNodes[from].edgeHead->nextEdge = NULL;
		}
		else
		{
			EdgeNode* EN = new EdgeNode;
			EN->adjGraphNode = to;
			EN->nextEdge = arrayGraphNodes[from].edgeHead;
			arrayGraphNodes[from].edgeHead = EN; 
		}
	}
}// end build graph


// ---------------------     displayGraph     -----------------------
// Description:     This prints out a graph that shows what edges
//					each node is attached to
// precondition:    You need arrayGraphNode to contain data
// postcondition:   Prints out the data from the graph
// ------------------------------------------------------------------
void GraphL::displayGraph() const 
{
	EdgeNode* cur;
	cout << "Graph: " << endl;
	for (int i = 1; i <= size; i++)
	{
		if (arrayGraphNodes[i].edgeHead != NULL)
		{
			cout << "Node " << i << setw(32) << *arrayGraphNodes[i].data << endl;
			cur = arrayGraphNodes[i].edgeHead;
			while (cur != NULL)
			{
				cout << setw(10) << "edge " << i << " ";
				cout << cur->adjGraphNode << endl;
				cur = cur->nextEdge;
			}
		}
	}// end for loop
	cout << endl;
}// end display graph



// -------------------     depthFirstSearch     ---------------------
// Description:     Performs a DFS 
// precondition:    You need arrayGraphNodes to contain data
// postcondition:   Prints out the DFS order
// ------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";
	for (int i = 1; i <= size; i++)
	{
		if (!arrayGraphNodes[i].visited)
		{
			depthFirstSearch(i);
		}
	}
	cout << endl;
}


// -------------------     depthFirstSearch     ---------------------
// Description:     This is essientially a recursive DFS helper function
// precondition:    You need arrayGraphNodes to contain data
// postcondition:   Prints our the DFS order
// ------------------------------------------------------------------
void GraphL::depthFirstSearch(int i)
{
	cout << setw(3) << i;
	arrayGraphNodes[i].visited = true;
	EdgeNode* cur = arrayGraphNodes[i].edgeHead;

	while (cur != NULL)
	{
		if (!arrayGraphNodes[cur->adjGraphNode].visited)
		{
			depthFirstSearch(cur->adjGraphNode);
		}
		cur = cur->nextEdge;
	}
}


// -----------------------     makeEmpty     ------------------------
// Description:     Deletes the GraphNodes
// precondition:    You need GraphNodes to delete
// postcondition:   You delete the GraphNodes
// ------------------------------------------------------------------
void GraphL::makeEmpty()
{
	for (int i = 1; i <= size; i++)
	{
		if (arrayGraphNodes[i].edgeHead != NULL)
		{
			makeEmpty(arrayGraphNodes[i].edgeHead);
		}
		arrayGraphNodes[i].edgeHead = NULL;
	}
}


// -----------------------     makeEmpty     ------------------------
// Description:     This is a recursive helper function
// precondition:    You need GraphNodes to delete 
// postcondition:   You delete the GraphNodes
// ------------------------------------------------------------------
void GraphL::makeEmpty(EdgeNode* cur)
{
	if (cur->nextEdge != NULL)
	{
		makeEmpty(cur->nextEdge);
		delete cur;
		cur = NULL;
	}
}
