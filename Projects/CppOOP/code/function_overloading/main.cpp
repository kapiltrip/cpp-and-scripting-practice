// Function overloading: the compiler selects among same-name functions
// using their argument types. This is compile-time polymorphism.
#include <iostream>

class print {
public:
    void show(int x) const { std::cout << "int " << x << '\n'; }
    void show(char ch) const { std::cout << "char " << ch << '\n'; }
};

int main() {
    print p1;
    p1.show(6);   // Selects show(int).
    p1.show('k'); // Selects show(char).
    return 0;
}
