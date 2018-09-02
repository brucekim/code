/* Given a binary tree, design an algorithm which creates a linked list of all the nodes at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).
*/
#include <iostream>
#include <queue>
#include <vector>
#include <list>

using namespace std;

struct Node
{
    Node(int _k) : k(_k), left(nullptr), right(nullptr) {}
    int k;
    Node *left, *right;
};
class BinaryTree
{
  public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        Release(root);
    }
    void Insert(int k)
    {
        root = InsertUtil(root, k);
    }
    void PrintLevelOrder()
    {
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *t = q.front();
            cout << t->k << " ";
            q.pop();
            if (t->left != nullptr)
            {
                q.push(t->left);
            }
            if (t->right != nullptr)
            {
                q.push(t->right);
            }
        }
    }
    void GenListsPerDepth()
    {
        queue<Node *> qu;
        queue<Node *> qv;
        int depth = 0;
        vector<list<Node *>> lists;

        qu.push(root);
        cout << "start"
             << "\n";
        while (!qu.empty())
        {
            ++depth;
            list<Node *> l;
            while (!qu.empty())
            {
                Node *t = qu.front();
                cout << t->k << " ";
                l.push_back(t);
                if (t->left != nullptr)
                {
                    qv.push(t->left);
                }
                if (t->right != nullptr)
                {
                    qv.push(t->right);
                }
                qu.pop();
            }
            cout << "\n";
            lists.push_back(l);
            while (!qv.empty())
            {
                qu.push(qv.front());
                qv.pop();
            }
        }
        cout << "depth:" << depth << endl;
        cout << "check lists" << endl;
        for (list<Node *> &it_a : lists)
        {
            list<Node *>::iterator it_b = begin(it_a);
            while (it_b != end(it_a))
            {
                cout << (*it_b)->k << " ";
                it_b++;
            }
            cout << "\n";
        }
    }

  private:
    Node *root;
    Node *InsertUtil(Node *node, int k)
    {
        if (node == nullptr)
        {
            return new Node(k);
        }
        if (k < node->k)
        {
            node->left = InsertUtil(node->left, k);
        }
        else if (node->k < k)
        {
            node->right = InsertUtil(node->right, k);
        }
        return node;
    }
    void Release(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        Release(node->left);
        Release(node->right);
        delete (node);
    }
};
void test()
{
    BinaryTree tree;
    int arr[] = {5, 3, 1, 2, 4, 7, 6, 8, 9};
    /*
                    5
               3         7
         1       4     6     8
           2                    9
    */
    for (auto &&it : arr)
    {
        tree.Insert(it);
    }
    tree.PrintLevelOrder();

    tree.GenListsPerDepth();
}
int main()
{
    test();
    return 0;
}
