
int izqA = 6;
int izqB = 7;
int izqC = 10;
int izqD = 11;

int derA = 4;
int derB = 5;
int derC = 8;
int derD = 9;

int vel = 255;            // Velocidad de los motores (0-255)
int estado = 'S';         // inicia detenido

int US1 = 2;            // define el pin 2 como (US1) para el Ultrasonido
int US2 = 13;            // define el pin 3 como (US2) para el Ultrasonido
int duracion, distancia;  // para Calcular distacia

float contador = 0;

//Cargamos las librerias encesarias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //fijamos la direccion del LCD y aclaramos que es del tipo 16x2

#include "DHT.h"
#define DHTPIN 12     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);



void setup()
{

  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(derC, OUTPUT);
  pinMode(derD, OUTPUT);

  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(izqC, OUTPUT);
  pinMode(izqD, OUTPUT);

  lcd.init();  //inicializamos LCD
  lcd.backlight(); //prendemos la luz de backlight

  dht.begin();


}

void loop()  {

  //-------------MANEJO DE MOTORES VIA bLUETOOHT---------------------

  if (Serial.available() > 0) // lee el bluetooth y almacena en estado
  {
    estado = Serial.read();

    if (estado == 'F') {       // Boton desplazar al Frente
motores_frente();
         }

    if (estado == 'L') {      // Boton IZQ
motores_izq ();
      
    }

    if (estado == 'S') {     // Boton Parar
      motores_stop();
    }

    if (estado == 'R') {      // Boton DER
     motores_der();
    }

    if (estado == 'B') {      // Boton Reversa
      motores_reversa();
   
    }
  }
  //------------------------LECTURA DE ULTRASONIDO------------------------

  long duracion, distancia;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(US1, OUTPUT);
  digitalWrite(US1, LOW);
  delayMicroseconds(2);
  digitalWrite(US1, HIGH);
  delayMicroseconds(5);
  digitalWrite(US1, LOW);

  pinMode(US1, INPUT);
  duracion = pulseIn(US1, HIGH);                   //VA A SEGUIR PRENDIDO HASTA QUE LA ONDA DE ULTRASONIDO VUELVA

  // convert the time into a distance
  distancia = microsecondsToCentimeters(duracion);      //DEVUELVE EL VALOR CUANDO REBOTA LA ONDA EN "cm"

  if (distancia <= 15 && distancia >= 2)
  { // si la distancia es menor de 15cm
    // necesitamos LCD que avise que frena porque está cerca de una pared

 motores_stop();

  }

  pinMode(US2, OUTPUT);
  digitalWrite(US2, LOW);
  delayMicroseconds(2);
  digitalWrite(US2, HIGH);
  delayMicroseconds(5);
  digitalWrite(US2, LOW);
  pinMode(US2, INPUT);
  duracion = pulseIn(US2, HIGH);

  // convert the time into a distance
  distancia = microsecondsToCentimeters(duracion);

  if (distancia <= 15 && distancia >= 2)
  { // si la distancia es menor de 15cm
    // necesitamos LCD que avise que frena porque está cerca de una pared
    
   motores_stop();

  }

  //----------------LECTURA DEL SENSOR DE TEMPERATURA Y HUIMEDDAD----------------

  if ((millis() - contador) > 2000)
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    lcd.setCursor(0, 0); //nos ubicamos en al posicion 0,0 del LCD
    lcd.print("Temperatura:");  //imprimimos mensaje
    lcd.print(t, 0);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humedad: " );
    lcd.print(h);
    lcd.print("%");
    contador = millis();
  }
}

//--------FUNCION QUE SE ENCARGA DE HACER LA CUENTA DE SEGUNDOS A CM------------

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void motores_stop(void)
{
  //-------motores de la derecha------
  digitalWrite(derA, 0);
  digitalWrite(derB, 0);
  digitalWrite(derC, 0);
  digitalWrite(derD, 0);

  //-------motores de la izquierda------
  digitalWrite(izqA, 0);
  digitalWrite(izqB, 0);
  digitalWrite(izqC, 0);
  digitalWrite(izqD, 0);
}

void  motores_reversa(void)
{
      //-------motores de la derecha------
      digitalWrite(derA, 1);
      digitalWrite(derB, 0);
      digitalWrite(derC, 1);
      digitalWrite(derD, 0);

      //-------motores de la izquierda------
      digitalWrite(izqA, 0);
      digitalWrite(izqB, 1);
      digitalWrite(izqC, 0);
      digitalWrite(izqD, 1);
}

 void motores_frente(void)
 {
   //-------motores de la derecha------
      digitalWrite(derA, 0);
      digitalWrite(derB, 1);
      digitalWrite(derC, 0);
      digitalWrite(derD, 1);

      //-------motores de la izquierda------
      digitalWrite(izqA, 1);
      digitalWrite(izqB, 0);
      digitalWrite(izqC, 1);
      digitalWrite(izqD, 0);
 } 
 void motores_izq (void)
 {
  //-------motores de la derecha------
      digitalWrite(derA, 0);
      digitalWrite(derB, 1);
      digitalWrite(derC, 0);
      digitalWrite(derD, 1);

      //-------motores de la izquierda------
      digitalWrite(izqA, 0);
      digitalWrite(izqB, 1);
      digitalWrite(izqC, 0);
      digitalWrite(izqD, 1);
 }

 void motores_der (void)
 {
  //-------motores de la derecha------
      digitalWrite(derA, 1);
      digitalWrite(derB, 0);
      digitalWrite(derC, 1);
      digitalWrite(derD, 0);

      //-------motores de la izquierda------
      digitalWrite(izqA, 1);
      digitalWrite(izqB, 0);
      digitalWrite(izqC, 1);
      digitalWrite(izqD, 0);

 }     
