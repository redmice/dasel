//
//  main.cpp
//  dasel-test: test file launching gtest unit tests
//
//  Created by Javier Garcia Visiedo on 12/30/16.
//  Copyright © 2016 Javier Garcia Visiedo. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"
#include "graph.hpp"


int main(int argc, const char * argv[]) {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
