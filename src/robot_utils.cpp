#include "robot_control.h"

int MAX_MG946R_INT = (int)MAX_MG946R;
int stepOnCircle = 0;

float oscillateOnCricle()
{
    // TODO: can we have overflow issues here with pos?
    stepOnCircle += 1;
    stepOnCircle = stepOnCircle % 360;
    float x = ((float)stepOnCircle);
    if (stepOnCircle > MAX_MG946R_INT)
    {
        x = 360.0 - x;
    }

    return x;
};

int interpolateMG946R(float x, float outMin, float outMax)
{
    return (int)(x - MIN_MG946R) * (outMax - outMin) / (MAX_MG946R - MIN_MG946R) + outMin;
};


int clamp(int val, int minVal, int maxVal) {
    return (val < minVal) ? minVal : (val > maxVal) ? maxVal : val;
};

int clampLowerArmForMechanicalLimits(int lowerArmPos, int mainArmPos)
{    
    if (isSafetyOK(lowerArmPos, mainArmPos))
    {
        return lowerArmPos;
    }
    else
    {
        return min((MAX_MG946R_INT - mainArmPos) + SAFETY_VAL, UPPER_LIM_LOWER_ARM);
    }
};


bool isSafetyOK(int lowerArmPos, int mainArmPos) {
    int diff = mainArmPos - (MAX_MG946R_INT - lowerArmPos);
    return diff > SAFETY_VAL;
}
