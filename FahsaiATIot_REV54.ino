/*
 * This example is meant to be used for beginner
 *
 * 2017/04/14
 * by Anto.io team
 *
 */
 int i = 1;
  int PUMP_mode;
 int Value_D6;
int Value_D7;
int Value_D8;
int Pin_D1 = 5; // PUMP
int Pin_D6 = 12; // Temp
int Pin_D7 = 13; // Humid
int Pin_D8 = 15; //GND_SEN

// TEMP VAR
int Vo;
float R1 = 1000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
// GND_SEN VAR
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
            pinMode(Pin_D1,OUTPUT);
          pinMode(Pin_D6,OUTPUT);
        pinMode(Pin_D7,OUTPUT);
  pinMode(Pin_D8,OUTPUT);
  pinMode(A0,INPUT);
    anto.sub("Temp");
  anto.sub("Humdi");
    anto.sub("GND_SEN");
    anto.sub("PUMP_Swtich");
}

void loop() {
  anto.mqtt.loop();


    digitalWrite(Pin_D6, HIGH);     //Turn D6 On
  delay(100);                     //Wait for sensor
  Value_D6 = analogRead(0);       //Read Analog pin as D6
  digitalWrite(Pin_D6, LOW);      //Turn D6 Off
    delay(100);                     //Wait for sensor

    
    digitalWrite(Pin_D7, HIGH);     //Turn D7 On
  delay(100);                     //Wait for sensor
  Value_D7 = analogRead(0);       //Read Analog pin as D7
  digitalWrite(Pin_D7, LOW);      //Turn D7 Off
  delay(100);                     //Wait for sensor
  
  //Repeat for D8
  digitalWrite(Pin_D8, HIGH);     //Turn D8 On
  delay(100);                     //Wait for sensor
  Value_D8 = analogRead(0);       //Read Analog pin as D8
  digitalWrite(Pin_D8, LOW);      //Turn D8 Off
  delay(100);                     //Wait for sensor
    delay(7000);   
    Serial.print("D7 = ");   
  Serial.print(Value_D7);
  Serial.print(" / D8 = ");   
  Serial.print(Value_D8);
    Serial.print(" / D6 = ");   
  Serial.println(Value_D6);
  
// TEMP LOOP
  R2 = R1 * (1023.0 / Value_D7 - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - (273.15+11);
      Serial.print("Recieved TEMP D7: ");
          Serial.println(Tc);
  delay (3000); 
// END OF TEMP LOOP
    anto.pub("Temp",Tc);
              delay(1000);
      anto.pub("GND_SEN",Value_D8);
                delay(1000);
      anto.pub("Humdi",Value_D6);
          delay(1000);
}

void messageReceived(String thing, String channel, String payload) {
  Serial.print("Recieved: ");
  Serial.print(thing);
  Serial.print("/");
  Serial.print(channel);
  Serial.print("-> ");
  Serial.println(payload);
        if(channel.equals("PUMP_Swtich")){
        PUMP_mode = payload.toInt();
                if(PUMP_mode == 1){
            digitalWrite(D1,HIGH);
        }
        else{
            digitalWrite(D1,LOW);
        }

    }
}
