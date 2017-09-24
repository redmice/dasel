/**
 *  graph-test.cpp
 *  Created on 1/7/17
 *
 *    Copyright © 2017 Javier Garcia Visiedo. All rights reserved.
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

#include <iostream>
#include "gtest/gtest.h"
#include "graph.hpp"


class UndirectedGraphTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        //Init g1 with 6 unnconected vertex:
        // num. vertex = 6
        // num edges = 0
        g1.addVertex(1);
        g1.addVertex(2);
        g1.addVertex(3);
        g1.addVertex(4);
        g1.addVertex(5);
        g1.addVertex(6);
        //Init g2 with some edges
        // num. vertex = 6
        // num edges = 12 (Undirected=>edges btw nodes are mutual and only
        // counted once)
        g2.addVertex(1);
        g2.addVertex(2);
        g2.addVertex(3);
        g2.addVertex(4);
        g2.addVertex(5);
        g2.addVertex(6);
        g2.addEdge(1, 1);
        g2.addEdge(1, 2);
        g2.addEdge(1, 3);
        g2.addEdge(1, 5);
        g2.addEdge(2, 3);
        g2.addEdge(2, 6);
        g2.addEdge(3, 1);
        g2.addEdge(4, 5);
        g2.addEdge(4, 6);
        g2.addEdge(5, 3);
        g2.addEdge(6, 3);
        g2.addEdge(6, 1);
        g2.addEdge(6, 5);
        g2.addEdge(6, 2);
    }
    
    // virtual void TearDown() {}
    
    UndirectedGraph g0;
    UndirectedGraph g1;
    UndirectedGraph g2;
};

TEST_F(UndirectedGraphTest, IsEmptyInitially) {
    EXPECT_EQ(0, g0.getNumVertex());
}

TEST_F(UndirectedGraphTest, AddVertexWorks) {
    EXPECT_EQ(6, g1.getNumVertex());
    EXPECT_EQ(1, g1.getVertex(1).getId());
    EXPECT_EQ(0, g1.getNumEdges());
    EXPECT_EQ(0, g1.getVertex(2).getDeg());
    g1.addVertex(5);
    EXPECT_EQ(6, g1.getNumVertex());
    EXPECT_EQ(6, g1.getMaxID());
}

TEST_F(UndirectedGraphTest, AddEdgesWorks) {
    g1.addEdge(1, 1);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 5);
    g1.addEdge(2, 3);
    g1.addEdge(2, 6);
    g1.addEdge(3, 1);
    g1.addEdge(4, 5);
    g1.addEdge(4, 6);
    g1.addEdge(5, 3);
    g1.addEdge(6, 3);
    g1.addEdge(6, 1);
    g1.addEdge(6, 5);
    g1.addEdge(6, 2);
    EXPECT_EQ(12, g1.getNumEdges());
    EXPECT_EQ(5, g1.getVertex(6).getDeg());
    EXPECT_EQ(5, g1.getVertex(1).getDeg());
    g1.addEdge(1, 7);
    EXPECT_EQ(12, g1.getNumEdges());
    EXPECT_EQ(5, g1.getVertex(1).getDeg());
}

TEST_F(UndirectedGraphTest, RemoveVertexWorks) {
    EXPECT_EQ(6, g2.getNumVertex());
    EXPECT_EQ(12, g2.getNumEdges());

    g2.removeVertex(1);
    EXPECT_EQ(5, g2.getNumVertex());
    EXPECT_EQ(7, g2.getNumEdges());
    
    
    g2.removeVertex(234);
    EXPECT_EQ(5, g2.getNumVertex());
    EXPECT_EQ(7, g2.getNumEdges());
}

TEST_F(UndirectedGraphTest, RemoveEdgeWorks) {
    EXPECT_EQ(6, g2.getNumVertex());
    EXPECT_EQ(12, g2.getNumEdges());
    g2.removeEdge(2, 3);
    EXPECT_EQ(11, g2.getNumEdges());
    g2.removeEdge(3,34);
    EXPECT_EQ(11, g2.getNumEdges());
}

TEST_F(UndirectedGraphTest, RightNumEdges) {
    uint64_t count;
    for (UndirectedGraph::VertexIterator vertexI = g2.begin(); vertexI != g2.end(); vertexI++) {
        count += vertexI->second.getOutDeg();
        //cout << vertexI->second.getId() << "\t" << vertexI->second.getDeg() << "\n";
    }
    EXPECT_EQ(count, g2.getNumEdges()*2); //count*2 since it is undirected. Each edge is counted twice
}

// Multiple vertex / edges manipulations
TEST(UndirectedGraphTest_2, ManipulateVertexEdges) {
    uint64_t numVertex = 1000;
    uint64_t numEdges = 10000;

    UndirectedGraph Graph;
    UndirectedGraph Graph1;
    UndirectedGraph Graph2;
    uint64_t NCount;
    uint64_t LCount;
    uint64_t from,to;
    uint64_t Deg, InDeg, OutDeg;
    
    //Empty
    EXPECT_EQ(0,Graph.getNumVertex());
    EXPECT_EQ(0,Graph.getNumEdges());
    EXPECT_EQ(0,Graph.getMaxID());
    
    // create the nodes
    for (int i = 0; i < numVertex; ++i) {
        Graph.addVertex(i);
    }
    EXPECT_EQ(numVertex,Graph.getNumVertex());
    EXPECT_EQ(0,Graph.getNumEdges());
    EXPECT_EQ(numVertex-1,Graph.getMaxID());
    
    // create random edges
    NCount = numEdges;
    LCount = 0; //Number of loops
    while (NCount > 0) {
        from = (uint64_t) (drand48() * numVertex);
        to = (uint64_t) (drand48() * numVertex);
        if (!Graph.isEdge(from,to)) {
            Graph.addEdge(from, to);
            --NCount;
            if (from == to) {
                LCount++;
            }
        }
    }
    
    EXPECT_EQ(numEdges,Graph.getNumEdges());
    
    for (int i = 0; i < numVertex; ++i) {
        EXPECT_EQ(true,Graph.isVertex(i));
    }
    
    EXPECT_EQ(false,Graph.isVertex(numVertex));
    EXPECT_EQ(false,Graph.isVertex(numVertex+1));
    EXPECT_EQ(false,Graph.isVertex(2*numVertex));
    
    // nodes iterator
    NCount = 0;
    for (UndirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
        NCount++;
    }
    EXPECT_EQ(numVertex,NCount);
    
    // edges per node iterator
    NCount = 0;
    for (UndirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
        NCount += vertexI->second.getOutDeg();
    }
    EXPECT_EQ(numEdges*2-LCount, NCount); //numEdges*2 since it is undirected. -Lcount since loops are counted once.

    
    // vertex degree
    for (UndirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
        Deg = vertexI->second.getDeg();
        InDeg = vertexI->second.getInDeg();
        OutDeg = vertexI->second.getOutDeg();
        
        EXPECT_EQ(Deg,InDeg);
        EXPECT_EQ(Deg,OutDeg);
    }
    
    // assignment
    Graph1 = Graph;
    EXPECT_EQ(numVertex,Graph1.getNumVertex());
    EXPECT_EQ(numEdges,Graph1.getNumEdges());
    
    
    // remove all the nodes and edges
    for (int i = 0; i < numVertex; ++i) {
        Graph.removeVertex(i);
        Graph1.removeVertex(i);
    }
    
    EXPECT_EQ(0,Graph.getNumVertex());
    EXPECT_EQ(0,Graph.getNumEdges());
    EXPECT_EQ(0,Graph1.getNumVertex());
    EXPECT_EQ(0,Graph1.getNumEdges());
    
}

class DirectedGraphTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        //Init g1 with 6 unnconected vertex:
        // num. vertex = 6
        // num edges = 0
        g1.addVertex(1);
        g1.addVertex(2);
        g1.addVertex(3);
        g1.addVertex(4);
        g1.addVertex(5);
        g1.addVertex(6);
        //Init g2 with some edges
        // num. vertex = 6
        // num edges = 14 (Directed=>edges btw nodes are unidirectional)
        g2.addVertex(1);
        g2.addVertex(2);
        g2.addVertex(3);
        g2.addVertex(4);
        g2.addVertex(5);
        g2.addVertex(6);
        g2.addEdge(1, 1);
        g2.addEdge(1, 2);
        g2.addEdge(1, 3);
        g2.addEdge(1, 5);
        g2.addEdge(2, 3);
        g2.addEdge(2, 6);
        g2.addEdge(3, 1);
        g2.addEdge(4, 5);
        g2.addEdge(4, 6);
        g2.addEdge(5, 3);
        g2.addEdge(6, 3);
        g2.addEdge(6, 1);
        g2.addEdge(6, 5);
        g2.addEdge(6, 2);
    }
    
    // virtual void TearDown() {}
    
    DirectedGraph g0;
    DirectedGraph g1;
    DirectedGraph g2;
};

TEST_F(DirectedGraphTest, IsEmptyInitially) {
    EXPECT_EQ(0, g0.getNumVertex());
}

TEST_F(DirectedGraphTest, AddVertexWorks) {
    EXPECT_EQ(6, g1.getNumVertex());
    EXPECT_EQ(1, g1.getVertex(1).getId());
    EXPECT_EQ(0, g1.getNumEdges());
    EXPECT_EQ(0, g1.getVertex(2).getDeg());
    EXPECT_EQ(0, g1.getVertex(2).getInDeg());
    EXPECT_EQ(0, g1.getVertex(2).getOutDeg());
    g1.addVertex(5);
    EXPECT_EQ(6, g1.getNumVertex());
    EXPECT_EQ(6, g1.getMaxID());
    g1.addVertex(8);
    EXPECT_EQ(7, g1.getNumVertex());
    EXPECT_EQ(8, g1.getMaxID());
    
}

TEST_F(DirectedGraphTest, AddEdgesWorks) {
    g1.addEdge(1, 1);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 5);
    g1.addEdge(2, 3);
    g1.addEdge(2, 6);
    g1.addEdge(3, 1);
    g1.addEdge(4, 5);
    g1.addEdge(4, 6);
    g1.addEdge(5, 3);
    g1.addEdge(6, 3);
    g1.addEdge(6, 1);
    g1.addEdge(6, 5);
    g1.addEdge(6, 2);
    EXPECT_EQ(14, g1.getNumEdges());
    EXPECT_EQ(6, g1.getVertex(6).getDeg());
    EXPECT_EQ(2, g1.getVertex(6).getInDeg());
    EXPECT_EQ(4, g1.getVertex(6).getOutDeg());
    EXPECT_EQ(7, g1.getVertex(1).getDeg());
    EXPECT_EQ(3, g1.getVertex(1).getInDeg());
    EXPECT_EQ(4, g1.getVertex(1).getOutDeg());
    g1.addEdge(1, 7);
    EXPECT_EQ(14, g1.getNumEdges());
    EXPECT_EQ(7, g1.getVertex(1).getDeg());
}

TEST_F(DirectedGraphTest, RemoveVertexWorks) {
    EXPECT_EQ(6, g2.getNumVertex());
    EXPECT_EQ(14, g2.getNumEdges());
    
    g2.removeVertex(1);
    EXPECT_EQ(5, g2.getNumVertex());
    EXPECT_EQ(8, g2.getNumEdges());
    
    g2.removeVertex(234);
    EXPECT_EQ(5, g2.getNumVertex());
    EXPECT_EQ(8, g2.getNumEdges());
}

TEST_F(DirectedGraphTest, RemoveEdgeWorks) {
    EXPECT_EQ(6, g2.getNumVertex());
    EXPECT_EQ(14, g2.getNumEdges());
    g2.removeEdge(2, 3);
    EXPECT_EQ(13, g2.getNumEdges());
    g2.removeEdge(3,34);
    EXPECT_EQ(13, g2.getNumEdges());
}

TEST_F(DirectedGraphTest, RightNumEdges) {
    uint64_t count = 0;
    for (DirectedGraph::VertexIterator vertexI = g2.begin(); vertexI != g2.end(); vertexI++) {
        count += vertexI->second.getOutDeg();
    }
    EXPECT_EQ(count, g2.getNumEdges());
}

// Test vertex, edge creation
TEST(DirectedGraphTest_2, ManipulateVertexEdges) {
    uint64_t numVertex = 10000;
    uint64_t numEdges = 100000;
    
    DirectedGraph Graph;
    DirectedGraph Graph1;
    DirectedGraph Graph2;
    uint64_t NCount;
    uint64_t LCount;
    uint64_t from,to;
    uint64_t Deg, InDeg, OutDeg;
    
    //Empty
    EXPECT_EQ(0,Graph.getNumVertex());
    EXPECT_EQ(0,Graph.getNumEdges());
    EXPECT_EQ(0,Graph.getMaxID());
    
    // create the nodes
    for (int i = 0; i < numVertex; ++i) {
        Graph.addVertex(i);
    }
    EXPECT_EQ(numVertex,Graph.getNumVertex());
    EXPECT_EQ(0,Graph.getNumEdges());
    EXPECT_EQ(numVertex-1,Graph.getMaxID());
    
    // create random edges
    NCount = numEdges;
    LCount = 0; //Number of loops
    while (NCount > 0) {
        from = (uint64_t) (drand48() * numVertex);
        to = (uint64_t) (drand48() * numVertex);
        if (!Graph.isEdge(from,to)) {
            Graph.addEdge(from, to);
            --NCount;
            if (from == to) {
                LCount++;
            }
        }
    }
    
    EXPECT_EQ(numEdges,Graph.getNumEdges());
    
    for (int i = 0; i < numVertex; ++i) {
        EXPECT_EQ(true,Graph.isVertex(i));
    }
    
    EXPECT_EQ(false,Graph.isVertex(numVertex));
    EXPECT_EQ(false,Graph.isVertex(numVertex+1));
    EXPECT_EQ(false,Graph.isVertex(2*numVertex));
    
    // nodes iterator
    NCount = 0;
    for (DirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
        NCount++;
    }
    EXPECT_EQ(numVertex,NCount);
    
    // edges per node iterator
    NCount = 0;
    for (DirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
        NCount += vertexI->second.getOutDeg();
    }
    EXPECT_EQ(numEdges, NCount);
    
    
    // vertex degree
    for (DirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
        Deg = vertexI->second.getDeg();
        InDeg = vertexI->second.getInDeg();
        OutDeg = vertexI->second.getOutDeg();
        
        EXPECT_EQ(Deg,InDeg + OutDeg);
    }
    
    // assignment
    Graph1 = Graph;
    EXPECT_EQ(numVertex,Graph1.getNumVertex());
    EXPECT_EQ(numEdges,Graph1.getNumEdges());
    
    
    // remove all the nodes and edges
    for (DirectedGraph::VertexIterator vertexI = Graph.begin(); vertexI != Graph.end(); vertexI++) {
         Graph.removeVertex(vertexI->second.getId());
    }
    for (int i = 0; i < numVertex; ++i) {
        Graph1.removeVertex(i);
    }
    
    EXPECT_EQ(0,Graph.getNumVertex());
    EXPECT_EQ(0,Graph.getNumEdges());
    EXPECT_EQ(0,Graph1.getNumVertex());
    EXPECT_EQ(0,Graph1.getNumEdges());
    
}



