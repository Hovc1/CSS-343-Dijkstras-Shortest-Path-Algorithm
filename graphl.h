#ifndef GRAPHL_H
#define GRAPHL_H
#include <iostream>
#include "nodedata.h"
#include "graphm.h"
using namespace std;

int const MAX_NODE_DATA = 101;

// the struct was coppied and pasted from canvas
struct EdgeNode;      // forward reference for the compiler
struct GraphNode 
{						// structs used for simplicity, use classes if desired
	EdgeNode* edgeHead; // head of the list of edges
	NodeData* data;     // data information about each node
	bool visited;               
};

struct EdgeNode 
{
	int adjGraphNode;  // subscript of the adjacent graph node
	EdgeNode* nextEdge;
};	

class GraphL
{
	public:
		GraphL();
		~GraphL();

		void buildGraph(ifstream&);	
		void displayGraph() const;
		void depthFirstSearch();
		void depthFirstSearch(int);	

	private:  
		NodeData data[MAX_NODE_DATA];  
		GraphNode arrayGraphNodes[MAX_NODE_DATA]; 
		int size;   

       void makeEmpty();
       void makeEmpty(EdgeNode*);
};
#endif
