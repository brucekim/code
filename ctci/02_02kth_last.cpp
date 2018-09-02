/*
 * Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.
Hints:#8, #25, #41, #67, #126
 */
#include <iostream>
#include <list>

using namespace std;

int get_kth_last(list<int> &l, int k)
{
    list<int>::iterator slow = begin(l);
    list<int>::iterator fast = begin(l);
    if (l.size() < k)
        return -1;
    int cnt = 0;
    while(fast != end(l)) {
        ++fast;
        ++cnt;
        if (cnt >= k)
            ++slow;
    }
    
    return *slow;
}

void test() {
    list<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    cout << get_kth_last(l, 1);
}
int main() {
    test();
}
