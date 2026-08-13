#include <iostream>
#include <string>
#include <utility>

class Student {
public:
    std::string name;
    double* cgpaPtr{};

    Student(std::string student_name, double cgpa)
        : name{std::move(student_name)}, cgpaPtr{new double{cgpa}}
    {
    }

    Student(const Student& other)
        : name{other.name}, cgpaPtr{new double{*other.cgpaPtr}}
    {
        std::cout << "deep-copy constructor\n";
    }

    Student& operator=(const Student& other)
    {
        if (this == &other) {
            return *this;
        }

        auto* copied_cgpa = new double{*other.cgpaPtr};
        delete cgpaPtr;
        name = other.name;
        cgpaPtr = copied_cgpa;
        return *this;
    }

    Student(Student&& other) noexcept
        : name{std::move(other.name)}, cgpaPtr{std::exchange(other.cgpaPtr, nullptr)}
    {
    }

    Student& operator=(Student&& other) noexcept
    {
        if (this == &other) {
            return *this;
        }
        delete cgpaPtr;
        name = std::move(other.name);
        cgpaPtr = std::exchange(other.cgpaPtr, nullptr);
        return *this;
    }

    ~Student()
    {
        delete cgpaPtr;
        std::cout << "Student resource released\n";
    }

    void getInfo() const
    {
        std::cout << "name: " << name << '\n';
        std::cout << "cgpa: " << *cgpaPtr << '\n';
    }
};

int main()
{
    Student first{"Rahul Kumar", 8.9};
    Student second{first};

    *second.cgpaPtr = 9.2;
    first.getInfo();
    second.getInfo();
}
