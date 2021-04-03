#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include <limits>  
//#include <climits>
#include "nodedata.h"
using namespace std;

const int MAX_NODES = 101; 

class GraphM
{
public:
   GraphM();   
   ~GraphM();    
   
   void buildGraph(ifstream&);   
   void findShortestPath();  
   bool insertEdge(int, int, int);  
   bool removeEdge(int, int);     

   void displayAll() const;   
   void display(int, int) const;  
   void displayPath(int, int) const;  
   void displayData(int, int) const;  

private:
   struct TableType // from canvas
   {
      bool visited;         //whether node has been visited or not
      int dist;             //shortest distance from source known so far
      int path;             //previous node in path of min dist      
   };
   
   NodeData data[MAX_NODES];          //string description for graph nodes
   int C[MAX_NODES][MAX_NODES];       //Cost array, aka adjacency matrix
   int size = 0;                          //number of nodes in the graph
   TableType T[MAX_NODES][MAX_NODES]; //stores visited, distance, and path
   
   int smallestNode(int);  
   void removeHelper();
};
#endif