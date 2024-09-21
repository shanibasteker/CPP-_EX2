//311318075
//shanibasteker@gmail.com

#include "Tree.hpp"
#include "Complex.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace ariel;

int main() {
    // Create a binary tree of Complex numbers
    Tree<Complex> *binaryTree = new Tree<Complex>();
    binaryTree->add_root(Complex(1, 1));

    auto root = binaryTree->get_root();
    binaryTree->add_sub_node(root, Complex(2, 2));
    binaryTree->add_sub_node(root, Complex(3, 3));

    auto child1 = root->children[0];
    binaryTree->add_sub_node(child1, Complex(4, 4));
    binaryTree->add_sub_node(child1, Complex(5, 5));

    auto child2 = root->children[1];
    binaryTree->add_sub_node(child2, Complex(6, 6));
    binaryTree->add_sub_node(child2, Complex(7, 7));


    // Display the tree and BFS traversal
    std::cout << "Binary Tree (BFS Traversal):" << std::endl;
    for (auto it = binaryTree->begin_bfs(); it != binaryTree->end_bfs(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout<< "Binary Tree (DFS Traversal):" << std::endl;
    for (auto it = binaryTree->begin_dfs(); it != binaryTree->end_dfs(); ++it) {
        std::cout<< *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout << "Pre-Order Traversal:" << std::endl;
    for (auto it = binaryTree->begin_pre_order(); it != binaryTree->end_pre_order(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout<< "In-Order Traversal:" << std::endl;
    for (auto it = binaryTree->begin_in_order(); it != binaryTree->end_in_order(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout<<"\n" << std::endl;

    std::cout<< "Post-Order Traversal:" << std::endl;
    for (auto it = binaryTree->begin_post_order(); it != binaryTree->end_post_order(); ++it) {
        std::cout << *it << std::endl;
    }
    
    try {
        auto it = binaryTree->myHeap();
        std::cout << "\nMin-Heap (BFS):" << std::endl;
        int level = 0;
        int num_nodes = 1;
        int printed_nodes = 0;
        while (it != binaryTree->end_bfs()) {
            if (printed_nodes == num_nodes) {
                std::cout << std::endl;
                level++;
                num_nodes *= 2;
                printed_nodes = 0;
            }
            std::cout << *it << " ";
            ++it;
            printed_nodes++;
        }
        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << std::endl;
    Tree<int, 3>* treeK = new Tree<int, 3>();
    treeK->add_root(1);
    treeK->add_sub_node(treeK->get_root(), 11);
    treeK->add_sub_node(treeK->get_root(), 12);
    treeK->add_sub_node(treeK->get_root(), 13);
    treeK->add_sub_node(treeK->get_root()->children[0], 14);
    treeK->add_sub_node(treeK->get_root()->children[0], 15);
    treeK->add_sub_node(treeK->get_root()->children[1], 16);
    treeK->add_sub_node(treeK->get_root()->children[1], 17);
    treeK->add_sub_node(treeK->get_root()->children[2], 18);
    treeK->add_sub_node(treeK->get_root()->children[2], 19);
    treeK->add_sub_node(treeK->get_root()->children[2], 20);

    
    std::cout<<"Tree K=3 DFS - Expeced Output from Orders on K != 2"<< std::endl;
    for(auto it = treeK->begin_dfs(); it != treeK->end_dfs(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // All printing should be in the same order as the DFS iterator
    std::cout <<"Tree K=3 In-Order:"<< std::endl;
    for(auto it = treeK->begin_in_order(); it != treeK->end_in_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout<<"Tree K=3 Pre-Order:"<< std::endl;
    for(auto it = treeK->begin_pre_order(); it != treeK->end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout<<"Tree K=3 Post-Order:"<< std::endl;
    for(auto it = treeK->begin_post_order(); it != treeK->end_post_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Create a window to draw the binary tree
    sf::RenderWindow window(sf::VideoMode(800, 600), "Complex Binary-Tree Drawing");

    // Main loop to keep the window open and handle events
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the close event is triggered
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black); // Clear the window with a black color
        binaryTree->draw(window); // Draw the binary tree on the window
        window.display(); // Display the contents of the window
    }

    // Create another window to draw the tree of type Tree<int, 3>
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Tree<int, 3> Drawing");

    // Main loop to keep the second window open and handle events
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
            // Close the window if the close event is triggered
            if (event.type == sf::Event::Closed) {
                window2.close();
            }
        }

        window2.clear(sf::Color::Black); // Clear the window with a black color
        treeK->draw(window2); // Draw the Tree<int, 3> on the window
        window2.display(); // Display the contents of the window
    }
    delete binaryTree;
    delete treeK;
    return 0;
}
