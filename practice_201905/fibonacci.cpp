#include <cstdio>

struct fibo {
    fibo() {
        memo[0] = 0;
        memo[1] = 1;
    }
    int fibo_memo(int n) {
        if ((n >= 2) && memo[n] == 0) {
            return memo[n] = fibo_memo(n - 1) + fibo_memo(n - 2);
        }
        return memo[n];
    }
    int fibo_recursive(int n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        } else {
            return fibo_recursive(n - 1) + fibo_recursive(n - 2);
        }
    }

    int memo[1000]{0};
};

int main() {
    int n = 6;
    fibo f;
    int ans1 = f.fibo_memo(n);
    int ans2 = f.fibo_recursive(n);
    printf("fibo(%d) = %d %d\n", n, ans1, ans2);
    return 0;
}
