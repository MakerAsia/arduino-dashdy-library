#ifndef DashdyBase_h
#define DashdyBase_h

#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#if defined(ESP32)
#include <WiFi.h>
#endif
#include "PubSubClient.h"
#include "DashdyParam.h"

// DASHDY VERSION
#define DASHDY_VERSION_1_0      1
#ifndef DASHDY_VERSION
#define DASHDY_VERSION DASHDY_VERSION_1_0
#endif
// BROKER ENDPOINT (maybe check version first)
#ifndef DASHDY_ENDPOINT
#define DASHDY_ENDPOINT "192.168.1.112"
#endif
#ifndef DASHDY_PORT
#define DASHDY_PORT 8080
#endif

#define DASHDY_INIT       0
#define DASHDY_CONNECTED  1
#define DASHDY_RECONNECT  2

#define DASHDY_WAIT_RECONNEC_TIME   5000
#define DASHDY_DEBUG Serial

#define DASHDY_MAX_CH     999
#define DASHDY_MAX_VPIN   99
#if defined(ESP8266)
#define DASHDY_MAX_GPIO_PIN   16
#endif
#if defined(ESP32)
#define DASHDY_MAX_GPIO_PIN   34
#endif
#define DASHDY_UNUSED __attribute__((__unused__))

#define OnReceive(pin) void DashdyOnReceived ## pin (const DashdyParam DASHDY_UNUSED &param)

#define OnConnected void DashdyOnConnected
#define OnDisconnected void DashdyOnDisconnected

#define COUNT_ARRAY_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


// VIRTUAL PIN
#define VPIN1 1
#define VPIN2 2
#define VPIN3 3
#define VPIN4 4
#define VPIN5 5
#define VPIN6 6
#define VPIN7 7
#define VPIN8 8
#define VPIN9 9
#define VPIN10 10
#define VPIN11 11
#define VPIN12 12
#define VPIN13 13
#define VPIN14 14
#define VPIN15 15
#define VPIN16 16
#define VPIN17 17
#define VPIN18 18
#define VPIN19 19
#define VPIN20 20
#define VPIN21 21
#define VPIN22 22
#define VPIN23 23
#define VPIN24 24
#define VPIN25 25
#define VPIN26 26
#define VPIN27 27
#define VPIN28 28
#define VPIN29 29
#define VPIN30 30
#define VPIN31 31
#define VPIN32 32
#define VPIN33 33
#define VPIN34 34
#define VPIN35 35
#define VPIN36 36
#define VPIN37 37
#define VPIN38 38
#define VPIN39 39
#define VPIN40 40
#define VPIN41 41
#define VPIN42 42
#define VPIN43 43
#define VPIN44 44
#define VPIN45 45
#define VPIN46 46
#define VPIN47 47
#define VPIN48 48
#define VPIN49 49
#define VPIN50 50

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*NoParamHandler)(void);
typedef void (*DataReceivedHandler)(const DashdyParam DASHDY_UNUSED &param);

//Event function
OnConnected();
OnDisconnected();

//VIRTUALPIN FUNCTION DEFINATION
OnReceive();

OnReceive(VPIN1 );
OnReceive(VPIN1 );
OnReceive(VPIN3 );
OnReceive(VPIN4 );
OnReceive(VPIN5 );
OnReceive(VPIN6 );
OnReceive(VPIN7 );
OnReceive(VPIN8 );
OnReceive(VPIN9 );
OnReceive(VPIN10);
OnReceive(VPIN11);
OnReceive(VPIN12);
OnReceive(VPIN13);
OnReceive(VPIN14);
OnReceive(VPIN15);
OnReceive(VPIN16);
OnReceive(VPIN17);
OnReceive(VPIN18);
OnReceive(VPIN19);
OnReceive(VPIN20);
OnReceive(VPIN21);
OnReceive(VPIN22);
OnReceive(VPIN23);
OnReceive(VPIN24);
OnReceive(VPIN25);
OnReceive(VPIN26);
OnReceive(VPIN27);
OnReceive(VPIN28);
OnReceive(VPIN29);
OnReceive(VPIN30);
OnReceive(VPIN31);
OnReceive(VPIN32);
OnReceive(VPIN33);
OnReceive(VPIN34);
OnReceive(VPIN35);
OnReceive(VPIN36);
OnReceive(VPIN37);
OnReceive(VPIN38);
OnReceive(VPIN39);
OnReceive(VPIN40);
OnReceive(VPIN41);
OnReceive(VPIN42);
OnReceive(VPIN43);
OnReceive(VPIN44);
OnReceive(VPIN45);
OnReceive(VPIN46);
OnReceive(VPIN47);
OnReceive(VPIN48);
OnReceive(VPIN49);
OnReceive(VPIN50);

#ifdef __cplusplus
}
#endif

class DashdyBase {
private:
    const char*   wifi_ssid;
    const char*   wifi_password;
    const char*   token;
    uint16_t      channel;
    String        client_id;
    uint32_t      time_stamp;
    PubSubClient  *client;
    uint8_t       state;
    bool auto_wifi = true;
    void subscribe_all();
    void dahsdy_message_callback(char* topic, byte* payload, unsigned int length);
    void reconnect();
    void write_gpio(uint16_t pin,uint16_t value);
    void write_vpin(uint16_t pin,const DashdyParam &value);
    void publish_data(int pin,String value);
    void init(WiFiClient &wifi_client,const char* endpoint = DASHDY_ENDPOINT,uint16_t port = DASHDY_PORT);
    DataReceivedHandler GetReadHandler(uint8_t pin);
    void init_connection();
public:
    DashdyBase();
    DashdyBase(WiFiClient &_client);
    DashdyBase(const char* endpoint, uint16_t port);
    DashdyBase(WiFiClient &_client,const char* endpoint, uint16_t port);
    
    void begin(const char* token, const char* ssid, const char* password = "",uint16_t channel = 1);
    void begin(const char* token);
    void connect_wifi();
    void virtualPinWrite(int pin,String value);
    void virtualPinWrite(int pin,int value);
    void virtualPinWrite(int pin,double value);
    void virtualPinWrite(int pin,float value);
    void run();
};
#endif
