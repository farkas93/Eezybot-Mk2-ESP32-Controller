#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H

#include <ESP32Servo.h>


// Pins
#define PIN_BASE_SERVO 25
#define PIN_MAIN_ARM_SERVO 26
#define PIN_LOWER_ARM_SERVO 27

// Joint Limits
#define UPPER_LIM_BASE 180
#define LOWER_LIM_BASE 0

#define UPPER_LIM_MAIN_ARM 150
#define LOWER_LIM_MAIN_ARM 55

#define UPPER_LIM_LOWER_ARM 180
#define LOWER_LIM_LOWER_ARM 110

#define MIN_MG946R 0.0
#define MAX_MG946R 180.0

//To protect two servos from crunching eachother
#define SAFETY_VAL 35
// milliseconds of delay for the servo to reach the position
#define DELAY 15
// stepping values the robot takes per iteration
#define ROBOT_JOINT_STEP 2

enum Command : int {
    stop = -1,
    left = 0,
    right = 1,
    up = 2, 
    down = 3,
    forward = 4,
    backward = 5
};

struct Robot {
    bool move_robot;
    int base_joint_pos;
    int base_joint_dpos;
    int main_arm_pos;
    int main_arm_dpos;
    int lower_arm_pos;
    int lower_arm_dpos;
};

int clamp(int val, int minVal, int maxVal);
int interpolateMG946R(float x, float outMin, float outMax);
bool isSafetyOK(int lowerArmPos, int mainArmPos);
int clampLowerArmForMechanicalLimits(int lowerArmPos, int mainArmPos);
float oscillateOnCricle();


void setup_robot();

void move_left(int step);
void move_right(int step);
void move_up(int step);
void move_down(int step);
void move_forward(int step);
void move_backward(int step);

void stop_move();

void move_loop();
void loop_robot_rom();
#endif