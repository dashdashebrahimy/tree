#include <iostream>
#include <queue>
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

    // Pre-order traversal
    void preOrder(Node* root) const {
        if (root == nullptr) return;

        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    // Post-order traversal
    void postOrder(Node* root) const {
        if (root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->value << " ";
    }

    // In-order traversal
    void inOrder(Node* root) const {
        if (root == nullptr) return;
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }

    // Level-order traversal (Breadth-First Search)
    void levelOrder(Node* root) const {
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->value << " ";
            if (curr->left != nullptr) q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
        }
    }

    // Traverse and print tree (Pre-order traversal)
    void positions() const {
        preOrder(root);
        cout << endl;
    }

    int depth(Node* node) const {
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
        cout << "7. Pre-order Traversal\n";
        cout << "8. In-order Traversal\n";
        cout << "9. Post-order Traversal\n";
        cout << "10. Level-order Traversal\n";
        cout << "11. Exit\n";
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
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "Pre-order traversal: ";
                    tree.preOrder(tree.getRoot());
                    cout << endl;
                }
                break;
            }
            case 8: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "In-order traversal: ";
                    tree.inOrder(tree.getRoot());
                    cout << endl;
                }
                break;
            }
            case 9: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "Post-order traversal: ";
                    tree.postOrder(tree.getRoot());
                    cout << endl;
                }
                break;
            }
            case 10: {
                if (tree.isEmpty()) {
                    cout << "Tree is empty.\n";
                } else {
                    cout << "Level-order traversal: ";
                    tree.levelOrder(tree.getRoot());
                    cout << endl;
                }
                break;
            }
            case 11: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
            }
        }
    } while (choice != 11);
}

int main() {
    menu();
    return 0;
}
