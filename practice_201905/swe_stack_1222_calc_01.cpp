/*
*/
#include <cstdio>
template <typename T>
struct node {
    node(T _data, node<T> *_prev = nullptr, node<T> *_next = nullptr) : data(_data), prev(_prev), next(_next) {}
    T data;
    node<T> *next;
    node<T> *prev;
};

template <typename T>
class xlist_iterator {
   public:
    xlist_iterator(node<T> *it) : current(it) {}
    xlist_iterator &operator++() {
        current = current->next;
        return *this;
    }
    T &operator*() {
        return current->data;
    }
    bool operator!=(const xlist_iterator<T> &it) const {
        return current != it.current;
    }
    bool operator==(const xlist_iterator<T> &it) const {
        return current == it.current;
    }

   private:
    node<T> *current;
};

template <typename T>
class xlist {
   public:
    using iterator = xlist_iterator<T>;
    xlist() : head(nullptr), tail(nullptr) {}
    virtual ~xlist() {
        while (head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    xlist_iterator<T> begin() {
        return xlist_iterator<T>(head);
    }
    xlist_iterator<T> end() {
        return xlist_iterator<T>(nullptr);
    }
    void push_back(T data) {
        node<T> *tmp = new node<T>(data);
        if (head == nullptr) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
    }

   private:
    node<T> *head;
    node<T> *tail;
};

template <typename T>
class xstack {
   public:
   xstack() : tail(nullptr) {}
    virtual ~xstack() {
        while (tail != nullptr) {
            node<T> *tmp = tail;
            tail = tail->prev;
            delete tmp;
        }
    }
    void push_back(T data) {
        node<T> *tmp = new node<T>(data);
        ++sz;
        if (tail == nullptr) {
            tail = tmp;
        } else {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tail->next;
        }
    }
    void pop() {
        if (tail != nullptr) {
            node<T> *tmp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            delete tmp;
            --sz;
        }
    }
    T top() const {
        if (tail != nullptr) {
            return tail->data;
        } else {
            return err_code;
        }
    }
    bool isEmpty() {
        return sz == 0;
    }

   private:
    int sz = 0;
    node<T> *tail;
    const int err_code = 0x30303030;
};

void solve() {
    const int max_sz = 1000;
    int n;
    char arr[max_sz]{0};
    xstack<char> op_stack;
    xlist<char> postfix;
    xstack<int> calc_stack;

    /* input */
    scanf("%d", &n);
    scanf("%s", arr);

    //gen postfix from prefix
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= '0' && arr[i] <= '9') {
            postfix.push_back(arr[i]);
        } else {
            if (op_stack.isEmpty() == true) {
                op_stack.push_back(arr[i]);
            } else {
                char c = op_stack.top();
                op_stack.pop();
                postfix.push_back(c);
                op_stack.push_back(arr[i]);
            }
        }
    }
    while (op_stack.isEmpty() != true) {
        char c = op_stack.top();
        op_stack.pop();
        postfix.push_back(c);
    }
    xlist<char>::iterator end = postfix.end();
    /*
    printf("postfix: ");
    for (xlist<char>::iterator it = postfix.begin(); it != end; ++it) {
        printf("%c ", *it);
    }
    printf("\n");
    */
    for (xlist<char>::iterator it = postfix.begin(); it != end; ++it) {
        if (*it >= '0' && *it <= '9') {
            calc_stack.push_back(*it - '0');
        } else {
            int opd_r = calc_stack.top();
            calc_stack.pop();
            int opd_l = calc_stack.top();
            calc_stack.push_back(opd_r + opd_l);
        }
    }
    printf("%d\n", calc_stack.top());
}
int main(void) {
    freopen("inputs/swe_stack_1222_input.txt", "r", stdin);
    for (int i = 0; i < 10; ++i) {
        printf("#%d ", i+1);
        solve();
    }
    return 0;
}
