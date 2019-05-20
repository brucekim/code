#include <cstdio>

const static int const_max_n = 20;

class solver{
    public:
    solver() : ans(0) {
        scanf("%d %d", &n, &s);
        for(int i=0; i<n; ++i) {
            visited[i] = false;
            scanf("%d", &arr[i]);
        }
    }
    void dfs(int k, int sum) {
       for(int i=k; i<n; ++i) {
            if (visited[i] == false) {
                visited[i] = true;
                if (sum+arr[i] == s) {
                    ++ans;
                }
                dfs(i+1, sum + arr[i]);
                visited[i] = false;
            }
        }
    }
    int answer() {
        return ans;
    }
    private:
    int n, s, ans;
    int arr[const_max_n]{0};
    bool visited[const_max_n]{0};
};

int main() {
    solver sol;
    sol.dfs(0, 0);
    printf("%d", sol.answer());
    return 0;
}
