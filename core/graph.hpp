/**
 * graph.hpp
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

#ifndef digraph_graph_h
#define digraph_graph_h

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdint.h>

using namespace std;

//#//////////////////////////////////////////////
/// \brief Implements an undirected graph. It contains a vertex class and an iterator
///
/// Each vertex in the undirected graph contains the adjacency
/// list. The adjacency list is implemented as a vector, and the vertex contains no
/// information but the vertex ID.
///
/// The list of vertex is maintained as an associative array, using C++
/// stl unordered_map, containing pairs of <vertex_ID, vertex>.
/// A C++ unordered_map uses a hash function over the ID, typically allowing O(1)
/// search.
///
class UndirectedGraph {
public:
    //#//////////////////////////////////////////////
    /// \brief Vertex class for an undirected graph.
    ///
    /// Contains the adjacency list, and vertex ID. It is up to the user to
    /// maintain a data structure mapping the
    /// IDs to any additional content.
    //ToDo: Convert into a template to hold content data of any type
    class Vertex{
        uint64_t id;     // Vertex ID
        vector<uint64_t> adjList;   // Adjacency list
        bool visited;   // Visited flag. Used by graph search algorithms

    public:
        /// Default constructor
        Vertex () : id (0), visited(false) { }
        ///Create a vertex with id = vID
        Vertex (const uint64_t& vID) : id (vID), visited(false) { }
        ///Copy constructor
        Vertex (const Vertex& copyVertex) : id (copyVertex.id), adjList(copyVertex.adjList), visited(copyVertex.visited) { }
        ///Access method for the vertex ID
        uint64_t getId () const {return id;}
        ///Returns the visited state for the vertex
        bool isVisited () const {return visited;}
        ///Sets the visited state of the vertex to "state"
        void setVisited (const bool& state) {visited = state;}
        ///Get the degree of the vertex
        uint64_t getDeg() const { return adjList.size(); }
        ///Gets the in-degree of the vertex (equal to the degree for an undirected graph
        uint64_t getInDeg() const { return getDeg(); }
        ///Gets the out-degree of the vertex (equal to the degree for an undirected graph
        uint64_t getOutDeg() const { return getDeg(); }
        ///Returns true if the vertex with the given ID is adjacent
        bool isAdjacent (const uint64_t& vID) const { return binary_search(adjList.begin(), adjList.end(), vID); }
        ///Returns the adjacent vertex ID in the given position of the adjacency list
        uint64_t getAdjID (const uint64_t& pos) const { return adjList[pos]; }
        ///Adds an edge to the given vertex ID by adding a new element to the adjacency list
        void addAdjacent (const uint64_t& vID);
        ///Removes edge to the given vertex ID from the adjacency list
        void removeAdjacent (const uint64_t&vID);
        friend class UndirectedGraph;
    };
    //#//////////////////////////////////////////////
    /// Vertex iterator. Only suports forward iteration (++ operator)
    class VertexIterator {
        typedef unordered_map<uint64_t, Vertex>::iterator TMapIter;
        TMapIter vIter;  // Vertex iterator
    public:
        ///Default constructor
        VertexIterator() : vIter() { };
        ///Construct a new iterator object from a
        VertexIterator(const TMapIter& iter) : vIter(iter) { };
        ///Copy constructor
        VertexIterator(const VertexIterator& vIt) : vIter(vIt.vIter) { };
        /// Asignment operator
        VertexIterator& operator = (const VertexIterator& vIt) { vIter = vIt.vIter; return *this; }
        /// Increment operator
        VertexIterator& operator++ (int) { vIter++; return *this; }
        /// Equal comparison operator
        bool operator == (const VertexIterator& vIt) const { return vIter == vIt.vIter; }
        /// Not equal comparison operator
        bool operator != (const VertexIterator& vIt) const { return vIter != vIt.vIter; }
        pair<const uint64_t,Vertex>& operator* () {return *vIter;}
        pair<const uint64_t, Vertex>* operator-> () {return &*vIter;}
        friend class UndirectedGraph;
        };
    
    
private:
    unordered_map<uint64_t, Vertex> vertexList; ///Hash table containing all vertex in the graph
    uint64_t numEdges;  ///Total number of edges in the graph
    uint64_t maxID;     ///Bigger than any vertex ID in the graph
public:
    //#//////////////////////////////////////////////
    // Constructors
    UndirectedGraph (): vertexList(), numEdges(0), maxID(0) { }
    ///Copy constructor
    UndirectedGraph (const UndirectedGraph& uGraph): vertexList (uGraph.vertexList), numEdges (uGraph.numEdges), maxID(uGraph.maxID) { }
    ///Constructor that reserves memory for "n" number of vertex
    UndirectedGraph (const uint64_t& n) : numEdges(0), maxID(0) {vertexList.reserve(n);}
    //#//////////////////////////////////////////////
    // Operators
    ///Asignment operator
    UndirectedGraph& operator = (const UndirectedGraph& uGraph) {
        if (&uGraph != this) {vertexList = uGraph.vertexList; numEdges = uGraph.numEdges; maxID = uGraph.maxID;} return *this;}
    //#//////////////////////////////////////////////
    // Access & Modifiers
    ///Return true if there is a vertex with the given ID
    bool isVertex (const uint64_t& id) const {return vertexList.count(id);}
    ///Returns true if there is an edge between the 2 vertex passed as parameters
    bool isEdge (const uint64_t& fromID, const uint64_t& toID);
    ///Returns the number of vertex in the graph
    size_t getNumVertex () const { return vertexList.size();}
    ///Returns the number of edges in the graph
    uint64_t getNumEdges () const { return numEdges;}
    ///Returns a reference to a vertex with the provided vertex ID if the vertex
    ///exists in the graph. Otherwise a new vertex is added to the graph with
    ///the provided ID, using its default constructor.
    // ToDo: Find alternative that returns something indicating it does not exists
    // instead of adding a new element
    Vertex& getVertex(const uint64_t& vID) { return addVertex(vID); }
    ///Adds a vertex to the graph with the given ID if the vertex does not exist
    /// and returns a reference to the vertex
    Vertex& addVertex(const uint64_t& newID);
    ///Removes a vertex from the graph with the given ID. Removes all edges pointing to the vertex
    void removeVertex(const uint64_t& id);
    ///Adds an edge between 2 vertex in the graph
    void addEdge (const uint64_t& from, const uint64_t& to);
    ///Removes an edge between 2 vertex in the graph
    void removeEdge (const uint64_t& from, const uint64_t& to);
    /// Returns a vertex iterator to the first node - unordered_map<uint64_t, vertex>
    /// pair - in the graph
    VertexIterator begin()  { return VertexIterator(vertexList.begin()); }
    /// Returns an iterator referring to the past-the-end vertex -
    /// unordered_map<uint64_t, vertex> pair - in the graph.
    VertexIterator end() { return VertexIterator(vertexList.end()); }
    /// Returns an iterator referring to the vertex of ID vId in the graph.
    VertexIterator getVertexI(const uint64_t& vId) { return VertexIterator(vertexList.find(vId)); }
    ///Removes the visited flag from all vertex in the graph
    void clearVisited();
    /// Returns a uint64_t which is equal or bigger to the biggest vertex ID in
    /// the graph
    uint64_t getMaxID () { return maxID;}
    //#//////////////////////////////////////////////
    // Search
    ///Uses a Depth-first traversal to print the connections for a vertex to std_out, up to the specified depth
    void printGraph (const uint64_t& root, const uint8_t& depth);
    void printDFS (Vertex& v, const uint8_t& depth, const uint8_t& level);
    ///Returns the distance between 2 vertex, using a Breath-first traversal
    int16_t distance (const uint64_t& from, const uint64_t& to);
    
    // ToDo:
    //  * Save method: saves graph to a file formatted: 2 columns fromID<space>toID
    //  * Constructor building the graph from a stream
    //  * addVertex() method with initial edge list
    
};


//#//////////////////////////////////////////////
/// \brief Implements a directed graph. It contains a vertex class and a vertex iterator
///
/// Each vertex in the directed graph contains the adjacency
/// list, and additionaly a list with income connections.
/// Both lists are implemented as vectors, and the vertex contains no
/// information but the vertex ID.
///
/// The list of vertex is maintained as an associative array, using C++
/// stl unordered_map, containing pairs of <vertex_ID, vertex>.
/// A C++ unordered_map uses a hash function over the ID, typically allowing O(1)
/// search.
///
class DirectedGraph {
public:
    //#//////////////////////////////////////////////
    /// \brief Vertex class for a directed graph.
    ///
    /// Contains the adjacency list, both for in and out connections, and
    /// vertex ID. It is up to the user to
    /// maintain a data structure mapping the
    /// IDs to any additional content.
    //ToDo: Convert into a templete to hold content data of any type
    class Vertex{
        uint64_t id;     /// Vertex ID
        vector<uint64_t> adjList;   // Adjacency list
        vector<uint64_t> inAdjList; // In connection list
        bool visited;   // Visited flag. Used by graph search algorithms
        
    public:
        Vertex () : id (0), visited(false) { }
        ///Create a vertex with id = vID
        Vertex (const uint64_t& vID) : id (vID), visited(false) { }
        ///Copy constructor
        Vertex (const Vertex& copyVertex) : id (copyVertex.id), adjList(copyVertex.adjList), inAdjList(copyVertex.inAdjList), visited(copyVertex.id) { }
        ///Access method for the vertex ID
        uint64_t getId () const {return id;}
        ///Returns the visited state for the vertex
        bool isVisited () const {return visited;}
        ///Sets the visited state of the vertex to "state"
        void setVisited (const bool& state) {visited = state;}
        ///Get the output degree of the vertex
        uint16_t getOutDeg() const {return adjList.size();}
        ///Get the input degree of the vertex
        uint16_t getInDeg() const {return inAdjList.size();}
        ///Get the degree of the vertex
        uint64_t getDeg() const { return getInDeg() + getOutDeg();}
        ///Returns true if the vertex with the given ID is an input connection to the current vertex
        bool isInEdge (const uint16_t& vID) const { return binary_search(inAdjList.begin(), inAdjList.end(), vID); }
        ///Returns true if the vertex with the given ID is adjacent
        bool isOutEdge (const uint64_t& vID) const { return binary_search(adjList.begin(), adjList.end(), vID); }
        ///Returns the adjacent vertex ID in the given position of the adjacency list
        uint64_t getOutAdjID (const uint64_t& pos) const { return adjList[pos]; }
        ///Returns the adjacent vertex ID in the given position of the adjacency list
        uint64_t getInAdjID (const uint64_t& pos) const { return inAdjList[pos]; }
        ///Adds an edge to the given vertex ID by adding a new element to the adjacency list
        void addOutEdge (const uint64_t& vID);
        ///Removes edge to the given vertex ID from the adjacency list
        void removeOutEdge (const uint64_t&vID);
        ///Adds an input edge from the given vertex ID by adding a new element to the in adjacency list
        void addInEdge (const uint64_t& vID);
        ///Removes an input edge to the given vertex ID from the in adjacency list
        void removeInEdge (const uint64_t&vID);
        friend class DirectedGraph;
    };
    //#//////////////////////////////////////////////
    /// Vertex iterator. Only suports forward iteration (++ operator)
    class VertexIterator {
        typedef unordered_map<uint64_t, Vertex>::iterator TMapIter;
        TMapIter vIter;  ///Vertex iterator
    public:
        ///Default constructor
        VertexIterator() : vIter() { };
        VertexIterator(const TMapIter& iter) : vIter(iter) { };
        ///Copy constructor
        VertexIterator(const VertexIterator& vIt) : vIter(vIt.vIter) { };
        /// Asignment operator
        VertexIterator& operator = (const VertexIterator& vIt) { vIter = vIt.vIter; return *this; }
        /// Increment operator
        VertexIterator& operator++ (int) { vIter++; return *this; }
        /// Equal comparison operator
        bool operator == (const VertexIterator& vIt) const { return vIter == vIt.vIter; }
        /// Not equal comparison operator
        bool operator != (const VertexIterator& vIt) const { return vIter != vIt.vIter; }
        pair<const uint64_t,Vertex>& operator* () {return *vIter;}
        pair<const uint64_t, Vertex>* operator-> () {return &*vIter;}
        friend class DirectedGraph;
    };
    
    
private:
    unordered_map<uint64_t, Vertex> vertexList; ///Hash table containing all vertex in the graph
    uint64_t numEdges;  ///Total number of edges in the graph
    uint64_t maxID;     ///Bigger than any vertex ID in the graph
public:
    //#//////////////////////////////////////////////
    // Constructors
    /// Default constructor
    DirectedGraph (): vertexList(), numEdges(0), maxID(0) { }
    ///Copy constructor
    DirectedGraph (const DirectedGraph& dGraph): vertexList (dGraph.vertexList), numEdges (dGraph.numEdges), maxID(dGraph.maxID) { }
    ///Constructor that reserves memory for "n" number of vertex
    DirectedGraph (const uint64_t& n) : numEdges(0), maxID(0) {vertexList.reserve(n);}
    //#//////////////////////////////////////////////
    // Operators
    ///Asignment operator
    DirectedGraph& operator = (const DirectedGraph& dGraph) {
        if (&dGraph != this) {vertexList = dGraph.vertexList; numEdges = dGraph.numEdges; maxID = dGraph.maxID;} return *this;}
    //#//////////////////////////////////////////////
    // Access & Modifiers
    ///Return true if there is a vertex with the given ID
    bool isVertex (const uint64_t& id) const {return vertexList.count(id);}
    ///Returns true if there is an edge between the 2 vertex passed as parameters
    bool isEdge (const uint64_t& fromID, const uint64_t& toID);
    ///Returns the number of vertex in the graph
    size_t getNumVertex () const { return vertexList.size();}
    ///Returns the number of edges in the graph
    uint64_t getNumEdges () const { return numEdges;}
    ///Returns a reference to a vertex with the provided vertex ID if the vertex
    ///exists in the graph. Otherwise a new vertex is added to the graph with
    ///the provided ID, using its default constructor.
    // ToDo: Find alternative that returns something indicating it does not exists
    // instead of adding a new element
    Vertex& getVertex(const uint64_t& vID) { return addVertex(vID); }
    ///Adds a vertex to the graph with the given ID if the vertex does not exist
    /// and returns a reference to the vertex
    Vertex& addVertex(const uint64_t& newID);
    ///Removes a vertex from the graph with the given ID. Removes all edges pointing to the vertex
    void removeVertex(const uint64_t& id);
    ///Adds an edge between 2 vertex in the graph
    void addEdge (const uint64_t& from, const uint64_t& to);
    ///Removes an edge between 2 vertex in the graph
    void removeEdge (const uint64_t& from, const uint64_t& to);
    /// Returns a vertex iterator to the first node - unordered_map<uint64_t, vertex>
    /// pair - in the graph
    VertexIterator begin()  { return VertexIterator(vertexList.begin()); }
    /// Returns an iterator referring to the past-the-end vertex -
    /// unordered_map<uint64_t, vertex> pair - in the graph.
    VertexIterator end() { return VertexIterator(vertexList.end()); }
    /// Returns an iterator referring to the vertex of ID vId in the graph.
    VertexIterator getVertexI(const uint64_t& vId) { return VertexIterator(vertexList.find(vId)); }
    ///Removes the visited flag from all vertex in the graph
    void clearVisited();
    /// Returns a uint64_t which is equal or bigger to the biggest vertex ID in
    /// the graph
    uint64_t getMaxID () { return maxID;}
    //#//////////////////////////////////////////////
    // Search
    ///Uses a Depth-first traversal to print the connections for a vertex to std_out, up to the specified depth
    void printGraph (const uint64_t& root, const uint8_t& depth);
    void printDFS (Vertex& v, const uint8_t& depth, const uint8_t& level=0);
    ///Returns the distance between 2 vertex, using a Breath-first traversal
    int16_t distance (const uint64_t& from, const uint64_t& to);
    
    // ToDo:
    //  * Save method: saves graph to a file formatted: 2 columns fromID<space>toID
    //  * Constructor building the graph from a stream
    //  * addVertex() method with initial edge list
    
};


#endif /* digraph_graph_h */
