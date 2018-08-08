#include <iostream>
#include <list>
#include <vector>

namespace bkim {
    
    typedef struct _node {
        int data;
        struct _node* next;
    } node;
    
    template <typename T>
    class list {
        
    public:
        list() : _size(0), head(nullptr), tail(nullptr) {}
        ~list() {
            while(head != nullptr) {
                node* tmp = head;
                head = head->next;
                delete tmp;
            }
            std::cout<< "destructor .. ok" << std::endl;
        }
        
        void push_front(int data) {
            node* item = new node;
            item->data = data;
            item->next = head;
            if (head == nullptr) {
                tail = item;
            }
            head = item;
            ++_size;
        }
        void pop_front() {
            if (head != nullptr) {
                node* tmp = head;
                head = head->next;
                delete tmp;
                --_size;
            }
            if (head == nullptr) {
                tail = nullptr;
            }
            
        }
        int front() {
            return head != nullptr ? head->data : -1;
        }
        
        void push_back(int data) {
            node* item = new node;
            item->data = data;
            if (tail == nullptr) {
                item->next = nullptr;
                head = item;
                tail = item;
            } else {
                tail->next = item;
                tail = item;
            }
            ++_size;
            
        }
        void pop_back() {
            if (head != nullptr) {
                if (head == tail) {
                    delete tail;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    node *driver = head;
                    while(driver->next != tail) {
                        driver = driver->next;
                    }
                    node* tmp = tail;
                    driver->next = tail->next;
                    tail = driver;
                    delete tmp;
                }
                --_size;
            }
        }
        int back() {
            return tail != nullptr ? tail->data : -1;
            
        }
        void print() {
            node* driver = head;
            while(driver != nullptr) {
                std::cout << driver->data << " ";
                driver = driver->next;
            }
            std::cout << std::endl;
        }
        
        int size() {
            return _size;
        }
        
    private:
        int _size;
        node *head;
        node *tail;
    };
}

void test_custom_list();


int main() {
    
    test_custom_list();
    
    return 0;
}

void test_custom_list() {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    
    bkim::list<int> l;
    l.front();
    l.back();
    l.pop_front();
    l.pop_back();
    l.print();
    
    for(auto &item : arr) {
        l.push_front(item);
        l.push_back(item);
    }
    l.pop_front();
    l.pop_front();
    l.pop_back();
    l.pop_back();
    l.print();
    
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.print();
    
    std::cout << "size:" << l.size() << std::endl;
}
