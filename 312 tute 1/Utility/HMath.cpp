#include "../utility/HMath.h"

    float FastSqrt(float number)
    {
        long i;
        float x, y;
        const float f = 1.5f;
    
        x = number * 0.5f;
        y = number;
        i = *(long *) &y;
        i = 0x5f3759df - (i >> 1);
        y = *(float *) &i;
        y = y * (f - (x * y * y));
        y = y * (f - (x * y * y));
        return number * y;
    }
    
    float InvSqrt(float x)
    {
      float xhalf = 0.5f * x;
      int i = *(int *) &x; // Get bits for floating value
      i = 0x5f375a86 - (i >> 1); // Gives initial guess (hax)
      x = *(float *) &i; // Convert bits back to float
      x = x * (1.5f - xhalf * x * x); // Newton step
      return x;
    }