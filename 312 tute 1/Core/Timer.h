/**
 * @class Timer
 * @brief Keeps accurate dt of frame time.
 *
 * @author Simon Manning
 * @version 0.a
 * @date 13-04-2011
 */

#ifndef _TIMER_H_
#define _TIMER_H_

namespace Honir {
namespace Core {

class Timer
{
  public:  
    /** Constructor */
    Timer();

    /** Destructor */
    ~Timer();

    /** Initialises game timer. */
    void Init();

    /** Updates timer - must be called each game frame */
    void Update();

    /** Returns current frame time */
    static float FrameTime();

  private:
    static float currTime;
    static float lastTime;
    static float frameTime;
    static unsigned __int64 timerInit;
    static unsigned __int64 tickRate;
};

} // namespace Core
} // namespace Honir

#endif