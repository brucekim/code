#include <cstdio>

const static int int_min = -9999;
class xminheap {
    public:
        xminheap(int _capa) : capa(_capa), sz(0) {
            arr = new int[capa]{0};
        }
        virtual ~xminheap() { delete []arr; }
        void swap(int &a, int &b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        int parent(int v) { return (v-1)/2; }
        int left(int v) { return (v*2)+1; }
        int right(int v) { return (v*2)+2; }
        int getMin() { return arr[0]; }
        int extractMin() {
            if (sz <= 0) {
                return int_min;
            } else if (sz == 1) {
                --sz;
                return arr[0];
            } else {
                int root = arr[0];
                arr[0] = arr[sz-1];
                --sz;
                heapify(0);
                return 0;
            }
        }
        /* delete value at index i */
        void deleteKey(int i) {
            decreaseKey(i, int_min);
            extractMin();
        }
        /* insert value k */
        void insertKey(int k) {
            if (sz == capa) {
                return;
            }
            int i = sz;
            ++sz;
            arr[i] = k;
            while (i != 0 && arr[parent(i)] > arr[i]) {
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
            int l = left(v);
            int r = right(v);
            int smallest = v; /* 2019.05.13
                                        여기서 min heap인데, 자식 노드 중에서 smallest를 고르는 의미가 있나?
                                        ans) 자식들보다 부모노드가 작다는 property를 보장하기 위해서는 자식 중에서도 더 작은 놈을 선별해서 비교해야 함
                                        */
            if (l < sz && arr[l] < arr[v]) {
                smallest = l;
            }
            if (r < sz && arr[r] < arr[smallest]) {
                smallest = r;
            }
            if (smallest != v) {
                swap(arr[smallest], arr[v]);
                heapify(smallest);
            }
        }
        void print() {
            for (int i=0; i<sz; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }

    private:
        int capa;
        int sz;
        int *arr;
};

void solve() {
    xminheap minheap(10);
    minheap.insertKey(5);
    minheap.insertKey(4);
    minheap.insertKey(3);
    minheap.insertKey(2);
    minheap.insertKey(1);
    minheap.print();

    printf("m %d\n", minheap.extractMin());
    minheap.insertKey(0);
    minheap.print();
    minheap.deleteKey(2);
    minheap.print();
}

int main() {
    solve();
    return 0;
}
