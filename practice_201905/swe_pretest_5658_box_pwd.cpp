#include <cstdio>

#define DBG_STDIN

const static int max_arr_sz = 1000;

class cbuf {
    public:
    cbuf(char *_arr, int _sz) : arr(_arr), sz(_sz) {}

    const char& operator[](int _idx) {
        int idx = _idx%sz;
        return arr[idx];
    }

    private:
    char *arr;
    int sz;
};

int digits[7] = {
    1,
    16,
    16*16,
    16*16*16,
    16*16*16*16,
    16*16*16*16*16,
    16*16*16*16*16*16
};

int hex2dec(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    } else if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    }
    return 999;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(int *arr, int l, int r) {
    if (l < r) {
        int pivot = arr[r];
        int i = l-1;
        for(int j = i+1; j<r; ++j) {
            if (arr[j] > pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[r]);
        return i+1;
    }
    return l;
}

void quick_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = partition(arr, l, r);
        quick_sort(arr, l, m-1);
        quick_sort(arr, m+1, r);
    }
}
void solve() {
    int n, k, shift, digit;
    char charr[max_arr_sz]{0};
    int arr[max_arr_sz] {0};
    int arr_nodup[max_arr_sz] {0};
    int idx = 0;
    for(int i=0; i<max_arr_sz; ++i) {
        charr[i] = 0;
        arr[i] = 0;
        arr_nodup[i] = 0;
    }

    scanf("%d %d", &n, &k);
    scanf("%s", charr);
    shift = n / 4;
    cbuf cb(charr, n);

    for(int i=0; i<n; ++i) {
        digit = 0;
        int decval = 0;
        for(int j=(i+shift)-1; j>=i; --j){
            decval = decval + ((hex2dec(cb[j])) * digits[digit]);
            ++digit;
        }
        arr[idx++] = decval;
    }

    quick_sort(arr, 0, n-1);

    idx = -1;
    for(int i=0; i<n; ++i) {
        if (idx == -1) {
            ++idx;
            arr_nodup[idx] = arr[i];
        } else if (arr_nodup[idx] != arr[i]) {
            ++idx;
            arr_nodup[idx] = arr[i];
        }
    }

    /*
    printf("arr:\n");
    for(int i=0; i<n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("arr_nodup:\n");
    for(int i=0; i<n; ++i) {
        printf("%d ", arr_nodup[i]);
    }
    printf("\n");
    */

    printf("%d\n", arr_nodup[k-1]);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swe_pretest_5658_input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        printf("#%d ", i+1);
        solve();
    }
    return 0;
}
