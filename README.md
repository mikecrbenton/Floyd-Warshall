# Floyd-Warshall
CSC300 Data Structures // C++ program that runs Floyd-Warshall algorithm with path reconstruction

## Overview:
Data structures graph project consisting of 3 assignments(Determining Paths, Shortest Paths, Path Reconstruction):

main.cpp reads from 2 files ( trains.txt, stations.txt)

trains.txt

* 5 6    // The first number(5) 
* 0 1 7
* 3 1 10
* 4 3 12
* 1 4 12
* 4 2 32
* 1 2 3

#### Determining Paths

The first problem to solve is determining if a path exists between two stations.
We’ve covered how to do this using breadth first search and an adjacency list. But an
adjacency list will not be as practical as we move on to other problems like
determining the shortest route between two stations. Therefore, your task is to
determine if a route exists between two stations using breadth first search and an
adjacency matrix.
