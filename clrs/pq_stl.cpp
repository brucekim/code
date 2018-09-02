//
//  main.cpp
//  priority_queue
//
//  Created by 김인태 on 2018. 8. 14..
//  Copyright © 2018년 김인태. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

void test_pq() {
    priority_queue<int, vector<int>, less<int>> pq;
    
    pq.push(50);
    pq.push(20);
    pq.push(70);
    pq.push(30);
    
    while(! pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
}

void test_pq_pair() {
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(50, 100));
    pq.push(make_pair(20, 500));
    pq.push(make_pair(70, 300));
    pq.push(make_pair(30, 200));
    cout << pq.size() << endl;
    while (! pq.empty()) {
        pair<int, int> top = pq.top();
        cout << top.first << " " << top.second << " " << pq.size() <<  endl;
        pq.pop();
    }
}

struct score {
    int num;
    int score;
};

struct cmp {
    bool operator()(score a, score b) {
        return a.num > b.num;
    }
};
void test_pq_struct() {
    priority_queue<score, vector<score>, cmp> pq;
    pq.push(score{50, 100});
    pq.push(score{20, 500});
    pq.push(score{70, 300});
    pq.push(score{30, 200});
    cout << pq.size() << endl;
    while (! pq.empty()) {
        score top = pq.top();
        cout << top.num << " " << top.score << " " << pq.size() <<  endl;
        pq.pop();
    }
}

int main(int argc, const char * argv[]) {
    test_pq();
    cout << endl << endl;
    test_pq_pair();
    cout << endl << endl;
    test_pq_struct();
    return 0;
}
