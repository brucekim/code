//
//  main.cpp
//  merge_sort_link
//
//  Created by 김인태 on 2018. 8. 14..
//  Copyright © 2018년 김인태. All rights reserved.
//

#include <iostream>
#include <list>

using namespace std;

struct _node {
    int data;
    struct _node* next;
};

typedef struct _node* nodeptr;


void push(nodeptr *head, int data) {
    nodeptr item = new _node;
    item->data = data;
    item->next = nullptr;
    
    
    if (*head == nullptr) {
        *head = item;
    } else {
        nodeptr t = *head;
        while(t->next != nullptr) {
            t = t->next;
        }
        t->next = item;
    }
}

void print(nodeptr head) {
    while(head != nullptr) {
        cout << head->data <<" ";
        head = head->next;
    }
    cout << endl;
}

void get_middle(nodeptr head, nodeptr *a, nodeptr *b) {
    nodeptr fast, slow;
    slow = head;
    fast = head->next;
    while(fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *a = head;
    *b = slow->next;
    slow->next = nullptr;
    cout << "l: " << head->data << " ";
    cout << "r: " << ((*b) != nullptr ? (*b)->data : 0) << endl;
    
}

nodeptr merge(nodeptr a, nodeptr b) {
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;
    
    nodeptr m;
    if (a->data < b->data) {
        m = a;
        m->next = merge(a->next, b);
    }
    else
    {
        m = b;
        m->next = merge(a, b->next);
    }
    
    return m;
}

void merge_sort(nodeptr *head) {
    
    nodeptr a = nullptr;
    nodeptr b = nullptr;
    
    if (*head == nullptr || (*head)->next == nullptr)
    {
        return;
    }
    
    get_middle(*head, &a, &b);
    
    merge_sort(&a);
    merge_sort(&b);
    
    *head = merge(a, b);
    
}

void test() {
    nodeptr head = nullptr;
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    
    print(head);
    
    merge_sort(&head);
    
    cout << "after" << endl;
    print(head);
   
}

int main(int argc, const char * argv[]) {
    test();
    return 0;
}
