#include "robot_control.h"

Servo base_servo;
Servo main_arm_servo;
Servo lower_arm_servo;

Robot robot;

void setup_robot()
{
    ESP32PWM::allocateTimer(0); // Allocate a timer for PWM
    ESP32PWM::allocateTimer(1); // Allocate additional timers if necessary
    ESP32PWM::allocateTimer(2);
    
    robot.base_joint_pos = LOWER_LIM_BASE;
    robot.main_arm_pos = LOWER_LIM_MAIN_ARM;
    robot.lower_arm_pos = UPPER_LIM_LOWER_ARM;

    // Attach the Pins to the Servos
    base_servo.attach(PIN_BASE_SERVO);
    main_arm_servo.attach(PIN_MAIN_ARM_SERVO);
    lower_arm_servo.attach(PIN_LOWER_ARM_SERVO);

    // Write initial positions
    base_servo.write(robot.base_joint_pos);
    main_arm_servo.write(robot.main_arm_pos);
    lower_arm_servo.write(robot.lower_arm_pos);
}

void move_left(int step) {
    robot.base_joint_dpos = -step;
    robot.move_robot = true;
}

void move_right(int step){
    robot.base_joint_dpos = step;
    robot.move_robot = true;
}

void move_up(int step) {
    robot.lower_arm_dpos = step;
    robot.move_robot = true;
}

void move_down(int step) {
    robot.lower_arm_dpos = -step;
    robot.move_robot = true;
}

void move_forward(int step) {
    robot.main_arm_dpos = step;
    robot.move_robot = true;
}

void move_backward(int step) {
    robot.main_arm_dpos = -step;
    robot.move_robot = true;
}

void move_main_arm(int new_pos){
    if (isSafetyOK(robot.lower_arm_pos, new_pos)){
        robot.main_arm_pos = clamp(new_pos, LOWER_LIM_MAIN_ARM, UPPER_LIM_MAIN_ARM);
        main_arm_servo.write(robot.main_arm_pos);
    }
}

void move_lower_arm(int new_pos) {    
    int temp = clamp(new_pos, LOWER_LIM_LOWER_ARM, UPPER_LIM_LOWER_ARM);
    robot.lower_arm_pos = clampLowerArmForMechanicalLimits(temp, robot.main_arm_pos);
    lower_arm_servo.write(robot.lower_arm_pos);
}

void move_base_joint(int new_pos) {
    robot.base_joint_pos = clamp(new_pos, LOWER_LIM_BASE, UPPER_LIM_BASE);
    base_servo.write(robot.base_joint_pos);
}

void move_loop() {
    if (robot.move_robot) {
        if (robot.base_joint_dpos != 0)
            move_base_joint(robot.base_joint_pos + robot.base_joint_dpos);
        if (robot.main_arm_dpos != 0) 
            move_main_arm(robot.main_arm_pos + robot.main_arm_dpos);
        if (robot.lower_arm_dpos != 0)
            move_lower_arm(robot.lower_arm_pos + robot.lower_arm_dpos);
        delay(DELAY);
    }
}

void stop_move() {
    robot.move_robot = false;
    robot.base_joint_pos = 0;
    robot.lower_arm_dpos = 0;
    robot.main_arm_dpos = 0;
}

void loop_robot_rom()
{
    float posOnCricle = oscillateOnCricle();

    int ma_val, la_val, base_val;

    // oscillate back and forth with the base
    robot.base_joint_pos = interpolateMG946R(posOnCricle, LOWER_LIM_BASE, UPPER_LIM_BASE);
    base_servo.write(robot.base_joint_pos);

    // oscillate back and forth with the main arm
    robot.main_arm_pos = interpolateMG946R(posOnCricle, LOWER_LIM_MAIN_ARM, UPPER_LIM_MAIN_ARM);
    main_arm_servo.write(robot.main_arm_pos);

    // oscillate back and forth with the lower arm
    robot.lower_arm_pos = interpolateMG946R(posOnCricle, LOWER_LIM_LOWER_ARM, UPPER_LIM_LOWER_ARM);
    robot.lower_arm_pos = clampLowerArmForMechanicalLimits(robot.lower_arm_pos, robot.main_arm_pos);
    lower_arm_servo.write(robot.lower_arm_pos);
    delay(DELAY);
}
