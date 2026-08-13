#pragma once

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace oop_study {

enum class Status {
    not_started,
    in_progress,
    complete,
};

[[nodiscard]] std::string_view to_string(Status status) noexcept;

class Activity {
public:
    virtual ~Activity() = default;

    Activity(Activity&&) noexcept = default;
    Activity& operator=(Activity&&) noexcept = default;

    [[nodiscard]] const std::string& title() const noexcept;
    [[nodiscard]] int estimated_minutes() const noexcept;
    [[nodiscard]] Status status() const noexcept;

    void start() noexcept;
    void complete() noexcept;

    [[nodiscard]] virtual std::string_view type() const noexcept = 0;
    [[nodiscard]] virtual std::string details() const = 0;
    [[nodiscard]] virtual std::unique_ptr<Activity> clone() const = 0;

protected:
    Activity(std::string title, int estimated_minutes);
    Activity(const Activity&) = default;
    Activity& operator=(const Activity&) = default;

private:
    std::string title_;
    int estimated_minutes_{};
    Status status_{Status::not_started};
};

class VideoLesson final : public Activity {
public:
    VideoLesson(std::string title, int estimated_minutes, std::string source);
    VideoLesson(const VideoLesson&) = default;
    VideoLesson& operator=(const VideoLesson&) = default;

    [[nodiscard]] std::string_view type() const noexcept override;
    [[nodiscard]] std::string details() const override;
    [[nodiscard]] std::unique_ptr<Activity> clone() const override;

private:
    std::string source_;
};

class CodingExercise final : public Activity {
public:
    CodingExercise(std::string title, int estimated_minutes, std::string topic);
    CodingExercise(const CodingExercise&) = default;
    CodingExercise& operator=(const CodingExercise&) = default;

    [[nodiscard]] std::string_view type() const noexcept override;
    [[nodiscard]] std::string details() const override;
    [[nodiscard]] std::unique_ptr<Activity> clone() const override;

private:
    std::string topic_;
};

class StudyPlan {
public:
    explicit StudyPlan(std::string name);
    StudyPlan(const StudyPlan& other);
    StudyPlan(StudyPlan&&) noexcept = default;
    StudyPlan& operator=(StudyPlan other) noexcept;
    ~StudyPlan() = default;

    friend void swap(StudyPlan& left, StudyPlan& right) noexcept;

    void add(std::unique_ptr<Activity> activity);
    void start(std::size_t index);
    void complete(std::size_t index);

    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] const Activity& at(std::size_t index) const;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] int total_estimated_minutes() const noexcept;
    [[nodiscard]] std::size_t completed_count() const noexcept;

    void print(std::ostream& output) const;

private:
    std::string name_;
    std::vector<std::unique_ptr<Activity>> activities_;
};

}  // namespace oop_study
