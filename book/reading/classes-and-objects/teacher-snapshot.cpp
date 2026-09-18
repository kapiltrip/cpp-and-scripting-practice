/*
 * Classes and objects - short definitions
 *
 * Class: A class is a user-defined type that groups data and the functions
 * that operate on it. It defines the structure and behavior of its objects.
 *
 * Object: An object is an instance of a type that occupies storage and has
 * a lifetime. A class object is a particular instance of a class.
 *
 * A class defines the type; each object has its own non-static data members.
 * Detailed explanation: ../../../Projects/CppOOP/cpp-oop-notes.pdf.
 */

#include <iostream>
#include <string>
using namespace std;
// Encapsulation groups data with its operations and exposes a controlled interface.
class Teacher {
// attributes /  properties
  double salary ; // Its size is implementation-defined; measure with sizeof(double).

public :
// The following members are public. A class defaults to private before public:.

  std::string name ;
  std::string dept ;
  std::string subject;
  // methods
  void changeDepartment(std::string newDept){
    dept = newDept;

  }
  // setter
  void setSalary(double s ){
    salary= s ;
  }
  // getter
  double getSalary(){
    return salary;

  }
};
int main(){
  Teacher t1;
  t1.name= "Kapil" ;
  t1.dept = "MATHEMATICS ";
  t1.subject= "calculus ";
  t1.setSalary(25000);
  cout<< t1.name<< endl;
  cout<<t1.getSalary() << endl  ;

  return 0; // Report successful termination to the operating system.
}
