#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include "robot_control.h"

void setup_mqtt(PubSubClient& client);
void reconnect_mqtt(PubSubClient& client);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
