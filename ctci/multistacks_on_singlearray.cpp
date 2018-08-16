
#include <iostream>

using namespace std;

namespace b {
    
    struct Node {
        int k;
        Node *next;
        Node() : k(-1), next(nullptr) {}
        
    };
    class ArrayMemory {
    public:
        ArrayMemory(Node _arr[], int _n) : arr(_arr), n(_n) {
            occupied = new bool[n];
            for(int i=0; i<n; i++) {
                occupied[i] = false;
            }
        }
        ~ArrayMemory() {
            delete []occupied;
        }
        Node *GetMemory() {
            for(int i=0; i<n; i++) {
                if (occupied[i] == false) {
                    occupied[i] = true;
                    return &arr[i];
                }
            }
            return nullptr;
        }
        void Release(Node *addr) {
            int idx = (addr - arr) / sizeof (arr[0]);
            occupied[idx] = false;
        }
        
        void PrintMemStatus() {
            for (int i=0; i<n; i++) {
                cout << "["<< i << ":" << arr[i].k << ":" << occupied[i] << "] ";
            }
            cout << endl;
        }
        
    private:
        Node *arr;
        bool *occupied;
        
        
        int n;
        
    };
    
    class Stack {
    public:
        Stack(ArrayMemory *_arr_mem) : arr_mem(_arr_mem), top(nullptr), sz(0) {}
        void Push(int k) {
            Node *mem = arr_mem->GetMemory();
            if (mem == nullptr) {
                cout << "out of memory" << endl;
                return;
            }
            mem->k = k;
            mem->next = nullptr;
            
            if (top == nullptr)
                top = mem;
            else {
                mem->next = top;
                top = mem;
            }
            ++sz;
        }
        void Pop() {
            if (top != nullptr) {
                Node *tmp = top;
                top = top->next;
                arr_mem->Release(tmp);
                --sz;
            }
        }
        int Peek() {
            if (top == nullptr)
                return -1;
            return top->k;
        }
        bool Empty() {
            return sz == 0;
        }
        int Size() {
            return sz;
        }
        
    private:
        ArrayMemory *arr_mem;
        Node *top;
        int sz;
    };
}


void arr_test() {
    b::Node arr[10];
    b::ArrayMemory arr_mem(arr, 10);
    b::Node *test = arr_mem.GetMemory();
    test->k = 5;
    b::Node *test2 = arr_mem.GetMemory();
    test2->k = 6;
    
    arr_mem.PrintMemStatus();
    arr_mem.Release(test);
    arr_mem.PrintMemStatus();
    
}

void test() {
    /* one array - shared by all stacks under memory management */
    b::Node arr[5];
    b::ArrayMemory arr_mem(arr, 5);
    
    b::Stack st1(&arr_mem);
    b::Stack st2(&arr_mem);
    b::Stack st3(&arr_mem);
    
    st1.Push(10);
    st1.Push(20);
    st1.Push(30);
    st2.Push(100);
    st2.Push(200);
    st3.Push(1000);
    
    st1.Pop();
    cout << st1.Peek() << " " << st1.Size() << endl;
    cout << st2.Peek() << " " << st2.Size() << endl;
    cout << st3.Peek() << " " << st3.Size() << endl;
    
    st3.Push(1000);
    cout << st3.Peek() << " " << st3.Size() << endl;
    
    arr_mem.PrintMemStatus();
    
}

int main(int argc, const char * argv[]) {
    
    test();
    return 0;
}

