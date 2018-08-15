//
//  main.cpp
//  hash
//
//  Created by 김인태 on 2018. 8. 14..
//  Copyright © 2018년 김인태. All rights reserved.
//

#include <iostream>

using namespace std;

namespace kim {
    class dict {
    public:
        void add(int k, int v) {
            harr[hash(k)] = v;
        }
        bool exists(int k) {
            return harr[hash(k)] != infinite;
        }
        int get(int k) {
            return harr[hash(k)];
        }
        
        int hash(int k) {
            return k % cap;
        }
        
        void print() {
            for(int i=0; i<cap; i++) {
                int v = harr[i];
                if (v != infinite)
                    cout << v << " ";
            }
            cout << endl;
        }
        
        dict() : cap(100) {
            harr = new int[cap];
            for (int i=0; i<cap; i++) {
                harr[i] = infinite;
            }
        }
        ~dict() {
            delete [] harr;
        }
        
    private:
        int cap;
        int *harr;
        const static int infinite = -1;
    };
}

void test() {
    kim::dict dict;
    
    dict.add(10, 1000);
    dict.add(110, 2000);
    dict.add(20, 3000);
    cout << dict.get(10) << endl;
    cout << dict.get(110) << endl;
    dict.print();
}

int main(int argc, const char * argv[]) {
    test();
    return 0;
}
