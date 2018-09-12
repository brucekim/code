/*
link: https://www.acmicpc.net/problem/5639
preorder가 입력으로 주어지기 때문에 받은 그대로 root부터 구성해서 insert를 하면 원래의 bst가 만들어진다.
여기에서 postorder로 다시 출력한다.
O(n + n) = O(n)
*/
#include <iostream>
using namespace std;

struct Node {
    Node(int d) : k(d), left(nullptr), right(nullptr) {}
    int k;
    Node *left, *right;
};

class Bst {
   public:
    Bst() : root(nullptr) {}
    virtual ~Bst() {
        deleteUtil(root);
    }
    void insert(int d) {
        root = insertUtil(root, d);
    }
    void postOrder() {
        postOrderUtil(root);
    }

   private:
    Node *insertUtil(Node *node, int d) {
        if (node == nullptr) {
            return new Node(d);
        }
        if (d < node->k) {
            node->left = insertUtil(node->left, d);
        } else if (node->k < d) {
            node->right = insertUtil(node->right, d);
        }
        return node;
    }
    void deleteUtil(Node *node) {
        if (node != nullptr) {
            deleteUtil(node->left);
            deleteUtil(node->right);
            delete node;
        }
    }
    void postOrderUtil(Node *node) {
        if (node != nullptr) {
            postOrderUtil(node->left);
            postOrderUtil(node->right);
            cout << node->k << "\n";
        }
    }
    Node *root;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, d;
    Bst bst;
    for (i = 0; cin.eof() == false; ++i) {
        cin >> d;
        bst.insert(d);
    }
    bst.postOrder();

    return 0;
}
