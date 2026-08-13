#include "study_plan.hpp"

#include <iostream>
#include <memory>

int main()
{
    using oop_study::CodingExercise;
    using oop_study::StudyPlan;
    using oop_study::VideoLesson;

    StudyPlan today{"OOP one-shot revision"};
    today.add(std::make_unique<VideoLesson>(
        "Review constructors and this", 25, "Apna College OOP chapter"));
    today.add(std::make_unique<CodingExercise>(
        "Rebuild deep-copy example", 35, "copy constructor and RAII"));
    today.add(std::make_unique<CodingExercise>(
        "Add a new activity type", 45, "inheritance and virtual functions"));

    today.start(0);
    today.complete(0);
    today.start(1);

    StudyPlan tomorrow{today};
    tomorrow.complete(1);

    std::cout << "Today:\n";
    today.print(std::cout);
    std::cout << "\nIndependent deep copy for tomorrow:\n";
    tomorrow.print(std::cout);
}
