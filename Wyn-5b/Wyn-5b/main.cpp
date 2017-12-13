//Handler for maze solver
//contains graph based functions
//also controls main to  create graph and print values
//BW 07Nov16
//
// updated with 4 different graph solvers
//recursive, depth, depthshortest, and breadthshortest
// recuursive also finds shortest for maze1, which is a happy coincidence
//BW 14Nov16


#include "Maze.h"
using namespace boost;
using namespace std;

#define LargeValue 99999999

stack<pair <int, int> > globalStack;

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
	g[*(vItrRange.second-2)].marked = true; // designates end position
}

void graphReseter(Graph &g) {
	clearMarked(g);
	setNodeWeights(g, LargeValue);
	clearVisited(g);
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

// solves maerecursively
bool findPathDFSRecursive(Graph &g, Graph::vertex_descriptor vd) { // passed graph and current node
	g[vd].visited = true;// set node visited to true
	if (g[vd].marked == true) { // if destination node
		globalStack.push(g[vd].cell); // add this node to cell
		return true; // trigger exit pattern
	}
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // create this instance of edge itterator
	vItrRange = adjacent_vertices(vd, g); // set edge itterator
	for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) { // for all edges at this node
		if (g[*vItr].visited == false) { // if they havnt been visited
			if (findPathDFSRecursive(g, *vItr) == true) { // recurse with new node, if further in recursion returns true (last node found)
				globalStack.push(g[vd].cell); // add this cell to stack
				return true;// return true to contnue exit pattern
			}
		}
	}
	return false; // if recursion fails, return false 
}

// solves using depth search and a stack, not optimized to find shortest route
bool findPathDFSStack(Graph &g) {
	Graph::vertex_descriptor vd = 0, vdPast1, vdFinal, vdDebug;  // create vertex descriptors
	g[vd].pred = vd; // set past node to last node (node 0 sets to self)
	g[vd].visited = true;// set visited true for node 0
	vdPast1 = vd; // needed for first set
	pair <int, int> baseCell; baseCell.first = 0; baseCell.second = 0; //  used for exit patter
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
				if (g[vdDebug].marked == true) {// if it is last node
					globalStack.push(g[vdDebug].cell);//add last node cell to stack
					g[vdDebug].pred = vd; 
					vdFinal = g[vdDebug].pred; // set vd to next node in solved chain
					while (g[vdFinal].cell != baseCell) {// while the node isnt the start node
						globalStack.push(g[vdFinal].cell); // add the current node to the solve path stack
						vdFinal = g[vdFinal].pred; // set to previous node
					}
					globalStack.push(baseCell); // add 0,0 to solv stack
					return true; // return true;
				}
				g[vdDebug].visited = true; // set node to visited
				vdStack.push(vdDebug); // add to stack
			}
		}
		vdPast1 = vd; // once all edges itterated, set past to current node
		vd = vdStack.top(); // select next node in stack
		vdStack.pop(); //  pop selected node;
	}
	return false; // return false if exit not found
}

// find the shortest path by depth first search
bool findShortestPathDFS(Graph &g, Graph::vertex_descriptor finish) {
	Graph::vertex_descriptor vd = 0, vdFinal; // set itterators
	g[vd].pred = vd; // set base nodes past to self (error prevention)
	pair <int, int> baseCell; baseCell.first = 0; baseCell.second = 0; // set base cell coordinates as 0,0
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // make adjacency itterator
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrFinalFinder = vertices(g); // get range to itterate over
	vItrRange = adjacent_vertices(vd, g); // set adjacency itterator to current node
	stack <Graph::vertex_descriptor> vdStack; // make stack used to solve
	vdStack.push(vd); // add base cell to stack
	g[vd].weight = 0; // set base cell weight to 0
	while (vdStack.size() != 0) { // while stack is not empty
		vItrRange = adjacent_vertices(vd, g); // set adjacency itterator to current node
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) { // itterate over all edges
			if (g[*vItr].weight > (g[vd].weight +1)) { // if next edges weight is more than 1 greater than current edge (either previously unfound or found in less efficent manner
				g[*vItr].weight = g[vd].weight + 1; // set weight to previous nodes weight + 1
				g[*vItr].pred = vd; // set pred to the current node
				vdStack.push(*vItr); //add this node to the stack
			}
		}
		vd = vdStack.top(); // select next term in stack
		vdStack.pop(); // remove next term from stack
	}
	if (g[finish].weight < LargeValue) { // if the final term was found (check weight to see if it was ever modified)
		globalStack.push(g[finish].cell); // add final cell to print stack
		vdFinal = g[finish].pred; // see which  cel was previous
		while (g[vdFinal].cell != baseCell) { // while not back at 0,0
			globalStack.push(g[vdFinal].cell); // add cell to print stack
			vdFinal = g[vdFinal].pred; // go to previous cell
		}
		globalStack.push(baseCell); // add base cell to stack
		return true; // return true
	}
	return false; // return false if exit not found
}

//find shortest path through breadth first search
bool findShortestPathBFS(Graph &g) {
	Graph::vertex_descriptor vd = 0, vdPast, vdFinal; // create vertex descriptors
	g[vd].pred = vd; // set base nodes predecessor to itself (error pprevention)
	vdPast = vd; // set past to base node (error prevention)
	g[vd].visited = true; // set base node visited to true
	pair <int, int> baseCell; baseCell.first = 0; baseCell.second = 0; // sset base cell pair to 0,0 for exit stack
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange; // create adjacency itterator 
	vItrRange = adjacent_vertices(vd, g); // set adjacency itterator to first term
	queue <Graph::vertex_descriptor> vdQueue; // create que
	vdQueue.push(vd); // add first term to que
	while (vdQueue.size() != 0) {// while que isnt empty
		vdQueue.pop(); // remove term from que
		vItrRange = adjacent_vertices(vd, g); // set adjacency titerator to current term
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) { // for all adjacent terms
			if (g[*vItr].visited != true) { // if adjacent node hasnt been visited
				if (g[*vItr].marked == true) { // if adjacent node has been visited, launch same exxit procedure as DFS

					//use DFS exit procedure
					globalStack.push(g[*vItr].cell);
					vdFinal = g[*vItr].pred;
					while (g[vdFinal].cell != baseCell) {
						globalStack.push(g[vdFinal].cell);
						vdFinal = g[vdFinal].pred;
					}
					globalStack.push(baseCell);
					return true;
				}


				g[*vItr].visited = true; // set node visited to true
				g[*vItr].pred = vd; // set predecessor to current node
				vdQueue.push(*vItr); // add new node to que
			}
		}
		vd = vdQueue.front(); // take next node from front of que
	}
	return false; // return false if no exit found
}

int main()
{
	try
	{
		//set up file input
		ifstream fin;

		// Read the maze from the file.
		string fileName = "maze1.txt";
		cout << "please input desired file to open" << endl;
		cout << "filename should be mazeX.txt where X is the maze number" << endl;
		cin >> fileName;
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
		graphReseter(g); // set starting values for graph
		cout << g << endl; // print graph
		pair<Graph::vertex_iterator, Graph::vertex_iterator> graphStarter = vertices(g); // used for recursive to give start value
		pair <int, int> stackUnpacker;
		if (findPathDFSRecursive(g, *(graphStarter.first)) == false) cout << "No Path Exists" << endl; // finds path by depth first recursion
		while (globalStack.size() != 0) { // prints out solution
			stackUnpacker = globalStack.top();
			globalStack.pop();
			m.print(m.numRows() - 1, m.numCols() - 1,stackUnpacker.first , stackUnpacker.second);
		}
		graphReseter(g); // reset graph
		if (findPathDFSStack(g) == false) cout << "No Path Exists" << endl;// find bath depth by stack
		while (globalStack.size() != 0) {// print solution
			stackUnpacker = globalStack.top();
			globalStack.pop();
			m.print(m.numRows() - 1, m.numCols() - 1, stackUnpacker.first, stackUnpacker.second);
		}
		graphReseter(g); // reset graph
		if (findShortestPathBFS(g) == false) cout << "No Path Exists" << endl; // find shortest path with breadth first search
		while (globalStack.size() != 0) { // print solution
			stackUnpacker = globalStack.top();
			globalStack.pop();
			m.print(m.numRows() - 1, m.numCols() - 1, stackUnpacker.first, stackUnpacker.second);
		}
		graphReseter(g);// reset graph
		if (findShortestPathDFS(g, (*graphStarter.second)-2) == false) cout << "No Path Exists" << endl; // find shortest path with depth first search
		while (globalStack.size() != 0) { // print solution
			stackUnpacker = globalStack.top();
			globalStack.pop();
			m.print(m.numRows() - 1, m.numCols() - 1, stackUnpacker.first, stackUnpacker.second);
		}
		getchar(); //hold output 

	}
	catch (...)
	{
	}
	getchar();// hold output
}

