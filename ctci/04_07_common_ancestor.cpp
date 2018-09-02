#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Tree {
    Tree(int _k) : k(_k), left(nullptr), right(nullptr) {}
    int k;
    Tree *left, *right;
};

bool hasK(Tree *node, int k) {
    if (node == nullptr) {
        return false;
    }
    if (node->k == k) {
        return true;
    }
    return hasK(node->left, k) |
           hasK(node->right, k);
}

int findCA(Tree *root, int a, int b) {
    queue<Tree *> q;
    stack<Tree *> s;
    q.push(root);
    
    while(!q.empty()) {
        Tree *t = q.front();
        q.pop();
        s.push(t);

        if (t->left != nullptr) {
            q.push(t->left);
        }

        if (t->right!= nullptr) {
            q.push(t->right);
        }
    }

    while(!s.empty()) {
        Tree *t = s.top();
        s.pop();
        if (hasK(t, a) && hasK(t, b)) {
            return t->k;
        }
    }
    return -1;
}


void test() {
    /*        10
            2    6
        3    4
               5
    */
   Tree *root = new Tree(10);
   root->left = new Tree(2);
   root->left->left = new Tree(3);
   root->left->right = new Tree(4);
   root->left->right->right = new Tree(5);
   root->right = new Tree(6);

   cout << findCA(root, 4, 5) << endl;
   cout << findCA(root, 3, 6) << endl;
   cout << findCA(root, 3, 5) << endl;
   cout << findCA(root, 6, 6) << endl;
}

int main() {
    test();
    return 0;
}
