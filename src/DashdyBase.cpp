#include "DashdyBase.h"
#include <functional>

#ifdef __cplusplus
extern "C" {
#endif
#define DASHDY_ONDATA_IMP(pin) void DashdyOnReceived ## pin (const DashdyParam DASHDY_UNUSED &param) \
          __attribute__((weak))

DASHDY_ONDATA_IMP(VPIN1 );
DASHDY_ONDATA_IMP(VPIN2 );
DASHDY_ONDATA_IMP(VPIN3 );
DASHDY_ONDATA_IMP(VPIN4 );
DASHDY_ONDATA_IMP(VPIN5 );
DASHDY_ONDATA_IMP(VPIN6 );
DASHDY_ONDATA_IMP(VPIN7 );
DASHDY_ONDATA_IMP(VPIN8 );
DASHDY_ONDATA_IMP(VPIN9 );
DASHDY_ONDATA_IMP(VPIN10);
DASHDY_ONDATA_IMP(VPIN11);
DASHDY_ONDATA_IMP(VPIN12);
DASHDY_ONDATA_IMP(VPIN13);
DASHDY_ONDATA_IMP(VPIN14);
DASHDY_ONDATA_IMP(VPIN15);
DASHDY_ONDATA_IMP(VPIN16);
DASHDY_ONDATA_IMP(VPIN17);
DASHDY_ONDATA_IMP(VPIN18);
DASHDY_ONDATA_IMP(VPIN19);
DASHDY_ONDATA_IMP(VPIN20);
DASHDY_ONDATA_IMP(VPIN21);
DASHDY_ONDATA_IMP(VPIN22);
DASHDY_ONDATA_IMP(VPIN23);
DASHDY_ONDATA_IMP(VPIN24);
DASHDY_ONDATA_IMP(VPIN25);
DASHDY_ONDATA_IMP(VPIN26);
DASHDY_ONDATA_IMP(VPIN27);
DASHDY_ONDATA_IMP(VPIN28);
DASHDY_ONDATA_IMP(VPIN29);
DASHDY_ONDATA_IMP(VPIN30);
DASHDY_ONDATA_IMP(VPIN31);
DASHDY_ONDATA_IMP(VPIN32);
DASHDY_ONDATA_IMP(VPIN33);
DASHDY_ONDATA_IMP(VPIN34);
DASHDY_ONDATA_IMP(VPIN35);
DASHDY_ONDATA_IMP(VPIN36);
DASHDY_ONDATA_IMP(VPIN37);
DASHDY_ONDATA_IMP(VPIN38);
DASHDY_ONDATA_IMP(VPIN39);
DASHDY_ONDATA_IMP(VPIN40);
DASHDY_ONDATA_IMP(VPIN41);
DASHDY_ONDATA_IMP(VPIN42);
DASHDY_ONDATA_IMP(VPIN43);
DASHDY_ONDATA_IMP(VPIN44);
DASHDY_ONDATA_IMP(VPIN45);
DASHDY_ONDATA_IMP(VPIN46);
DASHDY_ONDATA_IMP(VPIN47);
DASHDY_ONDATA_IMP(VPIN48);
DASHDY_ONDATA_IMP(VPIN49);
DASHDY_ONDATA_IMP(VPIN50);

OnConnected() __attribute__((weak));
OnDisconnected() __attribute__((weak));

static const DataReceivedHandler receiveHandler[] = {
    DashdyOnReceivedVPIN1,  DashdyOnReceivedVPIN2,  DashdyOnReceivedVPIN3,  DashdyOnReceivedVPIN4,  DashdyOnReceivedVPIN5, 
    DashdyOnReceivedVPIN6,  DashdyOnReceivedVPIN7,  DashdyOnReceivedVPIN8,  DashdyOnReceivedVPIN9,  DashdyOnReceivedVPIN10, 
    DashdyOnReceivedVPIN11, DashdyOnReceivedVPIN12, DashdyOnReceivedVPIN13, DashdyOnReceivedVPIN14, DashdyOnReceivedVPIN15, 
    DashdyOnReceivedVPIN16, DashdyOnReceivedVPIN17, DashdyOnReceivedVPIN18, DashdyOnReceivedVPIN19, DashdyOnReceivedVPIN20, 
    DashdyOnReceivedVPIN21, DashdyOnReceivedVPIN22, DashdyOnReceivedVPIN23, DashdyOnReceivedVPIN24, DashdyOnReceivedVPIN25, 
    DashdyOnReceivedVPIN26, DashdyOnReceivedVPIN27, DashdyOnReceivedVPIN28, DashdyOnReceivedVPIN29, DashdyOnReceivedVPIN30, 
    DashdyOnReceivedVPIN31, DashdyOnReceivedVPIN32, DashdyOnReceivedVPIN33, DashdyOnReceivedVPIN34, DashdyOnReceivedVPIN35, 
    DashdyOnReceivedVPIN36, DashdyOnReceivedVPIN37, DashdyOnReceivedVPIN38, DashdyOnReceivedVPIN39, DashdyOnReceivedVPIN40, 
    DashdyOnReceivedVPIN41, DashdyOnReceivedVPIN42, DashdyOnReceivedVPIN43, DashdyOnReceivedVPIN44, DashdyOnReceivedVPIN45, 
    DashdyOnReceivedVPIN46, DashdyOnReceivedVPIN47, DashdyOnReceivedVPIN48, DashdyOnReceivedVPIN49, DashdyOnReceivedVPIN50
};

static const NoParamHandler onConnectedHandler = DashdyOnConnected;
static const NoParamHandler onDisconnectedHandler = DashdyOnDisconnected;

#ifdef __cplusplus
}
#endif
void DashdyBase::init(WiFiClient &wifi_client,const char* endpoint,uint16_t port){
  this->client = new PubSubClient(wifi_client);
  this->client->setServer(endpoint, port);
  this->client->setCallback(std::bind(&DashdyBase::dahsdy_message_callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  
#if defined(ESP32)
  this->client_id = "dashdy-esp32-" + WiFi.macAddress();
#elif defined(ESP8266)
  this->client_id = "dashdy-esp8266-" + WiFi.macAddress();
#else
  this->client_id = "dashdy-none-" + WiFi.macAddress();
#endif

}

// constructor 
DashdyBase::DashdyBase(){
  auto wifi_client = new WiFiClient();
  this->init(*wifi_client);
}
DashdyBase::DashdyBase(WiFiClient &_client){
  this->init(_client);
}
DashdyBase::DashdyBase(const char* endpoint, uint16_t port){
  auto wifi_client = new WiFiClient();
  this->init(*wifi_client,endpoint,port); 
}
DashdyBase::DashdyBase(WiFiClient &_client,const char* endpoint, uint16_t port){
  this->init(_client,endpoint,port);
}

// begin
void DashdyBase::begin(const char* token, const char* ssid, const char* password, uint16_t channel){
  this->auto_wifi = true;
  this->wifi_ssid = ssid;
  this->token = token;
  this->channel = channel;
  this->wifi_password = password;
  this->init_connection();
  
}
void DashdyBase::begin(const char* token){
  this->auto_wifi = false;
  this->init_connection();
}
void DashdyBase::init_connection(){
  if(this->state != DASHDY_INIT){
    this->state = DASHDY_INIT;
    this->time_stamp = millis();
  }
  if(this->auto_wifi){
    this->connect_wifi();
  }
}
//wifi connect
void DashdyBase::connect_wifi(){
  DASHDY_DEBUG.printf("[DASHDY]:>Connect WiFi<\n");
  DASHDY_DEBUG.printf("[DASHDY]:SSID : %s\n",this->wifi_ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(this->wifi_ssid, this->wifi_password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.println("Connecting to WiFi..");
//  }
  randomSeed(micros());
}
void DashdyBase::dahsdy_message_callback(char* topic, byte* payload, unsigned int length) {
  //DASHDY_DEBUG.println("=======");
  //DASHDY_DEBUG.println(topic);
  //check topic len first
  if(strlen(topic) < 16){
    DASHDY_DEBUG.println("[DASHDY]:REJECT SHOT TOPIC");
    DASHDY_DEBUG.println(topic);
    return; //reject
  }
  //check message not null
  if(length <= 0){
    DASHDY_DEBUG.println("[DASHDY]:REJECT PAYLOAD EMPTY");
    return; //reject
  }
  //check if first string is dashdy
  if(!(topic[0] == 'd' && topic[1] == 'a' && topic[2] == 's' && topic[3] == 'h' && topic[4] == 'd' && topic[5] == 'y')){
    DASHDY_DEBUG.println("[DASHDY]:REJECT NOT DASHDY");
    return; //reject
  }
  DASHDY_DEBUG.println("[DASHDY]:debug message\n=======");
  for(int i = 0; i < length; i++){
    DASHDY_DEBUG.print(payload[i] < 10 ? "0x0" : "0x");
    DASHDY_DEBUG.print(payload[i],HEX);
    DASHDY_DEBUG.print(",");
    if(i % 10 == 0 && i != 0){
      DASHDY_DEBUG.println(); 
    }
  }
  DASHDY_DEBUG.println("\n=======");
  //parse channel
  int channel = -1;
  int start_io_pin = 15;
  if(topic[8] == 'H' && topic[9] <= '9' && topic[9] >= '0'){
    channel = topic[9] - '0';
    if(topic[10] <= '9' && topic[10] >= '0'){
      channel *= 10;
      channel += (topic[10] - '0');
      start_io_pin = 16;
    }
    if(topic[11] <= '9' && topic[11] >= '0'){
      channel *= 10;
      channel += (topic[11] - '0');
      start_io_pin = 17;
    }
  }
  if(channel != this->channel){
    return; //reject
  }
  //parse pin
  bool isVpin = topic[start_io_pin-1] == 'N';
  bool isGpioPin = topic[start_io_pin-1] == 'O';
  int pin= -1;
  if((topic[start_io_pin-1] == 'O' || topic[start_io_pin-1] == 'N') 
      && topic[start_io_pin] <= '9' && topic[start_io_pin] >= '0'){
    pin = topic[start_io_pin] - '0';
    if(topic[start_io_pin+1] != '/' && topic[start_io_pin+1] <= '9' && topic[start_io_pin+1] >= '0'){
      pin *= 10;
      pin += (topic[start_io_pin + 1] - '0');
    }
    if(topic[start_io_pin+2] != '/' && topic[start_io_pin+2] <= '9' && topic[start_io_pin+2] >= '0'){
      pin *= 10;
      pin += (topic[start_io_pin + 2] - '0');
    }
  }
  //TODO : check gpio range again
  if(channel >= 1 && channel <= DASHDY_MAX_CH){
    if(isVpin && pin <= DASHDY_MAX_VPIN){
      //
      DashdyParam param(payload, 0, length);
      this->write_vpin(pin,param);
    }
    else if(isGpioPin && pin <= DASHDY_MAX_GPIO_PIN){
      bool value = payload[0]=='0' || payload[0]==0;
      this->write_gpio(pin,!value);
    }
  }
}

void DashdyBase::subscribe_all(){
    //String topic = String(this->token)+"/dashdy/CH"+this->channel+"/";
    //DASHDY_DEBUG.printf("sub:");
    //DASHDY_DEBUG.println(topic);
    String topic = String(this->token)+"/dashdy/";
    this->client->subscribe(topic.c_str());
    this->client->subscribe(topic.c_str());
}

void DashdyBase::reconnect(){
  if(this->state != DASHDY_RECONNECT){
    if(this->state == DASHDY_CONNECTED){
      if(onDisconnectedHandler){
        onDisconnectedHandler();
      }
    }
    this->state = DASHDY_RECONNECT;
    this->time_stamp = millis();
  }
  //wait for a while and reconnect again
  if((millis() - this->time_stamp > DASHDY_WAIT_RECONNEC_TIME) || this->state != DASHDY_RECONNECT){
    DASHDY_DEBUG.printf("[DASHDY]:Broker connecting...\n");
    String die_topic = String(this->token)+"/dashdy/absence/";
    String wake_topic = String(this->token)+"/dashdy/presence/";
    if (this->client->connect(this->client_id.c_str(),this->client_id.c_str(),NULL,die_topic.c_str(),1,false,this->client_id.c_str())){
      DASHDY_DEBUG.printf("[DASHDY]:Broker connected\n");
      this->client->publish(wake_topic.c_str(),this->client_id.c_str());
      this->subscribe_all();
      this->state = DASHDY_CONNECTED;
      if(onConnectedHandler){
        onConnectedHandler();
      }
      return;
    }else{
      DASHDY_DEBUG.printf("[DASHDY]:[state %d] Wait %d millisecond\n",this->client->state(),DASHDY_WAIT_RECONNEC_TIME);
      this->time_stamp = millis(); 
    }
  }
  
}
void DashdyBase::publish_data(int pin,String value){
  String topic = String(this->token)+"/dashdy/CH"+this->channel+"/VPIN"+pin+"/";
  DASHDY_DEBUG.printf("[DASHDY]: send message\n");
  DASHDY_DEBUG.println(topic);
  DASHDY_DEBUG.println(value);
  this->client->publish(topic.c_str(),value.c_str());
}
void DashdyBase::virtualPinWrite(int pin,String value){
  this->publish_data(pin,value);
}

void DashdyBase::virtualPinWrite(int pin, int value){
  this->publish_data(pin,String(value));
}

void DashdyBase::virtualPinWrite(int pin, double value){
  this->publish_data(pin,String(value));
}

void DashdyBase::virtualPinWrite(int pin, float value){
  this->publish_data(pin,String(value));
}

void DashdyBase::write_gpio(uint16_t pin, uint16_t value){
  pinMode(pin,OUTPUT);
  digitalWrite(pin,value);
}

void DashdyBase::write_vpin(uint16_t pin,const DashdyParam &value){
  DataReceivedHandler handler = this->GetReadHandler(pin);
  if(handler){
    handler(value);
  }
}

void DashdyBase::run(){
  if (!this->client->connected()) {
    this->reconnect();
  }else{
    this->client->loop();
  }
}

DataReceivedHandler DashdyBase::GetReadHandler(uint8_t pin){
  if (pin > COUNT_ARRAY_OF(receiveHandler)){
     return NULL;
  }
  return receiveHandler[pin-1];
}
