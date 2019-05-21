#include <cstdio>

const static int const_fresh = 0;
const static int const_mature = 1;
const static int const_empty = -1;

const static int const_max_val = 1000000;
const static int const_err_code = 0x3f3f3f3f;

struct coord {
    coord(int _r, int _c, int _h) : r(_r), c(_c), h(_h) {}
    int r, c, h;
};
template <typename T>
class xqueue {
    public:
        xqueue(int _capa=const_max_val) : capa(_capa), sz(0), front(-1), rear(-1) {
            arr = new T[capa]();
        }
        virtual ~xqueue() {
            delete[] arr;
        }
        int enque(T data) {
            if ((rear == capa-1 && front == 0) || (rear == (front-1)%capa)) {
                return const_err_code;
            } else if (front == -1) {
                front = rear = 0;
            }else if (rear == capa-1 && front != 0) {
                rear = 0;
            } else {
                ++rear;
            }
            arr[rear] = data;
            ++sz;
            return 0;
        }
        int deque() {
            if (front == -1) {
                return const_err_code;
            } else if (front == rear) {
                front = rear = -1;
            } else if (front == capa-1) {
                front = 0;
            } else {
                ++front;
            }
            --sz;
            return 0;
        }
        bool isEmpty() {
            return sz == 0;
        }
        int getSize() {
            return sz;
        }
    private:
        int capa, sz;
        int front, rear;
        T *arr;
};

class solver {
    public:
        solver() : fresh(0) {
            scanf("%d %d %d", &m, &n, &h);
            arr = new int[m*n*h]{0};
            int tmp;
            for(int i=0; i<h; ++i) {
                for(int j=0; j<n; ++j) {
                    for(int k=0; k<m; ++k) {
                        scanf("%d", &tmp);
                        arr[i*(m*n)+j+k] = tmp;
                        if (tmp == const_fresh) {
                            ++fresh;
                        } else if (tmp == const_mature) {
                        }
                    }
                }
            }
        }
        virtual ~solver() {
            delete[] arr;
        }

        void run() {
        }
    private:
        int m, n, h, fresh;
        int *arr;
        xqueue<coord> q;
};
int main() {
    solver sol;
    sol.run();
    return 0;
}
