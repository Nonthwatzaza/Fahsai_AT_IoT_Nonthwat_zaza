/*
 * This example is meant to be used for beginner
 *
 * 2017/04/14
 * by Anto.io team
 *
 */
int Value_D7;
int Value_D8;
int Pin_D7 = 13;
int Pin_D8 = 15;
#include <AntoIO.h>

const char *ssid = "Suwat2510_2.4G";
const char *pass = "0819044717";
const char *user = "Nonthwat_zaza";
const char *token = "Wacj0979ZW56qNbIn1EPL6SsL9FU8T7rlY7O2SLO";
const char *thing = "fahsaiATIOT";

AntoIO anto(user, token, thing);

void setup() {
  Serial.begin(9600);
  anto.begin(ssid, pass, messageReceived);
    pinMode(Pin_D7,OUTPUT);
  pinMode(Pin_D8,OUTPUT);
  pinMode(A0,INPUT);
  anto.sub("channel");
}

void loop() {
  anto.mqtt.loop();
  anto.pub("other channel", 1);
    digitalWrite(Pin_D7, HIGH);     //Turn D7 On
  delay(100);                     //Wait for sensor
  Value_D7 = analogRead(0);       //Read Analog pin as D7
  digitalWrite(Pin_D7, LOW);      //Turn D7 Off

  //Repeat for D8
  digitalWrite(Pin_D8, HIGH);     //Turn D8 On
  delay(100);                     //Wait for sensor
  Value_D8 = analogRead(0);       //Read Analog pin as D8
  digitalWrite(Pin_D8, LOW);      //Turn D8 Off
  delay(100);                     //Wait for sensor

  delay(3000);
    Serial.print("D7 = ");   
  Serial.print(Value_D7);
  Serial.print(" / D8 = ");   
  Serial.println(Value_D8);
}

void messageReceived(String thing, String channel, String payload) {
  Serial.print("Recieved: ");
  Serial.print(thing);
  Serial.print("/");
  Serial.print(channel);
  Serial.print("-> ");
  Serial.println(payload);
}
