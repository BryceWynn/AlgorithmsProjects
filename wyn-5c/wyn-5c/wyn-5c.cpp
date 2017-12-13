// djKstras and Bellman Ford alogrithms for graphs
//contains given initilialize function to create graph from file
//uses a relax function with a boolean output to save proocessing time
//also  includes print file to give shortest path from first to last node
//BW 11/21/16

#include "stdafx.h"
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include<boost/graph/adjacency_list.hpp> 

#include "d_except.h"
#include "d_matrix.h"
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



// given function for reading in the graph from the file
void initializeGraph(Graph &g,
	Graph::vertex_descriptor &start,
	Graph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}

pair<Graph::edge_descriptor, bool> edgeBetween; // declared global to save the need for redeclarations every  time relax is called

bool relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v) {// relax  function for both sets
	edgeBetween = edge(u, v, g); // find the edge seperating the two nodes
	if (g[v].weight > g[u].weight + g[edgeBetween.first].weight) { // if the weight of the second is less than the node weight of the first and the edge weight
		g[v].weight = g[u].weight + g[edgeBetween.first].weight; // set the second node weight to the sum of the two weights
		g[v].pred = u;// set the predecessor of the second to the first
		return true; // return true saying the relax took place
	}
	return false; // return false showing no relax
}

// sets all node weights to max value so algorithms will work
void setNodeWeights(Graph &g, int w) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // find vertices range
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for every vertex
		g[*vItr].weight = w; // set weight to w
	}
}

//performs dijkstra algorithm on graph
bool dijkstra(Graph &g, Graph::vertex_descriptor v) {
	int index; // index for heap library use
	heapV<Graph::vertex_descriptor, Graph> pointHeap; // create pointheap using custom heap class HeapV
	setNodeWeights(g, LargeValue); // set all nodes to largevalue weight
	g[v].weight = 0; // set starting node weight to zero
	vector<Graph::vertex_descriptor> heapBuilder; // make vector of all the nodes for making heapV
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // create vertices range
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for all vertices
		heapBuilder.push_back(*vItr); // add vertice to vector
	}
	pointHeap.initializeMinHeap(heapBuilder, g); // creat minHeap heapV
	index = pointHeap.getIndex(v);//get index for term 1
	pointHeap.minHeapDecreaseKey(index, g); // make sure term 1 is first term
	Graph::vertex_descriptor logicV, temp;
	logicV = pointHeap.extractMinHeapMinimum(g); // set logicV to start node and remove start node from heap
	g[logicV].pred = logicV; // set start node to self;
	while (pointHeap.size() != 0) { // while nodes remain in heap
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // create this instance of edge itterator
		vItrRange = adjacent_vertices(logicV, g); // set edge itterator
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) { // for all edges at this node
			if (relax(g, logicV, *vItr)) { // if relaxx occurs and path is changed
				temp = *vItr; // used due to type issues with getIndex
				g[*vItr].pred = logicV; // set pred of next node to  logicV
				index = pointHeap.getIndex(temp); // get index for altered node
				pointHeap.minHeapDecreaseKey(index, g); // minHeapify altered node
			}
		}
		logicV = pointHeap.extractMinHeapMinimum(g); // find newest minimum value
	}
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for all vertices
		if (g[*vItr].weight == LargeValue) return false; // if a vertex wasn't reached weight remains LargeValue, return false
	}
	return true; // if all nodes were reached, return true
}

// bellman ford algorithm for finding shortest path through graph
bool bellmanFord(Graph &g, Graph::vertex_descriptor s) {
	setNodeWeights(g, LargeValue); // set all node weights to max value
	Graph::vertex_descriptor targetV, sourceV; // decalre needed vector descriptors
	g[s].weight = 0; // set starting node weight to 0
	int iterations = 0; // set iterations to 0
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // set up vItrRange
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for all vertices
		iterations++; // count vertices
	}
	iterations--; //reduce by one so last loop will be negative check
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); // itterate over every edge
	while (iterations != 0){
		iterations--; // dock itterations a value
		for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
			if (relax(g, source(*eItr, g), target(*eItr, g))) { // attempt to relax every edge
				sourceV = source(*eItr, g); // used due to imitations with BGLs ability to handle types
				targetV = target(*eItr, g); // same as above
				g[targetV].pred = sourceV; // set predecessor
			}
		}
	}
	for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
		if (relax(g, source(*eItr, g), target(*eItr, g))) return false; // if relax is still possible, negative cycle
	}
	return true; // return true otherwise
}

// print out graph
bool graphPrinter(Graph::vertex_descriptor v, Graph::vertex_descriptor u, Graph &g) {
	Graph::vertex_descriptor temp; // create needed vertex descriptors
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // set up itterator range 
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // for all vertices
		if (g[*vItr].weight == LargeValue) return false; // if weight still large value, not fully reachable from start, return false
	}
	temp = u; // temp equals end term
	cout << "end vertex number " << temp << " path to start" << endl; // output start
	stack <Graph::vertex_descriptor> printStack; // create stack to flip node order to go start to end using only predecessors
	while (g[temp].pred != v) { // while predecessor isnt start node
		printStack.push(temp); //push current node into stack
		temp = g[temp].pred; // set current node to predecessor
	}
	printStack.push(v); // add start node to stack
	while (printStack.size() != 0) { // while stack isnt empty
		cout << printStack.top() << endl; // print top node in stack
		printStack.pop(); // remove top node from stack
	}
	return true; // return true
}

int main(){
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
		Graph myGraph; //create graph
		Graph::vertex_descriptor first, last; // used for typing issues with BGL and heapV
		pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(myGraph); // set verticce range
		first = *vItrRange.first; // correct typing issues
		last = *(vItrRange.second - 1); // '', -1 gives end node instead of space past it
		initializeGraph(myGraph, first, last, fin); // create graph from file
		vItrRange = vertices(myGraph); // create new vItr range with finished graph
		first = *vItrRange.first; // correct typing issues 
		last = *(vItrRange.second - 1);// ''
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(myGraph); // itterate over every edge
		bool noNegEdge = true;
		for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) if (myGraph[*eItr].weight < 0) noNegEdge = false; // ensure there are no neg edges before dijkstras
		if (noNegEdge) {
			if (!dijkstra(myGraph, first)) cout << "no shortest path exists"; // if dijkkstras does not reach every node, print no shortest path
			else (graphPrinter(first, last, myGraph)); // otherwise print graph
		}
		else cout << "negative edges, dijkstras skipped" << endl; // print that ddisjkstras skipped due to neg edges
		if (!bellmanFord(myGraph, first)) cout << "negative loop in graph"; // if negative loop say so
		else {
			if (!graphPrinter(first, last, myGraph)) cout << "no shortest path exists"; // check if graph solved, if so print graph
		}
		getchar(); // hold
	}
	catch (...) {
		getchar(); // handle all errors
	}
	getchar(); // hold
}