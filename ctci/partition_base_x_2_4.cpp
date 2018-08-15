/*
 Partition: Write code to partition a linked list around a value x, such that all nodes less than x come before all nodes greater than or equal to x. If x is contained within the list, the values of x only need to be after the elements less than x (see below). The partition element x can appear anywhere in the "right partition"; it does not need to appear between the left and right partitions.
 EXAMPLE
 Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1[partition=5] 
 Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
 Hints: #3, #24
 */

#include <iostream>

using namespace std;

struct node {
    node(int _k) : k(_k) {}
    int k = -1;
    node *next = nullptr;
};

void partition(node **l, int x) {
    node *first = *l;
    node *first_pre = *l;
    node *left = *l;
    
    while(first != nullptr) {
        
        if (first->k < x && first_pre != left) {
            first_pre->next = first->next;
            first->next = left->next;
            left->next = first;
            left = first;
            
            first = first_pre->next;
        } else {
            first_pre = first;
            first = first->next;
        }
    }
}

void print_list(node *l) {
    while(l != nullptr){
        cout<< l->k << " ";
        l = l->next;
    }
    cout <<"\n";
}
void test() {
    node *l;
    node *n1 = new node(3);
    node *n2 = new node(5);
    node *n3 = new node(8);
    node *n4 = new node(5);
    node *n5 = new node(10);
    node *n6 = new node(2);
    node *n7 = new node(1);
    l = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    
    print_list(l);
    
    cout << "after partition" << endl;
    partition(&l, 5);

    print_list(l);
    
    while(l != nullptr){
        node *t = l;
        l = l->next;
        delete t;
    }
}
int main(int argc, const char * argv[]) {
    test();
    return 0;
}

