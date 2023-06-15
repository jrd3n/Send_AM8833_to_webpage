float temperatureMatrix[8][8];
//

struct Config {
  char ssid[32];
  char password[32];
  char serverIP[16];
  char serverPort[16];
};

Config config;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  config_setup();
  amg88xx_setup();
  wifi_setup();

}

void loop() {

//  wifi_loop();
  populate_matrix();
  sendMatrixOverUDP();
//  delay(1000);
}
