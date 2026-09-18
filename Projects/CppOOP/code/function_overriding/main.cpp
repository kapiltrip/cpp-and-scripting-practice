// Overriding supplies a derived implementation of a virtual base function.
#include <iostream>

class parent {
public:
    virtual void getinfo() const { std::cout << "parent class\n"; }
    virtual ~parent() = default;
};

class child : public parent {
public:
    void getinfo() const override { std::cout << "child class\n"; }
};

int main() {
    child c1;
    std::cout << "Direct call\n";
    c1.getinfo();
    parent& p1 = c1;
    std::cout << "Through parent reference\n";
    p1.getinfo(); // Dispatches to child::getinfo.
    return 0;
}
