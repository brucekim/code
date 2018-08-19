
#include <iostream>
#include <stack>

using namespace std;

void MergeStack(stack<int> &s, stack<int> &s1, stack<int> &s2) {
    stack<int> t;
    while(!s1.empty() && !s2.empty()) {
        if (s1.top() < s2.top()) {
            t.push(s1.top());
            s1.pop();
        } else {
            t.push(s2.top());
            s2.pop();
        }
    }
    while(!s1.empty()) {
        t.push(s1.top());
        s1.pop();
    }
    while(!s2.empty()) {
        t.push(s2.top());
        s2.pop();
    }
    while(!t.empty()) {
        s.push(t.top());
        t.pop();
    }
}

void SortStack(stack<int> &s) {
    if (s.size() == 1)
        return;
    
    stack<int> s1, s2;
    int half = s.size() / 2;
    for(int i=0; i<half; ++i) {
        s1.push(s.top());
        s.pop();
    }
    while(!s.empty()) {
        s2.push(s.top());
        s.pop();
    }
    SortStack(s1);
    SortStack(s2);
    MergeStack(s, s1, s2);
}

void test() {
    int arr[] = { 1, 10, 2, 20, 3, 30, 4, 40, 50};
    stack<int> s;
    for(auto &&it: arr) {
        s.push(it);
    }
    
    SortStack(s);
    while(!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
    
    
}
int main(int argc, const char * argv[]) {
    test();
    return 0;
}
