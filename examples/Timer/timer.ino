#include "Dashdy.h"
#include <Ticker.h>
Ticker timer;
OnReceive(VPIN1){
  int value = param.asInt();
  Serial.printf("Received Data value = %d\n",value);
}
OnConnected(){
  Serial.println("Connected");
  timer.attach(1,WriteTemperature);
}
OnDisconnected(){
  Serial.println("Disconnected from server");
}
void WriteTemperature() {
  int temp = random(200, 300);
  Serial.printf("sending temp %.2f\n",temp/10.0f);
  Dashdy.virtualPinWrite(VPIN1,temp/10.0f);
}
void setup() {
  Serial.begin(115200);
  Dashdy.begin("--- token key ---","--- wifi ssid ---","--- wifi password ---");
}
void loop() {
  Dashdy.run();
}
