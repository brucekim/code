#include <iostream>

using namespace std;

struct Node {
    Node(char _k) : k(_k), left(nullptr), right(nullptr), depth(0) {}
    char k;
    Node *left;
    Node *right;
    int depth;
};

int CheckBalance(Node *root, bool &is_balanced) {
    if (root == nullptr)
        return 0;
    int l = CheckBalance(root->left, is_balanced);
    int r = CheckBalance(root->right, is_balanced);

    cout << root->k << ":" << l << r << endl;
    if (abs(l-r) > 1) {
        cout << "violation" << endl;
        is_balanced = false;
    }
    return l < r ? r+1 : l+1;
}


void test() {
    Node *root = new Node('r');
    Node *a = new Node('a');
    Node *b = new Node('b');
    Node *c = new Node('c');
    Node *d = new Node('d');
    Node *e = new Node('e');
    Node *f = new Node('f');
    Node *g = new Node('g');

    root->left = a;
    root->right = b;
    a->left = c;
    a->right = d;
    c->left = f;
    b->left = e;

/*         r
       a      b
    c   d    e
  f
*/
    bool is_balanced = true;
    CheckBalance(root, is_balanced);
    cout << is_balanced << endl;

    f->left = g;
/*            r
           a      b
        c   d    e
      f
    g
*/
    is_balanced = true;
    CheckBalance(root, is_balanced);
    cout << is_balanced << endl;

}
int main() {
    test();
    return 0;
}