#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
    BST bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);
    bst.add_node(20);
    bst.add_node(15);
    bst.add_node(22);
    
    // EXPECT_EQ(bst.length(), 13);
    // EXPECT_TRUE(bst.delete_node(25)); // both children exist
    // EXPECT_EQ(bst.length(), 12);
    // EXPECT_EQ(bst.get_root()->value, 22);
    // EXPECT_EQ(bst.get_root()->left->value, 10);
    // EXPECT_EQ(bst.get_root()->left->right->right, nullptr);
    std::cout<<bst<<std::endl;
    bst.delete_node(25);
    std::cout<<bst<<std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}