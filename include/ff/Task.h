#pragma once
#include <thread>
#include <mutex>
#include <vector>

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
    std::mutex mx;

public:
    Task();
    virtual void process() = 0; // performs the task
    bool is_ready() const;      // checks if the task has been compleeted

private:
    friend class Task_list;
    void take(); // checks if task is free and takes it if so
};

class Task_list
{
private:
    std::vector<std::unique_ptr<Task>> tasks;
    std::vector<std::thread> threads; // vector containing invoked threads
    bool stop;

public:
    Task_list();
    ~Task_list();
    void add(std::unique_ptr<Task> tsk);
    template <typename T>
    void add(const T &tsk) { add(std::make_unique<T>(tsk)); }
    void clear();
    const Task &operator[](size_t i) const;
    Task &operator[](size_t i);
    void process(uint32_t n_threads);

private:
    void take_tasks();
};
