#include <cstdio>

class solver {
    public:
    solver() : ans(0) {
        scanf("%d", &x);
        for(int i=0; i<10; ++i) {
            num[i] = false;
        }
    }
    int run() {
        while(x > 0) {
            int r = x%10;
            if (num[r] == false) {
                num[r] = true;
                ++ans;
            }
            x = x/10;
        }
        return ans;
    }
    private:
    int x;
    int ans;
    bool num[10];
};
void solve(int i) {
    solver sol;
    int ans = sol.run();
    printf("#%d %d\n", i, ans);
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
