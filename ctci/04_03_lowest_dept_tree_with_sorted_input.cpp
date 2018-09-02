/* Given a sorted (increasing order) array with unique integer elements, write an algorithm to create a binary search tree with minimal height */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    Node(int _k) : k(_k), left(nullptr), right(nullptr) {}
    int k;
    Node *left;
    Node *right;
};

class Tree
{
  public:
    Tree() : root(nullptr) {}
    void Insert(int k)
    {
        root = InsertUtil(root, k);
    }
    void PreOrder()
    {
        cout << "Preorder: ";
        int cnt = PreOrderUtil(root);
        cout << "..end(" << cnt << ")" << endl;
    }
    void LevelOrder()
    {
        cout << "Levelorder: ";
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *t = q.front();
            cout << t->k << " ";
            q.pop();
            if (t->left != nullptr)
                q.push(t->left);
            if (t->right != nullptr)
                q.push(t->right);
        }
        cout << "..end" << endl;
    }

  private:
    Node *root;
    Node *InsertUtil(Node *node, int k)
    {
        if (node == nullptr)
            return new Node(k);
        if (k < node->k)
            node->left = InsertUtil(node->left, k);
        else if (k > node->k)
            node->right = InsertUtil(node->right, k);
        return node;
    }
    int PreOrderUtil(Node *node)
    {
        if (node == nullptr)
            return 0;
        cout << node->k << " ";
        return PreOrderUtil(node->left) + PreOrderUtil(node->right) + 1;
    }
};

void BuildSmallTree(vector<int> &arr, Tree &t, int l, int r)
{
    if (l <= r)
    {
        int m = l + (r - l) / 2;
        t.Insert(arr[m]);
        if (l < m)
            BuildSmallTree(arr, t, l, m - 1);
        if (r > m)
            BuildSmallTree(arr, t, m + 1, r);
    }
}
void test()
{
    vector<int> arr;
    Tree t;
    for (int i = 1; i <= 10; i++)
    {
        arr.push_back(i);
    }
    BuildSmallTree(arr, t, 0, 9);
    t.PreOrder();
    t.LevelOrder();
    /*
    5 2 1 3 4 8 6 7 9 10 ..end(10)
                    5
                2        8
           1      3    6    9 
                    4    7    10
    */
}
int main()
{
    test();
    return 0;
}
