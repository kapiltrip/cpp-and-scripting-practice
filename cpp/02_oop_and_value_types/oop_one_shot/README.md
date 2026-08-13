# C++ OOP One-Shot Revision Lab

This module turns the [Apna College OOP one-shot lesson](https://www.youtube.com/watch?v=mlIUKyZIUUU)
and the handwritten scan into a small, executable revision path. Read
[Day 01](<notes/Day 01.md>) with the code open beside it, then rebuild each
example without copying.

## What is here

```text
oop_one_shot/
|-- README.md
|-- CMakeLists.txt
|-- lecture_basics/              # Her sequence and class names, made runnable
|-- examples/                    # One runnable program per concept group
|-- notes/
|   |-- Day 01.md                # All 20 pages, explained in order
|   |-- images/Day 01/           # Readable rendered pages
|   `-- source/                  # Original handwritten PDF
`-- project/study_planner/
    |-- include/                 # Public class interfaces
    |-- src/                     # Implementation and demo program
    `-- tests/                   # Self-contained behavior tests
```

## Video chapter map

| Time | Topic | Best matching material |
| ---: | --- | --- |
| 00:00-03:37 | Introduction and OOP motivation | Note page 8 |
| 03:38 | Class and object | Pages 8-9; example 02 |
| 17:05 | Access specifiers | Page 9; example 02 |
| 23:48 | Encapsulation | Page 9; example 02 |
| 29:10 | Constructors | Pages 9-10; example 03 |
| 41:08 | `this` pointer | Page 10; example 03 |
| 46:33 | Copy constructor | Pages 11-13; example 04 |
| 51:56 | Shallow and deep copy | Pages 11-13; example 04 |
| 1:09:07 | Destructor | Page 13; example 04 |
| 1:14:35 | Inheritance | Pages 14-15; example 05 |
| 1:24:45 | Modes of inheritance | Page 14; example 05 |
| 1:27:01 | Types of inheritance | Pages 14-15; example 05 |
| 1:30:41 | Function overloading | Pages 15-16; example 07 |
| 1:35:10 | Polymorphism | Pages 15-17; examples 06-07 |
| 1:43:33 | Function overriding | Pages 16-17; example 06 |
| 1:46:40 | Virtual functions | Pages 17-19; example 06 |
| 1:48:25 | Abstraction | Pages 18-19; example 06 |
| 1:49:58 | Abstract classes | Pages 18-19; example 06 |
| 1:55:15 | `static` keyword | Page 20; example 07 |

Pages 1-7 are a useful prerequisite bridge covering process memory, object
lifetime, pointers, references, and swapping. They explain why copying and
destruction matter once a class owns a resource.

## Two code layers

Use [lecture_basics](lecture_basics/README.md) first. Those files deliberately
stay close to her visible code: `Teacher`, `Student` with `cgpaPtr`, `Person` and
`Student`, `Print::show`, `Parent`/`Child`, `Shape`/`Circle`, and function-local
`static int x`. I completed the missing pieces and corrected ownership and
virtual-destruction issues so every file builds and runs.

Then study `examples/`. Those programs teach the same concepts with private
invariants, standard owning types, `const`, `override`, and APIs that scale
better into a real project. The point is to understand her basic mechanism and
also learn what you would keep or change in production-quality C++.

## Build and verify

From this directory (on Windows, a Developer PowerShell for Visual Studio 2022
provides the compiler environment):

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

The CMake file builds these executables:

| Target | Main revision question |
| --- | --- |
| `memory_and_references` | What is owned, and what is merely an alias? |
| `classes_and_encapsulation` | What invariant does the public API protect? |
| `constructors_and_this` | How is a valid object established? |
| `copy_and_raii` | Does a copy share or duplicate the owned resource? |
| `inheritance` | Is every derived object genuinely usable as its base? |
| `polymorphism_and_abstraction` | Which behavior is selected through the base interface? |
| `static_and_compile_time_polymorphism` | What belongs to the class rather than one object? |
| `oop_study_planner` | How do the concepts cooperate in one program? |
| `oop_study_planner_tests` | Does copying remain independent and are contracts enforced? |

It also builds six `lecture_*` targets corresponding to the six files in
`lecture_basics/`.

The examples target C++23 but intentionally use facilities available in C++20.
If an older compiler rejects `-std=c++23`, change `CMAKE_CXX_STANDARD` to `20`;
no source rewrite should be necessary.

## How the study planner combines the chapter

The integration project is deliberately small enough to understand in one
sitting:

- `Activity` is an abstract base class and the stable interface.
- `VideoLesson` and `CodingExercise` override its virtual operations.
- `StudyPlan` owns activities with `std::unique_ptr`, so ownership is explicit.
- `clone()` gives `StudyPlan` a real deep copy without slicing derived objects.
- constructors reject invalid states instead of creating half-valid objects.
- the tests prove that changing a copied plan does not mutate the original.

The lecture's raw-pointer deep-copy example is valuable for seeing the
mechanism. New application code should usually prefer the rule of zero and
standard owning types. See [C++ Core Guidelines C.20](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero).
Polymorphic base classes also need a safe destruction policy; the project uses
a public virtual destructor as described by
[C.35](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual).

## What to code next

Complete these in order. Each step forces several OOP concepts to work together
without making the directory larger than necessary.

- [ ] **Rebuild before extending:** recreate examples 02, 04, and 06 from a
      blank file. Explain each data member's owner and lifetime aloud.
- [ ] **Add `MiniProjectActivity`:** derive it from `Activity`, store a milestone
      count, implement `details()` and `clone()`, and add one test. Do not add a
      type-checking `if` chain to `StudyPlan`.
- [ ] **Make the demo interactive:** add `list`, `start <index>`, and
      `complete <index>` commands. Keep input parsing outside the domain classes.
- [ ] **Add persistence:** save and restore a plan using a small documented text
      format. Reject malformed status values and non-positive durations.
- [ ] **Test all boundaries:** empty title, zero duration, bad index, empty plan,
      copying an empty plan, self-assignment, and copying a mixed derived list.
- [ ] **Run sanitizers:** use AddressSanitizer and UndefinedBehaviorSanitizer on
      GCC/Clang, then intentionally introduce one lifetime bug and observe the
      diagnostic before fixing it.
- [ ] **Refactor judgment:** identify one relationship that is better expressed
      with composition than inheritance and write down why.

Definition of done: every target builds with warnings enabled, tests pass, the
copied plan is independent, and you can explain why `override`, a virtual
destructor, and `std::unique_ptr` are present without reading these notes.
