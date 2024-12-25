#include <iostream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(const string& v) : value(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;
    int size;

public:
    BinaryTree() : root(nullptr), size(0) {}

    bool isEmpty() const {
        return size == 0;
    }

    Node* getRoot() const {
        return root;
    }

    Node* addRoot(const string& v) {
        if (root != nullptr) {
            throw runtime_error("Tree already has a root.");
        }
        root = new Node(v);
        size = 1;
        return root;
    }

    Node* find(const string& value, Node* current = nullptr) const {
        if (isEmpty()) return nullptr;
        if (current == nullptr) current = root;

        if (current->value == value) {
            return current;
        }

        Node* result = find(value, current->left);
        if (result != nullptr) return result;

        return find(value, current->right);
    }

    Node* parent(Node* node, Node* current = nullptr) const {
        if (isEmpty()) return nullptr;
        if (current == nullptr) current = root;
        if ((current->left == node || current->right == node)) {
            return current;
        }
        Node* result = parent(node, current->left);
        if (result != nullptr) return result;

        return parent(node, current->right);
    }


    Node* leftChild(Node* node) const {
        return node->left;
    }

    Node* rightChild(Node* node) const {
        return node->right;
    }

    void addLeftChild(Node* parent, const string& v) {
        if (parent->left != nullptr) {
            throw runtime_error("Left child already exists.");
        }
        parent->left = new Node(v);
        size++;
    }

    void addRightChild(Node* parent, const string& v) {
        if (parent->right != nullptr) {
            throw runtime_error("Right child already exists.");
        }
        parent->right = new Node(v);
        size++;
    }

    void traverse(Node* node) const {
        if (node == nullptr) return;
        cout << node->value << " ";
        traverse(node->left);
        traverse(node->right);
    }

    void positions() const {
        traverse(root);
        cout << endl;
    }

    int depth(Node* node) const {
        // Find the depth recursively by traversing the parent nodes.
        int depth = 0;
        Node* current = root;
        while (current != nullptr && current->value != node->value) {
            if (node->value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
            depth++;
        }
        return depth;
    }

    int height(Node* node) const {
        if (node == nullptr) return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return max(leftHeight, rightHeight) + 1;
    }
};

void menu() {
    BinaryTree tree;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Root\n";
        cout << "2. Add Left Child\n";
        cout << "3. Add Right Child\n";
        cout << "4. Display Tree\n";
        cout << "5. Search Node\n";
        cout << "6. Check Depth and Height\n";
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
                    string parentValue, leftChildValue;
                    cout << "Enter parent value: ";
                    cin >> parentValue;
                    Node* parentNode = tree.find(parentValue);
                    if (parentNode) {
                        cout << "Enter left child value: ";
                        cin >> leftChildValue;
                        tree.addLeftChild(parentNode, leftChildValue);
                        cout << "Left child added.\n";
                    } else {
                        cout << "Parent not found.\n";
                    }
                }
                break;
            }
            case 3: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty. Add a root first.\n";
                } else {
                    string parentValue, rightChildValue;
                    cout << "Enter parent value: ";
                    cin >> parentValue;
                    Node* parentNode = tree.find(parentValue);
                    if (parentNode) {
                        cout << "Enter right child value: ";
                        cin >> rightChildValue;
                        tree.addRightChild(parentNode, rightChildValue);
                        cout << "Right child added.\n";
                    } else {
                        cout << "Parent not found.\n";
                    }
                }
                break;
            }
            case 4: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "Tree elements: ";
                    tree.positions();
                }
                break;
            }
            case 5: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    string searchValue;
                    cout << "Enter value to find: ";
                    cin >> searchValue;
                    Node* foundNode = tree.find(searchValue);
                    if (foundNode) {
                        cout << "Node found: " << foundNode->value << endl;
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
                        cout << "Depth: " << tree.depth(node) << endl;
                        cout << "Height: " << tree.height(node) << endl;
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
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
