/*
 Palindrome: Implement a function to check if a linked list is a palindrome. Hints:#5, #13, #29, #61, #101
 */

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

namespace b {
    
    template <typename T>
    struct node {
        T k;
        node* next;
        node(T _k) : k(_k), next(nullptr) {}
    };
    
    template <typename T>
    class list {
    public:
        list() : head(nullptr) {}
        ~list() {
            while(head != nullptr) {
                node<T> *t = head;
                head = head->next;
                delete t;
            }
        }
        void print() {
            node<T> *t = head;
            while(t != nullptr) {
                cout << t->k;
                t = t->next;
            }
            cout << endl;
        }
        void insert_key(T k) {
            node<T> *n = new node<T>(k);
            if (head == nullptr) {
                head = n;
            } else {
                node<T> *t = head;
                while(t->next != nullptr) {
                    t = t->next;
                }
                t->next = n;
            }
        }
        auto front() -> node<T>* {
            return head;
        }
        
    private:
        node<T> *head;
    };
}

template <typename T>
bool palindrome(b::list<T> &l) {
    stack<b::node<T>*> st;
    
    b::node<T>* t = l.front();
    
    int cnt = 0;
    while( t != nullptr) {
        st.push(t);
        t = t->next;
        cnt++;
    }
    t = l.front();
    for (int i=0; i<cnt/2; i++) {
        cout << " compare: " << t->k << " vs " << st.top()->k << endl;
        if (t->k != st.top()->k) {
            return false;
        }
        t = t->next;
        st.pop();
    }
    
    return true;
}

void test() {
    b::list<char> l1;
    
    l1.insert_key('r');
    l1.insert_key('a');
    l1.insert_key('c');
    l1.insert_key('e');
    l1.insert_key('c');
    l1.insert_key('a');
    l1.insert_key('r');
    l1.print();
    cout << palindrome<char>(l1) << endl;
    
    
    b::list<char> l2;
    l2.insert_key('a');
    l2.insert_key('p');
    l2.insert_key('p');
    l2.insert_key('l');
    l2.insert_key('e');
    l2.print();
    cout << palindrome<char>(l2) << endl;
    
}

int main(void)
{
    test();
    return 0;
}
