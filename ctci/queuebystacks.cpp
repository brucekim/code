
#include <iostream>
#include <stack>

using namespace std;

#define INVALID 0x80000000

namespace b {
    class MyQueue {
    public:
        MyQueue() {
            
        }
        
        void enque(int k) {
            s1.push(k);
        }
        
        int deque() {
            if (s2.empty()) {
                while(!s1.empty())
                {
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            if (s2.empty())
                return INVALID;
            
            int ret = s2.top();
            s2.pop();
            return ret;
        }
        
        
        bool empty() {
            return s1.empty() && s2.empty();
        }
        
        
    private:
        stack<int> s1;
        stack<int> s2;
        
    };
}

void test() {
    b::MyQueue myq;
    
    for(int i=1; i<=5; i++) {
        myq.enque(i);
    }
    
    cout << myq.deque() << " ";
    
    for(int i=6; i<=10; i++)
        myq.enque(i);
    
    while(!myq.empty()) {
        cout << myq.deque() << " ";
    }
}


int main(int argc, const char * argv[]) {
    test();
    
    return 0;
}
