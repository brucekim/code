/* 4.9(12) Paths with Sum: You are given a binary tree in which each node contains an integer value (which might be positive or negative). Design an algorithm to count the number of path that sum to a given value. The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes). */
#include <iostream>
using namespace std;

struct Tree {
    Tree(int d) : v(d), left(nullptr), right(nullptr) {}
    int v;
    Tree *left, *right;
};
int pathWithSumFromNode(Tree *node, int target_sum, int acc_sum) {
    if (node == nullptr) {
        return 0;
    }
    acc_sum += node->v;
    int total_cnt = 0;
    if (target_sum == acc_sum) {
        ++total_cnt;
    }
    total_cnt += pathWithSumFromNode(node->left, target_sum, acc_sum);
    total_cnt += pathWithSumFromNode(node->right, target_sum, acc_sum);
    return total_cnt;
}

int pathWithSum(Tree *node, int target_sum) {
    if (node == nullptr) {
        return 0;
    }
    int cnt_at_node = pathWithSumFromNode(node, target_sum, 0);
    int cnt_at_left = pathWithSum(node->left, target_sum);
    int cnt_at_right = pathWithSum(node->right, target_sum);

    return cnt_at_node + cnt_at_left + cnt_at_right;
}
void test() {
    Tree *root = new Tree(4);
    root->left = new Tree(1);
    root->left->left = new Tree(2);
    root->left->right = new Tree(-3);
    root->left->left->right = new Tree(1);
    root->left->left->right->right = new Tree(-1);
    root->right = new Tree(10);
    root->right->left = new Tree(-12);
    root->right->right = new Tree(2);
    /*
                     4
               1           10
           2      -3    -12    2
            1
              -1

        target = 2
        4 1 -3
        4 10 -12
        2
        2 1 -1
        2
        total 5
    */
    int target = 2;
    cout << pathWithSum(root, target);
}

int main() {
    test();
    return 0;
}
