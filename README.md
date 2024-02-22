# EezybotARM Mk2 MQTT 
Simple MQTT compatible controller for the [Eezybot Mk2](http://www.eezyrobots.it/eba_mk2.html).


## Prerequisites

You have built your own EezybotARM Mk2 and want to control it with an ESP32 module (upesy_wroom).


## Setup

Once you have checked out this repo, please make sure to create your own `config.json`file by copying the template within the `config.d`folder, renaming it, and then setting your own preferenes (WiFi SSID, PW, MQTT host and topic).

## Install
Build it with platform IO for your ESP32 module.

## Use

Send MQTT messages in following form:
```
{
  "command": YOUR_CMD_INT
}
```

The program can interpret following commands:

```
enum Command : int {
    stop = -1,
    left = 0,
    right = 1,
    up = 2, 
    down = 3,
    forward = 4,
    backward = 5
};
```

If you send any of the commands, the robot will execute that command until it gets a stop signal.

The steps and delay per move loop are set in the `robot_control.h` file.
```
// milliseconds of delay for the servo to reach the position
#define DELAY 15
// stepping values the robot takes per iteration
#define ROBOT_JOINT_STEP 2
```
These two variables will determine the motion speed.

The implementation has some very simple (empirically based) mechanical limit safety checks to prevent your arm servos from destroying eachother.

For more see the  `robot_control.h`, `robot_control.cpp` and `robot_utils.cpp` files.