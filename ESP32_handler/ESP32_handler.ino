#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "esp32/Himanish"
#define AWS_IOT_SUBSCRIBE_Selena "esp32/Selena"
#define AWS_IOT_SUBSCRIBE_Stephen "esp32/Stephen"
#define AWS_IOT_SUBSCRIBE_Isha "esp32/Isha"

const int ledPin = 12;
const int buttonPin = 27;

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void connectAWS()
{
//  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_Selena);
  client.subscribe(AWS_IOT_SUBSCRIBE_Stephen);
  client.subscribe(AWS_IOT_SUBSCRIBE_Isha);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
//  doc["time"] = millis();
//  doc["sensor_a0"] = analogRead(0);
//  char jsonBuffer[512];
//  serializeJson(doc, jsonBuffer); // print to client

  doc["operation"] = "getObject";
  doc["bucket"] = "yeetaudio";
  doc["key"] = "esp32testaudio.mp3";
  doc["replyTo"] = "esp32/Himanish";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

}

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  connectAWS();
  
}

void loop() {

  if (digitalRead(buttonPin) == HIGH) {
    Serial.println("button pressed");
    digitalWrite(ledPin, HIGH);
    publishMessage();
    client.loop();
    delay(1000);
  } else {
    digitalWrite(ledPin, LOW);
  }
  client.loop();

}
