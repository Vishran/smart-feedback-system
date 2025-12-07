// Define pin constants
#define LED_PIN 2  // Digital output pin for the LED
const int excellentButtonPin = 17;
const int goodButtonPin = 32;
const int averageButtonPin = 26;
int excellentCount = 0;
int goodCount = 0;
int averageCount = 0;
#include <WiFi.h>
#include <HTTPClient.h>
#define WIFI_SSID "Vis"
#define WIFI_PASSWORD "12345678"
const char *serverUrl = "https://console.thingzmate.com/api/v1/device-types/ragunathdevi34t/devices/ragunathdevicet31/uplink"; // Replace with your server endpoint
String AuthorizationToken = "Bearer 865ad72f449d0bb185a83d3d2ce47cae"
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  delay(4000); // Delay to let serial settle
 // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  // Define LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}
void loop() {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
http.addHeader("Authorization", AuthorizationToken); //Authorization token
  // Create JSON payload
  String payload = "{\"AVE\":" + String(averageCount) +",\"Good\":" + String(goodCount) +",\"EXE\":" + String(excellentCount) +  "}";
  // Send POST request
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println(response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Check if data is available in the serial buffer
  if (Serial.available() > 0) {
    // Read the entire command as a string
    String command = Serial.readStringUntil('\n');  // Read input until newline
    // Trim whitespace
    //command.trim();
    // Perform actions based on the received command
    if (command == "1" ) {
      Serial.println("Excellent Feedback Received");
      excellentCount++;
      Serial.println(excellentCount);
      digitalWrite(LED_PIN, HIGH);  // Turn on the LED
      delay(200);
      digitalWrite(LED_PIN, LOW);
    } 
    else if (command == "2" ) {
      Serial.println("Good Feedback Received");
      goodCount++;
      Serial.println(goodCount);
      digitalWrite(LED_PIN, HIGH);  
      delay(200);
      digitalWrite(LED_PIN, LOW);
    }
    else if (command == "3" ) {
      Serial.println("Average Feedback Received");
      averageCount++;
      Serial.println(averageCount);
      digitalWrite(LED_PIN, HIGH);  // Turn on the LED
      delay(200);
      digitalWrite(LED_PIN, LOW);
    } 
    else {
      Serial.println("Use 'ON'/'1' or 'OFF'/'0' to control the LED.");
    }
  }
}