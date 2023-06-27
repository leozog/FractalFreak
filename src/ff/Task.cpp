#include "ff/Task.h"

#define _thread_debug

#ifdef _thread_debug
#include <iostream>
#endif

Task::Task() : state{State::free}
{
}

bool Task::is_ready() const
{
    return state == State::ready;
}

bool Task::is_taken() const
{
    return state == State::taken;
}

void Task::take(uint8_t trd_id)
{
    mx.lock_shared();
    if (state != State::free)
        return;
    state = State::taken;
    mx.unlock_shared();
#ifdef _thread_debug
    std::cout << "trd_id=" + std::to_string(trd_id) + " taken\n";
#endif
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

void Task_list::clear()
{
    stop = true;
    while (true)
    {
        bool running = false;
        for (auto &tsk : tasks)
        {
            if (tsk->is_taken())
                running = true;
        }
        if (!running)
            break;
    }
    tasks.clear();
    stop = false;
}

size_t Task_list::size() const
{
    return tasks.size();
}

const Task &Task_list::operator[](size_t i) const
{
    return *tasks[i];
}
Task &Task_list::operator[](size_t i)
{
    return *tasks[i];
}

void Task_list::process(int32_t n_threads)
{
    if (n_threads < 0)
        n_threads = std::thread::hardware_concurrency();
    for (int i = 0; i < n_threads; i++) // invoking the threads
    {
#ifdef _thread_debug
        std::cout << "invoking thread " + std::to_string(i + 1) + " / " + std::to_string(n_threads) + " of " + std::to_string(std::thread::hardware_concurrency()) + " hardware_concurrency\n";
#endif
        std::thread(&Task_list::take_tasks, this, i).detach();
    }
}

void Task_list::take_tasks(uint8_t trd_id)
{
#ifdef _thread_debug
    std::cout << "trd_id=" + std::to_string(trd_id) + " running\n";
#endif
    for (auto &tsk : tasks)
    {
        if (stop)
        {
#ifdef _thread_debug
            std::cout << "trd_id=" + std::to_string(trd_id) + " terminated\n";
#endif
            return;
        }
        tsk->take(trd_id);
    }
#ifdef _thread_debug
    std::cout << "trd_id=" + std::to_string(trd_id) + " finish\n";
#endif
}