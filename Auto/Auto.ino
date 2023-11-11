#include <SoftwareSerial.h> //Incluir la biblioteca SoftwareSerial
#include "LedControl.h" // Incluye la biblioteca LedControl
LedControl lc = LedControl(13, 8, 12, 1); // Crea el objeto LedControl
// Pines del Bluetooth HC-05
#define bluetoothTx D6
#define bluetoothRx D7
const int Trigger = 4;   //Pin digital 2 para el Trigger del sensor de ultrasonido
const int Echo = 7;   //Pin digital 3 para el Echo del sensor de ultrasonido
// Pines del puente h L298N
int motorA_1 = D4;
int motorA_2 = D3;
int motorB_1 = D2;
int motorB_2 = D1;
//Pines control de velociades
<<<<<<< HEAD
int ENA = D0;
int ENB = D5;
=======
int ENA = 11;
int ENB = 3;
>>>>>>> parent of cbe8883 (Se actualizaron algunos pines de control de velocidad)
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
  pinMode(A0, OUTPUT);
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
      digitalWrite(A0, HIGH);
      break;
    case 'v':
      digitalWrite(A0, LOW);
      break;
    case 'U':
      break;
    case 'u':
      break;
    case 'X':                 // Cuando el módulo reciba una 'X' va a ejecutar la función Pacman()
      pacman();
      break;
    case 'x':
      carafeliz();
      break;
    case 'W':
      break;
    case 'w':
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
  lc.clearDisplay(0); // Vaciar la matris
  for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, Feliz[row]);
  }
  estadomatriz = 2; //Definir la variable estadomatriz como 1
} 
void ultrasonido(){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10); //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (d <= 5){ 
    digitalWrite(A0, HIGH); //Encender buzzer
    delay(100);
    digitalWrite(A0, LOW); //Apagar buzzer
    delay(100);
    digitalWrite(A0, HIGH); //Encender buzzer
    delay(100);
    digitalWrite(A0, LOW); //Apagar buzzer 
    delay(1500);
    atras(); //Ejecutar la función atras por 500ms
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