#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial arduino(13, 15);

// Set your WiFi network credentials
const char* ssid = "your SSID";
const char* password = "Your Password";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);

int mq2, mq3, mq6, mq7, average, temperature;

void setup() {
  // Serial port for debugging purposes
  lcd.init();
  lcd.backlight();
  arduino.begin(9600);
  Serial.begin(115200);
  Serial.println();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());


  // Start server
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) {
  // Create a JSON object
  DynamicJsonDocument jsonDoc(200);
  
  // Add sensor values to the JSON object
  jsonDoc["mq2"] = mq2;
  jsonDoc["mq3"] = mq3;
  jsonDoc["mq6"] = mq6;
  jsonDoc["mq7"] = mq7;
  jsonDoc["average"] = average;
  jsonDoc["temperature"] = temperature;

  // Convert JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send the JSON response
  request->send(200, "application/json", jsonString);
});
  server.begin();
}

void loop() {
  if (arduino.available() > 0) {
    char inputString[100];
    arduino.readBytesUntil('\n', inputString, sizeof(inputString));

    char *token = strtok(inputString, " \n");

    if (token != NULL) {
      mq2 = atoi(token);
      token = strtok(NULL, " \n");
    }

    if (token != NULL) {
      mq3 = atoi(token);
      token = strtok(NULL, " \n");
    }

    if (token != NULL) {
      mq6 = atoi(token);
      token = strtok(NULL, " \n");
    }

    if (token != NULL) {
      mq7 = atoi(token);
      token = strtok(NULL, " \n");
    }

    if (token != NULL) {
      average = atoi(token);
      token = strtok(NULL, " \n");
    }

    if (token != NULL) {
      temperature = atoi(token);
    }

    Serial.print("mq2: ");
    Serial.println(mq2);
    Serial.print("mq3: ");
    Serial.println(mq3);
    Serial.print("mq6: ");
    Serial.println(mq6);
    Serial.print("mq7: ");
    Serial.println(mq7);
    Serial.print("average: ");
    Serial.println(average);
    Serial.print("temperature: ");
    Serial.println(temperature);
  }
}
