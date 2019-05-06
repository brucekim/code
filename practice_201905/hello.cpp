#include <iostream>

using namespace std;
struct base {
    base() { cout << "base ctor" << endl; }
    virtual ~base() { cout << "base dtor" << endl; }
    virtual void hello() = 0;
};

class derived : public base {
   public:
    derived() { cout << "derived ctor" << endl; }
    virtual ~derived() { cout << "derived dtor" << endl; }
    virtual void hello() override {
        cout << "derived hello" << endl;
    }
};

int main() {
    derived s;
    return 0;
}
