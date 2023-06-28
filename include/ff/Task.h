#pragma once
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <string>

class Task
{
private:
    enum State
    {
        free,
        taken,
        ready
    };
    State state;
    std::shared_mutex mx;

public:
    Task();
    virtual void process() = 0; // performs the task
    bool is_ready() const;      // checks if the task has been compleeted
    bool is_taken() const;      // checks if the task has been taken

private:
    friend class Task_list;
    void take(uint8_t trd_id); // checks if task is free and takes it if so
};

class Task_list
{
private:
    std::vector<std::unique_ptr<Task>> tasks;
    bool stop;

public:
    Task_list();
    ~Task_list();
    void add(std::unique_ptr<Task> &&tsk) { tasks.push_back(std::move(tsk)); }
    void clear();
    size_t size() const;
    const Task &operator[](size_t i) const;
    Task &operator[](size_t i);
    void process(int32_t n_threads);

private:
    void take_tasks(uint8_t trd_id);
};
