#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class StudentProfile {
public:
    StudentProfile(std::string name, double cgpa)
        : name_{std::move(name)}, cgpa_{std::make_unique<double>(cgpa)}
    {
        validate_cgpa(*cgpa_);
    }

    StudentProfile(const StudentProfile& other)
        : name_{other.name_}, cgpa_{std::make_unique<double>(*other.cgpa_)}
    {
    }

    StudentProfile& operator=(const StudentProfile& other)
    {
        if (this == &other) {
            return *this;
        }

        auto copied_cgpa = std::make_unique<double>(*other.cgpa_);
        name_ = other.name_;
        cgpa_ = std::move(copied_cgpa);
        return *this;
    }

    StudentProfile(StudentProfile&&) noexcept = default;
    StudentProfile& operator=(StudentProfile&&) noexcept = default;
    ~StudentProfile() = default;

    void set_cgpa(double cgpa)
    {
        validate_cgpa(cgpa);
        *cgpa_ = cgpa;
    }

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] double cgpa() const noexcept { return *cgpa_; }

private:
    static void validate_cgpa(double cgpa)
    {
        if (cgpa < 0.0 || cgpa > 10.0) {
            throw std::invalid_argument{"CGPA must be in [0, 10]"};
        }
    }

    std::string name_;
    std::unique_ptr<double> cgpa_;
};

int main()
{
    StudentProfile original{"Kapil", 8.4};
    StudentProfile copy{original};
    copy.set_cgpa(9.1);

    std::cout << "original CGPA = " << original.cgpa() << '\n';
    std::cout << "copy CGPA     = " << copy.cgpa() << '\n';
}
