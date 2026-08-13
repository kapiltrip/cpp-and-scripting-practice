#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Teacher {
private:
    double salary_{};

public:
    std::string name;
    std::string dept;
    std::string subject;

    Teacher() : dept{"Computer Science"} {}

    Teacher(std::string teacher_name, std::string teacher_dept)
        : name{std::move(teacher_name)}, dept{std::move(teacher_dept)}
    {
    }

    Teacher(
        std::string name,
        std::string dept,
        std::string subject,
        double salary)
        : salary_{salary},
          name{std::move(name)},
          dept{std::move(dept)},
          subject{std::move(subject)}
    {
        if (salary_ < 0.0) {
            throw std::invalid_argument{"salary cannot be negative"};
        }
    }

    void changeDept(std::string new_dept) { dept = std::move(new_dept); }

    void setSalary(double salary)
    {
        if (salary < 0.0) {
            throw std::invalid_argument{"salary cannot be negative"};
        }
        this->salary_ = salary;
    }

    [[nodiscard]] double getSalary() const noexcept { return salary_; }

    void getInfo() const
    {
        std::cout << "name: " << name << '\n';
        std::cout << "subject: " << subject << '\n';
        std::cout << "department: " << dept << '\n';
        std::cout << "salary: " << getSalary() << '\n';
    }
};

int main()
{
    Teacher teacher{"Shradha", "Computer Science", "C++", 25'000.0};
    teacher.changeDept("Engineering");
    teacher.getInfo();
}
