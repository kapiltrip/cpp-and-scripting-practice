// Abstraction exposes draw() while circle supplies its implementation.
#include <iostream>

class shape {
public:
    virtual void draw() const = 0; // Pure virtual: shape is abstract.
    virtual ~shape() = default;
};

class circle : public shape {
public:
    void draw() const override { std::cout << "Drawing a circle\n"; }
};

void showShape(const shape& item) {
    item.draw(); // Uses the interface without depending on circle's internals.
}

int main() {
    // shape s1; // Cannot construct an object of the abstract class shape.
    circle c1;
    showShape(c1);
    return 0;
}
