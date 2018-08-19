//
//  main.cpp
//  hanoi_tower
//
//  Created by 김인태 on 2018. 8. 18..
//  Copyright © 2018년 김인태. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

void hanoi(int n, stack<int> &src, stack<int> &dest, stack<int> &aux) {
    if (n == 1) {
        dest.push(src.top());
        src.pop();
        return;
    }
    hanoi(n-1, src, aux, dest);
    dest.push(src.top());
    src.pop();
    hanoi(n-1, aux, dest, src);
}

void test() {
    stack<int> src;
    stack<int> aux;
    stack<int> dest;
    
    int n = 10;
    for(int i=n; i>0; --i) {
        src.push(i);
    }
    
    hanoi(10, src, dest, aux);
    
    while(!dest.empty()) {
        cout << dest.top() << endl;
        dest.pop();
    }
}

int main(int argc, const char * argv[]) {
    test();
    return 0;
}

