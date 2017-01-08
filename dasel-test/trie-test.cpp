/**
 *  trie-test.cpp
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


#include "gtest/gtest.h"
#include "trie.hpp"


class TrieTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        //Init t1 with 11 words:
        // Dictionary size = 11
        t1.insertWord("hello");
        t1.insertWord("Octopus");
        t1.insertWord("Octogonal");
        t1.insertWord("ornitorrinco");
        t1.insertWord("Advice");
        t1.insertWord("files");
        t1.insertWord("file");
        t1.insertWord("Supercalifragilisticexpialidocious");
        t1.insertWord("super");
        t1.insertWord("supra");
        t1.insertWord("north");

    }
    
    // virtual void TearDown() {}
    
    Trie t0;
    Trie t1;
};

TEST_F(TrieTest, IsEmptyInitially) {
    EXPECT_EQ(0, t0.getDictionarySize());
}

TEST_F(TrieTest, insertWordsWorks) {
    EXPECT_EQ(11, t1.getDictionarySize());
    t1.insertWord("calamari");
    EXPECT_EQ(12, t1.getDictionarySize());
}

TEST_F(TrieTest, searchWorks) {
    EXPECT_EQ(true, t1.isWord("file"));
    EXPECT_EQ(true, t1.isWord("aDvIcE"));
    EXPECT_EQ(true, t1.isWord("supercalifraGILIsticexpialidocious"));
    EXPECT_EQ(true, t1.isPrefix("super"));
    EXPECT_EQ(true, t1.isPrefix("sup"));
    EXPECT_EQ(true, t1.isPrefix("ornito"));
    EXPECT_EQ(true, t1.isPrefix("no"));
    EXPECT_EQ(false, t1.isWord("friend"));
    EXPECT_EQ(false, t1.isWord("supr"));
    EXPECT_EQ(false, t1.isWord("superc"));
    EXPECT_EQ(false, t1.isPrefix("Amelia"));
    EXPECT_EQ(false, t1.isPrefix("melon"));
    EXPECT_EQ(false, t1.isPrefix("calamarido"));
    EXPECT_EQ(false, t1.isPrefix("orth"));
}

TEST_F(TrieTest, RemoveWordWorks) {
    EXPECT_EQ(true, t1.isWord("supercalifraGILIsticexpialidocious"));
    EXPECT_EQ(true, t1.isPrefix("superca"));
    EXPECT_EQ(11, t1.getDictionarySize());
    t1.removeWord("supercalifraGILIsticexpialidocious");
    EXPECT_EQ(false, t1.isWord("supercalifraGILIsticexpialidocious"));
    EXPECT_EQ(false, t1.isPrefix("superca"));
    EXPECT_EQ(true, t1.isWord("super"));
    EXPECT_EQ(true, t1.isPrefix("sup"));
    EXPECT_EQ(10, t1.getDictionarySize());
    t1.removeWord("noThere");
    EXPECT_EQ(10, t1.getDictionarySize());
}
