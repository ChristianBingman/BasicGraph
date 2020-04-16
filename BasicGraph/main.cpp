//
//  main.cpp
//  BasicGraph
//
//  Created by Christian Bingman on 4/16/20.
//  Copyright © 2020 Christian Bingman. All rights reserved.
//

#include <iostream>
#include <string>

#include "graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
    graph<string, int> gr(6); // Initialize graph with up to 6 Vertices
    
    // Add vertex A-F to create graph
    gr.addVertex("A");
    gr.addVertex("B");
    gr.addVertex("C");
    gr.addVertex("D");
    gr.addVertex("E");
    gr.addVertex("F");
    
    // Add weighted edges
    gr.addEdge("A", "B", 100);
    gr.addEdge("B", "C", 20);
    gr.addEdge("C", "E", 29);
    gr.addEdge("E", "C", 29);
    gr.addEdge("B", "A", 80);
    gr.addEdge("A", "D", 115);
    gr.addEdge("B", "D", 12);
    gr.addEdge("D", "C", 7);
    
    // Show text output of graph
    gr.dump(cout);
    
    string input;
    cout << endl;
    cout << "Enter a vertex or #> ";
    cin >> input;
    
    while (input != "#") {
        // Get the list of nearby neighbors
        vector<string> nearby = gr.neighbors(input);
        
        // Ensure that there are actually any neighbors
        if(nearby.size() == 0){
            cout << "no neighbors" << endl;
        }else{
            // Loop through the neighbors
            for(string vt : nearby){
                // Print out the name of the Vertex and the weight
                int weight;
                if(!gr.getWeight(input, vt, weight)){
                    cout << "Unable to get weight" << endl;
                }
                cout << vt << " " << weight << endl;
            }
        }
        
        cout << endl;
        cout << "Enter a vertex or #> ";
        cin >> input;
    }
    
    return 0;
}
