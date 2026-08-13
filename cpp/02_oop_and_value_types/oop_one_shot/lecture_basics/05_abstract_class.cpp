#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle final : public Shape {
public:
    void draw() const override { std::cout << "drawing a circle\n"; }
};

void draw_shape(const Shape& shape) { shape.draw(); }

int main()
{
    const Circle circle;
    draw_shape(circle);
}
