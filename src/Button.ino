#include "ButtonSecrets.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti wifi;

void setup() {
  // Keep ourselves on!
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);

  Serial.begin(115200);

  Serial.println("Connecting...");
  wifi.addAP(ap_name, ap_password);
}

void loop() {
   // wait for WiFi connection
   Serial.print(".");
   if((wifi.run() == WL_CONNECTED)) {
        Serial.print("Connected!\n");

        HTTPClient http;

        http.begin(http_server, http_port, http_path); //HTTP

        // Sends an empty POST
        int httpCode = http.POST(0, 0);
        if(httpCode) {
            Serial.printf("Success!: %d\n", httpCode);
        } else {
            Serial.write("Error POSTing\n");
        }
        // Wait to ensure all buffers are flushed
        delay(500);

        // Turn off again
        digitalWrite(0, LOW);
    }

  delay(500);
}
