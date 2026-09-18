// sizeof measures storage in C++ bytes; CHAR_BIT gives the bits in one byte.
#include <climits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main() {
    std::cout << "CHAR_BIT = " << CHAR_BIT << '\n';
    std::cout << "Type | bytes\n";
    std::cout << "bool | " << sizeof(bool) << '\n';
    std::cout << "char | " << sizeof(char) << '\n';
    std::cout << "signed char | " << sizeof(signed char) << '\n';
    std::cout << "unsigned char | " << sizeof(unsigned char) << '\n';
    std::cout << "short int | " << sizeof(short int) << '\n';
    std::cout << "unsigned short int | " << sizeof(unsigned short int) << '\n';
    std::cout << "int | " << sizeof(int) << '\n';
    std::cout << "unsigned int | " << sizeof(unsigned int) << '\n';
    std::cout << "long int | " << sizeof(long int) << '\n';
    std::cout << "unsigned long int | " << sizeof(unsigned long int) << '\n';
    std::cout << "long long int | " << sizeof(long long int) << '\n';
    std::cout << "unsigned long long int | " << sizeof(unsigned long long int) << '\n';
    std::cout << "float | " << sizeof(float) << '\n';
    std::cout << "double | " << sizeof(double) << '\n';
    std::cout << "long double | " << sizeof(long double) << '\n';
    std::cout << "wchar_t | " << sizeof(wchar_t) << '\n';
    std::cout << "char8_t | " << sizeof(char8_t) << '\n';
    std::cout << "char16_t | " << sizeof(char16_t) << '\n';
    std::cout << "char32_t | " << sizeof(char32_t) << '\n';
    std::cout << "double* | " << sizeof(double*) << '\n';
    std::cout << "int minimum = " << std::numeric_limits<int>::lowest() << '\n';
    std::cout << "int maximum = " << std::numeric_limits<int>::max() << '\n';
    std::cout << "unsigned int maximum = "
              << std::numeric_limits<unsigned int>::max() << '\n';
    std::cout << "float guaranteed decimal digits = "
              << std::numeric_limits<float>::digits10 << '\n';
    std::cout << "double guaranteed decimal digits = "
              << std::numeric_limits<double>::digits10 << '\n';
    std::cout << "long double guaranteed decimal digits = "
              << std::numeric_limits<long double>::digits10 << '\n';
    std::cout << "float maximum = " << std::numeric_limits<float>::max() << '\n';
    std::cout << "double maximum = " << std::numeric_limits<double>::max() << '\n';
    std::cout << "Plain char is signed = " << std::boolalpha
              << std::numeric_limits<char>::is_signed << '\n';
    double cgpa = 8.19;
    double* cgpaptr = &cgpa;
    std::cout << "sizeof(cgpaptr) = " << sizeof(cgpaptr) << '\n';
    std::cout << "sizeof(*cgpaptr) = " << sizeof(*cgpaptr) << '\n';
    double values[3] = {8.19, 9.2, 7.5};
    std::cout << "sizeof(double[3]) = " << sizeof(values) << '\n';
    struct StudentHandle { std::string name; double* cgpaptr; };
    struct ExamplePadding { char grade; int rollno; };
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << '\n';
    std::cout << "sizeof(StudentHandle) = " << sizeof(StudentHandle) << '\n';
    std::cout << "sizeof(ExamplePadding) = " << sizeof(ExamplePadding) << '\n';
    std::cout << std::fixed << std::setprecision(20);
    std::cout << "8.19 stored as double = " << cgpa << '\n';
    return 0;
}
