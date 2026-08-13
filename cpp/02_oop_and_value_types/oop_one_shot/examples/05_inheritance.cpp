#include <iostream>
#include <string>
#include <utility>

class Person {
public:
    Person(std::string name, int age) : name_{std::move(name)}, age_{age} {}
    virtual ~Person() = default;

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] int age() const noexcept { return age_; }

private:
    std::string name_;
    int age_{};
};

class Student : public Person {
public:
    Student(std::string name, int age, int roll_number)
        : Person{std::move(name), age}, roll_number_{roll_number}
    {
    }

    [[nodiscard]] int roll_number() const noexcept { return roll_number_; }

private:
    int roll_number_{};
};

class GraduateStudent : public Student {
public:
    GraduateStudent(
        std::string name,
        int age,
        int roll_number,
        std::string thesis_topic)
        : Student{std::move(name), age, roll_number},
          thesis_topic_{std::move(thesis_topic)}
    {
    }

    [[nodiscard]] const std::string& thesis_topic() const noexcept
    {
        return thesis_topic_;
    }

private:
    std::string thesis_topic_;
};

class Employee {
public:
    explicit Employee(int employee_id) : employee_id_{employee_id} {}
    [[nodiscard]] int employee_id() const noexcept { return employee_id_; }

private:
    int employee_id_{};
};

class TeachingAssistant final : public GraduateStudent, public Employee {
public:
    TeachingAssistant(
        std::string name,
        int age,
        int roll_number,
        std::string thesis_topic,
        int employee_id)
        : GraduateStudent{
              std::move(name), age, roll_number, std::move(thesis_topic)},
          Employee{employee_id}
    {
    }
};

int main()
{
    TeachingAssistant assistant{
        "Aarav", 24, 42, "Energy-efficient processors", 7'001};

    std::cout << assistant.name() << " is student #"
              << assistant.roll_number() << " and employee #"
              << assistant.employee_id() << ".\n";
    std::cout << "Thesis: " << assistant.thesis_topic() << '\n';
}
