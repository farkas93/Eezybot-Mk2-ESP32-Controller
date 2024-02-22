#include "mqtt_client.h"

const char* mqtt_server = MQTT_SERVER;
const char* mqtt_topic = MQTT_TOPIC;

void setup_mqtt(PubSubClient& client) {
    client.setServer(mqtt_server, 1883);
    client.setCallback(mqtt_callback);
}

void reconnect_mqtt(PubSubClient& client) {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("connected");
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    
    // Create a temporary buffer for the JSON payload
    char tempPayload[length + 1]; // +1 for the null terminator
    memcpy(tempPayload, payload, length);
    tempPayload[length] = '\0'; // Null-terminate the string
    
    // Parse the JSON payload
    StaticJsonDocument<200> doc; // Adjust size according to your needs
    DeserializationError error = deserializeJson(doc, tempPayload);
    
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }
    
    // Extract the command value
    int commandValue = doc["command"];
    
    // Map the command value to the enum
    Command command = static_cast<Command>(commandValue);
    
    // Handle the command as needed
    switch (command) {
        case left:
            Serial.println("Command: left");
            move_left(ROBOT_JOINT_STEP);
            // Add your code to handle the left command
            break;
        case right:
            Serial.println("Command: right");
            move_right(ROBOT_JOINT_STEP);
            // Add your code to handle the right command
            break;
        case up:
            Serial.println("Command: up");
            // Add your code to handle the up command
            move_up(ROBOT_JOINT_STEP);
            break;
        case down:
            Serial.println("Command: down");
            // Add your code to handle the down command
            move_down(ROBOT_JOINT_STEP);
            break;
        case forward:
            Serial.println("Command: forward");
            // Add your code to handle the forward command
            move_forward(ROBOT_JOINT_STEP);
            break;
        case backward:
            Serial.println("Command: backward");
            // Add your code to handle the backward command
            move_backward(ROBOT_JOINT_STEP);
            break;
    }
}
