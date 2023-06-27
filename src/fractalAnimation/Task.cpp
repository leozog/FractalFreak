#include "fractalAnimation/Task.h"

#include <iostream> //usunac
#include <string>

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
    std::cout << "trd_id=" + std::to_string(trd_id) + " taken\n";
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

void Task_list::process(uint32_t n_threads)
{
    for (int i = 0; i < n_threads; i++) // invoking the threads
    {
        std::cout << "invoking thread " + std::to_string(i + 1) + " / " + std::to_string(n_threads) + " of " + std::to_string(std::thread::hardware_concurrency()) + " possible\n";
        std::thread(&Task_list::take_tasks, this, i).detach();
    }
}

void Task_list::take_tasks(uint8_t trd_id)
{
    std::cout << "trd_id=" + std::to_string(trd_id) + " running\n";
    for (auto &tsk : tasks)
    {
        if (stop)
        {
            std::cout << "trd_id=" + std::to_string(trd_id) + " terminated\n";
            return;
        }
        tsk->take(trd_id);
    }
    std::cout << "trd_id=" + std::to_string(trd_id) + " finish\n";
}