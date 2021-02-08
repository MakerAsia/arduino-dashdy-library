#include "Dashdy.h"
OnConnected(){
  Serial.println("Connected");
}
OnDisconnected(){
  Serial.println("Disconnected");
}
void setup() {
  Serial.begin(115200);
  Dashdy.begin("--- token key ---","--- wifi ssid ---","--- wifi password ---");
}
void loop() {
  Dashdy.run();
}
