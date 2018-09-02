#include <iostream>
using namespace std;
namespace b{
    struct node {
        node(int _k) : k(_k), next(nullptr) {}
        int k;
        node *next;
    };
    
    class stack{
    public:
        stack(int _cap) : cap(_cap), sz(0), top(nullptr), next(nullptr) {}
        ~stack() {
            while(top != nullptr) {
                node *t = top;
                top = top->next;
                delete t;
            }
        }
        bool push(int k) {
            if (sz >= cap)
                return false;
            node *n = new node(k);
            n->next = top;
            top = n;
            ++sz;
            return true;
        }
        int peek() {
            if (top == nullptr)
                return -1;
            else
                return top->k;
        }
        bool pop() {
            if (top == nullptr)
                return false;
            node* tmp = top;
            top = top->next;
            delete tmp;
            --sz;
            return true;
        }
        bool Full() {
            return sz == cap;
        }
        void print() {
            node *t = top;
            while(t != nullptr) {
                cout << t->k << " ";
                t = t->next;
            }
            cout << endl;
        }
        
        stack *next;
    private:
        int cap;
        int sz;
        node *top;
        
    };
    
    class setofstacks {
    public:
        setofstacks(int _cap) : cap(_cap), top(nullptr) {}
        ~setofstacks() {
            while(top != nullptr) {
                stack* t = top;
                top = top->next;
                delete t;
            }
        }
        void push(int k) {
            if (top == nullptr || top->Full()) {
                stack *new_st = new stack(cap);
                new_st->push(k);
                new_st->next = top;
                top = new_st;
            } else {
                top->push(k);
            }
        }
        void pop() {
            if (top == nullptr)
                return;
            if (top->pop() == false) {
                stack *t = top;
                top = top->next;
                if (top != nullptr) {
                    top->pop();
                }
                delete t;
            }
        }
        int peek() {
            if (top == nullptr)
                return -1;
            return top->peek();
        }
        void print() {
            stack* t = top;
            while(t != nullptr) {
                t->print();
                t = t->next;
            }
        }
    private:
        int cap;
        stack *top;
        
    };
}

void test() {
    b::setofstacks s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    s.push(7);
    s.push(8);
    s.push(9);
    s.push(10);
    
    
    s.print();
    cout << "--" << endl;
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    
    s.print();
    
}

int main() {
    test();
    return 0;
}