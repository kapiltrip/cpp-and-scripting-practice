cmake_minimum_required(VERSION 3.20)

project(oop_one_shot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(add_oop_example target source)
    add_executable(${target} ${source})
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(
            ${target}
            PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow
        )
    endif()
endfunction()

add_oop_example(memory_and_references examples/01_memory_and_references.cpp)
add_oop_example(classes_and_encapsulation examples/02_classes_and_encapsulation.cpp)
add_oop_example(constructors_and_this examples/03_constructors_and_this.cpp)
add_oop_example(copy_and_raii examples/04_copy_and_raii.cpp)
add_oop_example(inheritance examples/05_inheritance.cpp)
add_oop_example(polymorphism_and_abstraction examples/06_polymorphism_and_abstraction.cpp)
add_oop_example(
    static_and_compile_time_polymorphism
    examples/07_static_and_compile_time_polymorphism.cpp
)

add_oop_example(lecture_teacher_basics lecture_basics/01_teacher_basics.cpp)
add_oop_example(lecture_student_copy lecture_basics/02_student_copy.cpp)
add_oop_example(lecture_inheritance lecture_basics/03_inheritance.cpp)
add_oop_example(lecture_polymorphism lecture_basics/04_polymorphism.cpp)
add_oop_example(lecture_abstract_class lecture_basics/05_abstract_class.cpp)
add_oop_example(lecture_static_keyword lecture_basics/06_static_keyword.cpp)

add_library(study_plan project/study_planner/src/study_plan.cpp)
target_include_directories(
    study_plan
    PUBLIC project/study_planner/include
)
if(MSVC)
    target_compile_options(study_plan PRIVATE /W4 /permissive-)
else()
    target_compile_options(
        study_plan
        PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow
    )
endif()

add_executable(oop_study_planner project/study_planner/src/main.cpp)
target_link_libraries(oop_study_planner PRIVATE study_plan)

enable_testing()
add_executable(
    oop_study_planner_tests
    project/study_planner/tests/study_plan_tests.cpp
)
target_link_libraries(oop_study_planner_tests PRIVATE study_plan)
if(MSVC)
    target_compile_options(oop_study_planner_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(
        oop_study_planner_tests
        PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow
    )
endif()
add_test(NAME oop_study_planner_tests COMMAND oop_study_planner_tests)
