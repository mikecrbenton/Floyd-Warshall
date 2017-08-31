# Floyd-Warshall
CSC300 Data Structures // C++ program that runs Floyd-Warshall algorithm with path reconstruction

## Overview:
Data structures graph project consisting of 3 assignments(Determining Paths, Shortest Paths, Path Reconstruction):

main.cpp reads from 2 files ( trains.txt, stations.txt)

### stations.txt - number and color representing the train at each station
* 0 Red
* 1 Green
* 2 Blue
* 3 Purple
* 4 Yellow

### trains.txt - description below
* 5 6    // The 1st number(5)represents the number of trains, the 2nd number(6) represents the number of routes 
* 0 1 7  // Route 1 - There is a route from 0(Red) to 1(Green) with a weight of 7
* 3 1 10  // Route 2 - There is route from 3(Purple) to 1(Green) with a weight of 10
* 4 3 12  // Route 3
* 1 4 12  // Route 4
* 4 2 32  // Route 5
* 1 2 3   // Route 6

#### Assignment 1: Determining Paths
The first problem to solve is determining if a path exists between two stations.
We’ve covered how to do this using breadth first search and an adjacency list. But an
adjacency list will not be as practical as we move on to other problems like
determining the shortest route between two stations. Therefore, your task is to
determine if a route exists between two stations using breadth first search and an
adjacency matrix.

#### Assignment 2: Shortest Path
This will be a continuation of assignment 1. The next problem we need to solve is
determining the shortest route between two stations. On the next assignment we will reconstruct
this route, but for now we will only worry about the distance itself. We’ve spent the
last couple of lectures covering different shortest path problems as well as specific
algorithms for solving such problems. This assignment challenges you to use the
Floyd-Warshall all-pairs shortest path algorithm to determine the shortest route
between two stations.

#### Assignment 3: Path Reconstruction
This will be a continuation of assignment 7. The final problem we will be looking to
solve is path reconstruction. Our code is capable of determining what the shortest
path is between two stations, but it can’t tell us what routes we need to take. We will
write some code to do this for us. 
Your program should be built to use a weighted, directed graph.
Your program will still be expected to handle station names instead of relying on
integer identifiers. Therefore, you will need to read data from two separate files and
keep track of the information appropriately.
The format of the first file will remain the same as assignment 2 so you shouldn’t
have to rewrite any of that code.


