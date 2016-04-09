/* Version 0.1
   Sensor's eyes:
                 1 = black-line - led spento
                 0 = white - led acceso
   Ultra sensor: HC-SR04 , 2cm to 400cm
   Shift register: 74HC595
   Binary to Decimal: http://goo.gl/TbCHd
   Arduino Uno R3 PinOut: http://goo.gl/00BIhe

   Git: DaveCalaway
*/

#include <SoftwareSerial.h>
#include <AFMotor.h>
// ------------------------- Pins
// Pin connected to HC-SR04
#define trigPin 15 //A1 13
#define echoPin 16 //A2 12
// Pin connected to 74HC595
#define latchPin 17 //A3 8
#define clockPin 18 //A4 10
#define dataPin 19 //A5 11
// ------------------------- bitOrder 
#define MSBF 0
#define LSBF 1

// motor define
AF_DCMotor m_SX(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor m_DX(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

int linea = 0;
int ultra = 0;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT); // ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(A0, INPUT);     //  linea sensor
  pinMode(latchPin, OUTPUT);  // 74HC595
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  m_SX.setSpeed(70);     // set the speed to 0/255
  m_DX.setSpeed(70);
}

// Corpo del programma
void loop() {
  // Motori avanti
  m_SX.run(FORWARD);
  m_DX.run(FORWARD);
  
  // Stato linea
  while (readlinea(linea) == 1) {
    // sorpasso sicuro
    if (readultra(distance) > 300) {
      Serial.println("Sorpasso sicuro");
      // accendi led verdi
      shift(7,LSBF);
    }
    // sorpasso al limite
    if (readultra(distance) > 100 && readultra(distance) < 300) {
      Serial.println("Sorpasso limite");
      // accendi led gialli
      shift(24,LSBF);
    }
    // no sorpasso
    if (readultra(distance) < 100) {
      Serial.println("No sorpasso");
      // accendi led rossi
      shift(7,MSBF);
    }
  }
  Serial.println("Linea continua");   
  // accendi led rossi
  shift(7,MSBF);
  delay(250);
}

