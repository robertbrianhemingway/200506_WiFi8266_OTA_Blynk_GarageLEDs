/*
 *  200506 upgrading 200502 sketch to incorporate OTA
 *  -------------------------------------------------
 *  Previous notes in Notes_0n_project
 */
#define times 6   // indicates successful upload
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Arduino.h>
#include <BlynkSimpleEsp8266.h>
#include "LEDPIR_Unit.h"
#include <WidgetRTC.h>

#define  sirenPin   D7
#define  ldrPin     A0
#define  nighttimeLimit 40  // analogRead(A0), Low = night
// -------------------------- Variables ---
String version = "200502 v4a";
LEDUnit     Front(D1,D2);     // led pin, pir pin
LEDUnit     Back(D1,D5);

WidgetLED LEDs(V0);
WidgetTerminal terminal(V2);
WidgetRTC rtc;
byte      sirenValue;  // used to write to Blynk LED widget V0
byte      lastSirenValue; // so we don't write unnecessaarily to Blynk
const char* ssid = "OPTUS_369ECE";
const char* password = "borelleres79249";
char auth[] = "RFQizkZailhQNgGQ2t_1QMKPIFqSuq3j";
bool  eMailButtonState;
bool  manualOnOffButton;

//variabls for blinking an LED with Millis
const int led = D4; // ESP8266 Pin to which onboard LED is connected
// in Tools -> Built in LED is set to "2" which is D4 (may change)
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 200;  // interval at which to blink (milliseconds)
int ledState = LOW;  // ledState used to set the LED

// -------------------------- functions --------
BLYNK_WRITE(V1) {
  eMailButtonState = param.asInt();
}
BLYNK_WRITE(V3) {
  manualOnOffButton = param.asInt();
}
BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
  delay(2000);
}
String getDateTime() {  // returns a String such as '19/03/2020<14:18>'
  String curTime = String(hour())+":"+minute()+":"+second();
  String curDate = String(day())+"/"+month()+"/"+year();
  return curDate+"<"+curTime+"> ";
}
void terminalWrite(String message) { // writes date time message to terminal
    terminal.print(getDateTime());
    terminal.println(message);
    terminal.flush();
}
void setSirenOn() {
    // irrispective of day or night
    digitalWrite(sirenPin, HIGH);
    sirenValue = 255;
}
void setSirenOff() {
    digitalWrite(sirenPin, LOW);
    sirenValue = 50;
}

byte    isItNighttime() {
    /*
     *  returns true if it is isItNighttime
     *  as determined by analog value on A0
     */
     return (analogRead(ldrPin) < nighttimeLimit);
     // typically <32 when dark
}
void Front_ISR() {  // keep simple and short
    if (isItNighttime()) {
        setSirenOn();
        Front.setOn();  // sets ledPin high, records time on
        Back.setOn();
    }
}

void Back_ISR() {  // keep simple and short
    if (isItNighttime()) {
        setSirenOn();
        Back.setOn();  // sets ledPin high, records time on
        Front.setOn();
    }
}
// ----------------- flashD4 ---------------------
void flashD4(byte _times) { // to signal a sucessful upload
    // by flashing D4 (GPIO 2) a number of times
    if ((_times < 0) || (_times > 8)) _times = 4; // just in case
    for (int i=0;i<_times;i++) {
        digitalWrite(D4,HIGH);
        delay(300);
        digitalWrite(D4, LOW);
        delay(300);
    }
}
// -----------------
