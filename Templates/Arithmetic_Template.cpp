/**
 * @file Arithmetic_Template.cpp
 * @brief Demonstration of Generic Programming using C++ Class Templates.
 * * Focus: Understanding compile-time polymorphism which is essential 
 * for building generic Data Structures in UCR CS010C.
 * * Time Complexity: O(1) for all operations.
 * Space Complexity: O(1) - constant space used per instance.
 */

#include <iostream>

using namespace std;

template<class T>
class Arithmetic {
private:
    T a;
    T b;

public:
    Arithmetic(T a, T b);
    T add();
    T sub();
};

template<class T>
Arithmetic<T>::Arithmetic(T a, T b) {
    this->a = a;
    this->b = b;
}

template<class T>
T Arithmetic<T>::add() {
    return a + b; // O(1)
}

template<class T>
T Arithmetic<T>::sub() {
    return a - b; // O(1)
}

int main() {
    // Demonstrating with float
    Arithmetic<float> ar(10.2, 5.4);
    cout << "Add (float): " << ar.add() << endl;
    cout << "Sub (float): " << ar.sub() << endl;

    // Demonstrating with int
    Arithmetic<int> ar2(10, 5);
    cout << "Add (int): " << ar2.add() << endl;

    return 0;
}
