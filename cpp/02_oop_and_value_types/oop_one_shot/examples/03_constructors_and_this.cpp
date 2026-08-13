#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Course {
public:
    Course() : Course{"Untitled course", 1} {}

    explicit Course(std::string name) : Course{std::move(name), 1} {}

    Course(std::string name, int credits)
        : name_{std::move(name)}, credits_{credits}
    {
        validate();
    }

    Course& rename(std::string name)
    {
        if (name.empty()) {
            throw std::invalid_argument{"course name must not be empty"};
        }
        this->name_ = std::move(name);
        return *this;
    }

    Course& set_credits(int credits)
    {
        this->credits_ = credits;
        validate();
        return *this;
    }

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] int credits() const noexcept { return credits_; }

private:
    void validate() const
    {
        if (name_.empty()) {
            throw std::invalid_argument{"course name must not be empty"};
        }
        if (credits_ <= 0) {
            throw std::invalid_argument{"credits must be positive"};
        }
    }

    std::string name_;
    int credits_{};
};

int main()
{
    Course course{"Object-Oriented Programming", 4};
    course.rename("Modern C++ OOP").set_credits(5);

    std::cout << course.name() << " carries " << course.credits()
              << " credits.\n";
}
