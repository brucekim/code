/*
link: https://www.acmicpc.net/problem/1431
std sort를 사용하는데, compare함수를 문제에 설명된대로 구현한다.

A와 B의 길이가 다르면, 짧은 것이 먼저 온다.
만약 서로 길이가 같다면, A의 모든 자리수의 합과 B의 모든 자리수의 합을 비교해서 작은 합을 가지는 것이 먼저온다. (숫자인 것만 더한다)
만약 1,2번 둘 조건으로도 비교할 수 없으면, 사전순으로 비교한다. 숫자가 알파벳보다 사전순으로 작다.

5
ABCD
145C
A
A910
Z321

A
ABCD
Z321
145C
A910
*/
#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(const string &a, const string &b)
{
    if (a.length() != b.length())
    {
        return a.length() < b.length();
    }
    else
    {
        int suma = 0;
        int sumb = 0;
        for (int i = 0; i < a.length(); ++i)
        {
            if (a[i] >= '0' && a[i] <= '9')
            {
                suma += a[i] - '0';
            }
            if (b[i] >= '0' && b[i] <= '9')
            {
                sumb += b[i] - '0';
            }
        }
        if (suma != sumb)
        {
            return suma < sumb;
        }
        return a < b;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string arr[1000];
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    sort(arr, arr + n, cmp);

    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << "\n";
    }
    return 0;
}
