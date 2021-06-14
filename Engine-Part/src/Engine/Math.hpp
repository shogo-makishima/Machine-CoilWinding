#ifndef _MATHC_H_
#define _MATHC_H_

namespace Math {
    static int Clamp(int min, int max, int value) {
        if (value >= max) return max;
        else if (value <= min) return min;
        else return value;
    }

    static float Clamp(float min, float max, float value) {
        if (value >= max) return max;
        else if (value <= min) return min;
        else return value;
    }

    static int CycleClamp(float min, float max, float value) {
        if (value > max) return min;
        else if (value < min) return max;
        else return value;
    }

    static bool InRange(int min, int max, int value) {
        return (value > min && value < max);
    }
}

#endif