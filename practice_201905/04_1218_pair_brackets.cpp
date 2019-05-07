/* '()', '[]', '{}', '<>' */
#include <cstdio>

const char left[4]{'(', '[', '{', '<'};
const char right[4]{')', ']', '}', '>'};
const static char errch = 'x';

template <typename T>
struct node {
    node(T t) : v(t) {}

    T v;
    node *prev = nullptr;
    node *next = nullptr;
};
class xstack {
   public:
    virtual ~xstack() {
        node<char> *tmp = nullptr;
        while (top) {
            tmp = top;
            top = top->prev;
            delete tmp;
        }
    }
    void push(char c) {
        node<char> *tmp = new node<char>(c);
        if (top == nullptr) {
            top = tmp;
        } else {
            top->next = tmp;
            tmp->prev = top;
            top = top->next;
        }
    }
    void pop() {
        if (top != nullptr) {
            node<char> *tmp = top;
            top = top->prev;
            delete tmp;
        }
    }
    char gettop() {
        if (top != nullptr) {
            return top->v;
        } else {
            return errch;
        }
    }

   private:
    node<char> *top = nullptr;
};

bool isLeft(char &c) {
    for (int i = 0; i < 4; ++i) {
        if (c == left[i]) {
            return true;
        }
    }
    return false;
}
int getIndexLeft(char &c) {
    for (int i = 0; i < 4; ++i) {
        if (c == left[i]) {
            return i;
        }
    }
    return -1;
}

bool solve() {
    int n;
    char str[1000]{0};
    char c{0};
    bool valid = true;
    xstack stack;
    scanf("%d", &n);
    scanf("%s", str);
    for (int i = 0; i < n; ++i) {
        c = str[i];
        if (valid != true) {
            continue;
        }
        if (isLeft(c) == true) {
            stack.push(c);
        } else {
            char pop = stack.gettop();
            stack.pop();
            /* invalid case
                case no.1 empty stack 
                case no.2 mis-pair
                */
            if (pop == errch || c != right[getIndexLeft(pop)]) {
                valid = false;
            }
        }
    }
    return valid;
}

int main() {
    freopen("04_1218_input.txt", "r", stdin);
    for (int i = 0; i < 10; ++i) {
        bool ans = solve();
        printf("#%d %d\n", i+1, ans == true ? 1 : 0);
    }
    return 0;
}

/* answer

#1 691
#2 9092
#3 8998
#4 9597
#5 8757
#6 10008
#7 10194
#8 10188
#9 9940
#10 8684
*/
