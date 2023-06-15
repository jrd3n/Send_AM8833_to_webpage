/*
  Pi Pico W WiFi Station Demo
  picow-wifi-station.ino
  Use WiFi library to connect Pico W to WiFi in Station mode
 
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
 
// Include the WiFi Library
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
 
unsigned int localPort = 2390;         // Local port to listen on
char packetBuffer[255];                // Buffer to hold incoming packet

WiFiUDP udp;

void wifi_setup() {
  // Initialize serial and wait for the port to open

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
      // Connect to WiFi network
    WiFi.begin(config.ssid, config.password);
    delay(1000);
  }

  // Print WiFi connection details
  Serial.println("Connected to WiFi");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

  // Begin UDP
  udp.begin(localPort);
}

void wifi_loop() {
  // Send UDP packet
  unsigned long my_val = millis();
  String message = String(my_val);

  sendUDP(message.c_str());

  delay(1000); // Delay between packets
}

void sendUDP(const char* message) {
  WiFiUDP udp;
  udp.beginPacket(config.serverIP, atoi(config.serverPort));
  udp.write((const uint8_t*)message, strlen(message));
  udp.endPacket();
  Serial.println(message);
}

void sendMatrixOverUDP() {
  // Global variable to hold the temperature matrix
//  float temperatureMatrix[8][8];

  // Update temperatureMatrix...

  // Convert temperatureMatrix to a string
  String matrixString;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      matrixString += String(temperatureMatrix[y][x]) + " ";
    }
    matrixString += "\n";
  }

  // Send matrixString over UDP
  sendUDP(matrixString.c_str());
}
