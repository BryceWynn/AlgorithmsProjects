//Handler for maze solver
//contains graph based functions
//also controls main to  create graph and print values
//BW 07Nov16



#include "Maze.h"
using namespace boost;
using namespace std;

#define LargeValue 99999999

// currently unused, sets all nodes to unvisited
void clearVisited(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);//set itterator range
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // iterate over all vertices
		g[*vItr].visited = false; // set term to false
	}
}
// Mark all nodes in g as not visited.

// repeat above for setting weights to w
void setNodeWeights(Graph &g, int w) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		g[*vItr].weight = w;
	}
}

// repeat above for clearing marked
void clearMarked(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		g[*vItr].marked = false;
	}
}

// overloaded operator for graph for printing all terms
ostream &operator<<(ostream &ostr, const Graph &g) {
	int iterator = 1; // used in output only
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // get range to itterate over
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) { // loop over itterator range
		cout << "node " << iterator << endl; // print node #, than all terms related to node
		cout << g[*vItr].cell.first << "," << g[*vItr].cell.second << endl;
		cout << g[*vItr].pred << endl;
		cout << g[*vItr].weight << endl;
		cout << g[*vItr].visited << endl;
		cout << g[*vItr].marked << endl;
		iterator++; // increase itterator
	}

	iterator = 1;
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); // edge itterator range
	for (auto eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) { // itterate over every edge
		cout << "edge " << iterator << endl; // print out edge number
		cout << source(*eItr, g) << "," << target(*eItr, g) << endl;// print out which nodes it connects
		iterator++;
	}
	return ostr;
}




int main()
{
	try
	{
		//set up file input
		ifstream fin;

		// Read the maze from the file.
		string fileName = "maze1.txt";

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		maze m(fin); // initialize maze
		fin.close(); // close file
		int numVectors = m.size(); // find out number of vertices
		m.print(m.numRows() - 1, m.numCols() - 1, 0, 0); // print matrix

		Graph g(numVectors); // create graph with correct number of vertices
		m.mapMazeToGraph(g); // create graph
		cout << g << endl; // print graph
		getchar(); //hold output

	}
	catch (...)
	{
	}
}

