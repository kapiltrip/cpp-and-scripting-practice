// Teacher grants the members of Payroll access to its private salary.
#include <iostream>

class Teacher {
private:
    double salary;
public:
    Teacher(double startingSalary) : salary(startingSalary) {}
    friend class Payroll;
};

class Payroll {
public:
    void printSalary(const Teacher& teacher) const {
        std::cout << "Payroll salary: " << teacher.salary << '\n';
    }
};

int main() {
    Teacher t1(20000);
    Payroll payroll;
    payroll.printSalary(t1);
    return 0;
}
