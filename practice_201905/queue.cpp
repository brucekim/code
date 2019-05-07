#include <cstdio>

const int MAX_DEPTH = 5;
const int ERR_CODE = 0x3030'3030;

struct queueBase {
    virtual ~queueBase() = default;
    virtual void enque(int _item) = 0;
    virtual int deque() = 0;
    virtual int front() = 0;
    virtual void print() = 0;
};

class queueArr : public queueBase {
    public:
        virtual void enque(int _item) override {
            if (head == -1) {
                head = tail = 0;
                arr[tail++] = _item;
                ++sz_q;
            } else if (sz_q < MAX_DEPTH) {
                arr[tail] = _item;
                tail = (tail+1)%MAX_DEPTH;
                ++sz_q;
            } else {
                //queue is full
                printf("q - full\n");
            }
        }
        virtual int deque() override {
            if (head == -1) {
                return ERR_CODE;
            } else if (sz_q > 0) {
                head = (head+1)%MAX_DEPTH;
                --sz_q;
                return 0;
            } else {
                printf("q empty\n");
                return -1; //empty queue;
            }
        }
        virtual int front() override {
            if (head == -1) {
                return ERR_CODE;
            } else {
                return  arr[head];
            }
        }
        virtual void print() override {
            int s = head;
            for(int i=0; i<sz_q; ++i) {
                printf("%d(%d) ", arr[s], s);
                s = (s+1)%MAX_DEPTH;
            }
            printf("\n");
        }
    private:
        int arr[MAX_DEPTH]{0};
        int head = -1;
        int tail = -1;
        int sz_q = 0;

};

int main() {
    queueArr q;
    q.enque(10);
    q.enque(20);
    q.enque(30);
    q.enque(40);
    q.enque(50);
    q.enque(60);
    q.enque(70);
    q.deque();
    q.deque();
    q.deque();
    q.deque();
    q.deque();
    q.deque();

    q.print();
    return 0;
}
