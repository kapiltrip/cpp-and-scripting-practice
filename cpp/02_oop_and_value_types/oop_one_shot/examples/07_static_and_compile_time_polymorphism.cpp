#include <iostream>
#include <string>
#include <string_view>
#include <utility>

class Printer {
public:
    static void show(int value) { std::cout << "integer: " << value << '\n'; }
    static void show(std::string_view value)
    {
        std::cout << "text: " << value << '\n';
    }
};

class Score {
public:
    explicit Score(int points) : points_{points} {}

    [[nodiscard]] int points() const noexcept { return points_; }

    [[nodiscard]] Score operator+(const Score& other) const noexcept
    {
        return Score{points_ + other.points_};
    }

private:
    int points_{};
};

class Student {
public:
    explicit Student(std::string name)
        : id_{next_id_++}, name_{std::move(name)}
    {
    }

    [[nodiscard]] int id() const noexcept { return id_; }
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

private:
    inline static int next_id_{1};
    int id_{};
    std::string name_;
};

int next_call_number() noexcept
{
    static int call_count{0};
    return ++call_count;
}

int main()
{
    Printer::show(42);
    Printer::show("compile-time overload selection");

    const Score total = Score{35} + Score{45};
    std::cout << "combined score: " << total.points() << '\n';

    const Student first{"Kapil"};
    const Student second{"Aarav"};
    std::cout << first.name() << " has ID " << first.id() << '\n';
    std::cout << second.name() << " has ID " << second.id() << '\n';

    std::cout << "function call " << next_call_number() << '\n';
    std::cout << "function call " << next_call_number() << '\n';
}
