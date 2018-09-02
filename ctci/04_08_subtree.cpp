#include <iostream>
#include <sstream>
using namespace std;

struct Tree {
    Tree(int d) : k(d), left(nullptr), right(nullptr) {}
    int k;
    Tree *left;
    Tree *right;
};

void getOrder(Tree *t, stringstream &trace) {
    if (t == nullptr) {
        trace << "X";
        return;
    }
    trace << t->k;
    getOrder(t->left, trace);
    getOrder(t->right, trace);
}
bool isSubTree1(Tree *t1, Tree *t2) {
    stringstream trace_t1;
    stringstream trace_t2;
    getOrder(t1, trace_t1);
    getOrder(t2, trace_t2);
    size_t pos = trace_t1.str().find(trace_t2.str());
    return pos == string::npos ? false : true;
}
void test() {
    /*
    t1      5
          7
        
    t2      5
               7
        
    y1         3
          1        4
            2          5
                           7
    y2          1
                    7
    */
    Tree *t1 = new Tree(5);
    t1->left = new Tree(7);
    Tree *t2 = new Tree(5);
    t2->right = new Tree(7);
    Tree *y1 = new Tree(3);
    y1->left = new Tree(1);
    y1->left->right = new Tree(2);
    y1->right = new Tree(4);
    y1->right->right = new Tree(5);
    y1->right->right->right = new Tree(7);
    Tree *y2 = new Tree(1);
    y2->right = new Tree(7);

    cout << isSubTree1(t1, t2) << endl;
    cout << isSubTree1(y1, t1) << endl;
    cout << isSubTree1(y1, t2) << endl;
    cout << isSubTree1(y1, y2) << endl;
}
int main() {
    test();
    return 0;
}
