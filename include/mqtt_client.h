#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include "robot_control.h"

#define ROBOT_JOINT_STEP 5

enum Command : int {
    stop = -1,
    left = 0,
    right = 1,
    up = 2, 
    down = 3,
    forward = 4,
    backward = 5
};

void setup_mqtt(PubSubClient& client);
void reconnect_mqtt(PubSubClient& client);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
