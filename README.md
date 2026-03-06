Graph Algorithms Toolkit (C++)

Overview
This project implements several fundamental graph algorithms in C++ using an adjacency list representation.  
It is designed as a learning tool to understand how classical graph algorithms work internally rather than relying on external libraries.

The program allows users to construct a graph and interactively run different algorithms through a menu-driven interface.

Implemented Algorithms

Graph Traversal
- Breadth First Search (BFS)
- Depth First Search (DFS)

Graph Analysis
- Connected Components detection using DFS

Shortest Path
- Dijkstra's Algorithm (for graphs with non-negative edge weights)

Minimum Spanning Tree
- Kruskal's Algorithm using Union-Find (Disjoint Set)

Directed Graph Processing
- Topological Sort (Kahn's Algorithm)

Data Structures Used

Adjacency List  
Priority Queue (Min Heap)  
Union-Find / Disjoint Set with:
- Path Compression
- Union by Rank

Features

Supports both directed and undirected graphs

Weighted edges support

Input validation for vertex indices

Warning when negative weights are used with Dijkstra

Displays:
- BFS traversal
- DFS traversal
- Connected components
- Shortest path distances and paths
- Minimum Spanning Tree edges and total weight
- Topological order of DAG

Interactive menu-driven execution.

Program Flow

1. User enters number of vertices and edges.
2. User specifies whether the graph is directed or undirected.
3. User inputs edges in the format:

u v weight

4. The program provides a menu to execute algorithms.

Menu options:

1 BFS  
2 DFS  
3 Connected Components  
4 Dijkstra Shortest Path  
5 Kruskal Minimum Spanning Tree  
6 Topological Sort  
0 Exit

Compilation

Compile the program using a C++ compiler:

g++ graph_toolkit.cpp -o graph

Run the program:

./graph

Example Input-

Vertices: 5  
Edges: 6

Edges:
0 1 4  
0 2 1  
2 1 2  
1 3 1  
2 3 5  
3 4 3

Learning Objectives

Understand adjacency list graph representation

Implement classical graph algorithms from scratch

Learn shortest path computation using priority queues

Understand Minimum Spanning Tree construction

Practice Disjoint Set (Union-Find) optimization techniques

Study topological ordering of Directed Acyclic Graphs

Limitations

Dijkstra does not support negative edge weights.

Topological sorting only works on Directed Acyclic Graphs.

Kruskal MST only applies to undirected graphs.

The program is designed for learning purposes and does not include graphical visualization.

Possible Future Improvements

Add Bellman-Ford algorithm for graphs with negative weights

Add Floyd-Warshall algorithm for all-pairs shortest paths

Implement Prim's algorithm for MST

Add cycle detection for directed graphs

Add visualization of graph traversal

## Author

CSE Student learning algorithms and preparing for GATE.
