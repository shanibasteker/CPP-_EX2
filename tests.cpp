//311318075
//shanibasteker@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "Tree.hpp"

TEST_CASE("Complex Number Constructor Default") {
    Complex c1;
    CHECK(c1.re() == doctest::Approx(0));
    CHECK(c1.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Constructor with Parameters") {
    Complex c1(3, 4);
    CHECK(c1.re() == doctest::Approx(3));
    CHECK(c1.im() == doctest::Approx(4));
}

TEST_CASE("Complex Number Unary Operator NOT") {
    Complex c1(0, 0);
    CHECK(!c1 == true);  // !c1 check if re == 0 and im == 0
}

TEST_CASE("Complex Number Unary Operator Minus") {
    Complex c2(3, -4);
    Complex c3 = -c2; // the operator - return new complex number with the real and imaginary parts negated
    CHECK(c3.re() == doctest::Approx(-3));
    CHECK(c3.im() == doctest::Approx(4));
}

TEST_CASE("Complex Number Binary Operator Plus") {
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3 = c1 + c2;  // return a new complex number with the real and imaginary parts added
    CHECK(c3.re() == doctest::Approx(4));
    CHECK(c3.im() == doctest::Approx(6));
}

TEST_CASE("Complex Number Binary Operator Plus Equals") {
    Complex c1(1, 2);
    Complex c2(3, 4);
    c1 += c2;  // add the real and imaginary parts of the given complex number to the current complex number
    CHECK(c1.re() == doctest::Approx(4));
    CHECK(c1.im() == doctest::Approx(6));
}

TEST_CASE("Complex Number Binary Operator Minus Equals") {
    Complex c1(4, 6);
    Complex c4(5, 6);
    c1 -= c4;  // subtract the real and imaginary parts of the given complex number from the current complex number
    CHECK(c1.re() == doctest::Approx(-1));
    CHECK(c1.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Binary Operator Multiply Equals") {
    Complex c5(1, 1);
    Complex c6(2, 2);
    c5 *= c6;  // multiply the real and imaginary parts of the given complex number from the current complex number
    CHECK(c5.re() == doctest::Approx(0));
    CHECK(c5.im() == doctest::Approx(4));
}

TEST_CASE("Complex Number Prefix Increment") {
    Complex c1(0, 0);
    ++c1;  // prefix increment - increment the real part of the complex number
    CHECK(c1.re() == doctest::Approx(1));
    CHECK(c1.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Postfix Increment") {
    Complex c2(0, 0);
    Complex c3 = c2++;  // postfix increment - return a copy of the original complex number
    CHECK(c2.re() == doctest::Approx(1));
    CHECK(c2.im() == doctest::Approx(0));
    CHECK(c3.re() == doctest::Approx(0));
    CHECK(c3.im() == doctest::Approx(0));
}

TEST_CASE("Complex Number Comparison Less Than") {
    Complex c1(3, 4); // Magnitude = 5 = sqrt(a^2 + b^2) = sqrt(3^2 + 4^2) = sqrt(9 + 16) = sqrt(25) = 5
    Complex c2(5, 12); // Magnitude = 13 = sqrt(a^2 + b^2) = sqrt(5^2 + 12^2) = sqrt(25 + 144) = sqrt(169) = 13
    CHECK(c1 < c2);
}

TEST_CASE("Complex Number Comparison Greater Than") {
    Complex c1(3, 4); // Magnitude = 5
    Complex c2(5, 12); // Magnitude = 13
    CHECK(c2 > c1);
}

TEST_CASE("Complex Number Equality") {
    Complex c1(1, 2);
    Complex c2(1, 2);
    CHECK(c1 == c2); // c1.im == c2.im && c1.re == c2.re
}

TEST_CASE("Complex Number Inequality") {
    Complex c1(1.1, 2.1);
    Complex c3(1.2, 2.2);
    CHECK(c1 != c3); // c1.im != c2.im || c1.re != c2.re
}

TEST_CASE("Complex Number Stream Output Operator") {
    std::stringstream ss;
    Complex c1(3, 4);
    ss << c1;  // using << operator - ostream
    CHECK(ss.str() == "3+4i");
}

TEST_CASE("Complex Number Stream Input Operator") {
    std::stringstream ss;
    Complex c2;
    ss.str("5-6i");
    ss >> c2;  // using >> operator - istream
    CHECK(c2.re() == doctest::Approx(5));
    CHECK(c2.im() == doctest::Approx(-6));
}

TEST_CASE("BinaryTree Constructor and Add Root") {
    ariel::Tree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
}

TEST_CASE("BinaryTree Add Sub Node") {
    ariel::Tree<int> tree;
    tree.add_root(1); 
    auto root = tree.get_root();
    CHECK_NOTHROW(tree.add_sub_node(root, 2));
    CHECK_NOTHROW(tree.add_sub_node(root, 3));
    CHECK(root->children[0]->key == 2);
    CHECK(root->children[1]->key == 3);
}

TEST_CASE("Tree Constructor and Add Root") {
    ariel::Tree<int,3> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK(tree.get_root()->key == 1);
}

TEST_CASE("Tree Add Sub Node") {
    ariel::Tree<int,3> tree;
    tree.add_root(1); 
    auto root = tree.get_root();
    CHECK_NOTHROW(tree.add_sub_node(root, 2));
    CHECK_NOTHROW(tree.add_sub_node(root, 3));
    CHECK_NOTHROW(tree.add_sub_node(root, 4));
    CHECK(root->children[0]->key == 2);
    CHECK(root->children[1]->key == 3);
    CHECK(root->children[2]->key == 4);
}

TEST_CASE("BinaryTree BFS Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 4);
    tree.add_sub_node(child1, 5);
    auto it = tree.begin_bfs();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(!(it != tree.end_bfs()));
}

TEST_CASE("Tree BFS Iterator"){
    ariel::Tree<int, 3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 5);
    tree.add_sub_node(child1, 6);
    tree.add_sub_node(child1, 7);
    auto it=tree.begin_bfs();
    CHECK(*it == 1);
    int i = 1;
    for(; it != tree.end_bfs(); ++it){
        CHECK(*it == i);
        i++;
    }
    CHECK(!(it != tree.end_bfs()));
}
TEST_CASE("BinaryTree DFS Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 4);
    tree.add_sub_node(child1, 5);
    auto it = tree.begin_dfs();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(!(it != tree.end_dfs()));
}

TEST_CASE("Tree DFS Iterator") {
    ariel::Tree<int, 3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 6);
    tree.add_sub_node(child1, 7);
    tree.add_sub_node(child1, 8);

    auto it = tree.begin_dfs();
    CHECK(*it == 1); 
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 6);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(!(it != tree.end_dfs()));
}



TEST_CASE("BinaryTree PreOrder Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 4);
    tree.add_sub_node(child1, 5);
    auto it = tree.begin_pre_order();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(!(it != tree.end_pre_order()));
}

TEST_CASE("Tree PreOrder Iterator - Need to preform DFS") {
    ariel::Tree<int, 3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 6);
    tree.add_sub_node(child1, 7);
    tree.add_sub_node(child1, 8);
    auto it = tree.begin_pre_order();
    CHECK(*it == 1); 
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 6);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(!(it != tree.end_pre_order()));
}

TEST_CASE("BinaryTree InOrder Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    auto it = tree.begin_in_order();
    CHECK(*it == 2); 
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(!(it != tree.end_in_order()));
}

TEST_CASE("Tree InOrder Iterator - Need to preform DFS") {
    ariel::Tree<int, 3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 6);
    tree.add_sub_node(child1, 7);
    tree.add_sub_node(child1, 8);
    auto it = tree.begin_in_order();
    CHECK(*it == 1); 
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 6);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(!(it != tree.end_in_order()));
}

TEST_CASE("BinaryTree PostOrder Iterator") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 4);
    tree.add_sub_node(child1, 5);
    auto it = tree.begin_post_order();
    CHECK(*it == 4); // In a binary tree, the postorder traversal visits the children first, then the root
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(!(it != tree.end_post_order()));
}

TEST_CASE("Tree PostOrder Iterator - Need to preform DFS") {
    ariel::Tree<int, 3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 6);
    tree.add_sub_node(child1, 7);
    tree.add_sub_node(child1, 8);
    auto it = tree.begin_post_order();
    CHECK(*it == 1); 
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 6);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(!(it != tree.end_post_order()));
}

TEST_CASE("BinaryTree Display") {
    ariel::Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    CHECK_NOTHROW(tree.display());
}

TEST_CASE("BinaryTree - myHeap"){
    ariel::Tree<int> tree;
    tree.add_root(2);
    auto root = tree.get_root();
    tree.add_sub_node(root, 5);
    tree.add_sub_node(root, 3);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 8);
    tree.add_sub_node(child1, 7);
    auto child2 = root->children[1];
    tree.add_sub_node(child2, 4);
    tree.add_sub_node(child2, 6);
    auto childofChild = child1->children[0];
    tree.add_sub_node(childofChild, 1);
    tree.add_sub_node(childofChild, 2);
    CHECK_NOTHROW(tree.myHeap());
    auto it = tree.myHeap();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 6);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 5);
}

TEST_CASE("Tree - myHeap"){
    ariel::Tree<int,3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(root, 2);
    tree.add_sub_node(root, 3);
    tree.add_sub_node(root, 4);
    CHECK_THROWS(tree.myHeap());
}

TEST_CASE("Tree Display") {
    ariel::Tree<int,3> tree;
    tree.add_root(1);
    auto root = tree.get_root();
    tree.add_sub_node(tree.get_root(), 2);
    tree.add_sub_node(tree.get_root(), 3);
    tree.add_sub_node(tree.get_root(), 4);
    auto child1 = root->children[0];
    tree.add_sub_node(child1, 5);
    tree.add_sub_node(child1, 6);
    tree.add_sub_node(child1, 7);
    auto child2 = root->children[1];
    tree.add_sub_node(child2, 8);
    tree.add_sub_node(child2, 9);
    tree.add_sub_node(child2, 10);
    auto child3 = root->children[2]; 
    tree.add_sub_node(child3, 11);
    tree.add_sub_node(child3, 12);
    tree.add_sub_node(child3, 13);
    CHECK_NOTHROW(tree.display());  // check No exception is thrown (display and displayHelper functions)

    sf::RenderWindow window2(sf::VideoMode(800, 600), "Tree <int, 3> Drawing");
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window2.close();
            }
        }

        window2.clear(sf::Color::Black);
        CHECK_NOTHROW(tree.draw(window2)); // check No exception is thrown (draw and drawNode and DrawArrow functions)
        window2.display();
    }
}

TEST_CASE("Binary Tree - Constructor and Destructor "){
    ariel::Tree<int>* tree = new ariel::Tree<int>();
    tree->add_root(1);
    auto root = tree->get_root();
    tree->add_sub_node(root, 2);
    tree->add_sub_node(root, 3);
    auto child1 = root->children[0];
    tree->add_sub_node(child1, 6);
    tree->add_sub_node(child1, 7);
    auto child2 = root->children[1];
    tree->add_sub_node(child2, 8);
    delete tree;    
}

TEST_CASE("Tree - Constructor and Destructor K = 3"){
    ariel::Tree<int,3>* tree = new ariel::Tree<int,3>();
    tree->add_root(1);
    auto root = tree->get_root();
    tree->add_sub_node(root, 2);
    tree->add_sub_node(root, 3);
    tree->add_sub_node(root, 4);
    auto child1 = root->children[0];
    tree->add_sub_node(child1, 6);
    tree->add_sub_node(child1, 7);
    auto child2 = root->children[1];
    tree->add_sub_node(child2, 8);
    delete tree;    
}

TEST_CASE("Tree K=2 Try insert 3 Childrens"){
    ariel::Tree<int>* tree = new ariel::Tree<int>();
    tree->add_root(1);
    auto root = tree->get_root();
    tree->add_sub_node(root, 2);
    tree->add_sub_node(root, 3);
    CHECK_THROWS(tree->add_sub_node(root, 4));
    delete tree;    
}

