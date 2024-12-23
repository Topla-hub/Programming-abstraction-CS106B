/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,Loc end,Grid<double>& world,double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Vector<Loc> res;//found path
	Grid<int> allLocs(world.nRows,world.nCols);//every Loc is gray(if 1 yellow)(if 2 green)
	Grid<double> distance(world.nRows, world.nCols);//keeps track of the distances to each node
	for (int row = 0; row < world.nRows; ++row) {
		for (int col = 0; col < world.nCols; ++col) {
			distance[row][col] = DBL_MAX;
		}
	}
	distance[start.row][start.col] = 0;//marke start cell
	Map<Loc, Loc> parents;//keeps track of the parent cell for each cell in the grid
	TrailblazerPQueue<Loc>  candidates;
	allLocs[start.row][start.col] = 1;//make start yellow.
	colorCell(world, start, YELLOW);//graphic color
	candidates.enqueue(start, heuristic(start,end,world));
	while (!candidates.isEmpty()) {
		Loc curr = candidates.dequeueMin();
		allLocs[curr.row][curr.col] = 2;//make Green
		colorCell(world, curr, GREEN);//graphic color;
		if (curr == end) {
			while (curr != start) {
				res.insert(0, curr);
				curr = parents[curr];
			}
			res.insert(0, start);
			return res;
		}
		Vector<Loc> neighbors;//add all neighbors
		neighbors.add({ curr.row - 1, curr.col });
		neighbors.add({ curr.row - 1, curr.col - 1 });
		neighbors.add({ curr.row, curr.col - 1 });
		neighbors.add({ curr.row + 1, curr.col - 1 });
		neighbors.add({ curr.row + 1, curr.col });
		neighbors.add({ curr.row + 1, curr.col + 1 });
		neighbors.add({ curr.row, curr.col + 1 });
		neighbors.add({ curr.row - 1, curr.col + 1 });
        for (Loc neighbor : neighbors) {
            if (world.inBounds(neighbor.row, neighbor.col)) {
                double newDist = distance[curr.row][curr.col] + costFn(curr, neighbor, world);
                if (allLocs[neighbor.row][neighbor.col] == 0) { // Is gray
                    allLocs[neighbor.row][neighbor.col] = 1; //Color v yellow.
					colorCell(world, neighbor, YELLOW);//graphic color
                    distance[neighbor.row][neighbor.col] = newDist;// Set v's candidate distance to be dist + L
                    parents[neighbor] = curr;// Set v's parent to be curr
					double Apriority = newDist + heuristic(neighbor, end, world);
                    candidates.enqueue(neighbor, Apriority);//Enqueue v into the priority queue with priority dist + L
                } else if (allLocs[neighbor.row][neighbor.col] == 1 && distance[neighbor.row][neighbor.col] > newDist) { // Is yellow
                    distance[neighbor.row][neighbor.col] = newDist;// Set v's candidate distance to be dist + L
                    parents[neighbor] = curr;//Set v's parent to be curr
					double Apriority = newDist + heuristic(neighbor, end, world);
                    candidates.decreaseKey(neighbor, Apriority);// Update v's priority in the priority queue to dist + L
                }
            }
        }
	}
    return res;
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> res;//this will be our answer
	Set<Edge> allEdges;//using set to avoid duplicates 
	createAllEdges(numRows, numCols, allEdges);//mathod is implemented down
	Map<Loc, Loc> clusters;//using map for clusters
	//at the beginning give each node its own cluster
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			Loc node = { i, j };
			clusters[node] = node;
		}
	}
	//priority queue for edges with random priorities
	TrailblazerPQueue<Edge> candidates;
	for (Edge edge : allEdges) {
		candidates.enqueue(edge, randomReal(0, 1));
	}
	//Kruskal's algorithm on a graph
	while (!candidates.isEmpty() && res.size() < clusters.size() - 1) {//until all nodes are in the same cluster
		Edge e = candidates.dequeueMin();
		Loc start = e.start;
		Loc end = e.end;
		Loc startCluster = clusters[start];
		Loc endCluster = clusters[end];
		if (startCluster != endCluster) {
			Loc newCluster = startCluster; 
			for (Loc loc : clusters) {//merge the clusters containing the endpoints of e
				if (clusters[loc] == endCluster)
					clusters[loc] = newCluster;
			}
			res.add(e);
		}

	}
	return res;
}


//this method creates all posible edges for maze n by m
void createAllEdges(int numRows, int numCols, Set<Edge>& allEdges) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			//all neighbors
			Loc start = { i , j };
			Loc top = { i - 1, j };
			Loc right = { i, j + 1 };
			Loc down = { i + 1, j };
			Loc left = { i, j - 1 };
			//create edge and add 
			if (top.row >= 0 && top.col >= 0 && j < numCols) {
				Edge topEdge = { start, top };
				allEdges.add(topEdge);
			}
			if (right.col < numCols && i < numRows) {
				Edge rightEdge = { start, right };
				allEdges.add(rightEdge);
			}
			if (down.row < numRows && j < numCols) {
				Edge downEdge = { start, down };
				allEdges.add(downEdge);
			}
			if (left.col >= 0 && i < numRows) {
				Edge leftEdge = { start, left };
				allEdges.add(leftEdge);
			}
		}
	}
}