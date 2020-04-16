# BasicGraph
Program that allows the addition of Vertex and Weighted Edges with the ability to output graph information.

## Overview
Meant to show a directed graph programming sample

<img src="GraphLab251/overview/screen shot 2020-04-16 at 1.33.35 pm.png" />

## User Manual
**Usage**
* The software is meant to show off the graph class and as such only allows the user to get nearby vertices and weights

*Input a vertex name to get the information*

<img src="GraphLab251/user manual/usage/screen shot 2020-04-16 at 2.24.49 pm.png" />

## Implementation
* This class is implemented by a multidimensional array of EdgeData structs and a Vertex Vector.
  * Each edge data struct holds a boolean determining if an edge exists and its respective weight
* When a Vertex is added, it is pushed on to the Vertex vector
  * The row index corrosponds with the index of the Vertex Vector to easily determine that Vertex value
* The graph currently doesn't support dynamic allocation of the Vertex Array, therefore the constructor only does basic error checking
* The class includes checking for duplicate Vertices and has a maximum size of 100 Vertices

- [ ] Use dynamically allocated array

## Documentation
**ADD DOCUMENTATION**
