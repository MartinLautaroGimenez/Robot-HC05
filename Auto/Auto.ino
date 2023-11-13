#include <SoftwareSerial.h> //Incluir la biblioteca SoftwareSerial
#include "LedControl.h" // Incluye la biblioteca LedControl
LedControl lc = LedControl(13, 8, 12, 1); // Crea el objeto LedControl
// Pines del Bluetooth HC-05
#define bluetoothTx 7
#define bluetoothRx 2
// Pines del puente h L298N
int motorA_1 = 5;
int motorA_2 = 6;
int motorB_1 = 9;
int motorB_2 = 10;
//Pines control de velociades
int ENA = 3; 
int ENB = 11;
//Variable para comprobar cuando el robot gira en cualquier sentido
int estadomatriz = 0;
//Define los pines RX, y TX del modulo HC-05
SoftwareSerial bluetooth(bluetoothRx, bluetoothTx); // RX, TX

void setup() {
  // Inicializar comunicación serial de ambos lados
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  // Configurar pines del puente h L298N como salidas
  pinMode(motorA_1, OUTPUT);
  pinMode(motorA_2, OUTPUT);
  pinMode(motorB_1, OUTPUT);
  pinMode(motorB_2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  // Configurar pines de los leds y del buzzer como salidas
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  // Configuración matris led
  lc.shutdown(0, false); // Inicializa la matriz de LED
  lc.setIntensity(0, 10); // Ajusta la intensidad del brillo (puedes modificar este valor según tus preferencias)
  lc.clearDisplay(0); // Limpia la matriz antes de comenzar
  // Configuración del sensor de ultrasonido
  pinMode(Trigger, OUTPUT); // Define el pin Trigger como salida
  pinMode(Echo, INPUT);  // Define el pin Echo como entrada
  digitalWrite(Trigger, LOW);// Inicializamos el pin con valor 0
  // Iniciar con velocidad de motores al máximo
  analogWrite(ENA, 225);
  analogWrite(ENB, 225);
}

void loop() {
  // Chequea si se le envia algun dato
  if (bluetooth.available()) {
    char command = bluetooth.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
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
      digitalWrite(A3, HIGH);
      break;
    case 'v':
      digitalWrite(A3, LOW);
      break;
    case 'U':
      digitalWrite(A4, HIGH);
      break;
    case 'u':
      digitalWrite(A4, LOW);
      break;
    case 'X':                 // Cuando el módulo reciba una 'X' va a ejecutar la función Pacman()
      pacman();
      break;
    case 'x':
      carafeliz();
      break;
    case 'W':
      digitalWrite(A5, HIGH);
      break;
    case 'w':
      digitalWrite(A5, LOW);
    case '1':
      analogWrite(ENA, 130);   //Cuando el módulo reciba un 1 va a ajustar la velocidad a 130
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
      0x01, 0x02, 0xf4, 0x04, 0x04, 0xf4, 0x02, 0x01
  };
  lc.clearDisplay(0); // Vaciar la matris
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Triste[row]);
  }
  estadomatriz = 1; //Definir la variable estadomatriz como 1
}

void pacman() {
   //Define la variable pacman
    byte Feliz[8] = {
      0x0c, 0x04, 0xf2, 0x02, 0x02, 0xf2, 0x04, 0x0c
  };
  lc.clearDisplay(0); // Vaciar la matris
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Feliz[row]);
  }
  estadomatriz = 2; //Definir la variable estadomatriz como 1
} 
void guineizquierdo(){
  byte Guineizquierdo[8] = {
    0x18, 0x3c, 0x7e, 0x9b, 0x18, 0x18, 0x18, 0x18
  };
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Guineizquierdo[row]);

}
estadomatriz = 0;
}
void guinederecho(){
  byte Guinederecho[8] = {
    0x18, 0x18, 0x18, 0x18, 0xdb, 0x7e, 0x3c, 0x18
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