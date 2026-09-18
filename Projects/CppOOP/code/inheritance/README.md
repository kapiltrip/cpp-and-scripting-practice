# Inheritance: person, student, gradStudent

**Interview definition (summary):** Inheritance lets a derived class build on a base class. Public inheritance expresses an "is a" relationship between the derived and base types.

[Runnable example](main.cpp) | [Companion PDF, page 12](../../cpp-oop-notes.pdf#page=12) | [Book passage and explanation](../../../../book/reading/constructors-copying-and-lifetime/README.md#public-inheritance)

## The chain in your example

`person -> student -> gradStudent` is multilevel inheritance. Each gradStudent object contains one student base subobject, which contains one person base subobject. The person part holds name and age; student adds rollno; gradStudent adds researchArea.

`class student : public person` declares the inheritance relationship. In the student constructor, `: person(studentName, studentAge), rollno(studentRollno)` is an initializer list. It constructs the person base with the supplied name and age, then initializes rollno, before the student constructor body runs.

The gradStudent constructor forwards its three arguments to student. The call `gradStudent s1("Kapil", 26, 33)` therefore supplies "Kapil" and 26 to person, and 33 to student's rollno. Its researchArea string initially contains no characters; main then assigns "VLSI".

The inheritance path through student already supplies the person part. Declaring both student and person as direct bases would add another person base subobject and make direct access to name or age ambiguous. This example uses the single chain above.

`s1.getInfo()` calls the public function inherited from student. That function can read name and age through the person base, along with student's rollno.

## Run and observe the order

From the repository root:

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic inheritance
```

The compiler prints its build message first. The program then prints:

```text
person constructor
student constructor
gradStudent constructor
Name: Kapil
Age: 26
Roll number: 33
Research area: VLSI
gradStudent destructor
student destructor
person destructor
```

The constructor bodies run from base to derived. When the local s1 leaves main, the destructor bodies run from derived to base. No dynamic allocation is needed in this example.

**Source:** Bjarne Stroustrup, [A Tour of C++, 3rd edition, section 5.5 Class Hierarchies, one-based PDF page 104](../../../../book/A%20Tour%20of%20C%2B%2B%20-%203rd%20Edition.pdf#page=104). The book uses a Shape hierarchy; the person/student/gradStudent explanation above is a lesson summary using your example.
