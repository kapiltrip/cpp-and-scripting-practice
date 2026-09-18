// Encapsulation groups data with operations and exposes a controlled interface.
#include <iostream>
#include <string>

class Teacher {
    double salary = 0.0; // Class members are private by default.
                        // Use sizeof(double) to measure its size in bytes.
public:
    std::string name;
    std::string dept;
    std::string subject;

    bool setSalary(double newSalary) {
        if (newSalary >= 0.0) {
            salary = newSalary;
            return true;
        }
        return false; // Invalid updates leave salary unchanged.
    }

    double getSalary() const { return salary; }
};

int main() {
    Teacher t1;
    t1.name = "Kapil";
    t1.setSalary(20000.0);
    std::cout << "Name: " << t1.name << '\n';
    std::cout << "Salary: " << t1.getSalary() << '\n';
    std::cout << "Negative salary accepted: "
              << std::boolalpha << t1.setSalary(-500.0) << '\n';
    std::cout << "Salary after rejected update: " << t1.getSalary() << '\n';
    // t1.salary = 500.0; // Inaccessible: salary is private.
    return 0;
}
