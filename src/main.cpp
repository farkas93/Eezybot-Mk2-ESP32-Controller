#include <Arduino.h>
#include "mqtt_client.h"
#include "wifi_connect.h"
#include "robot_control.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    setup_wifi();
    setup_mqtt(client);
    setup_robot();
}

void loop() {
    if (!client.connected()) {
        reconnect_mqtt(client);
    }
    client.loop();
    move_loop();
}
