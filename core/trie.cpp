/**
 *  trie.cpp
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


#include <exception>
#include <stdint.h>
#include "trie.hpp"

void Trie::TrieNode::setChild(TrieNode *newNode){
    if (newNode != nullptr) {
        uint8_t idx = sanitizeContent(newNode->getContent()) - 'a';
        children[idx] = newNode;
    }
}

void Trie::TrieNode::removeChild(char letter){
    uint8_t idx = sanitizeContent(letter) - 'a';
    if ( children[idx] != nullptr) {
        if ( !children[idx]->getNumChildren() ) {
            delete(children[idx]);
            children[idx] = nullptr;
        }
    }
}

char Trie::TrieNode::sanitizeContent (const char& letter) {
    char c = tolower(letter);
    if ((c < 'a') || (c >'z') ){
        throw out_of_range("TrieNode: Character out of range");
    }
    return c;
}

void Trie::deleteTrie(TrieNode *node){
    if (node == nullptr) {
        return;
    }
    for (uint8_t i=0; i < kAlphabetSize; ++i) {
        if (node->getChild(i + 'a') != nullptr) {
            deleteTrie(node->getChild(i + 'a'));
            node->removeChild(i + 'a');
        }
    }
}

void Trie::insertWord (const string& word){
    TrieNode* currentNode = root;
    TrieNode* newNode;
    for (auto c : word){
        newNode = currentNode->getChild(c);
        if ( newNode == nullptr) {
            newNode = new TrieNode (c, currentNode);
            currentNode->setChild(newNode);
        }
        currentNode = newNode;
    }
    currentNode->setWordMarker(true);
    ++dictionarySize;
}

void Trie::removeWord (const string& word) {
    TrieNode* leaf;
    if ((leaf = searchWord (word)) != nullptr) {
        leaf->setWordMarker(false);
        while ((leaf != root)){
            if (leaf->getNumChildren() || leaf->isWord()) { //Done deleting nodes
                leaf = root;
            }
            else {
                char letter = leaf->getContent();
                leaf = leaf->getParent();
                leaf->removeChild(letter);
            }
        }
        --dictionarySize;
    }
}

Trie::TrieNode* Trie::searchWord (const string& word, const bool& searchWholeWord) const {
    TrieNode * currentNode = root;
    TrieNode * nextNode;
    
    for (auto c : word){
        if ( (nextNode = currentNode->getChild(c)) == nullptr){
            return nullptr;
        }
        currentNode = nextNode;
    }
    if ((currentNode->isWord()) || (!searchWholeWord)) {
        return currentNode;
    }
    else {
        return nullptr;
    }
}

