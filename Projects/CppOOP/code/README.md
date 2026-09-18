# C++ topic examples

These 20 independent programs keep your Teacher, student, person, print, parent/child, and shape examples small. Each topic has its own folder and entry point. Run one at a time; several programs use the same class names.

## Exact run commands

Run these commands in a PowerShell terminal opened at the repository root. Each command compiles the selected source and runs the resulting program.

| Topic and source | Run command |
| --- | --- |
| [Classes and objects](classes_and_objects/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic classes_and_objects` |
| [Encapsulation](encapsulation/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic encapsulation` |
| [Constructors and this](constructors_and_this/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic constructors_and_this` |
| [Copy constructor](copy_constructor/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic copy_constructor` |
| [Shallow copy](shallow_copy/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic shallow_copy` |
| [Deep copy](deep_copy/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic deep_copy` |
| [Destructor](destructor/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic destructor` |
| [Inheritance](inheritance/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic inheritance` |
| [Function overloading](function_overloading/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic function_overloading` |
| [Constructor overloading](constructor_overloading/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic constructor_overloading` |
| [Operator overloading](operator_overloading/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic operator_overloading` |
| [Function overriding](function_overriding/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic function_overriding` |
| [Virtual functions and runtime polymorphism](virtual_functions/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic virtual_functions` |
| [Abstraction and abstract classes](abstraction/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic abstraction` |
| [Local static variables](static_local_variables/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic static_local_variables` |
| [Static data members and member functions](static_members/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic static_members` |
| [Friend function](friend_function/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic friend_function` |
| [Friend class](friend_class/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic friend_class` |
| [Object lifetime](object_lifetime/README.md) | `& ./Projects/CppOOP/code/run.ps1 -Topic object_lifetime` |
| [Type sizes](type_sizes/main.cpp) | `& ./Projects/CppOOP/code/run.ps1 -Topic type_sizes` |

Each linked topic explanation includes its runnable main.cpp source. The deep-copy class is in [student.hpp](deep_copy/student.hpp).

## Current practice and command list

[practice.cpp](../practice.cpp) is your current editable example. Run it or list every available command:

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic practice
& ./Projects/CppOOP/code/run.ps1 -List
```

If the terminal is already inside Projects/CppOOP, use `& ./code/run.ps1 -Topic virtual_functions`.

The runner uses the installed Visual Studio 2022 x64 compiler in C++20 mode with warnings treated as errors. Generated files stay in the ignored repository tmp folder. These programs need no C++23 features.

To compile and run every topic and refresh the PDF builder's output cache:

```powershell
& ./Projects/CppOOP/code/verify.ps1
```

## Read alongside the examples

The [companion PDF](../cpp-oop-notes.pdf) and [editable notes](../../../book/reading/classes-and-objects/README.md) explain each idea with focused snippets and exact book-page references. Definitions are lesson summaries.

The owning pointer remains visible in the deep-copy exercise because dynamic storage is the concept being practiced. Copy assignment is explicitly disabled there. A plain double cgpa member is sufficient when the goal is simply to store a grade.
