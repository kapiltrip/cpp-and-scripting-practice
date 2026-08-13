#include "study_plan.hpp"

#include <algorithm>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace oop_study {

std::string_view to_string(Status status) noexcept
{
    switch (status) {
    case Status::not_started:
        return "not started";
    case Status::in_progress:
        return "in progress";
    case Status::complete:
        return "complete";
    }
    return "unknown";
}

Activity::Activity(std::string title, int estimated_minutes)
    : title_{std::move(title)}, estimated_minutes_{estimated_minutes}
{
    if (title_.empty()) {
        throw std::invalid_argument{"activity title must not be empty"};
    }
    if (estimated_minutes_ <= 0) {
        throw std::invalid_argument{"estimated time must be positive"};
    }
}

const std::string& Activity::title() const noexcept { return title_; }

int Activity::estimated_minutes() const noexcept { return estimated_minutes_; }

Status Activity::status() const noexcept { return status_; }

void Activity::start() noexcept
{
    if (status_ == Status::not_started) {
        status_ = Status::in_progress;
    }
}

void Activity::complete() noexcept { status_ = Status::complete; }

VideoLesson::VideoLesson(
    std::string title,
    int estimated_minutes,
    std::string source)
    : Activity{std::move(title), estimated_minutes}, source_{std::move(source)}
{
    if (source_.empty()) {
        throw std::invalid_argument{"video source must not be empty"};
    }
}

std::string_view VideoLesson::type() const noexcept { return "video"; }

std::string VideoLesson::details() const
{
    return "source: " + source_;
}

std::unique_ptr<Activity> VideoLesson::clone() const
{
    return std::make_unique<VideoLesson>(*this);
}

CodingExercise::CodingExercise(
    std::string title,
    int estimated_minutes,
    std::string topic)
    : Activity{std::move(title), estimated_minutes}, topic_{std::move(topic)}
{
    if (topic_.empty()) {
        throw std::invalid_argument{"exercise concept must not be empty"};
    }
}

std::string_view CodingExercise::type() const noexcept { return "code"; }

std::string CodingExercise::details() const
{
    return "concept: " + topic_;
}

std::unique_ptr<Activity> CodingExercise::clone() const
{
    return std::make_unique<CodingExercise>(*this);
}

StudyPlan::StudyPlan(std::string name) : name_{std::move(name)}
{
    if (name_.empty()) {
        throw std::invalid_argument{"plan name must not be empty"};
    }
}

StudyPlan::StudyPlan(const StudyPlan& other) : name_{other.name_}
{
    activities_.reserve(other.activities_.size());
    for (const auto& activity : other.activities_) {
        activities_.push_back(activity->clone());
    }
}

StudyPlan& StudyPlan::operator=(StudyPlan other) noexcept
{
    swap(*this, other);
    return *this;
}

void swap(StudyPlan& left, StudyPlan& right) noexcept
{
    using std::swap;
    swap(left.name_, right.name_);
    swap(left.activities_, right.activities_);
}

void StudyPlan::add(std::unique_ptr<Activity> activity)
{
    if (!activity) {
        throw std::invalid_argument{"activity must not be null"};
    }
    activities_.push_back(std::move(activity));
}

void StudyPlan::start(std::size_t index) { activities_.at(index)->start(); }

void StudyPlan::complete(std::size_t index) { activities_.at(index)->complete(); }

const std::string& StudyPlan::name() const noexcept { return name_; }

const Activity& StudyPlan::at(std::size_t index) const
{
    return *activities_.at(index);
}

std::size_t StudyPlan::size() const noexcept { return activities_.size(); }

int StudyPlan::total_estimated_minutes() const noexcept
{
    int total{0};
    for (const auto& activity : activities_) {
        total += activity->estimated_minutes();
    }
    return total;
}

std::size_t StudyPlan::completed_count() const noexcept
{
    const auto count = std::count_if(
        activities_.begin(),
        activities_.end(),
        [](const auto& activity) {
            return activity->status() == Status::complete;
        });
    return static_cast<std::size_t>(count);
}

void StudyPlan::print(std::ostream& output) const
{
    output << name_ << " (" << completed_count() << '/' << size()
           << " complete, " << total_estimated_minutes() << " min)\n";

    for (std::size_t index{0}; index < activities_.size(); ++index) {
        const auto& activity = activities_.at(index);
        output << "  " << index + 1U << ". [" << to_string(activity->status())
               << "] " << activity->title() << " <" << activity->type()
               << "> - " << activity->details() << '\n';
    }
}

}  // namespace oop_study
