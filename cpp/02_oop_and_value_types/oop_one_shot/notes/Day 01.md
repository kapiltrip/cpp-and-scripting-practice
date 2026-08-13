# Day 01 - C++ Memory Foundations and Object-Oriented Programming

Source lesson: [OOPs Tutorial in One Shot - Apna College](https://www.youtube.com/watch?v=mlIUKyZIUUU)

Original scan: [oop-one-shot-handwritten-notes.pdf](source/oop-one-shot-handwritten-notes.pdf)

Code is intentionally provided in two layers: the
[lecture-linked basics](../lecture_basics/README.md) preserve her class names
and progression, while `../examples/` applies the same ideas with modern
ownership and interface design.

The scan contains 20 pages. Pages 1-7 establish the memory and reference model
needed for copying and destruction; pages 8-20 follow the lesson's OOP chapter.
The explanations below preserve that order, correct a few simplified classroom
statements, and connect each code-bearing topic to a complete runnable program.

## Page index

| Page | Topic rendered and explained below |
| ---: | --- |
| 1 | [Data structures, arrays, storage, and main memory](#page-01) |
| 2 | [Persistent data, databases, data mining, and big data](#page-02) |
| 3 | [Process address space: code, stack, and dynamic storage](#page-03) |
| 4 | [Function calls, activation records, and automatic variables](#page-04) |
| 5 | [Dynamic arrays, pointers, and data-structure memory](#page-05) |
| 6 | [Pointer swap versus reference swap](#page-06) |
| 7 | [Reference parameters and the call stack](#page-07) |
| 8 | [OOP, classes, objects, attributes, and methods](#page-08) |
| 9 | [Access control, encapsulation, and constructors](#page-09) |
| 10 | [Constructor overloads and the `this` pointer](#page-10) |
| 11 | [Copy construction and shallow copy](#page-11) |
| 12 | [Building a deep copy](#page-12) |
| 13 | [Copy assignment, destruction, and RAII](#page-13) |
| 14 | [Inheritance modes and inheritance shapes](#page-14) |
| 15 | [Multiple inheritance and the meaning of polymorphism](#page-15) |
| 16 | [Overloading, overriding, and run-time selection](#page-16) |
| 17 | [Virtual functions and dynamic dispatch](#page-17) |
| 18 | [Abstraction, pure virtual functions, and abstract classes](#page-18) |
| 19 | [A `Shape` interface and concrete implementations](#page-19) |
| 20 | [`static` state and final revision questions](#page-20) |

<a id="page-01"></a>

## Page 1 - Data structures, arrays, storage, and main memory

![Handwritten page about arrays, data structures, storage, RAM, and CPU](<images/Day 01/page-01-data-structures-and-memory.jpg>)

The page starts with `int A[5]` and draws five indexed cells. This is the first
important data-structure property: a built-in array contains a fixed number of
same-type elements in one contiguous sequence. Valid indices are `0` through
`4`; index `5` would be outside the array and accessing it would be undefined
behavior. The drawing therefore connects the source-level declaration to a
specific in-memory arrangement.

The lower diagram shows program instructions and data moving from persistent
storage into main memory so the CPU can execute them. That is a useful machine
model, with one qualification: a modern operating system gives a process a
*virtual address space*. Pages may be loaded on demand, cached, or temporarily
paged out. The application still reasons as if its live objects and instructions
occupy addressable memory.

The definition on the page is essentially correct: a data structure is an
organization of data chosen to support particular operations efficiently.
"Efficient" is not universal. An array is excellent for indexed access and
cache locality, but inserting at the front is expensive because elements must
move. The right structure depends on the required operations and invariants.

**Correction to remember:** `int A[5]` does not by itself mean "heap" or
"stack." A local array normally has automatic storage duration; a global array
has static storage duration; an array can also be a subobject of a dynamically
allocated object.

**Recall check:** Why is random access in an array constant time, and why does
that fact not make an array best for every workload?

<a id="page-02"></a>

## Page 2 - Persistent data, databases, data mining, and big data

![Handwritten page separating database storage from data structures used during execution](<images/Day 01/page-02-data-storage-and-program-data.jpg>)

The page separates two stages. A database stores persistent records in an
organized model on durable storage; a running program loads the relevant data
and represents it using in-memory structures. A database management system is
not itself one data structure. Internally it uses many structures - commonly
pages, indexes, trees, hash tables, logs, and caches - to satisfy queries and
durability requirements.

The "historical data" and "data mining algorithm" notes identify a workload:
an algorithm analyzes accumulated records to find patterns. The structure chosen
for the working set controls how quickly the program can filter, group, search,
or aggregate those records. The "big data" note extends the same idea beyond
one machine: when the data no longer fits comfortably on one computer, storage
layout, partitioning, transfer cost, and distributed processing become part of
the design.

**Correction to remember:** database, data mining, and big data name systems or
workloads, not interchangeable data structures. The useful question is: *which
operations must this program support, at what scale, and with what persistence
guarantees?*

**Recall check:** Give one structure suited to fast key lookup and one suited to
ordered traversal. What trade-off does each introduce?

<a id="page-03"></a>

## Page 3 - Process address space: code, stack, and dynamic storage

![Handwritten process-memory diagram with code, stack, heap, and function calls](<images/Day 01/page-03-process-memory-layout.jpg>)

The address sketch labels locations from `0` to `65535`. A 16-bit address has
$2^{16}=65,536$ distinct values, so the range is inclusive from `0` through
`65,535`. If each address selects one byte, this represents $64\,\text{KiB}$.
The arithmetic matters: `65535` is the greatest address, not the number of
addressable locations.

The larger drawing divides a running program into code, heap, and stack areas.
This is a common implementation model:

- compiled instructions occupy an executable code/text region;
- objects with static storage duration occupy a data region;
- function-call state and automatic local objects are commonly held in stack
  frames; and
- dynamic allocations are obtained from the free store, commonly implemented
  using a heap allocator.

The C++ language standard deliberately does not require this exact drawing.
It specifies storage duration, lifetime, scope, and behavior. "Stack" and
"heap" describe the usual platform implementation and remain valuable for
debugging and performance reasoning.

The `main`, `fun1`, and `fun2` sketch also distinguishes *code* from *one call*.
There is one compiled body for each function, but every active call needs its
own call state. Recursive calls therefore share instructions while holding
separate parameters and local variables.

**Recall check:** What is duplicated when a function recursively calls itself:
its machine instructions, its call frame, or both?

<a id="page-04"></a>

## Page 4 - Function calls, activation records, and automatic variables

![Handwritten stack-frame diagram for main, fun1, and fun2](<images/Day 01/page-04-stack-frames-and-automatic-storage.jpg>)

This page follows the nested call sequence. `main()` begins, then calls `fun1`,
which calls `fun2`. A typical stack grows by one activation record (stack frame)
per active call. A frame can contain parameters, automatic local variables,
the return address, saved registers, and bookkeeping required by the calling
convention. When `fun2` returns, its frame ends first; then `fun1` continues;
finally `main` returns. This last-in, first-out order is why a stack is a natural
implementation.

The drawn `a`, `b`, and `x` cells are separate objects belonging to different
invocations. Their names are source-code identifiers; at run time the compiler
usually addresses them by a frame-relative location or may keep them only in
registers after optimization.

The page says variables are "created automatically." More precisely, a local
variable declared normally has *automatic storage duration*: its lifetime
begins when execution reaches its declaration and ends when its scope exits.
That is different from dynamic allocation. Also, standard C++ does not support
variable-length built-in arrays; use `std::vector` when the element count is
known only at run time.

**Pitfall:** returning a pointer or reference to an automatic local object makes
it dangle after the function returns.

**Recall check:** In what order are `fun2`, `fun1`, and `main` local objects
destroyed when the calls return normally?

<a id="page-05"></a>

## Page 5 - Dynamic arrays, pointers, and data-structure memory

![Handwritten page showing a pointer to a dynamically allocated array](<images/Day 01/page-05-dynamic-memory-and-data-structures.jpg>)

The code on this page is the classic raw form:

```cpp
int* p = new int[5];
```

`p` is one pointer object. The expression `new int[5]` obtains storage for five
`int` objects and returns the address of the first element. If `p` is a local
variable, the pointer itself normally lives in the current call frame while the
five integers live in dynamically allocated storage. These are two different
lifetimes.

Assigning `p = nullptr` does **not** release the array; it merely forgets its
address and leaks it. Raw code must pair `new[]` with exactly one `delete[]`,
but new application code should usually express ownership with
`std::vector<int>` or `std::unique_ptr<int[]>`. Those types release their
resources automatically when their owning object is destroyed.

The data-structure list - array, tree, graph, hash table, queue, stack, linked
list - describes logical organizations. "Linear" versus "non-linear" is a
useful introductory classification, but the actual memory can be contiguous,
node-based, pooled, or distributed. A tree is logically hierarchical even if
its nodes are stored inside one contiguous vector.

**Recall check:** If a local `std::vector<int>` grows its elements dynamically,
which object has automatic lifetime and which resource does it own?

<a id="page-06"></a>

## Page 6 - Pointer swap versus reference swap

![Handwritten pointer and reference swap examples](<images/Day 01/page-06-pointers-references-and-swap.jpg>)

The first swap version receives pointers. The caller passes `&x` and `&y`; the
function dereferences those addresses with `*a` and `*b` to modify the caller's
integers. The pointer parameters themselves are passed by value, so the function
gets copies of the addresses.

The second version declares `swap(int& x, int& y)`. Each reference parameter is
an alias bound directly to the caller's object, so assignments to `x` and `y`
change the originals. The call becomes `swap(a, b)` because the reference
binding is expressed by the parameter type rather than by explicit `&` and `*`
operators at the call site.

References communicate "this object must exist" better than nullable pointers.
Use a pointer when null is a meaningful state or pointer reseating is part of
the operation. Use a reference for a required non-owning alias. Neither one
owns the referred object.

**Pitfall:** `&` means "address of" in an expression but declares a reference in
a type. Context decides which meaning applies.

**Recall check:** In `swap(int* a, int* b)`, which things are copied into the
function, and which things are actually modified?

<a id="page-07"></a>

## Page 7 - Reference parameters and the call stack

![Handwritten call-stack diagram for reference-based swapping](<images/Day 01/page-07-reference-swap-and-call-stack.jpg>)

The drawing correctly connects `main`'s variables with the reference parameters
inside `swap`. The parameter names are new names for the same two integer
objects, not two new integers that later need copying back. A compiler commonly
implements a reference using an address, but the language-level guarantee is
aliasing behavior, not a required pointer representation.

This explains why `swap` changes the caller while an ordinary
`swap(int x, int y)` does not. In the by-value version, only the local parameter
copies exchange values. In the by-reference version, assignments reach the
caller objects.

### Complete runnable example

[Source file](../examples/01_memory_and_references.cpp)

```cpp
#include <array>
#include <iostream>
#include <memory>
#include <vector>

void swap_by_reference(int& left, int& right) noexcept
{
    const int temporary{left};
    left = right;
    right = temporary;
}

int main()
{
    std::array<int, 5> fixed_values{10, 20, 30, 40, 50};
    std::vector<int> growing_values{2, 4, 6};
    growing_values.push_back(8);

    auto owned_value = std::make_unique<int>(99);

    int first{10};
    int second{20};
    swap_by_reference(first, second);

    std::cout << "fixed_values[2] = " << fixed_values.at(2) << '\n';
    std::cout << "growing_values size = " << growing_values.size() << '\n';
    std::cout << "dynamically stored value = " << *owned_value << '\n';
    std::cout << "after swap: first = " << first
              << ", second = " << second << '\n';
}
```

**Why this version is better for revision:** `std::array` expresses a fixed
size, `std::vector` expresses a run-time-sized sequence, and `std::unique_ptr`
expresses unique ownership. No manual `delete` is required.

<a id="page-08"></a>

## Page 8 - OOP, classes, objects, attributes, and methods

![Handwritten introduction to OOP classes, objects, attributes, and methods](<images/Day 01/page-08-oop-class-and-object.jpg>)

The page defines a class as a blueprint containing data members (attributes)
and member functions (methods), and an object as one instance of that class.
That is the key transition from loose variables and functions to a type that
owns both state and the operations allowed on that state.

Every object has its own non-static data members. The compiled member-function
instructions are not copied into every object; they are shared code and operate
on whichever object becomes the current object for a call. This is where the
later `this` pointer enters the model.

The `Teacher` sketch lists properties such as `name`, `subject`, and `salary`,
then a method such as `changeDepartment`. A good class goes beyond grouping:
it defines an invariant. For example, salary must not be negative and a
department must not be empty. Constructors establish that invariant, and the
public methods preserve it.

**Syntax pitfall:** a class definition ends with a semicolon:

```cpp
class Teacher {
    // members
};
```

**Recall check:** Which part is duplicated for each `Teacher` object - the
`name` data or the machine instructions for `change_department()`?

<a id="page-09"></a>

## Page 9 - Access control, encapsulation, and constructors

![Handwritten page on private public protected encapsulation and constructors](<images/Day 01/page-09-access-specifiers-encapsulation-constructors.jpg>)

The page lists `private`, `public`, and `protected`. In a `class`, members are
private by default; in a `struct`, they are public by default. Public members
form the caller-facing interface. Private members are accessible to the class's
own members and friends. Protected members also permit access from derived
classes, but they are not public to ordinary callers.

Encapsulation is not merely "make every variable private." Its purpose is to
keep representation choices and invariants behind a small, meaningful API. A
private salary with an unrestricted setter can still be poorly encapsulated;
a constructor and update operation that reject negative salary protect the
actual rule.

The constructor notes correctly say that a constructor has the class name, no
return type, and runs automatically as an object is created. One phrase needs a
precision fix: a constructor normally does not allocate the object's own
storage. Storage is obtained first; then the constructor initializes the object
in that storage. In a `new Teacher(...)` expression, allocation and construction
are two stages of the one expression.

First run the [lecture-linked `Teacher` version](../lecture_basics/01_teacher_basics.cpp)
to follow the same names and progression shown in the video. Then compare it
with the invariant-focused version below.

### Complete runnable example

[Source file](../examples/02_classes_and_encapsulation.cpp)

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Teacher {
public:
    Teacher(
        std::string name,
        std::string department,
        std::string subject,
        double monthly_salary)
        : name_{std::move(name)},
          department_{std::move(department)},
          subject_{std::move(subject)},
          monthly_salary_{monthly_salary}
    {
        if (name_.empty() || department_.empty() || subject_.empty()) {
            throw std::invalid_argument{"teacher fields must not be empty"};
        }
        if (monthly_salary_ < 0.0) {
            throw std::invalid_argument{"salary must not be negative"};
        }
    }

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] const std::string& department() const noexcept
    {
        return department_;
    }
    [[nodiscard]] const std::string& subject() const noexcept { return subject_; }
    [[nodiscard]] double monthly_salary() const noexcept
    {
        return monthly_salary_;
    }

    void change_department(std::string department)
    {
        if (department.empty()) {
            throw std::invalid_argument{"department must not be empty"};
        }
        department_ = std::move(department);
    }

private:
    std::string name_;
    std::string department_;
    std::string subject_;
    double monthly_salary_{};
};

int main()
{
    Teacher teacher{"Shradha", "Computer Science", "C++", 80'000.0};
    teacher.change_department("Software Engineering");

    std::cout << teacher.name() << " teaches " << teacher.subject()
              << " in " << teacher.department() << ".\n";
    std::cout << "Monthly salary: " << teacher.monthly_salary() << '\n';
}
```

**Points to remember:** constructor initializer lists initialize members
directly; `const` accessors promise not to mutate the object; returning a
`const std::string&` avoids an unnecessary string copy while preventing callers
from modifying the private member through that reference.

<a id="page-10"></a>

## Page 10 - Constructor overloads and the `this` pointer

![Handwritten page on constructor types and the this pointer](<images/Day 01/page-10-constructors-and-this-pointer.jpg>)

The top of the page lists non-parameterized, parameterized, and copy
constructors. Several constructors can share the class name because overload
resolution distinguishes their parameter lists. A default constructor is one
that can be called with no arguments; it may still be written with parameters
that all have defaults. A copy constructor has the conventional form
`T(const T&)`.

The teacher example exposes the shadowing problem: a parameter named `name` and
a member named `name` are both in scope. `this->name = name;` explicitly means
"assign the parameter on the right to the current object's member on the left."
The expression `this` is a pointer to the current object inside a non-static
member function. `*this` is therefore the current object itself and can be
returned by reference to support method chaining.

Prefer a member-initializer list in constructors. Assignment inside the body
first creates/default-initializes a member and then replaces its value; an
initializer constructs it directly with the intended value. Also remember that
the constructor does not choose stack versus dynamic storage - the expression
creating the object does.

### Complete runnable example

[Source file](../examples/03_constructors_and_this.cpp)

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Course {
public:
    Course() : Course{"Untitled course", 1} {}

    explicit Course(std::string name) : Course{std::move(name), 1} {}

    Course(std::string name, int credits)
        : name_{std::move(name)}, credits_{credits}
    {
        validate();
    }

    Course& rename(std::string name)
    {
        if (name.empty()) {
            throw std::invalid_argument{"course name must not be empty"};
        }
        this->name_ = std::move(name);
        return *this;
    }

    Course& set_credits(int credits)
    {
        this->credits_ = credits;
        validate();
        return *this;
    }

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    [[nodiscard]] int credits() const noexcept { return credits_; }

private:
    void validate() const
    {
        if (name_.empty()) {
            throw std::invalid_argument{"course name must not be empty"};
        }
        if (credits_ <= 0) {
            throw std::invalid_argument{"credits must be positive"};
        }
    }

    std::string name_;
    int credits_{};
};

int main()
{
    Course course{"Object-Oriented Programming", 4};
    course.rename("Modern C++ OOP").set_credits(5);

    std::cout << course.name() << " carries " << course.credits()
              << " credits.\n";
}
```

**Why `explicit` appears:** it prevents a one-argument constructor from silently
converting an unrelated string expression into a `Course` when that conversion
was not requested.

<a id="page-11"></a>

## Page 11 - Copy construction and shallow copy

![Handwritten page on the copy constructor and shallow copying](<images/Day 01/page-11-copy-constructor-shallow-copy.jpg>)

The page creates one `Teacher` from another. The canonical copy-constructor
shape is:

```cpp
Teacher(const Teacher& other);
```

The source is a `const` reference because copying should not modify it and
passing by reference avoids another copy merely to enter the constructor. If no
copy constructor is declared, the compiler can generate one that copy-constructs
each base and data member in order.

"Shallow copy" becomes important when a member is an owning raw pointer. A
memberwise copy duplicates the address, not the allocation at that address.
Both objects then claim the same resource. A modification through either pointer
is visible through the other, and two destructors may later attempt to release
the same allocation. That is aliasing plus a double-deletion risk.

Memberwise copying is not automatically bad. Copying a `std::string` or
`std::vector` asks that member type to perform its own safe value copy. The
problem is that a raw pointer does not communicate whether it owns, observes,
or shares its pointee.

**Correction to remember:** the default copy constructor does not "copy only
stack memory." It copies each member according to that member's copy semantics,
regardless of the process-memory diagram.

**Recall check:** After a memberwise copy of `double* cgpa`, how many pointer
objects exist and how many `double` objects exist?

<a id="page-12"></a>

## Page 12 - Building a deep copy

![Handwritten Student class with a dynamically allocated CGPA and custom copy constructor](<images/Day 01/page-12-deep-copy-constructor.jpg>)

This page makes the shallow-copy risk concrete. A `Student` owns a dynamically
allocated `double` through `cgpa`. A deep copy must perform two actions:

1. allocate a distinct `double` for the destination object; and
2. copy the source value into that new allocation.

In raw-pointer form, the essential copy-constructor body would be:

```cpp
Student(const Student& other)
    : name{other.name}, cgpa{new double{*other.cgpa}}
{
}
```

Copying `cgpa = other.cgpa` would be shallow because it copies only the address.
Copying `*cgpa = *other.cgpa` is safe only after `cgpa` has been made to point at
valid destination storage.

This classroom example deliberately uses dynamic allocation to reveal the
mechanism. A real `Student` should store a single CGPA as `double cgpa;` because
that value has no independent ownership need. Then the compiler-generated copy
operations are already correct. This is the rule of zero: choose member types
that manage themselves so the containing class needs no custom destructor or
copy/move operations.

**Pitfall:** once a class owns a raw resource, a copy constructor alone is not
enough. Copy assignment, move construction, move assignment, and destruction
must also have coherent behavior - the rule of five.

**Recall check:** Why does `new double{*other.cgpa}` both prevent shared mutation
and prevent double deletion?

<a id="page-13"></a>

## Page 13 - Copy assignment, destruction, and RAII

![Handwritten continuation of deep copy followed by a destructor](<images/Day 01/page-13-deep-copy-and-destructor.jpg>)

The top continues the deep-copy implementation. Copy assignment differs from
copy construction because the destination already exists and may already own a
resource. A correct assignment must handle self-assignment, obtain the new
resource safely, release the old one exactly once, and leave the object valid if
allocation throws.

The bottom introduces the destructor, written `~ClassName()`. It is invoked
automatically as an object's lifetime ends: on scope exit for automatic objects,
when a containing object is destroyed for member subobjects, or through an
appropriate `delete` for dynamically created objects. A destructor has no
return type and takes no parameters.

RAII joins these ideas: acquire a resource in an object that owns it, then let
that owner's destructor release it. The modern example below keeps the lecture's
deep-copy behavior while replacing manual `new`/`delete` with
`std::unique_ptr`. The explicit copy operations duplicate the pointed-to value;
the defaulted destructor releases it automatically.

The [lecture-linked raw-pointer `Student`](../lecture_basics/02_student_copy.cpp)
keeps `cgpaPtr` so you can see the exact ownership problem, then completes the
copy constructor, copy assignment, move operations, and destructor safely.

### Complete runnable example

[Source file](../examples/04_copy_and_raii.cpp)

```cpp
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
```

The copy assignment allocates first and mutates the destination second. If
allocation fails, the old object is still intact. For ordinary value members,
prefer eliminating the pointer entirely and letting the compiler implement all
five operations - [C++ Core Guidelines C.20](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero).

<a id="page-14"></a>

## Page 14 - Inheritance modes and inheritance shapes

![Handwritten inheritance page with base and derived classes](<images/Day 01/page-14-inheritance-modes-and-types.jpg>)

The page describes a base class such as `Person` and derived classes such as
`Student` and `GraduateStudent`. Public inheritance should express a real
"is-a" substitution: wherever a `Person` is expected, using a `Student` should
remain semantically valid. Reusing a few fields is not sufficient justification;
composition is often better when the relationship is "has-a" or "uses-a."

Inheritance mode changes how inherited public and protected members appear in
the derived class:

| Base member | `public` inheritance | `protected` inheritance | `private` inheritance |
| --- | --- | --- | --- |
| `public` | public | protected | private |
| `protected` | protected | protected | private |
| `private` | inaccessible directly | inaccessible directly | inaccessible directly |

Base private members still exist inside the derived object; derived code just
cannot access them directly. It should use the base class's protected or public
operations, which preserves the base invariant.

The page's diagrams lead into the common shapes: single inheritance, multilevel
inheritance, multiple inheritance, hierarchical inheritance, and hybrid
combinations. These are structural descriptions, not design goals. Use the
smallest hierarchy that communicates the domain relationship.

**Construction order:** base subobjects are constructed before derived members
and the derived constructor body. Destruction happens in the reverse order.

**Recall check:** Why is `Car : public Engine` usually wrong, while a `Car` data
member of type `Engine` is natural?

<a id="page-15"></a>

## Page 15 - Multiple inheritance and the meaning of polymorphism

![Handwritten page on multiple inheritance and polymorphism](<images/Day 01/page-15-multiple-inheritance-and-polymorphism.jpg>)

The top depicts multiple inheritance: one derived class has more than one direct
base. It can model independent roles, such as a teaching assistant being both a
graduate student and an employee. It also introduces risks: two bases can offer
the same member name, and a diamond hierarchy can contain repeated base
subobjects unless virtual inheritance is deliberately used. Prefer composition
unless callers genuinely need both base interfaces.

The page defines polymorphism as the ability for objects to take different forms
or behave differently through a common operation. C++ provides two broad forms:

- compile-time polymorphism, including function overloads, operator overloads,
  and templates; and
- run-time polymorphism, where a virtual call through a base reference or
  pointer selects the final overriding function for the actual object.

Constructor overloading is ordinary overload resolution: the argument list
selects one constructor at compile time. It should not be confused with
overriding, which needs a derived class and a virtual base operation.

Use the [lecture-linked inheritance version](../lecture_basics/03_inheritance.cpp)
for the video's `Person`, `Student`, `Teacher`, and `TA` sequence before the
more design-focused example below.

### Complete runnable inheritance example

[Source file](../examples/05_inheritance.cpp)

```cpp
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
```

The `final` keyword says `TeachingAssistant` is not intended as another base
class. `Person` has a virtual destructor so destroying a future derived object
through a `Person` owner remains safe.

<a id="page-16"></a>

## Page 16 - Overloading, overriding, and run-time selection

![Handwritten page comparing overloading, overriding, and run-time polymorphism](<images/Day 01/page-16-overloading-overriding-runtime-polymorphism.jpg>)

The page's `show(int)` and `show(char)` functions have the same name but
different parameter types. That is function overloading. The compiler examines
the argument at each call and chooses the best viable overload. Return type
alone cannot distinguish overloads because a call need not use the return value.

The `Parent`/`Child` sketch illustrates overriding: a derived member has the
same virtual signature as a base member and supplies derived behavior. Add the
`override` specifier in real code. It asks the compiler to reject accidental
signature differences, such as forgetting `const` or changing a parameter.

The handwritten `int x = y` example is not operator overloading; it is ordinary
assignment. Operator overloading means defining an operator function for at
least one class or enumeration operand, such as `Score::operator+`. It should
preserve the operator's familiar meaning rather than surprise callers.

### Lecture-linked runnable example

[Source file](../lecture_basics/04_polymorphism.cpp)

```cpp
#include <iostream>
#include <string_view>

class Print {
public:
    void show(int value) const { std::cout << "int: " << value << '\n'; }

    void show(char value) const { std::cout << "char: " << value << '\n'; }

    void show(std::string_view value) const
    {
        std::cout << "text: " << value << '\n';
    }
};

class Parent {
public:
    virtual ~Parent() = default;
    virtual void getInfo() const { std::cout << "parent class\n"; }
};

class Child final : public Parent {
public:
    void getInfo() const override { std::cout << "child class\n"; }
};

void describe(const Parent& object) { object.getInfo(); }

int main()
{
    const Print printer;
    printer.show(10);
    printer.show('K');
    printer.show("function overloading");

    const Parent parent;
    const Child child;
    describe(parent);
    describe(child);
}
```

The last two calls go through the same `const Parent&` interface, but the
object's dynamic type selects `Parent::getInfo` or `Child::getInfo`. That is the
run-time part; the three `show` calls are compile-time selection.

<a id="page-17"></a>

## Page 17 - Virtual functions and dynamic dispatch

![Handwritten page introducing virtual functions and parent-child calls](<images/Day 01/page-17-virtual-functions.jpg>)

The page adds `virtual` to a base operation. A virtual call is dynamically
dispatched when made through a base reference or pointer. The final overrider
for the actual object's type is selected. Calling `child.getInfo()` directly
can still be optimized as an ordinary direct call because the exact type is
already known.

The crucial test is therefore not merely "does the child have a same-named
function?" It is:

```cpp
Child child;
Parent& view = child;
view.getInfo();  // Child::getInfo when getInfo is virtual
```

If `getInfo` is non-virtual, the static type `Parent&` controls the call and the
base function runs. If it is virtual, the dynamic type `Child` participates.
Most implementations store a hidden virtual-table pointer in a polymorphic
object, but the C++ language specifies behavior rather than requiring one exact
table layout.

**Destructor rule:** if a class is intended to be destroyed through a public
base pointer, its destructor must be public and virtual. Otherwise deleting a
derived object through the base has undefined behavior. See
[C++ Core Guidelines C.35](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual).

**Object-slicing pitfall:** `Parent p = child;` constructs a standalone base
object and discards the derived portion. Use references, pointers, or a
polymorphic `clone()` operation when retaining the dynamic type matters.

**Recall check:** Which two types participate in a virtual call - the expression's
static type and the object's dynamic type - and what role does each play?

<a id="page-18"></a>

## Page 18 - Abstraction, pure virtual functions, and abstract classes

![Handwritten page defining abstraction and pure virtual functions](<images/Day 01/page-18-pure-virtual-functions-and-abstraction.jpg>)

The page defines abstraction as exposing the important operation while hiding
unnecessary implementation detail. Access control supports abstraction, but it
is not the whole concept. A caller using `Shape::area()` need not know whether a
circle stores a radius or whether a polygon caches its area. The public contract
is the abstraction; private representation is one implementation.

A pure virtual function is declared with `= 0`:

```cpp
virtual void draw() const = 0;
```

A class with at least one pure virtual function is abstract and cannot be
instantiated directly. A derived class remains abstract until it supplies all
required final overriders. Abstract classes can still have constructors,
implemented member functions, data, and a destructor; "abstract" does not mean
"contains no code."

### Lecture-linked runnable example

[Source file](../lecture_basics/05_abstract_class.cpp)

```cpp
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle final : public Shape {
public:
    void draw() const override { std::cout << "drawing a circle\n"; }
};

void draw_shape(const Shape& shape) { shape.draw(); }

int main()
{
    const Circle circle;
    draw_shape(circle);
}
```

The virtual destructor makes the interface safe for polymorphic ownership, and
`override` verifies that `Circle` really satisfies the interface.

<a id="page-19"></a>

## Page 19 - A `Shape` interface and concrete implementations

![Handwritten abstract Shape class with a pure virtual draw function](<images/Day 01/page-19-abstract-shape-interface.jpg>)

This page turns the abstraction definition into an interface. `Shape` states
what all shapes can do; a concrete class states how one shape does it. The
interface is useful because an algorithm can operate on any present or future
shape without an `if (type == ...)` chain.

The modern example below returns a value rather than only printing. It stores
heterogeneous derived objects behind `std::unique_ptr<Shape>`, giving one clear
owner per object and automatic destruction. The range loop calls the same base
interface for each element, while virtual dispatch selects the correct formula.

### Complete modern example

[Source file](../examples/06_polymorphism_and_abstraction.cpp)

```cpp
#include <iostream>
#include <memory>
#include <numbers>
#include <string_view>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
    [[nodiscard]] virtual double area() const noexcept = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_{radius} {}

    [[nodiscard]] std::string_view name() const noexcept override
    {
        return "circle";
    }

    [[nodiscard]] double area() const noexcept override
    {
        return std::numbers::pi_v<double> * radius_ * radius_;
    }

private:
    double radius_{};
};

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height) : width_{width}, height_{height} {}

    [[nodiscard]] std::string_view name() const noexcept override
    {
        return "rectangle";
    }

    [[nodiscard]] double area() const noexcept override
    {
        return width_ * height_;
    }

private:
    double width_{};
    double height_{};
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

    for (const auto& shape : shapes) {
        std::cout << shape->name() << " area = " << shape->area() << '\n';
    }
}
```

An interface-only base is most stable when it has no representation data and
contains public pure virtual operations plus a virtual destructor. This is also
the direction of [C++ Core Guidelines C.121](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-abstract).

**Recall check:** How can a new `Triangle` be added without editing the loop in
`main`?

<a id="page-20"></a>

## Page 20 - `static` state and final revision questions

![Handwritten page on static variables and OOP revision questions](<images/Day 01/page-20-static-members-and-review-questions.jpg>)

The page states that a function-local static variable is initialized once and
retains its value across calls. Since C++11, initialization of a block-scope
static is thread-safe: one thread performs initialization and other threads
wait if necessary. The object has static storage duration, but its name remains
local to the block.

A static data member belongs to the class rather than to each object. There is
one shared `next_id_` in the example, while each `Student` object stores its own
`id_`. An `inline static` member can be defined inside the class in C++17 and
later, avoiding a separate definition in one `.cpp` file.

Static member functions have no current object and therefore no `this` pointer.
They can directly use static members but need an object/reference to access
non-static members.

### Complete runnable example

[Source file](../examples/07_static_and_compile_time_polymorphism.cpp)

```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

class Printer {
public:
    static void show(int value) { std::cout << "integer: " << value << '\n'; }
    static void show(std::string_view value)
    {
        std::cout << "text: " << value << '\n';
    }
};

class Score {
public:
    explicit Score(int points) : points_{points} {}

    [[nodiscard]] int points() const noexcept { return points_; }

    [[nodiscard]] Score operator+(const Score& other) const noexcept
    {
        return Score{points_ + other.points_};
    }

private:
    int points_{};
};

class Student {
public:
    explicit Student(std::string name)
        : id_{next_id_++}, name_{std::move(name)}
    {
    }

    [[nodiscard]] int id() const noexcept { return id_; }
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

private:
    inline static int next_id_{1};
    int id_{};
    std::string name_;
};

int next_call_number() noexcept
{
    static int call_count{0};
    return ++call_count;
}

int main()
{
    Printer::show(42);
    Printer::show("compile-time overload selection");

    const Score total = Score{35} + Score{45};
    std::cout << "combined score: " << total.points() << '\n';

    const Student first{"Kapil"};
    const Student second{"Aarav"};
    std::cout << first.name() << " has ID " << first.id() << '\n';
    std::cout << second.name() << " has ID " << second.id() << '\n';

    std::cout << "function call " << next_call_number() << '\n';
    std::cout << "function call " << next_call_number() << '\n';
}
```

### Answers to the two handwritten review questions

1. **Constructor and destructor of `main`?** `main` is a function, not a class,
   so it has neither. Objects local to `main` are constructed when their
   declarations execute and destroyed in reverse construction order as `main`
   exits normally. Static objects follow static-lifetime rules.
2. **Friend function and friend class?** A declaration using `friend` grants a
   specific non-member function or another class access to private/protected
   members. Friendship is explicit, not inherited, not transitive, and not
   automatically reciprocal. Use it sparingly for tightly coupled helper
   operations such as symmetric operators; it is not a substitute for a clean
   public interface.

## End-of-day recall checklist

- [ ] I can distinguish scope, storage duration, and object lifetime.
- [ ] I can explain why a pointer copy may be shallow without saying all copies
      of pointers are wrong.
- [ ] I can state the invariant protected by the `Teacher` interface.
- [ ] I know what `this` and `*this` mean.
- [ ] I can trace construction and destruction through a hierarchy.
- [ ] I can distinguish overloading, overriding, and virtual dispatch.
- [ ] I know why a polymorphic public base destructor is virtual.
- [ ] I can add a new `Shape` without editing code that only uses `Shape`.
- [ ] I can identify which state belongs to one object and which state is
      shared with `static`.

## Next action

Open the module [README](../README.md), build every target, then follow the
"What to code next" checklist. Begin by recreating the lecture-linked
`Teacher`, deep-copy `Student`, and `Shape` examples from memory before adding a
new activity type to the study-planner project.
