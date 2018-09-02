#include <iostream>
#include <stack>

using namespace std;

#define MIN 0x8F3F'3F3F
#define MAX 0x3F3F'3F3F

struct Node {
    Node(int _k) : k(_k), left(nullptr), right(nullptr) {}
    int k;
    Node *left, *right;
};

bool isBalancedUtil(Node *node, int min, int max) {
    if (node == nullptr) {
        return true;
    }
    if (node->k < min || node->k > max) {
        cout << "fail: " << node->k << " " << min << " " << max << endl;
        return false;
    }
    return isBalancedUtil(node->left, min, node->k - 1) &&
           isBalancedUtil(node->right, node->k + 1, max);
}

bool isBalanced(Node *root) {
    return isBalancedUtil(root, MIN, MAX);
}
void test() {
    /*         5
          3         9
       2    6     4     11
    */
    Node *root = new Node(5);
    root->left = new Node(3);
    root->left->left = new Node(2);
    root->left->right = new Node(6);
    root->right = new Node(9);
    root->right->left = new Node(4);
    root->right->right = new Node(11);

    cout << isBalanced(root) << "\n";
}
int main() {
    test();
    return 0;
}
