#include <iostream>
#include <string>
#include <utility>

class Person {
public:
    Person(std::string person_name, int person_age)
        : name{std::move(person_name)}, age{person_age}
    {
    }
    virtual ~Person() = default;

    std::string name;
    int age{};
};

class Student : public Person {
public:
    Student(std::string name, int age, int roll_number)
        : Person{std::move(name), age}, rollno{roll_number}
    {
    }

    int rollno{};

    void getInfo() const
    {
        std::cout << "name: " << name << '\n';
        std::cout << "age: " << age << '\n';
        std::cout << "roll number: " << rollno << '\n';
    }
};

class Teacher : public Person {
public:
    Teacher(std::string name, int age, std::string subject, double salary)
        : Person{std::move(name), age},
          subject{std::move(subject)},
          salary{salary}
    {
    }

    std::string subject;
    double salary{};
};

class TA final : public Student, public Teacher {
public:
    TA(std::string student_name, std::string teacher_name)
        : Student{std::move(student_name), 24, 17},
          Teacher{std::move(teacher_name), 24, "C++ lab", 20'000.0}
    {
    }
};

int main()
{
    Student student{"Kapil", 22, 101};
    student.getInfo();

    TA assistant{"Kapil the student", "Kapil the TA"};
    std::cout << "TA student role: " << assistant.Student::name << '\n';
    std::cout << "TA teacher role: " << assistant.Teacher::name << '\n';
}
