/*graph.h*/

//
// Christian Bingman
// University of Illinois at chicago
// CS 251
// Spring 2020
//
// Class for managing Vertices and Weighted Edges
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>  /*pair*/

using namespace std;

template<typename VertexT, typename WeightT>
class graph
{
private:
  struct EdgeData
  {
    bool     EdgeExists;
    WeightT  Weight;

    EdgeData()
    {
      EdgeExists = false;  // initially no edge, and no weight
    }
  };
    
  //
  // _LookupVertex
  //
  // Returns the index if found or -1
  //
    int _LookupVertex(VertexT v) const{
        for (int i = 0; i < this->NumVertices(); ++i)
        {
          if (this->Vertices[i] == v)  // already in the graph:
            return i;
        }
        
        return -1;
    }
    
  //
  // We are using adjacency matrix implementation, where rows
  // are the starting vertex and cols are the ending vertex.
  // We keep track of the vertices in the Vertices vector,
  // where the vertex's position in the vector --- 0, 1, 2, 
  // 3, 4, 5, ... --- denotes the row in the adjacency matrix
  // where their edges are found.  Example: if vertex "ORD" is
  // in position 1 of the Vertices vector, then row 1 of
  // AdjMatrix are the edges that start at "ORD" and lead to
  // other vertices.
  //
  static constexpr int MatrixSize = 100;

  EdgeData         AdjMatrix[MatrixSize][MatrixSize];
  vector<VertexT>  Vertices;

public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices 
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception 
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  graph(int n)
  {
    if (n > MatrixSize)
      throw runtime_error("graph::constructor: n exceeds internal matrix size");
  }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const
  {
    return static_cast<int>(this->Vertices.size());
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const
  {
    int count = 0;

    //
    // loop through the adjacency matrix and count how many 
    // edges currently exist:
    //
    for (int row = 0; row < this->NumVertices(); ++row)
    {
      for (int col = 0; col < this->NumVertices(); ++col)
      {
        if (this->AdjMatrix[row][col].EdgeExists)
          count++;
      }
    }

    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v)
  {
    if (this->NumVertices() > MatrixSize)  // we're full:
      return false;

    //
    // is the vertex already in the graph?  If so, we do not 
    // insert again otherwise Vertices may fill with duplicates:
    //
      if(_LookupVertex(v) != -1){
          return false;
      }
    
    //
    // if we get here, vertex does not exist so insert.  Where
    // we insert becomes the rows and col position for this 
    // vertex in the adjacency matrix.
    //
    this->Vertices.push_back(v);

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight)
  {
    //
    // we need to search the Vertices and find the position 
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    int row = -1;

    // from vertex => row of adjacency matrix:
    int vertFind = _LookupVertex(from);

    if (vertFind != -1)  // found it:
    {
      row = vertFind;
    }

    if (row < 0)  // not found:
      return false;

    int col = -1;

    // to vertex => col of adjacency matrix:
    for (int i = 0; i < this->NumVertices(); ++i)
    {
      if (this->Vertices[i] == to)  // found it:
      {
        col = i;
        break;
      }
    }

    if (col < 0)  // not found:
      return false;

    //
    // the vertices exist and we have the row and col of the
    // adjacency matrix, so insert / update the edge:
    //
    this->AdjMatrix[row][col].EdgeExists = true;
    this->AdjMatrix[row][col].Weight = weight;

    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const
  {
    //
    // we need to search the Vertices and find the position 
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    int row = -1;

    // from vertex => row of adjacency matrix:
    int vertFind = _LookupVertex(from);

    if (vertFind != -1)  // found it:
    {
      row = vertFind;
    }

    if (row < 0)  // not found:
      return false;

    int col = -1;

    // to vertex => col of adjacency matrix:
    vertFind = _LookupVertex(to);

    if (vertFind != -1)  // found it:
    {
      col = vertFind;
    }

    if (col < 0)  // not found:
      return false;

    //
    // the vertices exist, but does the edge exist?
    //
    if (!this->AdjMatrix[row][col].EdgeExists)  // no:
      return false;

    //
    // Okay, the edge exists, return the weight via the 
    // reference parameter:
    //
    weight = this->AdjMatrix[row][col].Weight;

    return true;
  }

  //
  // neighbors
  //
  // Returns a vector containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  //
  vector<VertexT> neighbors(VertexT v) const
  {
    vector<VertexT>  V;

    //
    // we need to search the Vertices and find the position 
    // of v, that will be the row we need in the adjacency 
    // matrix:
    //
    int row = -1;
      
    int vertFind = _LookupVertex(v);

    if (vertFind != -1)  // found it:
    {
      row = vertFind;
    }

    if (row < 0)  // not found:
      return V;

    //
    // we found the row, so loop along the row and for every
    // edge that exists, add the column vertex to V:
    //
    // NOTE: how many columns are there?  The # of vertices.
    //
    for (int col = 0; col < this->NumVertices(); ++col)
    {
      if (this->AdjMatrix[row][col].EdgeExists)
      {
        VertexT dest = this->Vertices[col];  // dest vertex is here:

        V.push_back(dest);
      }
    }

    return V;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const
  {
    return this->Vertices;  // returns a copy:
  }

  //
  // dump
  // 
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const
  {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (int i = 0; i < this->NumVertices(); ++i)
    {
      output << " " << i << ". " << this->Vertices[i] << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (int row = 0; row < this->NumVertices(); ++row)
    {
      output << " row " << row << ": ";

      for (int col = 0; col < this->NumVertices(); ++col)
      {
        if (this->AdjMatrix[row][col].EdgeExists == false)
        {
          output << "F ";
        }
        else
        {
          output << "(T," 
            << this->AdjMatrix[row][col].Weight 
            << ") ";
        }
      }

      output << endl;
    }

    output << "**************************************************" << endl;
  }

};
