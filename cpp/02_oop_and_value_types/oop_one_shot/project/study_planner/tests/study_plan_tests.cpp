#include "study_plan.hpp"

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

int main()
{
    using oop_study::CodingExercise;
    using oop_study::Status;
    using oop_study::StudyPlan;
    using oop_study::VideoLesson;

    StudyPlan original{"Test plan"};
    original.add(
        std::make_unique<VideoLesson>("Watch lesson", 20, "YouTube"));
    original.add(std::make_unique<CodingExercise>(
        "Write class", 40, "encapsulation"));

    assert(original.size() == 2U);
    assert(original.total_estimated_minutes() == 60);
    assert(original.completed_count() == 0U);

    StudyPlan copy{original};
    copy.start(0);
    copy.complete(0);

    assert(copy.at(0).status() == Status::complete);
    assert(original.at(0).status() == Status::not_started);
    assert(copy.completed_count() == 1U);
    assert(original.completed_count() == 0U);

    std::ostringstream rendered;
    copy.print(rendered);
    assert(rendered.str().find("1/2 complete") != std::string::npos);
    assert(rendered.str().find("Watch lesson") != std::string::npos);

    bool rejected_null{false};
    try {
        original.add(nullptr);
    } catch (const std::invalid_argument&) {
        rejected_null = true;
    }
    assert(rejected_null);

    std::cout << "All study planner tests passed.\n";
}
