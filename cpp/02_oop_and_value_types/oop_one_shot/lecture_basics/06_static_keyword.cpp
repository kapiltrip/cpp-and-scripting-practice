#include <iostream>

void fun()
{
    static int x{0};
    std::cout << "x: " << x << '\n';
    ++x;
}

class Student {
public:
    Student() : roll_number_{next_roll_number_++} {}

    [[nodiscard]] int roll_number() const noexcept { return roll_number_; }

private:
    inline static int next_roll_number_{100};
    int roll_number_{};
};

int main()
{
    fun();
    fun();
    fun();

    const Student first;
    const Student second;
    std::cout << "first roll number: " << first.roll_number() << '\n';
    std::cout << "second roll number: " << second.roll_number() << '\n';
}
