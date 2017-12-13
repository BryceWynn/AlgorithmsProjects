// function for making forest from graph
//contains given initilialize function to create graph and nodes for forest from file
//uses uoptomized additions to select edges for trees in forest
//also  includes print file to give edge names and total weight
//BW 11/21/16
//addmsfprim function to create shortest forest possible, 12/12/16 BW

#include "stdafx.h"
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include<boost/graph/adjacency_list.hpp> 

#include "Except.h"
#include "Matrix.h"
#include "Heap.h"



#define LargeValue 99999999 

using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;
typedef Graph::edge_iterator edge_iterator;
typedef Graph::vertex_iterator vertex_iterator;
typedef Graph::adjacency_iterator adj_iterator;


struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

int numberOfNodes = 0;

//stripped down version of initialize graph to create the nodes of the graph but not the edges
void initializeForest(Graph &g) {
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < numberOfNodes; i++)
	{
		v = add_vertex(g);
	}
}

void initializeGraph(Graph &g, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> numberOfNodes;
	//	fin >> startId >> endId; not used due to slightly different graph input files in comparison to project 5
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < numberOfNodes; i++)
	{
		v = add_vertex(g);
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}

// sets all node weights to max value so algorithms will work
void setNodeUnvisited(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // find vertices range
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for every vertex
		g[*vItr].visited = false; // set weight to w
		g[*vItr].marked = false;
	}
}

// set all edges to unamrked so that the used edges can be transferred to the new graph
void setEdgeUnmarked(Graph &g) {
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); // edge itterator range
	for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
		g[*eItr].marked = false;
		g[*eItr].visited = false;
	}
}

//checks to see if the graph is connected by performing a DFS and flagging anything it reaches as visited. If all nodes are visited, returns true;
bool isConnected(Graph &g) {
	setNodeUnvisited(g);// set nodes unvisited for baseline

						// solves using depth search and a stack to see if all  nodes are reachable
	Graph::vertex_descriptor vd = 0, vdPast1, vdFinal, vdDebug;  // create vertex descriptors
	g[vd].pred = vd; // set past node to last node (node 0 sets to self)
	g[vd].visited = true;// set visited true for node 0
	vdPast1 = vd; // needed for first set
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // create adjacency itterator
	vItrRange = adjacent_vertices(vd, g); // set to node 0
	stack <Graph::vertex_descriptor> vdStack; // make stack for solving
	vdStack.push(vd); // add first term to stack
	while (vdStack.size() != 0) { // while stack isnt empty
		g[vd].pred = vdPast1; // set predecessor
		vItrRange = adjacent_vertices(vd, g); // set adjacency itterator to new node
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {// iterate over all adjacent nodes
			vdDebug = *vItr; // used for readability only
			if (g[vdDebug].visited != true) { // if it hasnt been visited
				g[vdDebug].visited = true; // set node to visited
				vdStack.push(vdDebug); // add to stack
			}
		}
		vdPast1 = vd; // once all edges itterated, set past to current node
		vd = vdStack.top(); // select next node in stack
		vdStack.pop(); //  pop selected node;
	}

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrFin = vertices(g); // find vertices range
	for (Graph::vertex_iterator vItr = vItrFin.first; vItr != vItrFin.second; ++vItr) { // for every vertex
		if (g[*vItr].visited == false) return false; // if any vertex wasnt visited, returned false
	}
	return true; // if all nodes were visited, return true

}

void setNodeWeights(Graph &g, int w) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // find vertices range
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for every vertex
		g[*vItr].weight = w; // set weight to w
	}
}


void msfPrim(Graph &g, Graph &sf) {
	heapV<Graph::vertex_descriptor, Graph> pointHeap;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // find vertices range
	setNodeWeights(g, LargeValue);
	setEdgeUnmarked(g);
	vector<Graph::vertex_descriptor> heapBuilder; // make vector of all the nodes for making heapV
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for every vertex
		g[*vItr].visited = false;
		g[*vItr].marked = false;
		heapBuilder.push_back(*vItr); // add vertice to vector
	}
	Graph::vertex_descriptor v = 0;
	pointHeap.initializeMinHeap(heapBuilder, g); // creat minHeap heapV
	int index = pointHeap.getIndex(v);//get index for term 1
	pointHeap.minHeapDecreaseKey(index, g); // make sure term 1 is first term
	Graph::vertex_descriptor logicV, targetNode, sourceNode, temp;
	logicV = pointHeap.extractMinHeapMinimum(g); // set logicV to start node and remove start node from heap
	g[logicV].pred = logicV; // set start node to self;
	g[logicV].marked = true;
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> eItrRange; // create this instance of edge itterator
	pair<Graph::edge_descriptor, bool> edgeFinder;
	Graph::vertex_descriptor dataTypeFix;
	while (pointHeap.size() != 0) { // while nodes remain in heap
		eItrRange = adjacent_vertices(logicV, g); // set edge itterator
		for (auto eItr = eItrRange.first; eItr != eItrRange.second; eItr++) { // for all edges at this node
			edgeFinder = edge(logicV, *eItr, g);
			if ((g[*eItr].weight > g[edgeFinder.first].weight) && (g[*eItr].marked == false)) {
				g[*eItr].weight = g[edgeFinder.first].weight;
				g[*eItr].pred = logicV;
				targetNode = *eItr;
				index = pointHeap.getIndex(targetNode); // get index for altered node
				pointHeap.minHeapDecreaseKey(index, g); // minHeapify altered node
			}
		}
		logicV = pointHeap.extractMinHeapMinimum(g); // find newest minimum value
		g[logicV].marked = true;
		edgeFinder = edge(logicV, g[logicV].pred, g);
		if (edgeFinder.second == true) g[edgeFinder.first].marked = true;
	}
	pair<Graph::edge_iterator, Graph::edge_iterator> edgeItrRange = edges(g); // edge itterator range
	Graph::edge_descriptor currentEdge; // edge for finding vertex descriptors
	EdgeProperties e; // used to assign weights for new graph
	for (auto edgeItr = edgeItrRange.first; edgeItr != edgeItrRange.second; ++edgeItr) { // itterate over every edge
		if (g[*edgeItr].marked == true) { // if the edge is marked for addition
			sourceNode = source(*edgeItr, g); // find the source node
			targetNode = target(*edgeItr, g); // find the target node
			e.weight = g[*edgeItr].weight; // find the weight
			add_edge(sourceNode, targetNode, e, sf); // produce the edge in the new graph
		}
	}

}

// performs a DFS and returns true if any no
bool isCyclic(Graph &g) {
	// checks using a DFS on each node, if a visited node is found, returns true

	Graph::vertex_descriptor vd = 0, vdPast1, vdFinal, vdDebug;  // create vertex descriptors
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrFin = vertices(g); // find vertices range
	for (Graph::vertex_iterator vItr = vItrFin.first; vItr != vItrFin.second; ++vItr) { // for every vertex
		setNodeUnvisited(g);
		g[*vItr].visited = true;// set visited true for node 0
		vd = *vItr;
		vdPast1 = vd; // needed for first set
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // create adjacency itterator
		vItrRange = adjacent_vertices(vd, g); // set to node 0
		stack <Graph::vertex_descriptor> vdStack; // make stack for solving
		vdStack.push(vd); // add first term to stack
		while (vdStack.size() != 0) { // while stack isnt empty
			g[vd].pred = vdPast1; // set predecessor
			vItrRange = adjacent_vertices(vd, g); // set adjacency itterator to new node
			for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {// iterate over all adjacent nodes
				vdDebug = *vItr; // used for readability only
				if (g[vdDebug].visited != true) { // if it hasnt been visited
					g[vdDebug].visited = true; // set node to visited
					vdStack.push(vdDebug); // add to stack
				}
				else return true; // if a visited node is found return true
			}
			vdPast1 = vd; // once all edges itterated, set past to current node
			vd = vdStack.top(); // select next node in stack
			vdStack.pop(); //  pop selected node;
		}
	}
	return false; // if no visited nodes could be found, return false;

}

// uses a DFS to create a spanning forest, and then adds the marked edges of the forest only to the second graph
void findSpanningForest(Graph &g, Graph &forest) {
	setNodeUnvisited(g); // set all ndoes to unvisited
	setEdgeUnmarked(g); // demark all edges in g
						// solves using depth search and a stack to see if all  nodes are reachable

	Graph::vertex_descriptor vd = 0, vdPast1, vdFinal, vdDebug;  // create vertex descriptors
	g[vd].pred = vd; // set past node to last node (node 0 sets to self)
	vdPast1 = vd; // needed for first set
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // create adjacency itterator
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrItr = vertices(g); // find vertices range

																				// for loop used to ensure vertices that are not on the 1st tree are still included, as it checks to ensure every node gets marked in some way
	for (Graph::vertex_iterator vItr = vItrItr.first; vItr != vItrItr.second; ++vItr) { // for every vertex	
		if (g[*vItr].visited == false) {  // if vertex was already used in a past itteration, skip this itteration
			g[*vItr].visited = true;
			vd = *vItr;
			vItrRange = adjacent_vertices(vd, g); // set to node 0
			stack <Graph::vertex_descriptor> vdStack; // make stack for solving
			vdStack.push(vd); // add first term to stack
			pair<Graph::edge_descriptor, bool> edgeFinder;
			while (vdStack.size() != 0) { // while stack isnt empty
				g[vd].pred = vdPast1; // set predecessor
				vItrRange = adjacent_vertices(vd, g); // set adjacency itterator to new node
				for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {// iterate over all adjacent nodes
					vdDebug = *vItr; // used for readability only
					if (g[vdDebug].visited != true) { // if it hasnt been visited
						g[vdDebug].visited = true; // set node to visited
						vdStack.push(vdDebug); // add to stack
						edgeFinder = edge(vd, *vItr, g); //  finds the edge between the two selected nodes
						g[edgeFinder.first].marked = true; // sets marked as true so that it will be added to the forest at the end 
					}
				}
				vdPast1 = vd; // once all edges itterated, set past to current node
				vd = vdStack.top(); // select next node in stack
				vdStack.pop(); //  pop selected node;
			}
		}
	}
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); // edge itterator range
	Graph::vertex_descriptor targetNode, sourceNode;// vertex nodes
	Graph::edge_descriptor currentEdge; // edge for finding vertex descriptors
	EdgeProperties e; // used to assign weights for new graph
	for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
		if (g[*eItr].marked == true) { // if the edge is marked for addition
			sourceNode = source(*eItr, g); // find the source node
			targetNode = target(*eItr, g); // find the target node
			e.weight = g[*eItr].weight; // find the weight
			add_edge(sourceNode, targetNode, e, forest); // produce the edge in the new graph
		}
	}
}

int main()
{
	try
	{
		//set up file input
		ifstream fin;

		// Read the maze from the file.
		string fileName;
		cout << "please input desired file to open" << endl;
		cout << "filename should be graphX.txt where X is the maze number" << endl;
		cin >> fileName;
		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}
		Graph testGraph, forest, shortForest;
		initializeGraph(testGraph, fin);
		fin.close();
		fin.open(fileName.c_str());
		initializeForest(forest); // must be done after graph
		fin.close();
		bool connected, cyclic;
		connected = isConnected(testGraph); // test graph for connectivity
		cyclic = isCyclic(testGraph); // test for cyclicity
		if (connected) cout << "Starting graph is connected" << endl;
		else cout << " starting graph is not connected" << endl;
		if (cyclic) cout << "Starting graph is cyclic" << endl << endl;
		else cout << " starting graph is not cyclic" << endl << endl;
		findSpanningForest(testGraph, forest); // finds and creates the forest and  places it in forest
		connected = isConnected(forest); // redo tests for forest
		cyclic = isCyclic(forest);
		if (connected) cout << "non-short Forest is connected" << endl;
		else cout << "non-short Forest is not connected" << endl;
		if (cyclic) cout << "non-short Forest is cyclic, somethign went wrong" << endl << endl;
		else cout << "non-short Forest is not cyclic" << endl << endl;
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(forest); // edge itterator range
		int iterator = 0;
		int weightSum = 0;
		for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
			cout << "edge " << iterator << " connects nodes "; // print out edge number
			cout << source(*eItr, forest) << "," << target(*eItr, forest) << endl;// print out which nodes it connects
			weightSum += forest[*eItr].weight; // add weight to sum
			iterator++; // increment edge number
		}
		cout << "sum of all weights for non short forest is " << weightSum << endl << endl; // print edge weights
		msfPrim(testGraph, shortForest);
		connected = isConnected(shortForest); // redo tests for forest
		cyclic = isCyclic(shortForest);
		if (connected) cout << "short Forest is connected" << endl;
		else cout << "short Forest is not connected" << endl;
		if (cyclic) cout << "short Forest is cyclic, somethign went wrong" << endl << endl;
		else cout << "short Forest is not cyclic" << endl << endl;
		eItrRange = edges(shortForest); // edge itterator range
		iterator = 0;
		weightSum = 0;
		for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
			cout << "edge " << iterator << " connects nodes "; // print out edge number
			cout << source(*eItr, shortForest) << "," << target(*eItr, shortForest) << endl;// print out which nodes it connects
			weightSum += shortForest[*eItr].weight; // add weight to sum
			iterator++; // increment edge number
		}
		cout << "sum of all weights for short forest is " << weightSum << endl << endl; // print edge weights
		getchar();
	}
	catch (...) {
		getchar();
	}

	getchar();
	getchar();
}
// given function for reading in the graph from the file
