#include <SoftwareSerial.h>
#include "LedControl.h" // Incluye la biblioteca LedControl
LedControl lc = LedControl(13, 8, 12, 1); // Crea el objeto LedControl
// Pines del Bluetooth HC-05
#define bluetoothTx 1
#define bluetoothRx 0
const int Trigger = 4;   //Pin digital 2 para el Trigger del sensor
const int Echo = 7;   //Pin digital 3 para el Echo del sensor
// Pines del puente h L298N
int motorA_1 = 5;
int motorA_2 = 6;
int motorB_1 = 9;
int motorB_2 = 10;
int ENA = 11;
int ENB = 3;
int estadomatriz = 0;

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx); // RX, TX

void setup() {
  // Inicializar comunicación serial de ambos lados (arduino celular, celular arduino)
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  // Configurar pines del puente h L298N como salidas
  pinMode(motorA_1, OUTPUT);
  pinMode(motorA_2, OUTPUT);
  pinMode(motorB_1, OUTPUT);
  pinMode(motorB_2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  //Leds y buzzer
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  //Configuración matris led
  lc.shutdown(0, false); // Inicializa la matriz de LED
  lc.setIntensity(0, 10); // Ajusta la intensidad del brillo (puedes modificar este valor según tus preferencias)
  lc.clearDisplay(0); // Limpia la matriz antes de comenzar
  //ultrasonido  
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  analogWrite(ENA, 225);
  analogWrite(ENB, 225);
}

void loop() {
  //Chequea si se le envia algun dato
  if (bluetooth.available()) {
    char command = bluetooth.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {    //Cadena de comandos
  switch (command) { 
    case 'F':             //Si el modulo Bluetooth HC-05 recibe un "F" 
      adelante();        //Va a ejecutar la función "Adelante"
      break;              //Y luego va a romper la cadena para no hacer todas las funciones
    case 'B':             //Si el modulo Bluetooth HC-05 recibe un "B" 
      atras();            //Va a ejecutar la función "Atras"
      break;              //Y luego va a romper la cadena para no hacer todas las funciones
    case 'R': 
      derecha();
      guinederecho();
      break;
    case 'L':
      izquierda();
      guineizquierdo();
      break;
    case 'S':
      para();
      break;
    case 'V':
      digitalWrite(A0, HIGH);
      break;
    case 'v':
      digitalWrite(A0, LOW);
      break;
    case 'U':
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      break;
    case 'u':
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      break;
    case 'X':
      pacman();
      break;
    case 'x':
      carafeliz();
      break;
    case 'W':
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      break;
    case 'w':
      digitalWrite(A3, LOW);
      digitalWrite(A4, LOW);
    case '1':
      analogWrite(ENA, 130);
      analogWrite(ENB, 130);
      break;
    case '2':
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      break;
    case '3':
      analogWrite(ENA, 170);
      analogWrite(ENB, 170);
      break;
    case '4':
      analogWrite(ENA, 190);
      analogWrite(ENB, 190);
      break;
    case '5':
      analogWrite(ENA, 200);
      analogWrite(ENB, 200);
      break;
    case '6':
      analogWrite(ENA, 209);
      analogWrite(ENB, 209);
      break;
    case '7':
      analogWrite(ENA, 210);
      analogWrite(ENB, 210);
      break;
    case '8':
      analogWrite(ENA, 215);
      analogWrite(ENB, 215);
      break;
    case '9':
      analogWrite(ENA, 220);
      analogWrite(ENB, 220);
    case 'q':
      analogWrite(ENA, 225);
      analogWrite(ENB, 225);
      break;
    // Agrega cualquier otra función que desees utilizar aquí
    default:
      // Comando inválido
      break;
    
  }
}

void adelante() {
digitalWrite(motorA_1, LOW);
digitalWrite(motorA_2, HIGH);
digitalWrite(motorB_1, HIGH);
digitalWrite(motorB_2, LOW);
comprobarestadomatriz();

} 
void atras() {
  digitalWrite(motorA_1, HIGH);
  digitalWrite(motorA_2, LOW);
  digitalWrite(motorB_1, LOW);
  digitalWrite(motorB_2, HIGH);
  comprobarestadomatriz();

}

void derecha() {
  digitalWrite(motorA_1, LOW);
  digitalWrite(motorA_2, HIGH);
  digitalWrite(motorB_1, LOW);
  digitalWrite(motorB_2, HIGH);
  comprobarestadomatriz();
}

void izquierda() {
  digitalWrite(motorA_1, HIGH);
  digitalWrite(motorA_2, LOW);
  digitalWrite(motorB_1, HIGH);
  digitalWrite(motorB_2, LOW);
  comprobarestadomatriz();
  }

void para() {
  digitalWrite(motorA_1, LOW);
  digitalWrite(motorA_2, LOW);
  digitalWrite(motorB_1, LOW);
  digitalWrite(motorB_2, LOW);
  comprobarestadomatriz();
}

void carafeliz() {
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
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Triste[row]);
  }
  estadomatriz = 1;
}

void pacman() {
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
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Feliz[row]);
  }
  estadomatriz = 2;
}
void ultrasonido(){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (d <= 5){
    digitalWrite(A0, HIGH);
    delay(100);
    digitalWrite(A0, LOW);
    delay(100);
    digitalWrite(A0, HIGH);
    delay(100);
    digitalWrite(A0, LOW);
    delay(1500);
    atras();
    delay(500);
    para();
  }
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