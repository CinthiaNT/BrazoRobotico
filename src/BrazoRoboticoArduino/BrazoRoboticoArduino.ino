//SE incluyen las librerias necesarias
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>

//Se inicializan los 4 servos a utilizar
Servo muneca; // Muñeca
Servo hombro; // Hombro
Servo codo; // Codo
Servo pinza; // PInza

int input;
int valor_muneca = 90; //valor del servo 1
int valor_hombro = 90; //valor del servo 2
int valor_codo = 90; //valor del servo 3
int valor_pinza = 90; //valor del servo 4

int eepromEntrada; //
int eepromAngulo; //

int boton = 12;
int ledServo1 = 4;
int ledServo2 = 5;
int ledServo3 = 6;
int ledServo4 = 7;
int duracion = 250; //Duración del sonido
int fMin = 2000; //Frecuencia más baja que queremos emitir
int fMax = 4000; //Frecuencia más alta que queremos emitir
int i = 0;
int buzzer = 15;
int aut = 0;

void setup() {
  pinMode (boton, INPUT);
  input = 0;
  //Parametros iniciales
  Serial.begin(9600);
  muneca.attach(10); //Muñeca
  hombro.attach(9); //Hombro
  codo.attach(8); //Codo
  pinza.attach(12); //Pinza
  pinMode(ledServo1, OUTPUT);
  pinMode(ledServo2, OUTPUT);
  pinMode(ledServo3, OUTPUT);
  pinMode(ledServo4, OUTPUT);
  pinMode (buzzer, OUTPUT); //pin configurado como salida
}

void loop() {
  if (boton == 1) {

  }

  int estado  = digitalRead(boton);
  eepromEntrada = EEPROM.read(1);
  eepromAngulo = EEPROM.read(2);

  if (eepromAngulo != 0 && eepromAngulo != 180) {


    input = eepromEntrada;
    if (input == '0') {

    } else if (input == '1') {
      aut = 0;
      valor_muneca = eepromAngulo;
      arriba(input);
    } else if (input == '2') {
      aut = 0;
      valor_muneca = eepromAngulo;
      abajo(input);
    } else if (input == '3') {
      aut = 0;
      valor_pinza = eepromAngulo;
      arriba(input);
    } else if (input == '4') {
      aut = 0;
      valor_pinza = eepromAngulo;
      abajo(input);
    } else if (input == '5') {
      aut = 0;
      valor_hombro = eepromAngulo;
      arriba(input);
    } else if (input == '6') {
      aut = 0;
      valor_hombro = eepromAngulo;
      abajo(input);
    } else if (input == '7') {
      aut = 0;
      valor_codo = eepromAngulo;
      arriba(input);
    } else if (input == '8') {
      aut = 0;
      valor_codo = eepromAngulo;
      abajo(input);
    }
  }
  if (Serial.available() > 0) {
    input = Serial.read();
    if (input == '0') {

    } else if (input == '1') {
      aut = 0;
      arriba(input);
    } else if (input == '2') {
      aut = 0;
      abajo(input);
    } else if (input == '3') {
      aut = 0;
      arriba(input);
    } else if (input == '4') {
      aut = 0;
      abajo(input);
    } else if (input == '5') {
      aut = 0;
      arriba(input);
    } else if (input == '6') {
      aut = 0;
      abajo(input);
    } else if (input == '7') {
      aut = 0;
      arriba(input);
    } else if (input == '8') {
      aut = 0;
      abajo(input);
    }
    else if (input == '9') {
      muneca.write(90);
      hombro.write(90);
      codo.write(90);
      pinza.write(90);
      digitalWrite(ledServo1, HIGH);
      digitalWrite(ledServo2, HIGH);
      digitalWrite(ledServo3, HIGH);
      digitalWrite(ledServo4, HIGH);
      delay(100);
      digitalWrite(ledServo1, LOW);
      digitalWrite(ledServo2, LOW);
      digitalWrite(ledServo3, LOW);
      digitalWrite(ledServo4, LOW);
      aut = 1;
      //automatico();
    }
    delay(2500);

  } else {

  }


}
void arriba(char entrada) {

  if (entrada == '1') {
    if (aut == 0) {
      for (; valor_muneca <= 160; valor_muneca++) {
        muneca.write(valor_muneca);
        delay(10);
        digitalWrite(ledServo1, HIGH);
        EEPROM.write(1, entrada);
        EEPROM.write(2, valor_muneca);

        if (boton == 1) {

          quieto1(valor_muneca);
        }
      }
    } else if (aut == 0) {
      valor_muneca += 10;
      if (valor_muneca <= 160) {
        muneca.write(valor_muneca);
        
        digitalWrite(ledServo1, HIGH);
       
        input = 0;
      }

    }
    digitalWrite(ledServo1, LOW);
  }

  if (entrada == '3') {
    for (; valor_pinza >= 0; valor_pinza--) {
      pinza.write(valor_pinza);
      delay(10);
      digitalWrite(ledServo4, HIGH);
      EEPROM.write(1, entrada);
      EEPROM.write(2, valor_pinza);
      if (boton == 1) {
        quieto4(valor_pinza);
      }
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '5') {
       if (aut == 0) {
      for (; valor_hombro <= 180; valor_hombro++) {
        hombro.write(valor_hombro);
        delay(10);
        digitalWrite(ledServo2, HIGH);
        EEPROM.write(1, entrada);
        EEPROM.write(2, valor_hombro);

        if (boton == 1) {

          quieto2(valor_hombro);
        }
      }
    } else if (aut == 0) {
      valor_hombro += 10;
      if (valor_hombro <= 180) { 
        hombro.write(valor_hombro);        
        digitalWrite(ledServo2, HIGH);
        input = 0;
      }

    }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '7') {
    for (; valor_codo >= 0; valor_codo--) {
      codo.write(valor_codo);
      delay(10);
      digitalWrite(ledServo3, HIGH);
      EEPROM.write(1, entrada);
      EEPROM.write(2, valor_codo);
      if (boton == 1) {

        quieto3(valor_codo);
      }
    }
  }
  digitalWrite(ledServo3, LOW);
}

void abajo(char entrada) {
  if (entrada == '2') {
      for (; valor_muneca >= 30; valor_muneca--) {
      muneca.write(valor_muneca);
      delay(10);
      digitalWrite(ledServo1, HIGH);
      EEPROM.write(1, entrada);
      EEPROM.write(2, valor_muneca);
      if (boton == 1) {

        quieto1(valor_muneca);
      }
    }
    digitalWrite(ledServo1, LOW);
  }
  if (entrada == '4') {
    for (; valor_pinza <= 120; valor_pinza++) {
      pinza.write(valor_pinza);
      delay(10);
      digitalWrite(ledServo4, HIGH);
      EEPROM.write(1, entrada);
      EEPROM.write(2, valor_pinza);
      if (boton == 1) {

        quieto4(valor_pinza);
      }
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '6') {
    for (; valor_hombro >= 70; valor_hombro--) {
      hombro.write(valor_hombro);
      delay(10);
      digitalWrite(ledServo2, HIGH);
      EEPROM.write(1, entrada);
      EEPROM.write(2, valor_hombro);
      if (boton == 1) {

        quieto2(valor_hombro);
      }
    }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '8') {
    for (; valor_codo <= 90; valor_codo++) {
      codo.write(valor_codo);
      delay(10);
      digitalWrite(ledServo3, HIGH);
      EEPROM.write(1, entrada);
      EEPROM.write(2, valor_codo);
      if (boton == 1) {

        quieto3(valor_codo);

      }
    }
  }
  digitalWrite(ledServo3, LOW);
}

void quieto1(int angulo) {

  muneca.write(angulo);
}
void quieto2(int angulo) {

  hombro.write(angulo);
}
void quieto3(int angulo) {

  codo.write(angulo);
}
void quieto4(int angulo) {
  pinza.write(angulo);
}



void automatico() {
  abajo('4');//izquierda
  delay(2000);
  abajo('2');//abajo hombro
  delay(2000);
  abajo('6');//abajo codo
  delay(2000);
  arriba('7');//abrir pinza
  delay(2000);
  abajo('8');//cierra pinza
  delay(2000);
  arriba('1');//arriba hombro
  delay(2000);
  arriba('5');//arriba codo
  delay(2000);
  arriba('3');//derecha
  delay(2000);
  abajo('2');//abajo hombro
  delay(2000);
  abajo('6');//abajo codo
  delay(2000);
  arriba('7');//abrir pinza
  delay(2000);
  abajo('8');//cierra pinza
  delay(2000);
  arriba('1');//arriba hombro
  delay(2000);
  arriba('5');//arriba codo
input = 9;
}
