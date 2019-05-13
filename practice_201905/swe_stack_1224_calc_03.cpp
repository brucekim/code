/*
#1 672676
#2 1974171
#3 12654
#4 38756
#5 4035
#6 155304
#7 6964
#8 2819
#9 24711
#10 208785

infix
“3+(4+5)*6+7”
postfix
"345+6*+7+"

to do
*/
#include <cstdio>

template <typename T>
struct node {
    node(T &_data) : data(_data), next(nullptr), prev(nullptr) {}
    T data;
    node<T> *next;
    node<T> *prev;
};

template <typename T>
class xlist_iterator {
    public:
    xlist_iterator(node<T> *it) : current(it) {}

    xlist_iterator<T>& operator++() {
        current = current->next;
        return *this;
    }

    bool operator!=(const xlist_iterator<T> &it) const {
        return current != it.current;
    }
    bool operator==(const xlist_iterator<T> &it) const {
        return current == it.current;
    }
    T operator*() {
        return current->data; }

    private:
    node<T> *current;
};

template <typename T>
class xlist {
    public:
    xlist() : head(nullptr), tail(nullptr) {}
    virtual ~xlist() {
        while(head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    using iterator = xlist_iterator<T>;
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
        while(tail != nullptr) {
            node<T> *tmp = tail;
            tail = tail->prev;
        }
    }
    void push_back(T data) {
        node<T> *tmp = new node<T>(data);
        ++sz;
        if (tail == nullptr) {
            tail = tmp;
        } else {
            tmp->prev = tail;
            tail = tmp;
        }
    }
    T& top() {
        if (sz == 0) {
            printf("empty stack \n");
            return err_code;
        } else {
            return tail->data;
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

    private:
    T err_code = static_cast<T>(0xFFFFFFFF);
    node<T> *tail;
    int sz;
};

struct utils {
    bool isDigit(char c) {
        if (c >= '0' && c <= '9') {
            return true;
        } else {
            return false;
        }
    }
    int prio(char &c) {
        int ans = 0;
        switch(c) {
            case '(': {
                ans = 0;
                break;
            }
            case '+': {
                ans = 1;
                break;
            }
            case '*': {
                ans = 2;
                break;
            }
        }
        return ans;
    }
    int expr(int opd_l, int opd_r, char op) {
        int ans = 0;
        switch(op) {
            case '+': {
                ans = opd_l + opd_r;
                break;
            }
            case '*': {
                ans = opd_l * opd_r;
                break;
            }
        }
        return ans;
    }
};

void solve() {
    const int max_str = 1000;
    int n;
    char arr[max_str]{0};
    char c;
    xstack<char> stack_op;
    xstack<int> stack_calc;
    xlist<char> list_postfix;
    utils util;

    /* input */
    scanf("%d", &n);
    scanf("%s", arr);
    for (int i=0; i<n; ++i) {
        c = arr[i];
        if (util.isDigit(c) == true) {
            list_postfix.push_back(c);
        } else {
            if (stack_op.isEmpty() == true || c == '(' ||
                    util.prio(stack_op.top()) <= util.prio(c)) {
                stack_op.push_back(c);
            } else if (c == ')') {
                while(stack_op.top() != '(') {
                    list_postfix.push_back(stack_op.top());
                    stack_op.pop();
                }
                stack_op.pop();
            }
            else {
                while(stack_op.isEmpty() != true && util.prio(stack_op.top()) >= util.prio(c)) { //2019.05.14 '>=' 여기 헷갈리는 포인트
                    list_postfix.push_back(stack_op.top());
                    stack_op.pop();
                }
                stack_op.push_back(c);
            }
        }
    }
    while (stack_op.isEmpty() != true) {
        list_postfix.push_back(stack_op.top());
        stack_op.pop();
    }
    xlist<char>::iterator end = list_postfix.end();
    for (xlist<char>::iterator it = list_postfix.begin(); it != end; ++it) {
        if (util.isDigit(*it) == true) {
            stack_calc.push_back(*it - '0');
        } else {
            int opd_r = stack_calc.top();
            stack_calc.pop();
            int opd_l = stack_calc.top();
            stack_calc.pop();
            stack_calc.push_back(util.expr(opd_l, opd_r, *it));
        }
    }
    printf("%d\n", stack_calc.top());

}

int main() {
    freopen("inputs/swe_stack_1224_input.txt", "r", stdin);
    for (int i = 0; i < 10; ++i) {
        printf("#%d ", i+1);
        solve();
    }
    return 0;
}
