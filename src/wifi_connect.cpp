#include "wifi_connect.h"


const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void setup_wifi() {
    Serial.begin(115200);
    delay(10);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
