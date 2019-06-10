#include <cstdio>

const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;


template <typename T>
struct node {
    node(T _data) : data(_data), next(nullptr) {}
    T data;
    node<T> *next;
};

template <typename T>
class xlist_iterator {
    public:
        xlist_iterator(node<T> *it) : current(it) {}

        T& operator*() {
            return current->data;
        }
        xlist_iterator<T>& operator++() {
            current = current->next;
            return *this;
        }
        bool operator!= (const xlist_iterator<T> &it) {
            return current != it.current;
        }
        bool operator== (const xlist_iterator<T> &it) {
            return current == it.current;
        }
    private:
        node<T> *current;
};

template <typename T>
class xlist {
    public:
        using iterator = xlist_iterator<T>;
        xlist() : head(nullptr), tail(nullptr), sz(0) {}
        virtual ~xlist() {
            while(head != nullptr) {
                node<T> *tmp = head;
                head = head->next;
                delete tmp;
            }
        }

        void push_back(T data) {
            node<T> *tmp = new node<T>(data);
            ++sz;
            if (head == nullptr) {
                head = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tail->next;
            }
        }
        void sort() {
            merge_sort(&head);
        }
        void merge_sort(node<T> **href) {

            node<T> *h = *href;
            node<T> *a = nullptr;
            node<T> *b = nullptr;

            if (h == nullptr || h->next == nullptr) {
                return;
            }

            split(h, &a, &b);

            merge_sort(&a);
            merge_sort(&b);

            *href = merge(a, b);
        }

        void split(node<T> *src, node<T> **fref, node<T> **bref) {
            node<T> *fast;
            node<T> *slow;
            slow = src;
            fast = src->next;

            while(fast != nullptr) {
                fast = fast->next;
                if (fast != nullptr) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            *fref = src;
            *bref = slow->next;
            slow->next = nullptr;
        }
        node<T> *merge(node<T> *a, node<T> *b) {
            node<T> *result = nullptr;

            if (a == nullptr)
                return b;
            else if (b == nullptr)
                return a;

            if (a->data <= b->data) {
                result = a;
                result->next = merge(a->next, b);
            } else {
                result = b;
                result->next = merge(a, b->next);
            }
            return result;
        }
        node<T> *getHead() {
            return head;
        }
        iterator begin() {
            return xlist_iterator<T>(head);
        }
        iterator end() {
            return xlist_iterator<T>(nullptr);
        }
        void print() {
            xlist<int>::iterator it = begin();
            xlist<int>::iterator _end = end();
            for(; it != _end; ++it) {
                printf("%d ", *it);
            }
        }

    private:
        node<T> *head, *tail;
        int sz;
};

void solve() {
    xlist<int> l1;
    l1.push_back(50);
    l1.push_back(40);
    l1.push_back(30);
    l1.push_back(20);
    l1.push_back(10);

    printf("befor sort: \n");
    l1.print();
    
    printf("\nafter sort: \n");
    l1.sort();
    l1.print();
}

int main() {
    solve();
    return 0;
}
