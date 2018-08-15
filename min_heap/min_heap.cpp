
#include <iostream>

using namespace std;

inline void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

class minheap
{
public:
    minheap(int _cap) : cap(_cap), sz(0) {
        arr = new int[cap];
    }
    ~minheap() {
        delete [] arr;
    }
    
    int parent(int i) {
        return (i-1) / 2;
    }
    int left(int i) {
        return 2*i + 1;
    }
    int right(int i) {
        return 2*i + 2;
    }

    void insert_key(int k);
    void decrease_key(int k, int v);
    void heapify(int i);
    int extract_min();
    int get_min();
    
    void delete_key(int k) {
        decrease_key(k, infinite);
        extract_min();
    }
private:
    int *arr;
    int cap;
    int sz;
    const static int infinite = -1;
};



void minheap::decrease_key(int k, int v) {
    arr[k] = v;
    int i = k;
    while(i != 0 && arr[parent(i)] > arr[i]) {
        swap(arr[parent(i)], arr[i]);
        i = parent(i);
    }
}

void minheap::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < sz && arr[l] < arr[i])
        smallest = l;
    if (r < sz && arr[r] < arr[smallest])
        smallest = r;
    if (i != smallest) {
        swap(arr[i], arr[smallest]);
        heapify(smallest);
    }
}

void minheap::insert_key(int k) {
    if (sz == cap) {
        cout << "overflow" << endl;
        return;
    }
    ++sz;
    int i = sz - 1;
    arr[i] = k;
    
    while(i != 0 && arr[parent(i)] > arr[i]) {
        swap(arr[parent(i)], arr[i]);
        i = parent(i);
    }
    
}

int minheap::extract_min() {
    if (sz == 0) {
        return infinite;
    } else if (sz == 1) {
        --sz;
        return arr[0];
    }
    int min = arr[0];
    arr[0] = arr[sz-1];
    heapify(0);
    --sz;
    return min;
}

int minheap::get_min() {
    return arr[0];
}


void test_driver() {
    minheap mh(11);
    mh.insert_key(3);
    mh.insert_key(2);
    
    mh.delete_key(1);
    
    mh.insert_key(15);
    mh.insert_key(5);
    mh.insert_key(4);
    mh.insert_key(45);
    
    cout << mh.extract_min() << endl;
    cout << mh.get_min() << endl;
    
    mh.decrease_key(2, 1);
    cout << mh.get_min() << endl;
}
int main(int argc, const char * argv[]) {
    test_driver();
    return 0;
}
