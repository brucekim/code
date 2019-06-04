#include <cstdio>

const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
    public:
        xstack() : capa(const_max_sz), sz(0) {
            arr = new T[capa];
        }
        virtual ~xstack() {
            delete[] arr;
        }
        int push_back(T data) {
            if (sz < capa) {
                arr[sz++] = data;
                return 0;
            } else {
                return const_err_code;
            }
        }
        int pop_back() {
            if (sz > 0) {
                --sz;
                return 0;
            } else {
                return const_err_code;
            }
        }
        bool isEmpty() {
            return sz == 0;
        }
        int getSize() {
            return sz;
        }
        T& top() {
            return arr[sz-1];
        }
    private:
        int sz, capa;
        T *arr;
};

template <typename T>
class xqueue {
    public:
        xqueue() {
            st1 = new xstack<T>();
            st2 = new xstack<T>();
        }
        virtual ~xqueue() {
            delete st1;
            delete st2;
        }
        int push_back(T data) {
            return st1->push_back(data);
        }
        int pop_front() {
            if (isEmpty() == true) {
                return const_err_code;
            } else if(st2->isEmpty() == true) {
                moveSt1ToSt2();
                return pop_front();
            } else {
                return st2->pop_back();
            }
        }
        const T& get_front() {
            if (st2->isEmpty() == true) {
                moveSt1ToSt2();
                if (st2->isEmpty() == true) {
                    return T(const_err_code);
                } else {
                    return st2->top();
                }
            } else {
                return st2->top();
            }
        }
        bool isEmpty() {
            return st1->isEmpty() && st2->isEmpty();
        }
        int getSize() {
            return st1->getSize() + st2->getSize();
        }
    private:
        void moveSt1ToSt2() {
            while(!st1->isEmpty()) {
                st2->push_back(st1->top());
                st1->pop_back();
            }
        }
        xstack<T> *st1;
        xstack<T> *st2;
};

void solve() {
    xqueue<int> q;


    q.push_back(10);
    q.push_back(20);
    q.push_back(30);

    int t = q.get_front();
    q.pop_front();
    printf("%d ", t);

    q.push_back(40);
    q.push_back(50);

    while(!q.isEmpty()) {
        t = q.get_front();
        q.pop_front();
        printf("%d ", t);
    }
    q.push_back(60);
    t = q.get_front();
    q.pop_front();
    printf("%d ", t);

    // to be
    // 10 20 30 40
}

int main() {
    solve();
}
