// Current practice: virtual-function overriding in your parent/child example.
// More focused examples and run commands are in code/README.md.
#include <iostream>

class parent {
public:
    void getinfo() const { std::cout << "parent class\n"; }
    virtual void hello() const { std::cout << "hello from parent\n"; }
    virtual ~parent() = default;
};

class child : public parent {
public:
    // The base getinfo is non-virtual; this declaration hides it.
    void getinfo() const { std::cout << "child class\n"; }
    // hello overrides the virtual base function; override checks the signature.
    void hello() const override { std::cout << "hello from child\n"; }
};

int main() {
    child c1;
    c1.hello();

    parent& p1 = c1; // The reference denotes the parent portion of c1.
    p1.getinfo();    // Non-virtual: parent::getinfo.
    p1.hello();      // Virtual: child::hello, because the object is a child.
    return 0;
}
