#include <NewPing.h>
#include "BluetoothSerial.h"
#define TRIGGER_PIN 2 // Pin del módulo HC-SR04 conectado al pin TRIGGER
#define ECHO_PIN 15    // Pin del módulo HC-SR04 conectado al pin ECHO
#define MAX_DISTANCE 400 // Profundidad máxima del recipiente en centímetros
#define motobomba 4
String a;
int b;
int nivel;
String motoBomba;
float litros;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("BluetoothESP32");
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(motobomba, OUTPUT);
}

void loop() {
  delay(1000); // Pequeña pausa para estabilidad
  /*
 float distance = sonar.ping_cm(); // Realiza una medición en centímetros
   if (distance == 0 ) {
    Serial.println("Fuera de rango"); // El sensor no detecta nada en su rango
  }
  else if (distance >= MAX_DISTANCE && distance <= MAX_DISTANCE/2.1) {
    Serial.println("La tuberia está llena"); 
    a=5;
  } else if (distance >= MAX_DISTANCE /2.09 && distance <= MAX_DISTANCE/1.64 ) {
    Serial.println("La tuberia está casi llena");
    a=4;
  } else if(distance >= MAX_DISTANCE / 1.63 && distance <= MAX_DISTANCE/1.26) {
    Serial.println("La tuberia esta a la mitad");
    a=3;
  }else if(distance >= MAX_DISTANCE/1.1) {
    Serial.println("La tuberia esta vacia");
    a=2;
  }*/

   unsigned int distancia = sonar.ping_cm(); // Realiza la medición en centímetros
if (distancia >= 10) {
    Serial.println("VACIO");
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    digitalWrite(motobomba, HIGH);
    a= "VACIO";
    b=2;}
  else if (distancia >= 10 && distancia  >=9) {
    Serial.println("Nivel bajo");
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    digitalWrite(motobomba, HIGH);
    a= "VACIO";
    b=2;
  } else if (distancia < 9 && distancia >= 6) {
    Serial.println("Nivel medio");
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    
    a= "MEDIO";
    b=3;
  } else if (distancia <= 6 && distancia >= 4) {
    Serial.println("Nivel casi lleno");
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    digitalWrite(motobomba, LOW);
    a= "CASI LLENO";
    b=4;
  } 
    // Puedes agregar más casos o acciones para otros rangos de distancia si es necesario
    else if (distancia <= 4 && distancia >= 2) {
    Serial.println("Nivel lleno");
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    digitalWrite(motobomba, LOW);
    a="LLENO";
    b=5;
  }
  /*SerialBT.println(";");
   * SerialBT.println(a);
  SerialBT.println(a);
  SerialBT.println("cm");*/
  
  nivel = (10 - distancia);
  litros = (nivel * 0.4226); 

  Serial.print("Volumen en litros: ");
  Serial.println(litros);
  
  SerialBT.print(distancia);
  SerialBT.print(";");
  SerialBT.print(litros);
  SerialBT.print(";");
  SerialBT.print(b);
  delay(1000);


}
