//Header file for maze class, contains class functions underneath
//based off of Sample solution for project #5
// reads a file into a matrix and then maps that matrix onto a graph
// BW 07Nov16

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "d_matrix.h"
#include<boost/graph/adjacency_list.hpp>

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


using namespace std;

class maze
{
public:
	maze(ifstream &fin); // constructor for matrix
	void print(int, int, int, int); // printer of matrix
	bool isLegal(int i, int j); // checks to see if input is valid
	void mapMazeToGraph(Graph &g); // fills graph from the input matrix
	void printPath(Graph::vertex_descriptor end,
		stack<Graph::vertex_descriptor> &s,
		Graph g); // prints out the stack containing the path
	int numRows() { return rows; }; // numrows in matrix
	int numCols() { return cols; }; // numcols in matrix
	int size() { return terms; }; // total number of vertices

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze12 a
	int terms = 0; // used for sizing graph
	matrix<bool> value;
};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
	fin >> rows;
	fin >> cols;

	char x;

	value.resize(rows, cols);
	for (int i = 0; i <= rows - 1; i++)
		for (int j = 0; j <= cols - 1; j++)
		{
			fin >> x;
			if (x == 'O') {
				value[i][j] = true;
				terms++;
			}
			else
				value[i][j] = false;
		}

}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
	cout << endl;

	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");

	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");

	for (int i = 0; i <= rows - 1; i++)
	{
		for (int j = 0; j <= cols - 1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
				if (i == currI && j == currJ)
					cout << "+";
				else
					if (value[i][j])
						cout << " ";
					else
						cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
	if (i < 0 || i > rows || j < 0 || j > cols)
		throw rangeError("Bad value in maze::isLegal");

	return value[i][j];
}

void maze::mapMazeToGraph(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // CREATES first/last address for iterator
	Graph::vertex_iterator vItr = vItrRange.first; // set iterator to first location in graph
	pair<int, int> position; // makes a pair of ints to track positions
	for (int rows = 0; rows < value.rows(); rows++) { // itterate over every row in the matrix
		for (int cols = 0; cols < value.cols(); cols++) { // iterate over every column for every row
			if (value[rows][cols] == true) { // if there is a value at the matrix coordinates
				position.first = rows; // set first part of position to the row
				position.second = cols; // second to the column
				g[*vItr].cell = position; // set the position to the vertice number
				vItr++; // increase the itterator
			}
		}
	}
	Graph::vertex_iterator vItr1 = vItrRange.first; // reset itterator
	Graph::vertex_iterator vItr2; // define second itterator
	for (int rows = 0; rows < value.rows() - 1; rows++) { // for all rows exccept far right
		for (int cols = 0; cols < value.cols() - 1; cols++) { // for all columns in all rows
			if (value[rows][cols] == true) { // if there is a term at the designated spot
				if (value[rows][cols+1] == true) { // if there is also a term one to the right of the found termm
					position.first = rows; // set position of first cell
					position.second = cols;
					while (g[*vItr1].cell != position) vItr1++; // iterate vItr1 to the location of the first cell
					boost::add_edge(*vItr1, *vItr1+1, g); // set edge connecting the next cell
					boost::add_edge(*vItr1 + 1, *vItr, g); // set reverse edge
					}
				if (value[rows+1][cols] == true){ // if there is a term below the designated spot
					position.first = rows; // set position again
					position.second = cols;
					while (g[*vItr1].cell != position) vItr1++; // catch vItr1 up to designated node
					vItr2 = vItr1; // knowing vItr2 must be past vItr 1
					position.first = rows + 1; // increment the rows by 1
					while (g[*vItr2].cell != position) vItr2++; // find the node for vItr2
					boost::add_edge(*vItr1, *vItr2, g); // create the two edges
					boost::add_edge(*vItr2, *vItr1, g);
				}
			}
		}
	}
}

// print the stack of moves that were made to get to the exit
void maze::printPath(Graph::vertex_descriptor end,
	stack<Graph::vertex_descriptor> &s,
	Graph g) {
	Graph::vertex_descriptor current; // create a temp descriptor
	while (s.size() != 0) { // while stack isnt empty
		current = s.top(); // set value to top vertice
		cout << g[current].cell.first << "," << g[current].cell.second << endl; // print out location
		s.pop(); // pop top value from stack
	}
}

