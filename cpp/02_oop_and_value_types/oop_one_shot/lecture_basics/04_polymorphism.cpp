#include <iostream>
#include <string_view>

class Print {
public:
    void show(int value) const { std::cout << "int: " << value << '\n'; }

    void show(char value) const { std::cout << "char: " << value << '\n'; }

    void show(std::string_view value) const
    {
        std::cout << "text: " << value << '\n';
    }
};

class Parent {
public:
    virtual ~Parent() = default;
    virtual void getInfo() const { std::cout << "parent class\n"; }
};

class Child final : public Parent {
public:
    void getInfo() const override { std::cout << "child class\n"; }
};

void describe(const Parent& object) { object.getInfo(); }

int main()
{
    const Print printer;
    printer.show(10);
    printer.show('K');
    printer.show("function overloading");

    const Parent parent;
    const Child child;
    describe(parent);
    describe(child);
}
