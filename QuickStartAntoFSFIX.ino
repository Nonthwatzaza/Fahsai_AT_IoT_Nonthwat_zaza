#define LDR D2
#include <AntoIO.h>

const char *ssid = "Suwat2510_2.4G";
const char *pass = "0819044717";
const char *user = "Nonthwat_zaza";
const char *token = "Wacj0979ZW56qNbIn1EPL6SsL9FU8T7rlY7O2SLO";
const char *thing = "fahsaiATIOT";

// initialize AntoIO instance
AntoIO anto(user, token, thing);



//LED VAR

int LOAD = 0;
float LS = 0;
float HM = 0;

// TEMP VAR
int Vo;
float R1 = 1000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
// LDR VAR
// HUMDI VAR

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion());


  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");

  anto.begin(ssid, pass, messageReceived);
  Serial.println("\nConnected Anto done");

  //Subscript Channels
  anto.sub("Humdi");
  anto.sub("LDR");
  anto.sub("LIght_Swtich");
  anto.sub("Temp");

  //Port input
  //pinMode(D1,INPUT);
  //pinMode(D2,INPUT);
   //pinMode(D5,INPUT);
  //Port output
   //pinMode(D7,OUTPUT);
}

void loop() {
  anto.mqtt.loop();
  // TEMP LOOP
      Vo = analogRead(D1);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - (273.15+11);
      Serial.print("Recieved TEMP D1: ");
          Serial.println(Tc);
  delay (3000); 
// END OF TEMP LOOP



// LDR LOOP
    float LS = analogRead(D2)*(1);
        Serial.print("Recieved LDR D2: ");
        Serial.println(LS);
      anto.pub("LDR",LDR);                                                                                                                                                                                                                                                                                                                 );
        delay (3000);
// END OF LDR LOOP



// HUMID LOOP
    float HM = analogRead((D5)*(5.0/1023.0)*100);
        Serial.print("Recieved HUMID D5: ");
        Serial.println(HM);
        delay (3000);
// END OF HUMID LOOP
}
// LED LOOP
// a callback function for arriving data.
void messageReceived(String thing, String channel, String payload) {

    Serial.print("Recieved: ");
    Serial.print(thing);
    Serial.print("/");
    Serial.print(channel);
    Serial.print("-> ");
    Serial.println(payload);
    if(channel.equals("Temp")){
        float value = payload.toFloat();
        Tc = value;
  }
  //else if(channel.equals("LDR")){
  //      float value = payload.toFloat();
  //      LS = value;
 // }
    else if(channel.equals("Humdi")){
        float value = payload.toFloat();
        HM = value;
    }
    else if(channel.equals("LIght_Swtich")){
        float value = payload.toInt();
       LOAD = value;
        if(LOAD == 1){
            digitalWrite(D7,HIGH);
        }
        else if (LOAD == 0) {
            digitalWrite(D7,LOW);
        }
        // END OF LED LOOP 
    }
  }
