# Constructor overloading

**Interview definition (summary):** Constructor overloading provides constructors with different parameter lists so objects of one class can be initialized in different ways. The compiler selects the applicable constructor from the supplied arguments.

[Runnable source](main.cpp) | [Companion PDF, page 14](../../cpp-oop-notes.pdf#page=14)

Your student example needs two starting states: an object created without a supplied name, and an object created with a name. Both constructors initialize a new student. A constructor has the class's name and no return type.

```cpp
class student {
public:
    std::string name;
    student() : name("Unknown") {
        std::cout << "Non-parameterized constructor\n";
    }
    student(const std::string& studentName) : name(studentName) {
        std::cout << "Parameterized constructor\n";
    }
};
```

The initializer lists give name its initial value before either constructor body runs. The const reference in the second constructor supplies an existing string without making the parameter a separate string copy; the member name still receives its own value.

```cpp
student s1;          // selects student()
student s2("Kapil"); // selects the constructor taking a string
```

| Declaration | Selected constructor | Initial name |
| --- | --- | --- |
| student s1 | No arguments | Unknown |
| student s2("Kapil") | One string argument | Kapil |

This selection is a form of compile-time polymorphism. Adding s1.name = "Kapil" afterward would assign to an already existing member; it would not call a constructor again. In the second declaration, the string literal can be used to supply a std::string argument.

Write `student s1;` for this no-argument construction. The declaration `student s1();` instead declares a function named s1 returning student. This syntax distinction matters when the goal is to create an object.

Run from the repository root:

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic constructor_overloading
```

**Source:** Stroustrup, [The C++ Programming Language, 4th edition, section 16.2.5 Constructors, PDF pages 624-625](../../../../book/The%20C%2B%2B%20Programming%20Language%20-%204th%20Edition.pdf#page=624). The book overloads Date constructors; this lesson keeps your student example.
