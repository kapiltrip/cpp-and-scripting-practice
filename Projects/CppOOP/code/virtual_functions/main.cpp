// Runtime polymorphism: compare your non-virtual getinfo and virtual hello.
#include <iostream>

class parent {
public:
    void getinfo() const { std::cout << "parent class\n"; }
    virtual void hello() const { std::cout << "hello from parent\n"; }
    virtual ~parent() = default;
};

class child : public parent {
public:
    void getinfo() const { std::cout << "child class\n"; } // Hides parent::getinfo.
    void hello() const override { std::cout << "hello from child\n"; }
};

int main() {
    child c1;
    std::cout << "Direct child calls\n";
    c1.getinfo();
    c1.hello();

    parent* p1 = &c1; // Points into c1; it does not create another object.
    std::cout << "Through parent pointer\n";
    p1->getinfo();
    p1->hello();

    parent& ref = c1;
    std::cout << "Through parent reference\n";
    ref.getinfo();
    ref.hello();
    return 0;
}
