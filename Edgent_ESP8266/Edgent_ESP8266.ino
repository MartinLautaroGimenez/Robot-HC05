/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL2F7NU1aS1"
#define BLYNK_TEMPLATE_NAME "Auto"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

int motorA_1 = D1;
int motorA_2 = D0;
int motorB_1 = D3;
int motorB_2 = D4;
int ENA = D2;
int ENB = D6;
int adelante;
int atras;
int derecha;
int izquierda
void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(motorA_1, OUTPUT);
  pinMode(motorA_2, OUTPUT);
  pinMode(motorB_1, OUTPUT);
  pinMode(motorB_2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run(); 
  if (adelante == 255) { //Adelante
    digitalWrite(motorA_1, LOW);
    digitalWrite(motorA_2, HIGH);
    digitalWrite(motorB_1, HIGH);
    digitalWrite(motorB_2, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("pa lante");
  }
  else if (atras == 255) { //Atras
    digitalWrite(motorA_1, LOW); //falla
    digitalWrite(motorA_2, LOW);
    digitalWrite(motorB_1, LOW);
    digitalWrite(motorB_2, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("pa tras");
  }
  else if (derecha == 255) { //Derecha
    digitalWrite(motorA_1, HIGH); //falla
    digitalWrite(motorA_2, LOW);
    digitalWrite(motorB_1, HIGH);
    digitalWrite(motorB_2, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("Derecha");
  }
  else if (adelante == 0 && atras == 0 && derecha == 0) { //Parar
    digitalWrite(motorA_1, LOW);
    digitalWrite(motorA_2, LOW);
    digitalWrite(motorB_1, LOW);
    digitalWrite(motorB_2, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
  }
}
BLYNK_WRITE(V0){ //adelante
adelante = param.asInt();
}
BLYNK_WRITE(V1){ //atras FALLA
atras = param.asInt();
Serial.println(param.asInt());
}
BLYNK_WRITE(V2){ //derecha
derecha = param.asInt();
}