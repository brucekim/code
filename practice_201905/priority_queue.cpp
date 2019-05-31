#include <cstdio>

const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
struct pvpair {
    pvpair(int _p=0, T _v=T()) : p(_p), v(_v) {}

    int p;
    T v;
};

template <typename T>
class priority_queue {
    public:
        priority_queue(int _capa=const_max_sz) : capa(_capa), sz(0) {
            arr = new pvpair<T>[capa]();
        }
        virtual ~priority_queue() {
            delete[] arr;
        }

        int push(int p, T v) {
            pvpair<T> pv(p, v);
            if (sz == capa) {
                return const_err_code;
            } else {
                int i = sz;
                ++sz;
                arr[i] = pv;
                while(i != 0 && arr[i].p < arr[parent(i)].p) {
                    swap(arr[i], arr[parent(i)]);
                    i = parent(i);
                }
            }
            return 0;
        }
        T& top() {
            return arr[0].v;
        }
        int pop() {
            if (sz == 0) {
                return const_err_code;
            } else if (sz == 1) {
                --sz;
            } else {
                arr[0] = arr[sz-1];
                --sz;
                heapify(0);
            }
            return 0;
        }
        bool isEmpty() {
            return sz == 0;
        }
    private:
        int parent(int v) { return (v-1)/2; }
        int left(int v) { return v*2 + 1; }
        int right(int v) { return v*2 + 2; }
        void heapify(int v) {
            int smallest = v;
            int l = left(v);
            int r = right(v);
            if (l < sz && arr[l].p < arr[smallest].p) {
                smallest = l;
            }
            if (r < sz && arr[r].p < arr[smallest].p) {
                smallest = r;
            }
            if (v != smallest) {
                swap(arr[v], arr[smallest]);
                heapify(smallest);
            }
        }
        void swap(pvpair<T> &a, pvpair<T> &b) {
            pvpair<T> tmp = a;
            a = b;
            b = tmp;
        }

        int capa, sz;
        pvpair<T> *arr;
};

void solve() {
    priority_queue<int> pq;
    pq.push(10, 100);
    pq.push(3, 30);
    pq.push(7, 70);
    pq.push(11, 110);
    pq.push(4, 40);

    while(!pq.isEmpty()) {
        printf("%d\n", pq.top());
        pq.pop();
    }
}
int main() {
    solve();
    return 0;
}
