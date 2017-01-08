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

