#include "Timer.h"
#include "../Global/Global.h"

#define WIN32_LEAN_AND_MEAN
#ifdef _WIN32
#include <windows.h>
#endif

using namespace Honir::Global;

namespace Honir {
namespace Core {

float Timer::currTime = 0;
float Timer::lastTime = 0;
float Timer::frameTime = 0;
unsigned __int64 Timer::timerInit = 0;
unsigned __int64 Timer::tickRate = 0;

Timer::Timer()
{
    Init();
}

Timer::~Timer()
{
    //
}

void Timer::Init()
{
    #ifdef _WIN32
    // Windows specific timer - faster & more accurate
    QueryPerformanceFrequency((LARGE_INTEGER*)&tickRate);
    QueryPerformanceCounter((LARGE_INTEGER*)&timerInit);

    lastTime = timerInit;
    #else
    // OS-independent timer using rendering API (slow and inaccurate)
    lastTime = _hr->getState(StateModifiers::SM_ELAPSED_TIME);
    #endif
}

void Timer::Update()
{
    #ifdef _WIN32
    // Windows specific timer - faster & more accurate
    __int64 timeNow;

    QueryPerformanceCounter((LARGE_INTEGER *)&timeNow);
    currTime = float(double(timeNow - timerInit) / double(tickRate));

    frameTime = currTime - lastTime;
    lastTime = currTime;
    #else
    // OS-independent timer using rendering API (slow and inaccurate)
    currTime = _hr->getState(StateModifiers::SM_ELAPSED_TIME);
    frameTime = (currTime - lastTime) / 1000.0;
    lastTime = currTime;
    #endif
}

float Timer::FrameTime()
{
    return frameTime;
}

} // namespace Core
} // namespace Honir