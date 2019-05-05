#include <iostream>

using namespace std;

class Apple {
    public:
        Apple() {
            cout << "Apple(): " << this << " cnt: " << cnt << endl;
            ++cnt;
        }
        ~Apple() {
            cout << "~Apple(): " << this << endl;
        }
    private:
        int x;
        int y;
        static int cnt;
};

int Apple::cnt = 0;

void *operator new(size_t _sz, Apple* p) {
    cout << "call operator new: " << p << endl;
    return p;
}

int main() {
    Apple *a = static_cast<Apple*>(operator new((sizeof(Apple)*10)));

    for (int i=0; i<10; ++i) {
        new (&a[i]) Apple();
    }

    /* 1. it should call destructor explicitly if it call operator new and placement new
     * 2. then call delete *pointer
     */

    for (int i=0; i<10; ++i) {
        a[i].~Apple();
        
    }
    delete a;

    return 0;
}
