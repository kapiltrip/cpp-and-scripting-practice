#include <iostream>
#include <memory>
#include <numbers>
#include <string_view>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
    [[nodiscard]] virtual double area() const noexcept = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_{radius} {}

    [[nodiscard]] std::string_view name() const noexcept override
    {
        return "circle";
    }

    [[nodiscard]] double area() const noexcept override
    {
        return std::numbers::pi_v<double> * radius_ * radius_;
    }

private:
    double radius_{};
};

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height) : width_{width}, height_{height} {}

    [[nodiscard]] std::string_view name() const noexcept override
    {
        return "rectangle";
    }

    [[nodiscard]] double area() const noexcept override
    {
        return width_ * height_;
    }

private:
    double width_{};
    double height_{};
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

    for (const auto& shape : shapes) {
        std::cout << shape->name() << " area = " << shape->area() << '\n';
    }
}
