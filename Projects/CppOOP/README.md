# C++ OOP lessons

Your Teacher, student, person, print, parent/child, and shape examples form this collection. Each concept has a separate runnable program. The [code index](code/README.md) gives all 20 sources and their exact run commands.

[cpp-oop-notes.pdf](cpp-oop-notes.pdf) explains the concepts through interview definitions, short relevant snippets, output traces, pointer diagrams, and specific book references. The [reading index](../../book/reading/classes-and-objects/README.md) links every section and the selected original source pages.

[practice.cpp](practice.cpp) is your current editable parent/child example. The topic programs stay available as you move on to another idea.

## Run in PowerShell

From the repository root:

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic virtual_functions
& ./Projects/CppOOP/code/run.ps1 -Topic abstraction
& ./Projects/CppOOP/code/run.ps1 -Topic static_members
& ./Projects/CppOOP/code/run.ps1 -Topic practice
```

Each command compiles one source and runs the result. To print the command for every available program:

```powershell
& ./Projects/CppOOP/code/run.ps1 -List
```

If the terminal is already inside this CppOOP folder, use `& ./code/run.ps1 -Topic virtual_functions`. Open this folder in VS Code to use the configured **C++: Run practice** or **C++: Run topic** task. The latter asks for a topic folder name.

The runner uses the installed Visual Studio 2022 x64 compiler in stable C++20 mode, with warnings treated as errors. These lessons need no C++23 features. Build products stay in the ignored repository tmp folder.

## Reading and verification

The [editable lesson](../../book/reading/classes-and-objects/companion.md) is the PDF's source. The [builder](../../book/reading/classes-and-objects/build_companion.py) checks reported measurements and output traces against the runnable examples, builds a review candidate, and renders its pages.

To compile and run all topic programs and refresh the measured-output cache:

```powershell
& ./Projects/CppOOP/code/verify.ps1
```

The [new source-page notes](../../book/reading/polymorphism-and-lifetime/README.md) cover overloading, overriding, virtual dispatch, abstraction, static, friendship, and lifetime. The [earlier source-page notes](../../book/reading/constructors-copying-and-lifetime/README.md) retain construction, copying, cleanup, and inheritance.
