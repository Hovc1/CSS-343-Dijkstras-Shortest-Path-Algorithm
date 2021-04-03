/* ----------------------     myDriver.cpp     ----------------------
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


//---------------------------------------------------------------------------
// This code tests the basic functionality of the classes to perform
// Dijkstra's algorihms and depth-first search for CSS 343 program 3.
// It is not meant to exhaustively test the class. 
//
// Assumptions:
//   -- students can follow the directions to interface with this file
//   -- text files "data31.txt" and "data32.txt" are formatted as described 
//   -- Data file data3uwb provides an additional data set for part 1;
//      it must be edited, as it starts with a description how to use it
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

//p1
//constructor		x
//buildGraph		x
//insertEdge		x
//removeEdge		x
//findShortestPath	x
//displayAll		x
//display			x

//p2
//constructor		x	
//buildGraph		x
//displayGraph		x
//depthFirstSearch	x

//All the other functions are utility or helper functions
//so testing the above will also test them

int main()   // I am using the same base driver for myDriver, along with 
{			//  text 31 and 32.

	// part 1
	ifstream infile1("data31.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes
	for (;;){
		GraphM G;	// constructor
		G.buildGraph(infile1); // buildGraph
							  //  buildGraph calls insertEdge
							 //   So this is also a test of insertEdge
		if (infile1.eof())
			break;
		G.findShortestPath();

		//////// OG data
		//G.displayAll();   
		//G.display(3, 1);   
		//G.display(1, 2);
		//G.display(1, 4);

		G.displayAll();              // display shortest distance, path to cout
		G.display(5, 4);
		G.display(5, 3); // there is not a path from 5 to 3 so it ptrints ----
		
		cout << "\n/////" << endl;
		G.display(1, 5);
		G.display(3, 2);
		G.removeEdge(1, 5); // test of removeEdge, it works!
		G.display(1, 5);
		G.display(3, 2);
	}

	// a divide between part 1 and 2
	cout << "\n\n///  ///  ///  ///  ///  ///  ///  /// \n\n" << endl;
	
	// part 2 
	ifstream infile2("data32.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile2); // this is buildGraph
		if (infile2.eof())
			break;
		G.displayGraph();	// this is display graph
		G.depthFirstSearch();    // DFS
	}
	
	//cout << endl;
	return 0;
}
