//311318075
//shanibasteker@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <sstream>
#include <unordered_set>

namespace ariel {

    // Define the Template of Tree class (Default 2 Children per Node)
    template <typename T, size_t K = 2>
    class Tree {
    public:
        
        // Define the Node struct
        struct Node {
            T key;  // Key of the node
            Node* children[K];  // Children of the node

            Node(const T& key) : key(key) {  // Constructor for the Node
                for (size_t i = 0; i < K; ++i) {
                    children[i] = nullptr;
                }
            }
        };

        Tree(); // Constructor
        ~Tree();  // Destructor

        void add_root(const T& key);  // Add root node
        void add_sub_node(Node* parent, const T& key);  // Add sub node
        Node* get_root() const;  // Get the root node
        void display() const;  // Display the tree
        void draw(sf::RenderWindow& window) const; // Draw the tree 

        // Iterator classes
        class BFSIterator;  // Breadth First Search Iterator
        class DFSIterator;  // Depth First Search Iterator
        class PreOrderIterator;  // PreOrder Iterator
        class InOrderIterator;  // InOrder Iterator
        class PostOrderIterator;  // PostOrder Iterator

        // Member Function Declarations of the 'Tree' class template
        BFSIterator begin_bfs();  // Begin BFS Iterator
        BFSIterator end_bfs();  // End BFS Iterator
        DFSIterator begin_dfs();  // Begin DFS Iterator
        DFSIterator end_dfs();  // End DFS Iterator
        PreOrderIterator begin_pre_order();  // Begin PreOrder Iterator
        PreOrderIterator end_pre_order();  // End PreOrder Iterator
        InOrderIterator begin_in_order();  // Begin InOrder Iterator
        InOrderIterator end_in_order();  // End InOrder Iterator
        PostOrderIterator begin_post_order();  // Begin PostOrder Iterator
        PostOrderIterator end_post_order();  // End PostOrder Iterator

        // Method to transform the tree into a min-heap and return an iterator
        typename Tree<T, K>::BFSIterator myHeap(); // Transform tree into a min-heap and return iterator        
        
    private:
        Node* root;  // Root node - field

        void clear(Node* node); // Helper functions to clear the tree - delete every node in the Tree.
        
        // ******GUI -SFML******
        void displayHelper(Node* node, int indent) const; // Helper functions to display the tree
        void drawNode(sf::RenderWindow& window, Node* node, sf::Vector2f position, float angle, float distance, int depth) const; // Helper function to draw the Nodes Tree
        void drawArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end) const;  // Helper function to draw the arrow
    };

    // Define the BFSIterator class
    template <typename T, size_t K>
    class Tree<T, K>::BFSIterator {
    public:
        BFSIterator(Node* root);  // BFSIterator constructor

        // Overloaded operators
        bool operator!=(const BFSIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        BFSIterator& operator++();      // Increment operator

    private:
        std::queue<Node*> queue; // Queue to store the nodes according to BFS
    };

    // Define the DFSIterator class
    template <typename T, size_t K>
    class Tree<T, K>::DFSIterator {
    public:
        DFSIterator(Node* root);  // DFSIterator constructor
        DFSIterator(); // Default constructor
    
        // Overloaded operators
        bool operator!=(const DFSIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        DFSIterator& operator++();  // Increment operator

        std::stack<Node*> getStack() const; // Return a copy of the stack

    private:
        std::stack<Node*> stack;  // Stack to store the nodes according to DFS
    };

    // PreOrderIterator class - root, left, right
    template <typename T, size_t K>
    class Tree<T, K>::PreOrderIterator {
    public:
        PreOrderIterator(Node* root);  // PreOrderIterator constructor

        // Overloaded operators
        bool operator!=(const PreOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        PreOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes according to Pre-Order
        DFSIterator dfs;  // DFSIterator object
    };

    // InOrderIterator class - left, root, right
    template <typename T, size_t K>
    class Tree<T, K>::InOrderIterator {
    public:
        InOrderIterator(Node* root);  // InOrderIterator constructor

        // Overloaded operators
        bool operator!=(const InOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        InOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes according to InOrder
        DFSIterator dfs;  // DFSIterator object
        void pushLeft(Node* node);  // Helper function to arrange the nodes in the stack
    };

    // PostOrderIterator class - left, right, root
    template <typename T, size_t K>
    class Tree<T, K>::PostOrderIterator {
    public:
        PostOrderIterator(Node* root);  // PostOrderIterator constructor

        // Overloaded operators
        bool operator!=(const PostOrderIterator& other) const;  // Not equal operator
        const T& operator*() const;  // Dereference operator
        PostOrderIterator& operator++();  // Increment operator

    private:
        std::stack<Node*> stack;  // Stack to store the nodes
        DFSIterator dfs;  // DFSIterator object
        void pushLeft(Node* node);  // Helper function to push the left nodes to the stack

    };


    // ********** Implementations **********


    //Constructor template
    template <typename T, size_t K>
    Tree<T, K>::Tree() : root(nullptr) {}

    //Destructor template
    template <typename T, size_t K>
    Tree<T, K>::~Tree() {
        clear(root);  // Clear the tree - freeing memory
    }

    // Add root node
    template <typename T, size_t K>
    void Tree<T, K>::add_root(const T& key) {
        if (!root) {
            root = new Node(key);
        } else {
            root->key = key;
        }
    }

    // Add sub node
    template <typename T, size_t K>
    void Tree<T, K>::add_sub_node(Node* parent, const T& key) {
        if (!parent) return;

        for (size_t i = 0; i < K; ++i) {
            if (!parent->children[i]) { // Add the sub node to the first empty slot
                parent->children[i] = new Node(key);
                return;
            }
        }
        throw std::invalid_argument("No empty slot to add sub node.");
    }

    // Get the root node
    template <typename T, size_t K>
    typename Tree<T, K>::Node* Tree<T, K>::get_root() const {
        return root;
    }

    // Clear the tree - free memory
    template <typename T, size_t K>
    void Tree<T, K>::clear(Node* node) {
        if (!node) return;
        for (size_t i = 0; i < K; ++i) {
            clear(node->children[i]);  // Recursively go the the children of each node and delete each node
        }
        delete node;
    }

    // Display the tree
    template <typename T, size_t K>
    void Tree<T, K>::display() const {
        displayHelper(root, 0);
    }

    template <typename T, size_t K>
    void Tree<T, K>::displayHelper(Node* node, int indent) const {
        // Base case: if the node is null, return
        if (!node) return;
        
        // Print indentation spaces for visual structure
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        
        // Print the node's key
        std::cout << node->key << std::endl;
        
        // Recursively call displayHelper for each child of the node
        for (size_t i = 0; i < K; ++i) {
            displayHelper(node->children[i], indent + 1);
        }
    }

    // Function to draw the tree in the specified SFML window
    template <typename T, size_t K>
    void Tree<T, K>::draw(sf::RenderWindow &window) const
    {
        try {
            // Check if the tree has a root node
            if (root) {
                // Calculate the initial distance from the root to the first level of children
                float initialDistance = window.getSize().y / 3;

                // Start drawing the tree from the root node
                // The root node is positioned in the middle at the top of the window (x: window's width / 2, y: 50)
                // Angle of 90 degrees for vertical alignment
                // Initial distance for the first level of children
                drawNode(window, root, sf::Vector2f(window.getSize().x / 2, 50), 90, initialDistance, 0);
            }
        } 
        catch (const std::exception& e) {
            // Catch and print any exceptions that occur during drawing
            std::cerr << e.what() << std::endl;
        }
    }


    // Function to draw a node and its children in a GUI window using SFML
    template <typename T, size_t K>
    void Tree<T, K>::drawNode(sf::RenderWindow& window, Node* node, sf::Vector2f position, float angle, float distance, int depth) const
    {
        // Base case: if the node is null, return
        if (!node) return;

        // Create a circle shape to represent the node
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius());
        window.draw(circle);
        
        // Load the font for text rendering
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font\n";
        }
        
        // Create text to display the node's key
        sf::Text text;
        text.setFont(font);

        // Use std::ostringstream to convert the node's key to a string
        std::ostringstream oss;
        oss << node->key;
        text.setString(oss.str());

        // Set the text properties
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(position.x - circle.getRadius() / 2, position.y - circle.getRadius() / 2);
        window.draw(text);

        // Calculate new distance for the next level of child nodes
        float new_distance = distance / 1.5f;  // Reduce the distance for the next level by a factor of 1.5

        // Calculate the angle increment to evenly distribute child nodes around the parent node
        // 45 degrees divided by (K - 1) ensures that the children are evenly spread out
        float angleIncrement = 45.0f / (K - 1);  

        // Recursively draw child nodes and arrows
        for (size_t i = 0; i < K; ++i) {
            if (node->children[i]) {
                // Calculate the angle for the current child node
                // Adjusts the angle for each child node to be evenly spaced
                float childAngle = angle - (i - (K / 2.0f)) * angleIncrement;

                // Convert the angle from degrees to radians for trigonometric functions
                float rad = childAngle * 3.14159265359 / 180.0f;

                // Calculate the new position for the child node using polar coordinates
                sf::Vector2f new_position = position + sf::Vector2f(cos(rad) * distance, sin(rad) * distance);
                
                try{
                    // Draw the child node at the calculated position
                    drawNode(window, node->children[i], new_position, childAngle, new_distance, depth + 1);
                } catch (const std::exception& e) {
                    std::cerr << "Error drawing node: " << e.what() << std::endl;
                }

                try{
                    // Draw an arrow from the current node to the child node
                    drawArrow(window, position, new_position);
                } catch (const std::exception& e) {
                    std::cerr << "Error drawing arrow: " << e.what() << std::endl;
                }
            
            
            }
        }
    }

    // Function to draw an arrow between two points in a GUI window using SFML
    template <typename T, size_t K>
    void Tree<T, K>::drawArrow(sf::RenderWindow &window, sf::Vector2f start, sf::Vector2f end) const
    {
        // Draw the main line of the arrow
        sf::Vertex line[] = {
            sf::Vertex(start),
            sf::Vertex(end)
        };
        window.draw(line, 2, sf::Lines);

        // Calculate the direction vector from start to end
        sf::Vector2f direction = end - start;
        
        // Calculate the length of the direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        // Normalize the direction vector to unit length
        direction /= length;

        // Set the size of the arrowhead
        float arrowSize = 10.0f;
        
        // Calculate the points for the arrowhead
        // The arrowhead is created by taking the direction vector and adjusting it perpendicularly
        sf::Vector2f arrowPoint1 = end - direction * arrowSize + sf::Vector2f(-direction.y, direction.x) * arrowSize * 0.5f;
        sf::Vector2f arrowPoint2 = end - direction * arrowSize + sf::Vector2f(direction.y, -direction.x) * arrowSize * 0.5f;

        // Draw the arrowhead
        sf::Vertex arrowhead[] = {
            sf::Vertex(end),
            sf::Vertex(arrowPoint1),
            sf::Vertex(end),
            sf::Vertex(arrowPoint2)
        };
        window.draw(arrowhead, 4, sf::Lines);
    }

    // Define the start point of BFS - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs() {
        return BFSIterator(root);
    }

    // Define the end point of BFS - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs() {
        return BFSIterator(nullptr);
    }
    // Define the start point of DFS - being in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs() {
        return DFSIterator(root);
    }

    // Define the end of DFS - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs() {
        return DFSIterator(nullptr);
    }

    // Define the start point of PreOrder - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() {
        return PreOrderIterator(root);
    }

    // Define the end point of PreOrder - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Define the start point of InOrder - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_in_order() {
        return InOrderIterator(root);
    }

    // Define the end point of InOrder - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator Tree<T, K>::end_in_order() {
        return InOrderIterator(nullptr);
    }

    // Define the start point of PostOrder - begin in the root of the tree
    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() {
        return PostOrderIterator(root);
    }

    // Define the end of PostOrder - end when its nullptr
    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() {
        return PostOrderIterator(nullptr);
    }

// Function to insert tree data into a vector, convert it to a min-heap, rebuild the tree as a min-heap, and return a BFS iterator
/*
    Step 1: Convert the binary tree to a vector
    Step 2: Build a min-heap from the collected elements
    Step 3: Rebuild the tree as a min-heap
    Step 4: Return a BFS iterator to the minimum heap
*/
template <typename T, size_t K>
typename Tree<T, K>::BFSIterator Tree<T, K>::myHeap()
{
    // Ensure the tree is binary (i.e., each node has at most 2 children)
    if (K != 2) {
        throw std::invalid_argument("Tree is not binary");
    }

    // Step 1: Convert the binary tree to a vector
    std::vector<T> elements;
    std::queue<Node*> nodeQueue;
    
    // If the root is not null, start the BFS traversal from the root
    if (root) {
        nodeQueue.push(root);
    }
    
    // Perform BFS traversal to collect all the node keys into a vector
    while (!nodeQueue.empty()) {
        Node* current = nodeQueue.front();
        nodeQueue.pop();
        
        // Add the current node's key to the elements vector
        elements.push_back(current->key);
        
        // Add the children of the current node to the queue
        for (size_t i = 0; i < K; ++i) {
            if (current->children[i]) {
                nodeQueue.push(current->children[i]);
            }
        }
    }

    // Step 2: Build a min-heap from the collected elements
    // make_heap does not create new container just reaarange the elements in the elements container
    // using iterator begin and end, and the comparison function std::greater<T>() (check if i <= j, else swap) to create a min-heap
    std::make_heap(elements.begin(), elements.end(), std::greater<T>());

    // Step 3: Rebuild the tree as a min-heap
    std::queue<Node**> pointerQueue;
    
    // Initialize the queue with the address of the root pointer
    pointerQueue.push(&root);
    
    // Iterate through the elements in the min-heap and rebuild the tree
    for (const T& element : elements) {
        // Get the current node pointer
        Node** currentPointer = pointerQueue.front();
        pointerQueue.pop();
        
        // Create a new node with the current element and assign it to the current pointer
        *currentPointer = new Node(element);
        
        // Add the addresses of the children pointers to the queue for further processing
        pointerQueue.push(&((*currentPointer)->children[0]));
        pointerQueue.push(&((*currentPointer)->children[1]));
    }

    // Step 4: Return a BFS iterator to the minimum heap
    return this->begin_bfs();  // Return BFS iterator to the minimum heap
}


    // BFSIterator - root, left, right
    template <typename T, size_t K>
    Tree<T, K>::BFSIterator::BFSIterator(Node* root) {
        if (root) {
            queue.push(root);
        }
    }
 
    // Not equal operator - main purpose to check it != end_bfs()
    template <typename T, size_t K>
    bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
        return queue != other.queue;
    }

    // Dereference operator - return the key of the front node in the queue
    template <typename T, size_t K>
    const T& Tree<T, K>::BFSIterator::operator*() const {
        return queue.front()->key;
    }

    // Increment operator for BFSIterator
    // This operator advances the iterator to the next node in the BFS traversal
    template <typename T, size_t K>
    typename Tree<T, K>::BFSIterator& Tree<T, K>::BFSIterator::operator++() {
        Node* current = queue.front();
        queue.pop();
        
        // Push the children of the current node into the queue
        for (size_t i = 0; i < K; ++i) {
            if (current->children[i]) {
                queue.push(current->children[i]);
            }
        }
        
        // Return the iterator itself
        return *this;
    }


    // DFSIterator - Constructor
    //default constructor - used for K != 2 Cases
    //Iterator return the nodes in DFS according to the discovery time
    template <typename T, size_t K>
    Tree<T, K>::DFSIterator::DFSIterator(){}

    // Constructor
    template <typename T, size_t K>
    Tree<T, K>::DFSIterator::DFSIterator(Node* root){
        if (root) {
            stack.push(root);
        }
    }

    // Not equal operator - mostly for iterator to check if it != end_dfs()
    template <typename T, size_t K>
    bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator &other) const
    {
        return stack != other.stack;
    }

    // Dereference operator - return the key of the top node in the stack
    template <typename T, size_t K>
    const T& Tree<T, K>::DFSIterator::operator*() const {
        return stack.top()->key;
    }

    // Increment operator for DFSIterator
    // Advances the iterator to the next node in the DFS traversal
    template <typename T, size_t K>
    typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
        if (!stack.empty()) {
            Node* current = stack.top();
            stack.pop();
            
            /*
            pops the top node from the stack and pushes its children onto the stack in reverse order.
            This ensures that the leftmost children are processed first,
            maintaining the correct DFS traversal order by discovery time.
            */
            for (int i = K-1; i >= 0; --i) {
                if (current->children[i]) {
                    stack.push(current->children[i]);
                }
            }
        }
        return *this;
    }

    // getter - return a copy of the stack (we need a copy to be able to modify the stack)
    template <typename T, size_t K>
    std::stack<typename Tree<T, K>::Node*> Tree<T, K>::DFSIterator::getStack() const {
        return stack;
    }

    // PreOrderIterator - root, left, right
    template <typename T, size_t K>
    Tree<T, K>::PreOrderIterator::PreOrderIterator(Node* root) {
        if (root) {
            if(K == 2){ // if K is 2, push the root to the stack
                stack.push(root);
            }
            else{  // if K is not 2, use DFSIterator to create stack in DFS order
                dfs = DFSIterator(root);
                stack = dfs.getStack();
            }
        }
    }

    // Not equal operator - mostly for iterator to check if it != end_pre_order()
    template <typename T, size_t K>
    bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
        return stack != other.stack;
    }

    // Dereference operator - return the key of the top node in the stack
    template <typename T, size_t K>
    const T& Tree<T, K>::PreOrderIterator::operator*() const {
        return stack.top()->key;
    }

    
    // Increment operator for PreOrderIterator
    // Advances the iterator to the next node in the pre-order traversal
    template <typename T, size_t K>
    typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
        Node* current = stack.top();
        stack.pop();

        // Push children onto the stack from right to left
        // This ensures that the leftmost child is processed first and the root after that
        // This maintains the correct pre-order traversal order
        for (size_t i = K; i-- > 0;) {
            if (current->children[i]) {
                stack.push(current->children[i]);
            }
        }
        return *this;
    }


    // InOrderIterator - left, root, right
    template <typename T, size_t K>
    Tree<T, K>::InOrderIterator::InOrderIterator(Node* root) {
        if(root){
            if(K == 2){
                pushLeft(root);  // init the stack with the left nodes
            }
            else{  // if K is not 2, use DFSIterator to create stack in DFS order
                dfs = DFSIterator(root);
                stack = dfs.getStack();
            }
        }
    }

    //Not equal operator - mostly for iterator to check if it != end_in_order()
    template <typename T, size_t K>
    bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) const {
        return stack != other.stack;
    }
    
    //Dereference operator - return the key of the top node in the stack
    template <typename T, size_t K>
    const T& Tree<T, K>::InOrderIterator::operator*() const {
        return stack.top()->key;
    }

    // Increment operator for InOrderIterator
    template <typename T, size_t K>
    typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
        if (K == 2) {  // Binary-Tree case
            Node* current = stack.top();
            stack.pop();  //popping the current node from the stack and then calling pushLeft on its right child
            pushLeft(current->children[1]);  // traverses to the leftmost node of the right child, pushing all nodes along the way onto the stack.
        } else {  
            ++dfs;
            stack = dfs.getStack();
        }
        return *this;
    }

    // Helper function to push the leftmost nodes onto the stack
    template <typename T, size_t K>
    void Tree<T, K>::InOrderIterator::pushLeft(Node* node) {
        // Traverse to the leftmost node and push all nodes onto the stack on the way, ensures the correct InOrder traversal order
        while (node) {
            stack.push(node);
            node = node->children[0];  // Traverse to the leftmost node
        }
    }


    // PostOrderIterator - left, right, root
    template <typename T, size_t K>
    Tree<T, K>::PostOrderIterator::PostOrderIterator(Node* root) {
        if(root){
            if(K == 2){ // if K is 2, run pushLeft to create stack in post-order
                pushLeft(root);  //calling to pushLeft to create stack in post-order traversal
            
            }else{  // if K is not 2, use DFSIterator to create stack in DFS order
                dfs = DFSIterator(root);
                stack = dfs.getStack();
            }
        }
    }

    // Not equal operator - mostly for iterator to check if it != end_post_order()
    template <typename T, size_t K>
    bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
        return stack != other.stack;
    }

    // Dereference operator - return the key of the top node in the stack
    template <typename T, size_t K>
    const T& Tree<T, K>::PostOrderIterator::operator*() const {
        return stack.top()->key;
    }

    // Increment operator for PostOrderIterator
    // Advances the iterator to the next node in the post-order traversal
    template <typename T, size_t K>
    typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
        if (K == 2) {
            stack.pop(); // Pop the top node from the stack for binary trees
        } else {
            ++dfs; // Advance the DFS iterator for non-binary trees
            stack = dfs.getStack(); // Update the stack with the current DFS state
        }
        return *this;
    }

    // Helper function to push nodes onto the stack in post-order
    template <typename T, size_t K>
    void Tree<T, K>::PostOrderIterator::pushLeft(Node* node) {
        std::stack<Node*> tempStack;  // Temporary stack to store the nodes
        tempStack.push(node); // Start with the given node
        
        // Get the first node and push its children onto the temporary stack
        // This ensures that the children are processed before the parent
        // more specific the next iteration will be the root being pushed to the stack and iterate over its children
        // adding its children from left to right to the stack and repeat the process
        // so when using pop the opposite order will be maintained (left, right, root)
        while (!tempStack.empty()) {
            Node* current = tempStack.top();
            tempStack.pop();
            stack.push(current); // Push the current node onto the stack

            // Push children of the current node onto the temporary stack
            for (size_t i = 0; i < K; ++i) {
                if (current->children[i]) {
                    tempStack.push(current->children[i]);
                }
            }
        }
    }

} 


#endif 
