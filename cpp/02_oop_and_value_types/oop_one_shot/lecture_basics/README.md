# Lecture-Linked Basics

These six programs deliberately keep the same class names and teaching sequence
used in the open Apna College lesson. They are the bridge between the video and
the more realistic programs under `../examples/`.

| File | Video idea kept recognizable | Small correction applied |
| --- | --- | --- |
| `01_teacher_basics.cpp` | `Teacher`, public properties, private salary, `changeDept`, constructors, `this` | getters are `const`; negative salary is rejected; initializer list used |
| `02_student_copy.cpp` | `Student`, `cgpaPtr`, copy constructor, shallow/deep copy, destructor | full rule of five; `delete`; source is `const Student&` |
| `03_inheritance.cpp` | `Person`, `Student`, `Teacher`, `TA` | virtual base destructor; constructors initialize all state |
| `04_polymorphism.cpp` | overloaded `Print::show`, `Parent`/`Child::getInfo` | `virtual` plus `override` so it demonstrates actual dynamic dispatch |
| `05_abstract_class.cpp` | abstract `Shape` and concrete `Circle` | pure virtual syntax and virtual destructor |
| `06_static_keyword.cpp` | function-local `static int x` and shared class state | inline static class member with clear lifetime output |

These files use modern initialization and warnings, but avoid hiding the basics
behind a larger architecture. Once you can recreate them from memory, move to
the corresponding `../examples/` file and compare the design choices.
