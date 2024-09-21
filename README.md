Tree Data Structure & Complex Numbers with SFML GUI
This repository provides a C++ implementation of a general tree data structure and operations on complex numbers. It supports various tree traversal methods and allows graphical visualization of the tree using the SFML library. Additionally, a custom Complex class offers arithmetic and comparison operations.

Features
Tree Data Structure
Flexible Structure: Supports any number of children per node (binary tree by default with 2 children).
Traversal Methods: Implements Breadth-First Search (BFS), Depth-First Search (DFS), PreOrder, InOrder, and PostOrder traversal.
Heap Transformation: Can transform the tree into a min-heap.
Visualization: Displays the tree structure using the SFML library.
Complex Number Class
Arithmetic Operations: Supports addition, subtraction, and multiplication.
Comparison Operators: Implements equality, inequality, less than, and greater than.
Stream Support: Provides input/output stream operators for easy interaction with the class.
Dependencies
SFML Library: Required for tree visualization.
C++ Standard Libraries: Includes <iostream>, <vector>, <queue>, <stack>, <cmath>, <functional>, <sstream>, and <unordered_set>.
Usage
Example - Tree Template with Complex Numbers and SFML GUI
cpp
Copy code
#include "Tree.hpp"
#include "Complex.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace ariel;

int main() {
    // Create a binary tree of Complex numbers
    Tree<Complex> binaryTree;
    binaryTree.add_root(Complex(1, 1));

    auto root = binaryTree.get_root();
    binaryTree.add_sub_node(root, Complex(2, 2));
    binaryTree.add_sub_node(root, Complex(3, 3));

    auto child1 = root->children[0];
    binaryTree.add_sub_node(child1, Complex(4, 4));
    binaryTree.add_sub_node(child1, Complex(5, 5));

    auto child2 = root->children[1];
    binaryTree.add_sub_node(child2, Complex(6, 6));
    binaryTree.add_sub_node(child2, Complex(7, 7));

    // Convert the tree to a min-heap and get a BFS iterator
    try {
        auto it = binaryTree.myHeap();
        std::cout << "\nMin-Heap (BFS):";
        for (; it != binaryTree.end_bfs(); ++it) {
            std::cout << " " << *it;
        }
        std::cout << "\n" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    // Display the tree and BFS traversal
    std::cout << "Binary Tree (BFS Traversal):" << std::endl;
    for (auto it = binaryTree.begin_bfs(); it != binaryTree.end_bfs(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "\n" << std::endl;

    // Display other traversal methods similarly...

    // Create a window to draw the tree
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tree Drawing");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        binaryTree.draw(window);
        window.display();
    }

    return 0;
}
Installation and Compilation
Step 1: Install SFML
You can install SFML on Linux with the following command:

bash
Copy code
sudo apt-get install libsfml-dev
Step 2: Clone the Repository
bash
Copy code
git clone https://github.com/shanibasteker/CPP_EX2
cd GraphTemplate-GUI-SFML
Step 3: Compile the Code
Use the provided Makefile to compile the project.

bash
Copy code
make all
This will build both the main program and the tests.

Step 4: Run the Program
After successful compilation, you can run the application using:

bash
Copy code
./main
To run the tests:

bash
Copy code
./tests
Makefile
The project is built using the following Makefile:

makefile
Copy code
# Variables
CXX = g++
# With Coverage flags
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target
TARGET = main

# Object files
OBJS = Complex.o main.o

TEST_OBJ = tests.o

# Rules
all: $(TARGET) tests

tree: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

tests: Complex.o tests.o
	$(CXX) Complex.o tests.o -o tests $(LDFLAGS)

Complex.o: Complex.cpp Complex.hpp
	$(CXX) -c Complex.cpp -o Complex.o $(CXXFLAGS)

Demo.o: Demo.cpp Tree.hpp Complex.hpp
	$(CXX) -c Demo.cpp -o Demo.o $(CXXFLAGS)

tests.o: tests.cpp Tree.hpp Complex.hpp
	$(CXX) -c tests.cpp -o tests.o $(CXXFLAGS)

# Phony targets
.PHONY: clean all tests coverage html_report

clean:
	rm -f $(OBJS) $(TARGET) tests.o tests *.gcno *.gcda *.gcov coverage.info
	rm -rf out

coverage: all
	./$(TARGET)
	@gcov $(SRCS)

html_report: coverage
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
License
This project is open-source and available under the MIT License.

