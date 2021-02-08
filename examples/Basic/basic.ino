#include "Dashdy.h"
void setup() {
  Serial.begin(115200);
  Dashdy.begin("--- token key ---","--- wifi ssid ---","--- wifi password ---");
}
void loop() {
  Dashdy.run();
}
