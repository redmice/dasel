/**
 *  trie.hpp
 *  Created on 1/6/17
 *
 *   Copyright © 2017 Javier Garcia Visiedo. All rights reserved.
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


#ifndef trie_hpp
#define trie_hpp

#include <string>
#include <vector>
#include <stdint.h>
#include <stdint.h>
#include <cstddef>

using namespace std;

const unsigned short kAlphabetSize = 26;    //Using only lowercase english letters

//#//////////////////////////////////////////////
/// \brief Implements a trie search tree.
///
/// The trie supports only english letters, and it is not case sensitive.
/// The Trie class contains a TrieNode class representing each node in the tree
///
class Trie {
    
public:
    /// Represents a node in the trie, containing a single character in a word or prefix
    class TrieNode {
        
    public:
        /// Creates an empty trie node. To be used for the root node only
        TrieNode (): parent(nullptr), content(0), numChildren(0), wordMarker (false) {}
        //#//////////////////////////////////////////////
        ///
        /// \brief Creates a trie node for the specified character
        ///
        /// Must be used to create any regular node (i.e. not root), since
        /// the class interface does not offer any other way to set the
        /// content or pointer to the parent node.
        ///
        ///  \param letter the caracter represented by the node
        ///  \param p pointer to the parent node
        //
        TrieNode (char letter, TrieNode *p): parent(p), content(sanitizeContent(letter)), numChildren(0), wordMarker(false) {}
        /// Returns the number of direct descendants of the node
        uint8_t getNumChildren () { return numChildren; }
        /// Returns a pointer to the children representing a given letter
        TrieNode *getChild (char letter) { return children[sanitizeContent(letter) - 'a']; }
        /// Returns the letter represented by the node
        char getContent () { return content; }
        /// Indicates if the node represents the end of a whole word
        bool isWord () { return wordMarker; }
        /// Returns a TrieNode pointer to the parent node
        TrieNode *getParent () { return parent; }
        /// Insert a pointer to a new child node. The new node must have a valid conten within the allowed alphabet
        void setChild (TrieNode *newNode);
        /// Removes the pointer to a specific child
        void removeChild (char letter);
        /// Sets the value of the whole word marker
        void setWordMarker (bool flag) {wordMarker = flag;}
        
    private:
        TrieNode* parent;  ///< Pointer to the parent node
        char content;       /// letter represented by the node
        TrieNode* children[kAlphabetSize] = { nullptr };    ///< Pointers to children nodes
        uint8_t numChildren;    ///NUmber of direct descendants
        bool wordMarker;    ///< True if the node is the end of a whole word
        /// Check that the letter represented by the node fits the allowed alphabet
        char sanitizeContent (const char& letter);
    };

    /// The default constructor, creates an empty tree with just the root node
    Trie (): root(new TrieNode), dictionarySize(0) {}
    ~Trie () { deleteTrie(root); }
    ///  \brief Inserts a word in the trie
    ///
    ///  \param word Word to be inserted in the tree
    //
    void insertWord (const string& word);
    ///
    ///  \brief Removes a word from the trie
    ///
    ///  \param word Word to be removed from the tree
    //
    void removeWord (const string& word);
    
    ///
    ///  \brief Searches a word in the trie
    ///
    ///  \param word Word to search for
    ///  \param isWhole True if it should match whole words only
    ///  \return Pointer to the ending node for the word. Null if the word is not
    /// part of the trie
    //
    TrieNode *searchWord (const string& word, const bool& isWhole=true) const;
    /// Returns true if the given string is a prefix or word in the dictionary
    bool isPrefix (const string& prefix) const { return (searchWord(prefix, false) != nullptr) ? true : false; }
    /// Returns true if the given string is a word in the dictionary
    bool isWord (const string& word) const { return (searchWord(word, true) != nullptr) ? true : false; }
    ///Returns the number of whole words in the dictionary
    uint64_t getDictionarySize() {return dictionarySize;}
    
private:
    TrieNode *root;
    uint64_t dictionarySize;
    ///
    /// \brief Removes all nodes in the tree under a given node, and frees up
    /// memory by making a post order traversal
    void deleteTrie (TrieNode *node);
};


#endif /* trie_hpp */
