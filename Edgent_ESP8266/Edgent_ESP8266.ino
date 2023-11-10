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
#include "LedControl.h" // Incluye la biblioteca LedControl
LedControl lc = LedControl(D8, D3, D7, 1); // Crea el objeto LedControl

int motorA_1 = D1;
int motorA_2 = D0;
int motorB_1 = D5;
int motorB_2 = D6;
int ENA = D2;
int ENB = D6;
int adelante;
int atras;
int derecha;
int izquierda;
int estadomatriz = 0;
int cfeliz;
int ctriste;
//Comprobar movimientos
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
BLYNK_WRITE(V3){ //derecha
  izquierda = param.asInt();
}
BLYNK_WRITE(V4){
  cfeliz = param.asInt();
}
BLYNK_WRITE(V5){
  ctriste = param.asInt();
}
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
  lc.shutdown(0, false); // Inicializa la matriz de LED
  lc.setIntensity(0, 10); // Ajusta la intensidad del brillo (puedes modificar este valor según tus preferencias)
  lc.clearDisplay(0); // Limpia la matriz antes de comenzar
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run(); 
  if (adelante == 255) { //Adelante
    digitalWrite(motorA_1, LOW);
    digitalWrite(motorA_2, HIGH);
    digitalWrite(motorB_1, LOW);
    digitalWrite(motorB_2, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("pa lante");
    comprobarestadomatriz();
  }
  else if (atras == 255) { //Atras
    digitalWrite(motorA_1, HIGH); //falla
    digitalWrite(motorA_2, LOW);
    digitalWrite(motorB_1, HIGH);
    digitalWrite(motorB_2, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("pa tras");
    comprobarestadomatriz();
  }
  else if (derecha == 255) { //Derecha
    digitalWrite(motorA_1, HIGH); 
    digitalWrite(motorA_2, LOW);
    digitalWrite(motorB_1, HIGH);
    digitalWrite(motorB_2, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("Derecha");
    comprobarestadomatriz();
    guinederecho();
  }
  else if (izquierda == 255) { //Izquierda
    digitalWrite(motorA_1, LOW); 
    digitalWrite(motorA_2, HIGH);
    digitalWrite(motorB_1, LOW);
    digitalWrite(motorB_2, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.println("Derecha");
    comprobarestadomatriz();
    guineizquierdo();
  }
  else if (cfeliz == 255) { 
    carafeliz();
  }
  else if (ctriste == 255) { 
    caratriste();
  }
  else if (adelante == 0 && atras == 0 && derecha == 0 && izquierda == 0) { //Parar
    digitalWrite(motorA_1, LOW);
    digitalWrite(motorA_2, LOW);
    digitalWrite(motorB_1, LOW);
    digitalWrite(motorB_2, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    comprobarestadomatriz();

  }
}

void caratriste() {
    // Define happy como su valor
    byte Triste[8] = {
      0x24, 
      0x24, 
      0x24, 
      0x24, 
      0x00, 
      0x3c, 
      0x42, 
      0x81,
  };
  lc.clearDisplay(0); // Vaciar la matris
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Triste[row]);
  }
  estadomatriz = 1; //Definir la variable estadomatriz como 1
}

void carafeliz() {
   //Define la variable pacman
    byte Feliz[8] = {
0x24, 
0x24, 
0x24, 
0x24, 
0x81,
0xc3, 
0x3c, 
0x00,
  };
  lc.clearDisplay(0); // Vaciar la matris
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Feliz[row]);
  }
  estadomatriz = 2; //Definir la variable estadomatriz como 1
} 

void guineizquierdo(){
  byte Guineizquierdo[8] = {
    0x08, 0x0c, 0x06, 0xff, 0xff, 0x06, 0x0c, 0x08
  };
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Guineizquierdo[row]);

}
estadomatriz = 0;
}

void guinederecho(){
  byte Guinederecho[8] = {
    0x10, 0x30, 0x60, 0xff, 0xff, 0x60, 0x30, 0x10
  };
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Guinederecho[row]);

}
estadomatriz = 0;
}

void comprobarestadomatriz() {
    if (estadomatriz != 1 && estadomatriz != 2) {

            lc.clearDisplay(0);
    }
}