#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// Node structure representing each element in the tree
struct Node {
    string element;
    Node* parent;
    vector<Node*> children;

    Node(const string& e) : element(e), parent(nullptr) {}
};

class Tree {
private:
    Node* rootNode;
    int size;

public:
    Tree() : rootNode(nullptr), size(0) {}

    // Returns true if the tree is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Returns the root of the tree
    Node* root() const {
        return rootNode;
    }

    // Adds the root node to the tree
    Node* addRoot(const string& e) {
        if (rootNode != nullptr) {
            throw runtime_error("Tree already has a root.");
        }
        rootNode = new Node(e);
        size = 1;
        return rootNode;
    }

    // Searches for a node by its value using DFS
    Node* find(const string& value, Node* current = nullptr) const {
        if (isEmpty()) return nullptr;
        if (current == nullptr) current = rootNode;

        if (current->element == value) {
            return current;
        }

        for (Node* child : current->children) {
            Node* result = find(value, child);
            if (result != nullptr) {
                return result;
            }
        }

        return nullptr; // Value not found
    }

    // Returns the parent of a node
    Node* parent(Node* node) const {
        return node->parent;
    }

    // Returns the children of a node
    vector<Node*> children(Node* node) const {
        return node->children;
    }

    // Returns the number of children of a node
    int numChildren(Node* node) const {
        return node->children.size();
    }

    // Adds a child to a given node
    Node* addChild(Node* parent, const string& e) {
        Node* child = new Node(e);
        child->parent = parent;
        parent->children.push_back(child);
        size++;
        return child;
    }

    // Returns true if the node is internal (has at least one child)
    bool isInternal(Node* node) const {
        return !node->children.empty();
    }

    // Returns true if the node is external (has no children)
    bool isExternal(Node* node) const {
        return node->children.empty();
    }

    // Returns true if the node is the root
    bool isRoot(Node* node) const {
        return node == rootNode;
    }

    // Traverses the tree and prints all elements (iterator simulation)
    void traverse(Node* node) const {
        if (node == nullptr) return;
        cout << node->element << " ";
        for (Node* child : node->children) {
            traverse(child);
        }
    }

    // Prints all positions (elements) in the tree
    void positions() const {
        traverse(rootNode);
        cout << endl;
    }
    int depth(Node* node){
        if(isRoot(node)) return 0;
        return 1 + depth(node->parent);
    }
    int height(Node* node){
        if (node == nullptr) return 0;
        if (isExternal(node)) return 0; // Leaf node has height 0

        int maxHeight = 0;
        for (Node* child : node->children) {
            maxHeight = max(maxHeight, height(child));
        }

        return 1 + maxHeight;
    }
};

void menu() {
    Tree tree;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Root\n";
        cout << "2. Add Child\n";
        cout << "3. Display Tree\n";
        cout << "4. Search Node\n";
        cout << "5. Check depth and height\n";
        cout << "6. Check Properties (isInternal, isExternal, isRoot)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (!tree.isEmpty()) {
                    cout << "Tree already has a root!\n";
                } else {
                    string rootValue;
                    cout << "Enter root value: ";
                    cin >> rootValue;
                    tree.addRoot(rootValue);
                    cout << "Root added.\n";
                }
                break;
            }
            case 2: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty. Add a root first.\n";
                } else {
                    string parentValue, childValue;
                    cout << "Enter parent value: ";
                    cin >> parentValue;
                    Node* parentNode = tree.find(parentValue);
                    if (parentNode) {
                        cout << "Enter child value: ";
                        cin >> childValue;
                        tree.addChild(parentNode, childValue);
                        cout << "Child added.\n";
                    } else {
                        cout << "Parent not found.\n";
                    }
                }
                break;
            }
            case 3: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "Tree elements: ";
                    tree.positions();
                }
                break;
            }
            case 4: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    string searchValue;
                    cout << "Enter value to find: ";
                    cin >> searchValue;
                    Node* foundNode = tree.find(searchValue);
                    if (foundNode) {
                        cout << "Node found: " << foundNode->element << endl;
                    } else {
                        cout << "Node not found.\n";
                    }
                }
                break;
            }
            case 5:{
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                }else {
                    string nodeValue;
                    cout << "Enter node value: ";
                    cin >> nodeValue;
                    Node* node = tree.find(nodeValue);
                    if (node) {
                        cout << "depth: " << tree.depth(node) << endl;
                        cout << "height: " << tree.height(node) << endl;
                    } else {
                        cout << "Node not found.\n";
                    }
                }
                break;
            }
            case 6: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    string nodeValue;
                    cout << "Enter node value: ";
                    cin >> nodeValue;
                    Node* node = tree.find(nodeValue);
                    if (node) {
                        cout << "Is internal: " << (tree.isInternal(node) ? "Yes" : "No") << endl;
                        cout << "Is external: " << (tree.isExternal(node) ? "Yes" : "No") << endl;
                        cout << "Is root: " << (tree.isRoot(node) ? "Yes" : "No") << endl;
                    } else {
                        cout << "Node not found.\n";
                    }
                }
                break;
            }
            case 7: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
            }
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
