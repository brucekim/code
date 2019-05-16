#include <cstdio>

const static int const_max_size = 5;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class cqueue {
    public:
        cqueue(int _capa = const_max_size) : capa(_capa), sz(0), front(-1), rear(-1) {
            arr = new T[capa]();
        }
        virtual ~cqueue() {
            delete[] arr;
        }

        int enq(T data) {
            // 5 cases - full(2), not full(3)
            if ((rear == capa - 1 && front == 0) || (rear == (front - 1) % capa)) {
                printf("buf full\n");
                return const_err_code;
            } else if (front == -1) {
                front = rear = 0;
                arr[rear] = data;
            } else if (rear == capa - 1 && front != 0) {
                rear = 0;
                arr[rear] = data;
            } else {
                arr[++rear] = data;
            }
            ++sz;
            return 0;
        }
        int deq() {
            if (front == -1) {
                return const_err_code;
            }
            if (front == rear) {
                front = rear = -1;
            } else if (front == capa - 1) {
                front = 0;
            } else {
                ++front;
            }
            --sz;

            return 0;
        }
        T&& getFront() {
            if (sz > 0) {
                return arr[front];
            } else {
                return T{};
            }
        }
        int print() {
            if (front == -1) {
                return const_err_code;
            } else if (front <= rear) {
                for(int i=front; i<=rear; ++i) {
                    printf("%d(id%d) ", static_cast<int>(arr[i]), i);
                }
            } else {
                for(int i=front; i<capa; ++i) {
                    printf("+%d(id%d) ", static_cast<int>(arr[i]), i);
                }
                for(int i=0; i<=rear; ++i) {
                    printf("*%d(id%d) ", static_cast<int>(arr[i]), i);
                }
            }
            printf("\n");
            return 0;
        }

    private:
        int front, rear, capa, sz;
        T* arr;
};

void test() {
    cqueue<int> cq(5);
    cq.enq(10);
    cq.print();
    cq.enq(20);
    cq.print();
    cq.enq(30);
    cq.print();
    cq.enq(40);
    cq.print();
    cq.enq(50);
    cq.print();
    cq.enq(60);
    cq.print();
    cq.deq();
    cq.print();
    cq.deq();
    cq.print();
    cq.enq(70);
    cq.print();
    cq.enq(80);
    cq.print();
}

int main() {
    test();
    return 0;
}
