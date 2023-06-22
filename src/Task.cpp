#include "Task.h"

Task::Task() : state{State::free}
{
}

bool Task::is_ready() const
{
    return state == State::ready;
}

void Task::take()
{
    mx.lock();
    if (state != State::free)
        return;
    state = State::taken;
    mx.unlock();
    process();
    state = State::ready;
}

Task_list::Task_list() : stop{false}
{
}

Task_list::~Task_list()
{
    clear();
}

template <typename T>
void Task_list::add(const T &tsk)
{
    tasks.push_back(std::make_unique<T>(tsk));
}

void Task_list::clear()
{
    stop = true;
    for (auto &th : threads)
        threads.join();
    tasks.clear();
    stop = false;
}

const Task &operator[](size_t i) const
{
    return *tasks[i];
}
Task &operator[](size_t i)
{
    return *tasks[i];
}

void Task_list::process(uint32_t n_threads)
{
    for (int i = 0; i < n_threads; i++) // invoking the threads
        threads.push_back(std::thread(&Task_list::take_tasks, &this));

    for (auto &th : threads)
        th.detach();
}

void Task_list::take_tasks()
{
    for (auto *tsk : tasks)
    {
        if (stop)
            return;
        tsk->take();
    }
}