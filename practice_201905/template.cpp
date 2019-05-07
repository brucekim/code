#include <cstdio>

template <typename T>
struct node {
    node(T& _v) : v(_v) {}
    T v;
};

int main() {
    char c = 'x';
    node<char> *n = new node<char>(c);
    printf("%c \n", n->v);
    delete n;
    return 0;
}
