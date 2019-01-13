#include "timer.h"

namespace ps
{
namespace utils
{
Timer::Timer()
{
    m_lastTick = std::chrono::high_resolution_clock::now();
}

double Timer::reset()
{
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - m_lastTick;
    m_lastTick = std::chrono::high_resolution_clock::now();
    return time.count();
}

double Timer::get()
{
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - m_lastTick;
    return time.count();
}

}
}
