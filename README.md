
# DASEL #

Welcome to **DASEL**, DAta Structure Educational Library.

DASEL is my personal playground, build with the ambition to learn more about different data structures and possible ways to implement them in C++.

I decided to publish the project with the ambition to support people interested on learning more about data structures and their implementation in C++.

The project is not intended to serve as a production library, at least not yet, but as a sandbox for educational purposes.

Included you can find some basic unit tests, using googletest framework, although I cannot guarantee it is totally bug free, or fully optimized code.

You are more than welcome to share your comments or suggestions, and contribute your improvements to the existing code, or add new classes supporting new data structures.


## Features ##

The current version supports the following data structures:

  * Undirected Graph: UndirectedGraph class
  * Directed Graph: DirectedGraph class
  * Trie tree: Trie class

## Platforms ##

I am not aware of any specific platform depencency, although I only tested the code under Mac OS X.

At this time, I am only distributing a .xcodeproj file to be built with Xcode. I will probably add a Makefile soon, although it should be easy for you to compile under any platform.

## Dependencies ##

DASEL is designed to have fairly minimal requirements to build. The code only use the C++11 standard library. The following is used to generate some additional targets:

   * Doxigen: Used to generate the source code documentation
   * googletest: Used to generate the dasel-test target containing some basic unit test cases

## Regenerating Source Files ##


The provided .xcodeproj file contains 2 targets
   * dasel: Depends on C++11 stl only, and comes with a basic main function generating an undirected graph from a file
   * dasel-test: Depends on the googletest framework

In addition, you can find a Doxyfile to generate the html code documentation.

### Contributing Code ###

I welcome corrections and additions of new data structures to the project. If you wish to contribute, just submit a push request to github.

Your code should contain doxigen-like comments, and as a bonus you may also want to generate some unit test cases for your added classes.

## Documentation ##

Class reference can be found at the [Dasel site](https://redmice.github.io/dasel/)
