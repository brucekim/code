//
//  main.cpp
//  animal_shelter_3_7.cpp
//
//  Created by 김인태 on 2018. 8. 19..
//  Copyright © 2018년 김인태. All rights reserved.
//

#include <iostream>
#include <queue>
#include <string>
#include <typeinfo>
#include <utility>

using namespace std;

namespace b {
    class Animal {
    public:
        Animal(string _name) : name(_name) {}
        virtual void toString() = 0;
        string GetName() {
            return name;
        }
    private:
        string name;
    };
    class Dog : public Animal {
    public:
        Dog(string _name) : b::Animal(_name) {}
        virtual void toString() {
            cout << "Dog: " << GetName() << endl;
        }
    };
    
    class Cat : public Animal {
    public:
        Cat(string _name) : b::Animal(_name) {}
        virtual void toString() {
            cout << "Cat: " << GetName() << endl;
        }
    };
    
    class Shelter {
    public:
        Shelter() {}
        
        void enqueue(Animal new_animal) {
            if (typeid(new_animal).name() == typeid(Cat).name()) {
                q_cat.push(make_pair(new_animal, cnt));
            }
            else if (typeid(new_animal).name() == typeid(Dog).name()) {
                q_dog.push(make_pair(new_animal, cnt));
            }
            
        }
        Animal dequeueAny() {
            
        }
        /*
        Dog dequeueDog() {
            
        }
        Cat dequeueCat() {
            
        }
         */
    private:
        queue<pair<Cat, int> > q_cat;
        queue<pair<Dog, int> > q_dog;
        int cnt = 0;
    };
}

void test() {
    b::Shelter s;
    s.enqueue(b::Dog("둥이"));
    s.enqueue(b::Dog("야옹이1"));
    s.enqueue(b::Dog("로미"));
    s.enqueue(b::Dog("야옹이2"));
    s.enqueue(b::Dog("꼬리"));
}
int main(int argc, const char * argv[]) {
    test();
    return 0;
}

