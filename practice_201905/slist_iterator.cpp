/* linked list + iterator */
#include <cstdio>

template <typename T>
struct node {
    node(T _data, node *_next=nullptr) : data(_data), next(_next) {}
    T data;
    node *next;
};

template <typename T>
class slist_iterator {
    public:
        slist_iterator(node<T> *_node) : current(_node) {}
        slist_iterator& operator ++() {
            current = current->next;
            return *this;
        }
        bool operator !=(const slist_iterator<T>& it) const {
            return current != it.current;
        }
        T& operator *() {
            return current->data;
        }
        node<T> *current;
};

template <typename T>
class slist {
    public:
        slist() : head(nullptr) {}

        using iterator = slist_iterator<T>;
        iterator begin() {
            return slist_iterator<T>(head);
        }
        iterator end() {
            return slist_iterator<T>(nullptr);
        }
        void push_front(const T& data) {
            head = new node<T>(data, head);
        }
        void print() {
            node<T> *tmp = head;
            while(tmp != nullptr) {
                printf("%d ", static_cast<int>(tmp->data));
                tmp = tmp->next;
            }
            printf("\n");
        }
    private:
        node<T> *head;
};

void test() {
    slist<int> l;
    l.push_front(10);
    l.push_front(20);
    l.push_front(30);
    l.push_front(40);
    l.push_front(50);

    for(slist<int>::iterator it = l.begin(); it != l.end(); ++it) {
        printf("(%d) ", *it);
    }
    printf("\n");
    printf("print..:");
    l.print();

}

int main(void) {
    test();
    return 0;
}
