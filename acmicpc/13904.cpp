/*
link: https://www.acmicpc.net/problem/13904
풀이:
1. 남은날짜로 내림차순 정렬 (구현에선 vector의 마지막 원소부터 빼서 썻음)
2. 첫 element의 남은 날짜와 같은 날짜의 element들을 max heap으로 만들기
3. max heap에서 하나 빼기-> 점수는 누적
4. 2번에서 남은날짜 기억했던 값과 -1 한 값을 (deadline) list에 있는 element의 남은날짜와 비교, 같은 element들을 max heap에 추가
=> list가 empty이면 수행 x
5. deadline이 0이 될때까지 3~4 반복
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct greater1 {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d, w, ans;
    int deadline;
    vector<pair<int, int>> v;
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater1> max_heap;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> d >> w;
        v.push_back(make_pair(d, w));
    }
    sort(begin(v), end(v));
    /*
    for (auto &&k : v) {
        cout << k.first << " " << k.second << endl;
    }
    cout << "--" << endl;
    */

    /* initial */
    deadline = v.back().first;
    while (deadline != 0) {
        while (v.empty() == false && v.back().first == deadline) {
            //cout << "push" << v.back().first << " " << v.back().second << endl;
            max_heap.push(v.back());
            v.pop_back();
        }
        --deadline;
        if (max_heap.size() == 0)
            continue;
        ans += max_heap.top().second;
        //cout << "add " << max_heap.top().first << " " << max_heap.top().second << endl;
        max_heap.pop();
    }
    cout << ans;

    return 0;
}
