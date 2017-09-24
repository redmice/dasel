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

#include <queue>
#include "iostream"
#include "graph.hpp"


//#/////////////////////////////////////////////////
// UndirectedGraph::Vertex
//
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

//#/////////////////////////////////////////////////
// UndirectedGraph
//
bool UndirectedGraph::isEdge(const uint64_t& fromID, const uint64_t& toID){
    if (!(isVertex(fromID) && isVertex(toID))){
        return false;
    }
    return vertexList[fromID].isAdjacent(toID);
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
                Vertex& adj = getVertex(i);
                adj.removeAdjacent(vID);
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
    
    v.setVisited(true);
    if (level<=depth){
        string indent;
        for (int i=0; i<level; ++i){
            indent += "|  ";
        }
        indent += "|- ";
        cout << indent << v.getId() << "\n";
        for (uint64_t i = 0; i < v.getDeg(); ++i){
            UndirectedGraph::Vertex& adj = getVertex(v.getAdjID(i));
            if (!adj.isVisited()) {
                printDFS (adj, depth, level+1);
            }
        }
    }
}

int16_t UndirectedGraph::distance(const uint64_t& from, const uint64_t& to){
    typedef struct {
        uint64_t    vID;   //Vertex ID
        int16_t     d;     //distance to "from"
    }tNodeInfo;
    queue<tNodeInfo> q;
    UndirectedGraph::Vertex& v = getVertex(from);
    
    clearVisited();
    q.push({from, 0});
    v.setVisited(true);
    while(!q.empty()) {
        tNodeInfo nodeInfo = q.front();
        q.pop();
        if (nodeInfo.vID == to){
            return nodeInfo.d;
        }
        v = getVertex(nodeInfo.vID);
        for (uint64_t i = 0; i < v.getDeg(); ++i){
            tNodeInfo child = {v.getAdjID(i), static_cast<int16_t>(nodeInfo.d + 1)};
            UndirectedGraph::Vertex& adj = getVertex(child.vID);
            if (!adj.isVisited()) {
                adj.setVisited(true);
                q.push(child);
            }
        }
    }
    return -1;
}

//#/////////////////////////////////////////////////
// DirectedGraph::Vertex
//
void DirectedGraph::Vertex::addOutEdge (const uint64_t& vID) {
    if (!isOutEdge(vID)){
        adjList.push_back(vID);
        sort(adjList.begin(), adjList.end());
    }
}

void DirectedGraph::Vertex::removeOutEdge(const uint64_t& vID) {
    vector<uint64_t>::iterator it=find(adjList.begin(),adjList.end(),vID);
    if (it!=adjList.end()){
        adjList.erase(it);
    }
}

void DirectedGraph::Vertex::addInEdge (const uint64_t& vID) {
    if (!isInEdge(vID)){
        inAdjList.push_back(vID);
        sort(inAdjList.begin(), inAdjList.end());
    }
}

void DirectedGraph::Vertex::removeInEdge (const uint64_t& vID) {
    vector<uint64_t>::iterator it=find(inAdjList.begin(), inAdjList.end(), vID);
    if (it!=inAdjList.end()){
        inAdjList.erase(it);
    }
}

//#/////////////////////////////////////////////////
// DirectedGraph
//
bool DirectedGraph::isEdge(const uint64_t& fromID, const uint64_t& toID){
    if (!(isVertex(fromID) && isVertex(toID))){
        return false;
    }
    return vertexList[fromID].isOutEdge(toID);
}
DirectedGraph::Vertex& DirectedGraph::addVertex(const uint64_t& vID) {
    
    if (!vertexList.count(vID)){
        DirectedGraph::Vertex newVertex(vID);
        vertexList.insert(pair<uint64_t, DirectedGraph::Vertex>(vID, newVertex));
        if (vID > maxID) {
            maxID = vID;
        }
    }
    return vertexList[vID];
}

void DirectedGraph::removeVertex(const uint64_t& vID) {
    unordered_map<uint64_t, Vertex>::iterator it = vertexList.find(vID);
    if (it != vertexList.end()) {
        //Remove all in-edges to the vertex
        for (auto i : it->second.inAdjList){
            if (i!=vID){
                DirectedGraph::Vertex& adj = getVertex(i);
                adj.removeOutEdge(vID);
                --numEdges;     //For self only decremented once for out
            }
        }
        //Remove all out-edges to the vertex
        for (auto i : it->second.adjList){
            if (i!=vID){
                DirectedGraph::Vertex& adj = getVertex(i);
                adj.removeInEdge(vID);
            }
            --numEdges;     //For self only decremented once for out
        }
        vertexList.erase(it);
    }
}

void DirectedGraph::addEdge (const uint64_t& from, const uint64_t& to) {
    if (isVertex(from) && isVertex(to)){
        Vertex& fV = vertexList[from];
        Vertex& tV = vertexList[to];
        if (!fV.isOutEdge(to)) {
            fV.addOutEdge(to);
            tV.addInEdge(from);
            ++numEdges;
        }
    }
}

void DirectedGraph::removeEdge (const uint64_t& from, const uint64_t& to) {
    if (isVertex(from) && isVertex(to)){
        Vertex& fV = vertexList[from];
        Vertex& tV = vertexList[to];
        fV.removeOutEdge(to);
        tV.removeInEdge(from);
        --numEdges;
    }
}

void DirectedGraph::clearVisited() {
    for (auto& m : vertexList){
        m.second.setVisited(false);
    }
}
void DirectedGraph::printGraph(const uint64_t& root, const uint8_t& depth) {
    Vertex& rootVertex = getVertex(root);
    printDFS (rootVertex, depth);
}

void DirectedGraph::printDFS (DirectedGraph::Vertex& v, const uint8_t& depth, const uint8_t& level) {
    
    v.setVisited(true);
    if (level<=depth){
        string indent;
        for (int i=0; i<level; ++i){
            indent += "|  ";
        }
        indent += "|-> ";
        cout << indent << v.getId() << "\n";
        for (uint64_t i = 0; i < v.getDeg(); ++i){
            DirectedGraph::Vertex& adj = getVertex(v.getOutAdjID(i));
            if (!adj.isVisited()) {
                printDFS (adj, depth, level+1);
            }
        }
    }
}

int16_t DirectedGraph::distance(const uint64_t& from, const uint64_t& to){
    typedef struct {
        uint64_t    vID;   //Vertex ID
        int16_t     d;     //distance to "from"
    }tNodeInfo;
    queue<tNodeInfo> q;
    DirectedGraph::Vertex& v = getVertex(from);
    
    clearVisited();
    q.push({from, 0});
    v.setVisited(true);
    while(!q.empty()) {
        tNodeInfo nodeInfo = q.front();
        q.pop();
        if (nodeInfo.vID == to){
            return nodeInfo.d;
        }
        v = getVertex(nodeInfo.vID);
        for (uint64_t i = 0; i < v.getDeg(); ++i){
            tNodeInfo child = {v.getOutAdjID(i), static_cast<int16_t>(nodeInfo.d + 1)};
            DirectedGraph::Vertex& adj = getVertex(child.vID);
            if (!adj.isVisited()) {
                adj.setVisited(true);
                q.push(child);
            }
        }
    }
    return -1;
}


