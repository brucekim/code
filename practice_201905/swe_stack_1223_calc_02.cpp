/*
https://www.swexpertacademy.com/main/learn/course/lectureProblemViewer.do
*/
#include <cstdio>

template <typename T>
struct node {
   public:
    node(T &_data, node<T> *_prev = nullptr, node<T> *_next = nullptr) : data(_data), prev(_prev), next(_next) {}
    T data;
    node<T> *prev;
    node<T> *next;
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
    void push_back(T data) {
        node<T> *tmp = new node<T>(data);
        if (head == nullptr) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }

   private:
    node<T> *head;
    node<T> *tail;
};

template <typename T>
class xstack {
   public:
    xstack() : tail(nullptr), sz(0) {}
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
            tmp->prev = tail;
            tail->next = tmp;
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
    bool isEmpty() {
        return sz == 0;
    }
    T top() {
        if (tail != nullptr) {
            return tail->data;
        } else {
            return err_code;
        }
    }

   private:
    int sz;
    const int err_code = 0x30303030;
    node<T> *tail;
};

bool isDigit(const char &c) {
    if (c >= '0' && c <= '9') {
        return true;
    } else {
        return false;
    }
}

int op_prio(char c) {
    int ret = 0;
    switch (c) {
        case '*': {
            ret = 10;
            break;
        }
        case '+': {
            ret = 9;
            break;
        }
        default: {
            ret = 0;
            break;
        }
    }
    return ret;
}

void solve() {
    const int max_sz = 1000;
    int n;
    char arr[max_sz]{0};
    xstack<char> stack_op;
    xstack<int> stack_calc;
    xlist<char> list_postfix;

    auto calc = [](int &opd_l, int &opd_r, const char &op) -> int {
        int ans = 0;
        switch(op) {
            case '*' : {
                ans = opd_l * opd_r;
                break;
            }
            case '+' : {
                ans = opd_l + opd_r;
                break;
            }
            default :
            break;
        }
        return ans;
    };
 
    /* input */
    scanf("%d", &n);
    scanf("%s", arr);

    for (int i = 0; i < n; ++i) {
        if (isDigit(arr[i]) == true) {
            list_postfix.push_back(arr[i]);
        } else {  // opreator
            if (stack_op.isEmpty() == true || op_prio(stack_op.top()) <= op_prio(arr[i])) {
                stack_op.push_back(arr[i]);
            } else {
                while (stack_op.isEmpty() != true || op_prio(stack_op.top()) > op_prio(arr[i])) {
                    list_postfix.push_back(stack_op.top());
                    stack_op.pop();
                }
                stack_op.push_back(arr[i]);
            }
        }
    }
    while(stack_op.isEmpty() != true) {
        list_postfix.push_back(stack_op.top());
        stack_op.pop();
    }

    xlist<char>::iterator end = list_postfix.end();
    for (xlist<char>::iterator it = list_postfix.begin(); it != end; ++it) {
        if (isDigit(*it) == true) {
            stack_calc.push_back(*it - '0');
        } else {
            int opd_r = stack_calc.top();
            stack_calc.pop();
            int opd_l = stack_calc.top();
            stack_calc.pop();
            stack_calc.push_back(calc(opd_l, opd_r, *it));
        }
    }
   printf("%d\n", stack_calc.top());

}

int main() {
    freopen("inputs/swe_stack_1223_input.txt", "r", stdin);
    for (int i = 0; i < 10; ++i) {
        printf("#%d ", i + 1);
        solve();
    }
    return 0;
}
