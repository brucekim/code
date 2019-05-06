#include <cstdio>

#define ERR 0x30303030
#define MAX_DEPTH 100

struct xstackbase {
    virtual ~xstackbase() = default;
    virtual int push(int item) = 0;
    virtual int gettop() = 0;
    virtual void pop() = 0;
    virtual void print() = 0;
};

class xstackarr : public xstackbase {
   public:
    virtual ~xstackarr() {}
    int push(int item) override {
        if (top_idx >= MAX_DEPTH) {
            return -1;
        }
        arr[++top_idx] = item;
        return 0;
    }

    int gettop() override {
        if (top_idx == -1) {
            printf("out of stack\n");
            return ERR;
        }
        return arr[top_idx];
    }

    void pop() override {
        if (top_idx >= 0) {
            --top_idx;
        }
    }

    void print() override {
        if (top_idx >= 0) {
            for (int i = 0; i <= top_idx; ++i)
                printf("%d ", arr[i]);
        }
        printf("\n");
    }

   private:
    int arr[MAX_DEPTH]{0};
    int top_idx = -1;
};

struct node {
    node(int _v) : v(_v), prev(nullptr), next(nullptr) {}

    int v;
    node *prev;
    node *next;
};

class xstackmem : public xstackbase {
   public:
    xstackmem() : top(nullptr) {}
    virtual ~xstackmem() {
        printf("delete... ");
        while (top != nullptr) {
            node *tmp = top;
            top = top->prev;
            printf("%d ", tmp->v);
            delete tmp;
        }
        printf("\n");
    }

    int push(int item) override {
        node *tmp = new node(item);
        if (top == nullptr) {
            top = tmp;
        } else {
            tmp->prev = top;
            top->next = tmp;
            top = top->next;
        }
        return 0;
    }
    int gettop() override {
        if (top == nullptr) {
            printf("out of stack\n");
            return ERR;
        } else {
            return top->v;
        }
    }
    void pop() override {
        if (top != nullptr) {
            node *tmp = top;
            top = top->prev;
            if (top != nullptr) {
                top->next = nullptr;
            }
            delete tmp;
        }
    }
    void print() override {
        node *tmp = top;
        while (tmp != nullptr) {
            printf("%d ", tmp->v);
            tmp = tmp->prev;
        }
        printf("\n");
    }

   private:
    node *top;
};

int main() {
    xstackmem s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.print();

    for (int i = 0; i < 10; ++i) {
        printf("top: %d\n", s.gettop());
        s.pop();
    }

    printf("end..\n");
    return 0;
}
