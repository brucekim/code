/* Write an algorithm to find the 'next' node (i.e., in-order successor) of a given node in a binary search tree. You may assume that each node has a link to its parent.
*/
#include <iostream>
using namespace std;

struct Node {
    Node(int _k) : k(_k), left(nullptr), right(nullptr), parent(nullptr) {}
    int k;
    Node *left, *right, *parent;
};

Node *minOfTree(Node *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
Node *getSuccessorUtil(Node *node) {
    if (node->right != nullptr) {
        return minOfTree(node->right);
    }
    Node *t = node->parent;
    while (t != nullptr && t->right == node) {
        node = t;
        t = node->parent;
    }
    return t;
}

Node *getSuccessor(int k, Node *root) {
    Node *t = root;
    while (t != nullptr) {
        if (k < t->k) {
            t = t->left;
        } else if (k > t->k) {
            t = t->right;
        } else {
            break;
        }
    }
    if (t == nullptr) {
        return nullptr;
    }
    return getSuccessorUtil(t);
}

void test() {
    /*             6
           3              8
        1     4        7
                 5
    */
    Node *root = new Node(6);
    root->left = new Node(3);
    root->left->parent = root;
    root->left->left = new Node(1);
    root->left->left->parent = root->left;
    root->left->right = new Node(4);
    root->left->right->parent = root->left;
    root->left->right->right = new Node(5);
    root->left->right->right->parent = root->left->right;
    root->right = new Node(8);
    root->right->parent = root;
    root->right->left = new Node(7);
    root->right->left->parent = root->right;

    Node *ans = getSuccessor(5, root);
    cout << (ans == nullptr ? -1 : ans->k) << endl;

    ans = getSuccessor(2, root);
    cout << (ans == nullptr ? -1 : ans->k) << endl;

    ans = getSuccessor(6, root);
    cout << (ans == nullptr ? -1 : ans->k) << endl;
}
int main() {
    test();
    return 0;
}
