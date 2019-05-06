#include <cstdio>

namespace bkim {
    class stack {
        public:
            stack() {
                printf("hello\n");
            }
            ~stack() {
                printf("bye\n");
            }
    };
}

using namespace bkim;

int main() {

    stack s;

    return 0;
}
