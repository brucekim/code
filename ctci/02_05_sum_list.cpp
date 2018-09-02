/*
 Sum Lists: You have two numbers represented by a linked list, where each node contains a single digit.The digits are stored in reverse order, such that the 1 's digit is at the head of the list. Write a function that adds the two numbers and returns the sum as a linked list.
 
 EXAMPLE
 Input:(7-> 1 -> 6) + (5 -> 9 -> 2).Thatis,617 + 295.
 Output:2 -> 1 -> 9.That is,912.
 
 FOLLOW UP
 Suppose the digits are stored in forward order. Repeat the above problem.
 
 EXAMPLE
 lnput:(6 -> 1 -> 7) + (2 -> 9 -> 5).That is,617 + 295.
 Output:9 -> 1 -> 2.Thatis,912.
 
 Hints: #7, #30, #71, #95, #109
 */


#include <iostream>
#include <list>
#include <stack>

using namespace std;

list<int> sum_list(list<int> &a, list<int> &b) {
    list<int> ans;
    int carry = 0;
    list<int>::iterator it_a = begin(a);
    list<int>::iterator it_b = begin(b);
    while(it_a != end(a) || it_b != end(b)) {
        int v = carry;
        if (it_a != end(a)) {
            v += *it_a;
            ++it_a;
        }
        if (it_b != end(b)) {
            v += *it_b;
            ++it_b;
        }
        carry = v / 10;
        ans.push_back(v % 10);
    }
    if (carry > 0)
        ans.push_back(carry);
    
    return ans;
}


list<int> sum_list_forward(list<int> &a, list<int> &b) {
    list<int> ans;
    stack<int> st_a;
    stack<int> st_b;
    
    int carry = 0;
    
    for(auto &&it: a) {
        st_a.push(it);
    }
    for(auto &&it: b) {
        st_b.push(it);
    }
    
    
    while(!st_a.empty() || !st_b.empty()) {
        int v = carry;
        
        if (!st_a.empty()) {
            v += st_a.top();
            st_a.pop();
        }
        if (!st_b.empty()) {
            v += st_b.top();
            st_b.pop();
        }
        
        carry = v / 10;
        ans.push_back(v % 10);
    }
    if (carry > 0)
        ans.push_back(carry);
    return ans;
}

void print_list(list<int> &ans) {
    for(auto &&it : ans) {
        cout << it;
    }
    cout << endl;
}
void test() {
    list<int> ans;
    
    list<int> a = {7, 1, 6};
    list<int> b = {5, 9, 2};
    ans = sum_list(a, b);
    print_list(ans);
    
    
    a = {6, 1, 7};
    b = {2, 9, 5};
    ans = sum_list_forward(a, b);
    print_list(ans);
    
    
    /* edge cases */
    a = {1};;
    b = {9, 2, 3, 4};
    ans = sum_list(a, b);
    print_list(ans);
    
    a = {4, 3, 2, 9};
    b = {1};
    ans = sum_list_forward(a, b);
    print_list(ans);
    
    a = {0, 0, 3};
    b = {0, 0, 7};
    ans = sum_list(a, b);
    print_list(ans);

}
int main(int argc, const char * argv[]) {
    test();
    return 0;
}

