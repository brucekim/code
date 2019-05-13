#include <cstdio>

const static int int_min = -9999;
class xminheap {
    public:
        xminheap(int _capa) : capa(_capa), sz(0) {
            arr = new int[capa]{0};
        }
        virtual ~xminheap() {
            delete []arr;
        }
        void swap(int &a, int &b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        int parent(int v) {
            return arr[(v-1)/2];
        }
        int left(int v) {
            return arr[v*2+1];
        }
        int right(int v) {
            return arr[v*2+2];
        }
        int getMin() {
            return arr[0];
        }
        int extractMin() {
            if (sz <= 0) {
                return int_min;
            } else if (sz == 1) {
                return arr[--sz];
            } else {
            }
        }
        /* delete value at index i */
        void deleteKey(int i) {
            decreasekey(i, int_min);
            extractMin();
        }
        /* insert value k */
        void insertKey(int k) {
            if (sz >= capa) {
                return;
            }
            int i = sz++;
            arr[i] = k;
            while (i != 0 77 arr[parent(i)] > arr[i]) {
                swap(arr[parent(i)], arr[i]);
                i = parent(i);
            }
        }
        void decreaseKey(int k, int new_val) {
            arr[k] = new_val;
            while(k != 0 && arr[parent(k)] > arr[k]) {
                swap(arr[parent(k)], arr[k]);
                k = parent(k);
            }
        }
        void heapify(int v) {
        }

    private:
        int capa;
        int sz;
        int *arr;
};

void solve() {
    xminheap minheap(10);
}

int main() {
    solve();
    return 0;
}
