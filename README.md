# C++ and Scripting Practice

A deliberate-practice repository for learning modern C++, algorithms, build
tooling, and small automation scripts. The objective is not to collect random
programs or finish as many books as possible. The objective is to produce a
traceable sequence of programs that become progressively more correct,
idiomatic, tested, and useful.

> **Standards status (reviewed 2026-08-01):** C++23 is the current published
> standard, formally [ISO/IEC 14882:2024]. C++26 is still under development as a
> Draft International Standard. New work in this repository should target
> C++23 when the compiler supports the required feature; otherwise, document the
> C++20 fallback.

## Outcomes

This repository should provide evidence that I can:

- write clear procedural, object-oriented, and generic C++;
- reason about types, object lifetime, ownership, references, and pointers;
- use the C++ Standard Library instead of rebuilding its facilities blindly;
- apply Resource Acquisition Is Initialization (RAII) and the rule of zero;
- implement and analyze common data structures and algorithms;
- build multi-file projects with CMake;
- test, debug, sanitize, benchmark, and profile code;
- automate repetitive work with Python and shell scripts; and
- build C++ tools relevant to embedded systems, VLSI, and Electronic Design
  Automation (EDA).

## Start here: the minimum effective bookshelf

Do **not** read several beginner books in parallel. Select one foundation book,
keep one reference nearby, and write code every week.

| Role | Resource | How to use it |
| --- | --- | --- |
| Primary course | [Programming: Principles and Practice Using C++, 3rd ed. (2024)][PPP3] | Read sequentially and implement the exercises. This is the default choice for this repository. It uses contemporary C++20/C++23. |
| Desk reference | [Professional C++, 6th ed. (2024)][ProfessionalCpp] | Consult after the basics; do not attempt a first cover-to-cover read. It covers almost all of C++23. |
| Fast review | [A Tour of C++, 3rd ed. (2022)][TourCpp] | Read after the foundation course or before interviews. It assumes programming experience. |
| Daily online reference | [cppreference] | Check exact syntax, library contracts, complexity, feature-test macros, and compiler support. |
| Practice guidance | [C++ Core Guidelines] | Apply a small, relevant subset during each refactor; do not try to memorize the document. |

For the embedded/VLSI direction, add [Real-Time C++, 4th ed.][RealTimeCpp]
after the core language and [The Art of Writing Efficient Programs][Efficient]
after learning to benchmark correctly.

### Choose the foundation book once

| Starting point | Choose | Reason |
| --- | --- | --- |
| New to programming, willing to study rigorously | [Programming: Principles and Practice Using C++, 3rd ed.][PPP3] | Strongest programming foundation and the default path below. |
| New to programming and needing a gentler explanation | [Modern C++ for Absolute Beginners, 2nd ed.][AbsoluteBeginners] | Friendly, structured introduction spanning C++11 through C++23. |
| Want a large textbook explicitly organized around C++23 | [Beginning C++23, 7th ed.][BeginningCpp23] | Current syntax, step-by-step examples, and exercises. |
| Engineering, numerical, or scientific background | [Discovering Modern C++, 2nd ed.][DiscoveringCpp] | Technical-domain examples with C++17/C++20 coverage. |
| Already proficient in another language | [C++20 for Programmers][Cpp20Programmers] | Faster route through modern C++ and the major C++20 facilities. |
| Need a rapid systems-oriented immersion | [C++ Crash Course, 1st ed.][CrashCourse] | Substantial C++17 treatment, but it requires C++20/C++23 supplementation. |

## Operating system for learning

### Weekly cadence

Budget **7–10 focused hours per week**. If only 4–5 hours are available, use two
calendar weeks for each roadmap week rather than deleting exercises.

1. **Read:** study one coherent topic, not an arbitrary page count.
2. **Recall:** close the book and rebuild the central example from memory.
3. **Drill:** solve at least five small exercises without copying solutions.
4. **Apply:** extend one repository program or the current project.
5. **Verify:** compile with warnings, add tests, and run sanitizers where
   supported.
6. **Explain:** write a short note covering the invariant, failure modes, time
   and space complexity where relevant, and one mistake corrected.
7. **Commit:** make one focused commit whose message states the learned outcome.

### Definition of done for a topic

A topic is complete only when all applicable items are true:

- [ ] I can explain it without looking at the source.
- [ ] I can implement a minimal example from memory.
- [ ] I solved at least five exercises and one integration problem.
- [ ] Normal, boundary, invalid, and empty-input cases are considered.
- [ ] The code compiles without project-owned warnings.
- [ ] Tests pass and AddressSanitizer (ASan) / UndefinedBehaviorSanitizer
      (UBSan) find no issue where those tools are available.
- [ ] I recorded complexity, ownership, and lifetime assumptions.
- [ ] I can state when **not** to use the feature.

## 24-week executable roadmap

The roadmap is topic-based so it remains usable with any of the foundation
books. Use the matching chapter in the selected book; do not switch books when
chapter numbering differs.

### Phase 1 — Language fundamentals

- [ ] **Week 1:** toolchain, compilation pipeline, `main`, input/output,
      fundamental types, initialization, and arithmetic. Deliver 8–10 tiny
      programs and a script that compiles and runs them.
- [ ] **Week 2:** expressions, conversions, scope, `const`, selection, loops,
      and assertions. Deliver boundary-tested numeric utilities.
- [ ] **Week 3:** functions, declarations, overloads, pass-by-value,
      pass-by-reference, and recursion. Deliver a small mathematics library.
- [ ] **Week 4:** `std::string`, `std::array`, `std::vector`, iterators, and
      range-based loops. Deliver a text-statistics command-line program.

**Exit check:** 25 small programs, no unexplained compiler warning, and one
program split into a header and implementation file.

### Phase 2 — Lifetime, ownership, and abstraction

- [ ] **Week 5:** references, pointers, object lifetime, stack versus dynamic
      storage, and `nullptr`. Draw lifetime diagrams for every owning object.
- [ ] **Week 6:** classes, invariants, constructors, destructors, access control,
      and encapsulation. Deliver a validated value type.
- [ ] **Week 7:** RAII, smart pointers, copy/move operations, rule of zero, and
      exception safety. Deliver a resource-owning wrapper, then refactor it to
      remove unnecessary manual ownership.
- [ ] **Week 8:** operator overloading, namespaces, separate compilation, and
      interfaces. Deliver a fixed-width bit-vector or logic-vector class with
      tests.

**Exit check:** explain every object's owner and lifetime; no raw owning
`new`/`delete` in new application code.

### Phase 3 — Standard Library and algorithms

- [ ] **Week 9:** sequence and associative containers; choose containers using
      access, insertion, ordering, invalidation, and memory requirements.
- [ ] **Week 10:** algorithms, iterators, lambdas, projections, and ranges.
      Rewrite hand-written loops when a library algorithm expresses the intent
      more clearly.
- [ ] **Week 11:** asymptotic analysis, searching, sorting, hashing, stacks,
      queues, heaps, and disjoint sets. Implement selected structures for
      learning, then compare with the library.
- [ ] **Week 12:** trees and graphs: traversal, shortest paths, topological
      ordering, and minimum spanning trees. Deliver a directed dependency-graph
      analyzer.

**Exit check:** 40 cumulative algorithm problems with stated complexity and
tests for empty and degenerate structures.

### Phase 4 — Generic and modern C++

- [ ] **Week 13:** function/class templates, deduction, specialization, and
      type traits. Deliver a generic algorithm with compile-time constraints.
- [ ] **Week 14:** concepts, ranges, views, `constexpr`, and compile-time
      evaluation. Compare a C++20/23 implementation with its older fallback.
- [ ] **Week 15:** value categories, move semantics, forwarding, copy elision,
      and moved-from states. Measure copies and moves rather than guessing.
- [ ] **Week 16:** error models: exceptions, `std::optional`, `std::variant`,
      and `std::expected`; select a policy based on the API contract.

**Exit check:** a generic library component with concepts, tests, documentation,
and no accidental copies in the measured path.

### Phase 5 — Professional engineering

- [ ] **Week 17:** CMake targets, include visibility, libraries, build types,
      and out-of-source builds. Convert one multi-file project to CMake.
- [ ] **Week 18:** unit tests, test doubles, property/boundary cases, sanitizers,
      static analysis, formatting, and continuous-integration concepts.
- [ ] **Week 19:** filesystems, parsing, serialization, command-line interfaces,
      logging, and robust error reporting. Deliver a parser with malformed-input
      tests.
- [ ] **Week 20:** benchmarking, profiling, cache locality, data layout, branch
      behavior, and compiler optimization. Keep before/after measurements.

**Exit check:** one reproducible release build with tests, sanitizer runs,
static-analysis notes, and a benchmark report.

### Phase 6 — VLSI/EDA capstone

- [ ] **Week 21:** specify a tool, input grammar, invariants, error behavior,
      performance target, and test plan before implementation.
- [ ] **Week 22:** implement the parsing and domain model with RAII and clear
      ownership.
- [ ] **Week 23:** add algorithms, tests, fuzz/property cases, profiling, and a
      Python or shell automation layer.
- [ ] **Week 24:** document architecture and limitations, reproduce benchmark
      results, clean the public interface, and prepare an interview explanation.

**Recommended capstone:** a Value Change Dump (VCD) analyzer that reads a useful
subset of waveform data, calculates transition counts and activity factors,
and exports comma-separated values for a Python visualization script.

Alternative capstones:

- a static-timing-report parser and critical-path summarizer;
- a gate-level netlist dependency graph and topological checker;
- a four-state logic-vector library with truth-table tests;
- a cache/memory-access trace analyzer; or
- a constrained-random test-vector generator with a C++ core and Python driver.

## Scripting track: support the C++ work

Scripting is used to remove repetition and connect tools, not to create a second
unbounded curriculum.

| Roadmap phase | Script deliverable |
| --- | --- |
| Weeks 1–4 | Shell compile/run/failure-report script. |
| Weeks 5–8 | Python generator for boundary and randomized test inputs. |
| Weeks 9–12 | Script that runs an algorithm corpus and aggregates results. |
| Weeks 13–16 | Compiler-feature probe and comparison runner. |
| Weeks 17–20 | Build, test, sanitizer, and benchmark driver. |
| Weeks 21–24 | Capstone converter, report, or visualization script. |

## Repository conventions

New work should converge on the following layout. Existing files do not need to
be moved merely for cosmetic consistency.

```text
cpp/
  00_basics/
  01_lifetime_raii/
  02_oop_and_value_types/
  03_stl_and_algorithms/
  04_templates_and_modern_cpp/
  05_concurrency_performance/
scripting/
  python/
  shell/
projects/
  vcd_analyzer/
notes/
```

For each non-trivial exercise or project, prefer:

```text
topic-name/
  README.md          # problem, approach, complexity, edge cases, lessons
  CMakeLists.txt
  include/
  src/
  tests/
```

Recommended commit prefixes:

- `cpp:` language or algorithm practice;
- `script:` Python or shell automation;
- `project:` capstone functionality;
- `test:` tests, sanitizers, or benchmarks; and
- `docs:` explanations and progress records.

## Compiler baseline

For GCC or Clang, begin with strict diagnostics:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
    source.cpp -o app
```

For debug validation with GCC or Clang:

```bash
g++ -std=c++23 -O1 -g -fno-omit-frame-pointer \
    -fsanitize=address,undefined source.cpp -o app
```

If a requested C++23 library feature is unavailable, confirm it in the
[compiler-support table], record the toolchain limitation, and use the smallest
clear fallback. Do not silently rewrite the entire project around experimental
support.

## Complete curated C++ book map

The tables are a selection map, not a reading queue. **One foundation book plus
one reference is enough until a real project exposes a specialization need.**

### Foundations and accelerated introductions

| Book | Edition / principal coverage | Best use | Decision |
| --- | --- | --- | --- |
| [Programming: Principles and Practice Using C++][PPP3] | 3rd, 2024; C++20/C++23 | First rigorous programming course | **Default primary book** |
| [Modern C++ for Absolute Beginners][AbsoluteBeginners] | 2nd, 2023; C++11–C++23 | Gentler first course | Best alternative for a complete beginner |
| [Beginning C++23][BeginningCpp23] | 7th, 2023; C++23 | Large, current-standard beginner text | Choose when standards currency is the priority |
| [Discovering Modern C++][DiscoveringCpp] | 2nd, 2021; C++17/C++20 | Engineers, scientists, numerical programmers | Excellent VLSI/EDA-adjacent alternative |
| [C++20 for Programmers][Cpp20Programmers] | 2022; C++20 | Experienced programmer changing languages | Accelerated, not a first programming course |
| [C++ Crash Course][CrashCourse] | 1st, 2019; C++17 | Fast systems-oriented immersion | Good supplement; no C++20/C++23 coverage |

### Core references and overviews

| Book/resource | Edition / principal coverage | Best use | Currency warning |
| --- | --- | --- | --- |
| [Professional C++][ProfessionalCpp] | 6th, 2024; almost all C++23 | Comprehensive professional desk reference | Current and very large |
| [A Tour of C++][TourCpp] | 3rd, 2022; C++20 plus selected C++23 | Rapid overview and interview revision | Assumes prior programming experience |
| [C++ Primer][CppPrimer5] | 5th, 2012; C++11 | Detailed explanations of core semantics | Valuable but requires modern supplementation |
| [The C++ Programming Language][TCppPL] | 4th, 2013; C++11 | Language depth, design rationale, reference | Not a current-standard learning path |
| [The C++ Standard Library][StdLibrary] | 2nd, 2012; C++11 library | Library concepts and historical depth | Use cppreference for current APIs |
| [cppreference] | Continuously updated | Exact language/library lookup | Reference, not a structured course |
| [ISO/IEC 14882:2024][ISO/IEC 14882:2024] | Published C++23 specification | Definitive language rules | A specification, not a textbook |

> **C++ Primer edition caveat:** InformIT now has a catalog page for
> [C++ Primer, 6th Edition][CppPrimer6], dated 2025, but the publisher marks it
> **not for sale** and supplies no substantive description or standard coverage.
> Treat it as unavailable/unverified for planning. Do not pre-order or replace a
> working study plan until a purchasable edition with contents is confirmed.

### Standard-version deep dives

| Book | Coverage | Use it when |
| --- | --- | --- |
| [C++20: The Complete Guide][Cpp20Guide] | C++20 language and library additions | Fundamentals are secure and a feature-by-feature treatment is needed. |
| [C++23: The Complete Guide][Cpp23Guide] | C++23 additions; currently offered as a draft | Tracking C++23 details; not as the primary textbook. |
| [C++17: The Complete Guide][Cpp17Guide] | C++17 additions | Maintaining a C++17-constrained codebase. |

### Practices, design, and architecture

| Book/resource | Focus | Read after |
| --- | --- | --- |
| [Beautiful C++][BeautifulCpp] | Thirty high-value C++ Core Guidelines | Classes, ownership, and Standard Library basics |
| [C++ Core Guidelines Explained][CoreExplained] | Systematic explanation of selected guidelines | Comfortable intermediate C++ |
| [Effective Modern C++][EffectiveModern] | C++11/14 type deduction, move semantics, smart pointers, lambdas, and concurrency | Core language; retain the version context |
| [Embracing Modern C++ Safely][Embracing] | Industrial risk analysis for C++11/14 adoption | Large or safety-sensitive codebase work |
| [C++ Software Design][CppSoftwareDesign] | Dependencies, abstractions, changeability, and patterns | At least one medium-sized project |
| [API Design for C++, 2nd ed.][ApiDesign] | API lifecycle, C++23 features, testing, versioning, scripting bindings, and extensibility | Designing reusable libraries or C++/script boundaries |
| [Design Patterns in Modern C++20][PatternsCpp20] | Pattern implementations using C++20 facilities | Software-design principles, not before them |
| [Large-Scale C++ Volume I][LargeScaleCpp] | Process, physical design, packaging, and architecture | Senior/large-codebase work |
| [C++ Core Guidelines] | Continuously maintained practice guidance | Every phase, one relevant rule set at a time |

### Templates, concurrency, performance, embedded systems, and tooling

| Need | Best specialist resource | Qualification |
| --- | --- | --- |
| Templates and generic-library internals | [C++ Templates: The Complete Guide, 2nd ed.][CppTemplates] | Definitive through C++17-era templates; advanced. |
| Value categories and forwarding | [C++ Move Semantics: The Complete Guide][MoveSemantics] | Focused treatment of moves and corner cases. |
| Threads, atomics, and memory model | [C++ Concurrency in Action, 2nd ed.][Concurrency] | Strong C++17 foundation; supplement C++20 synchronization facilities. |
| Hardware-aware optimization | [The Art of Writing Efficient Programs][Efficient] | Measure first; intended for experienced programmers. |
| Applied C++ optimization | [C++ High Performance, 2nd ed.][HighPerformance] | More application-oriented C++20 performance guide. |
| Embedded and real-time C++ | [Real-Time C++, 4th ed.][RealTimeCpp] | C++20 microcontroller programming; best fit for the VLSI/embedded path. |
| End-to-end CMake | [Modern CMake for C++, 2nd ed.][ModernCMake] | Start when projects become multi-file. |
| Scalable CMake practices | [CMake Best Practices, 2nd ed.][CMakePractices] | After basic target-based CMake. |
| Academic data structures and algorithms | [Data Structures and Algorithm Analysis in C++, 4th ed.][Weiss] | Excellent theory; its C++ style is not the modern-language source. |
| Competitive programming | [Guide to Competitive Programming, 3rd ed.][CompetitiveGuide] | Algorithms and contest preparation. |
| Free competitive-programming start | [Competitive Programmer's Handbook][CompetitiveHandbook] | Read before purchasing another contest book. |
| Native-code security | [Secure Coding in C and C++, 2nd ed.][SecureCoding] | Authoritative vulnerability treatment, but C++11-era. |

### Historically important, not primary modern textbooks

| Book | Why it still matters | Limitation |
| --- | --- | --- |
| [Effective C++, 3rd ed.][EffectiveCpp] | Classic class, resource, and template advice | Predates C++11; validate every idiom in modern C++. |
| [Modern C++ Design][ModernCppDesign] | Policy-based design and template metaprogramming history | “Modern” means 2001-era C++. |
| [Inside the C++ Object Model][ObjectModel] | Conceptual view of layout and virtual dispatch | 1996; never treat it as the current ABI for a compiler. |
| [Accelerated C++][AcceleratedCpp] | Influential Standard-Library-first pedagogy | 2000-era language and style. |

## Purchase and reading rules

1. **Buy or borrow only the current stage:** one foundation, one reference, and
   at most one active specialist book.
2. **Verify title, edition, year, and ISBN:** marketplace listings frequently
   merge reviews and inventory from different editions.
3. **Ignore volatile price tables:** compare the publisher, institutional
   access, reputable Indian booksellers, and legal e-book options at purchase
   time.
4. **Do not use age alone as a quality score:** older books can explain stable
   concepts exceptionally well, but their syntax, library advice, and idioms
   must be classified by standard version.
5. **Do not read the ISO standard as a course:** use it only when exact normative
   wording matters.
6. **Do not let competitive programming replace software engineering:** contest
   speed does not teach API design, ownership, testing, builds, or maintenance.
7. **Do not start templates, concurrency, or optimization as avoidance:** first
   demonstrate solid functions, classes, RAII, containers, algorithms, and
   tests.

## Exact recommendation for this repository

Follow this sequence; later items are conditional rather than simultaneous:

1. **Now:** [Programming: Principles and Practice Using C++, 3rd ed.][PPP3]
   with the first 12 roadmap weeks.
2. **Reference from week 5:** [Professional C++, 6th ed.][ProfessionalCpp] and
   [cppreference].
3. **Revision after week 16:** [A Tour of C++, 3rd ed.][TourCpp].
4. **Project design after week 16:** [C++ Software Design][CppSoftwareDesign].
5. **Build discipline at week 17:** [Modern CMake for C++, 2nd ed.][ModernCMake].
6. **VLSI/embedded specialization after week 20:** [Real-Time C++][RealTimeCpp]
   followed by [The Art of Writing Efficient Programs][Efficient].
7. **Only when a project demands it:** select one of templates, concurrency,
   security, API design, or competitive programming from the specialist table.

The highest-value general combination is:

> **PPP3 + Professional C++ 6e + A Tour of C++ 3e + cppreference**

For the VLSI/embedded direction, add:

> **Real-Time C++ 4e + The Art of Writing Efficient Programs**

## Progress record template

Add this short record to the relevant exercise or project README:

```markdown
## Learning record

- Topic:
- Source and sections:
- Program/exercise:
- Invariant or contract:
- Ownership and lifetime:
- Complexity:
- Edge cases tested:
- Warning/sanitizer/test result:
- Mistake corrected:
- What I can now explain without notes:
- Next action:
```

[AcceleratedCpp]: https://www.informit.com/store/accelerated-c-plus-plus-practical-programming-by-example-9780201703535
[AbsoluteBeginners]: https://link.springer.com/book/10.1007/978-1-4842-9274-7
[ApiDesign]: https://www.oreilly.com/library/view/api-design-for/9780443222207/
[BeautifulCpp]: https://www.informit.com/store/beautiful-c-plus-plus-30-core-guidelines-for-writing-9780137647842
[BeginningCpp23]: https://link.springer.com/book/10.1007/978-1-4842-9343-0
[CMakePractices]: https://www.packtpub.com/en-us/product/cmake-best-practices-9781835880654
[compiler-support table]: https://en.cppreference.com/w/cpp/compiler_support
[Concurrency]: https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition
[CompetitiveGuide]: https://link.springer.com/book/10.1007/978-3-031-61794-2
[CompetitiveHandbook]: https://cses.fi/book.pdf
[CoreExplained]: https://www.pearson.com/en-us/subject-catalog/p/c-core-guidelines-explained-best-practices-for-modern-c/P200000007274/9780136875611
[C++ Core Guidelines]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
[Cpp17Guide]: https://www.cppstd17.com/
[Cpp20Guide]: https://www.cppstd20.com/
[Cpp20Programmers]: https://deitel.com/c-plus-plus-20-for-programmers/
[Cpp23Guide]: https://www.cppstd23.com/
[CppPrimer5]: https://www.informit.com/store/c-plus-plus-primer-9780133053036
[CppPrimer6]: https://www.informit.com/store/c-plus-plus-primer-9780135161777
[CppSoftwareDesign]: https://www.oreilly.com/library/view/c-software-design/9781098113155/
[CppTemplates]: https://www.informit.com/store/c-plus-plus-templates-the-complete-guide-9780134778792
[CrashCourse]: https://nostarch.com/cppcrashcourse
[DiscoveringCpp]: https://www.informit.com/store/discovering-modern-c-plus-plus-9780136677642
[EffectiveCpp]: https://www.oreilly.com/library/view/effective-c-third/0321334876/
[EffectiveModern]: https://www.oreilly.com/library/view/effective-modern-c/9781491908419/
[Efficient]: https://www.packtpub.com/en-us/product/the-art-of-writing-efficient-programs-9781800208117
[Embracing]: https://www.informit.com/store/embracing-modern-c-plus-plus-safely-9780137380350
[HighPerformance]: https://www.packtpub.com/en-us/product/c-high-performance-9781839212581
[ISO/IEC 14882:2024]: https://www.iso.org/standard/83626.html
[LargeScaleCpp]: https://www.informit.com/store/large-scale-c-plus-plus-volume-i-process-and-architecture-9780201717068
[ModernCMake]: https://www.packtpub.com/en-us/product/modern-cmake-for-c-9781805123361
[ModernCppDesign]: https://www.informit.com/store/modern-c-plus-plus-design-generic-programming-and-design-9780201704310
[MoveSemantics]: https://www.cppmove.com/
[ObjectModel]: https://www.informit.com/store/inside-the-c-plus-plus-object-model-9780201834543
[PatternsCpp20]: https://link.springer.com/book/10.1007/978-1-4842-7295-4
[PPP3]: https://www.stroustrup.com/programming.html
[ProfessionalCpp]: https://www.wiley.com/en-us/Professional%2BC%2B%2B%2C%2B6th%2BEdition-p-9781394193172
[RealTimeCpp]: https://link.springer.com/book/10.1007/978-3-662-62996-3
[SecureCoding]: https://www.informit.com/store/secure-coding-in-c-and-c-plus-plus-9780321822130
[StdLibrary]: https://www.informit.com/store/c-plus-plus-standard-library-the-a-tutorial-and-reference-9780321623218
[TCppPL]: https://www.stroustrup.com/books.html
[TourCpp]: https://www.stroustrup.com/tour3.html
[Weiss]: https://www.pearson.com/en-us/subject-catalog/p/data-structures-and-algorithm-analysis-in-c/P200000003459/9780133404180
[cppreference]: https://en.cppreference.com/w/
