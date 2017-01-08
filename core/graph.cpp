/**
* graph.cpp
*
* Copyright (c) 2017 by Javier G. Visiedo
*
* This file is part of dasel
*
* Dasel is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Dasel is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Dasel.  If not, see <http://www.gnu.org/licenses/>
*
*/

#include "iostream"
#include "graph.hpp"

///Adds an edge to the given vertex ID by adding a new element to the adjacency list
void UndirectedGraph::Vertex::addAdjacent (const uint64_t& vID) {
    if (!isAdjacent(vID)){
        adjList.push_back(vID);
        sort(adjList.begin(), adjList.end());
    }
}

void UndirectedGraph::Vertex::removeAdjacent(const uint64_t& vID) {
    vector<uint64_t>::iterator it=find(adjList.begin(),adjList.end(),vID);
    if (it!=adjList.end()){
        adjList.erase(it);
    }
}

UndirectedGraph::Vertex& UndirectedGraph::addVertex(const uint64_t& vID) {
    
    if (!vertexList.count(vID)){
        Vertex newVertex(vID);
        vertexList.insert(pair<uint64_t, Vertex>(vID, newVertex));
        if (vID > maxID) {
            maxID = vID;
        }
    }
    return vertexList[vID];
}

void UndirectedGraph::removeVertex(const uint64_t& vID) {
    unordered_map<uint64_t, Vertex>::iterator it = vertexList.find(vID);
    if (it != vertexList.end()) {
        //Remove in-edges to the vertex
        for (auto i : it->second.adjList){
            if (i!=vID){
                VertexIterator adjI = getVertexI(i);
                adjI->second.removeAdjacent(vID);
            }
            --numEdges;
        }
        vertexList.erase(it);
    }
}

void UndirectedGraph::addEdge (const uint64_t& from, const uint64_t& to) {
    if (isVertex(from) && isVertex(to)){
        Vertex& fV = vertexList[from];
        Vertex& tV = vertexList[to];
        if (!(fV.isAdjacent(to) && tV.isAdjacent(from))) {
            fV.addAdjacent(to);
            tV.addAdjacent(from);
            ++numEdges;
        }
    }
}

void UndirectedGraph::removeEdge (const uint64_t& from, const uint64_t& to) {
    if (isVertex(from) && isVertex(to)){
        Vertex& fV = vertexList[from];
        Vertex& tV = vertexList[to];
        fV.removeAdjacent(to);
        tV.removeAdjacent(from);
        --numEdges;
    }
}

void UndirectedGraph::clearVisited() {
    for (auto& m : vertexList){
        m.second.setVisited(false);
    }
}

void UndirectedGraph::printGraph(const uint64_t& root, const uint8_t& depth) {
    Vertex& rootVertex = getVertex(root);
    
    clearVisited();
    printDFS (rootVertex, depth, 0);
}

void UndirectedGraph::printDFS (UndirectedGraph::Vertex& v, const uint8_t& depth, const uint8_t& level) {
    
    if (level<=depth){
        string indent;
        for (int i=0; i<level; ++i){
            indent += "  ";
        }
        indent += "|- ";
        cout << indent << v.getId() << "\n";
        if (!v.isVisited()) {
            v.setVisited(true);
            for (uint64_t i = 0; i < v.getDeg(); ++i){
                UndirectedGraph::Vertex& adj = getVertex(v.getAdjID(i));
                printDFS (adj, depth, level+1);
            }
        }
    }
}
