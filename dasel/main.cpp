//
//  main.cpp
//  Command line test
//
//  Created by Javier G. Visiedo on 11/1/16.
//  Copyright © 2016 visiedo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "graph.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream inFile;
    uint64_t fromID, toID;
    char fileName[FILENAME_MAX];
    string line;
    UndirectedGraph myGraph(2000000);
    int progressSpan=0;
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    
    inFile.open(fileName, ios::in);
    while (getline(inFile, line))
    {
        if (line[0] != '#' )
        {
            istringstream iss(line);
            iss >> fromID >> toID;
            cout << "addVertex()\n";
            myGraph.addVertex(fromID);
            cout << "addVertex()\n";
            myGraph.addVertex(toID);
            cout << "addEdge()\n";
            myGraph.addEdge(fromID, toID);
            if (progressSpan == 1000){
                cout << "." << flush;
                progressSpan = 0;
            }
            ++progressSpan;
        }
        
    }
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
    auto micro = duration % 1000;
    auto mil = (duration / 1000 ) % 1000;
    auto seg = (duration / (1000 * 1000) ) % 60;
    auto min = (duration / (1000 * 1000 * 60));
    
    cout << endl << "Graph built in " << duration << " microseconds" << endl;
    cout << "Or " << min << "min " << seg << "seg " << mil << "mil " << micro << "mic" <<  endl;
    cout << "getNumVertex()\n";
    cout << "\tVertex: " << myGraph.getNumVertex() << endl;
    cout << "getNumEdges()\n";
    cout << "\tEdges: " << myGraph.getNumEdges() << endl;
    cout << "printGraph()\n";
    myGraph.printGraph(1, 2);
    cout << "removeVertex()\n";
    myGraph.removeVertex(1);
    return 0;
}
