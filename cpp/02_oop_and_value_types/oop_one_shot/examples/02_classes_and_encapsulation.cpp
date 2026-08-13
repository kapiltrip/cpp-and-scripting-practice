#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Teacher {
public:
    Teacher(
        std::string name,
        std::string department,
        std::string subject,
        double monthly_salary)
        : name_{std::move(name)},
          department_{std::move(department)},
          subject_{std::move(subject)},
          monthly_salary_{monthly_salary}
    {
        if (name_.empty() || department_.empty() || subject_.empty()) {
            throw std::invalid_argument{"teacher fields must not be empty"};
        }
        if (monthly_salary_ < 0.0) {
            throw std::invalid_argument{"salary must not be negative"};
        }
    }

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] const std::string& department() const noexcept
    {
        return department_;
    }
    [[nodiscard]] const std::string& subject() const noexcept { return subject_; }
    [[nodiscard]] double monthly_salary() const noexcept
    {
        return monthly_salary_;
    }

    void change_department(std::string department)
    {
        if (department.empty()) {
            throw std::invalid_argument{"department must not be empty"};
        }
        department_ = std::move(department);
    }

private:
    std::string name_;
    std::string department_;
    std::string subject_;
    double monthly_salary_{};
};

int main()
{
    Teacher teacher{"Shradha", "Computer Science", "C++", 80'000.0};
    teacher.change_department("Software Engineering");

    std::cout << teacher.name() << " teaches " << teacher.subject()
              << " in " << teacher.department() << ".\n";
    std::cout << "Monthly salary: " << teacher.monthly_salary() << '\n';
}
