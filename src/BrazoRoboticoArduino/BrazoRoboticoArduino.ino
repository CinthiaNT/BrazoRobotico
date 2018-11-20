//SE incluyen las librerias necesarias
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>
#include <Stepper.h>

//Se inicializan los 4 servos a utilizar
Servo muneca; // Muñeca
Servo hombro; // Hombro
Servo codo; // Codo
Servo pinza; // PInza
Stepper vuelta(2048,2,4,3,5);

int input;
int valor_muneca = 90; //valor del servo 1
int valor_hombro = 90; //valor del servo 2
int valor_codo = 90; //valor del servo 3
int valor_pinza = 90; //valor del servo 4
int estado;
int eepromEntrada; //
int eepromAngulo; //
int cont=0;
int cont2=0;
int cont3=0;
int boton = 16;
int ledServo1 = 13;
int ledPasos = 15;
int ledServo2 = 6;
int ledServo3 = 7;
int ledServo4 = 11;
int duracion = 250; //Duración del sonido
int fMin = 2000; //Frecuencia más baja que queremos emitir
int fMax = 4000; //Frecuencia más alta que queremos emitir
int i = 0;
int buzzer = 15;
int aut = 0;
char addStatusSize = 0;
byte statusSize;


void setup() {
  pinMode (boton, INPUT);
  input = 0;
  //Parametros iniciales
  getStatusSize();
  statusSize=cont3;
  Serial.begin(9600);
  muneca.attach(10); //Muñeca
  hombro.attach(9); //Hombro
  codo.attach(8); //Codo
  pinza.attach(12); //Pinza
  pinMode(ledServo1, OUTPUT);
  pinMode(ledServo2, OUTPUT);
  pinMode(ledServo3, OUTPUT);
  pinMode(ledServo4, OUTPUT);
  pinMode(ledPasos, OUTPUT);
  pinMode (buzzer, OUTPUT); 
  //pin configurado como salida
  vuelta.setSpeed(5);
}

void loop() {
  if (boton == 1) {

  }
  getStatusSize();
  statusSize=cont3;
  leer();

  estado  = digitalRead(boton);
  //automatico();
  if (Serial.available() > 0) {
    input = Serial.read();
     if (input == '1') {
      //aut = 0;
      arriba(input);
    } else if (input == '2') {
      //aut = 0;
      abajo(input);
      
    }else if (input == 'A') {
      //aut = 0;
      restablecer(input);
    }else if (input == 'B') {
      //aut = 0;
      restablecer(input);
    } else if (input == '3') {
      //aut = 0;
      arriba(input);
    } else if (input == '4') {
      //aut = 0;
      abajo(input);
    } else if (input == '5') {
      //aut = 0;
      arriba(input);
    } else if (input == '6') {
      //aut = 0;
      abajo(input);
    } else if (input == '7') {
      //aut = 0;
      arriba(input);
    } else if (input == '8') {
      //aut = 0;
      abajo(input);
    }else if (input == 'C') {
      //aut = 0;
      giroDer(input);
    }else if (input == 'D') {
      //aut = 0;
      giroDer(input);
    }
    else if (input == 'E') {
      //aut = 0;
      giroDer(input);
    }else if (input == 'F') {
      //aut = 0;
      giroIzq(input);
    }else if (input == 'G') {
      //aut = 0;
      giroIzq(input);
    }else if (input == 'H') {
      //aut = 0;
      giroIzq(input);
    }else if (input == 'X') {
      //aut = 0;
      borrar();
    }else if (input == '9') {
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
      automatico();
    }
    delay(2500);
  } else {

  }


}
void arriba(char entrada) {

  if (entrada == '1') {
    //if (aut == 0) {
      for (; valor_muneca <= 160; valor_muneca++) {
        if (digitalRead(boton) == HIGH) {

          quieto1(valor_muneca);
        }
        muneca.write(valor_muneca);
        delay(10);
        digitalWrite(ledServo1, HIGH);
        
      }
//    } else if (aut == 0) {
//      valor_muneca += 10;
//      if (valor_muneca <= 160) {
//        muneca.write(valor_muneca);
//        
//        digitalWrite(ledServo1, HIGH);
//       
//        input = 0;
//      }
//
//    }
    digitalWrite(ledServo1, LOW);
  }

  if (entrada == '3') {
    for (; valor_pinza >= 0; valor_pinza--) {
      pinza.write(valor_pinza);
      delay(10);
      digitalWrite(ledServo4, HIGH);
      if (digitalRead(boton) == HIGH) {
        estado = LOW;
        quieto4(valor_pinza);
      }
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '5') {
      // if (aut == 0) {
      for (; valor_hombro <= 180; valor_hombro++) {
        hombro.write(valor_hombro);
        delay(10);
        digitalWrite(ledServo2, HIGH);
        if (digitalRead(boton) == HIGH) {
          estado = LOW;
          quieto2(valor_hombro);
        }
      }
//    } else if (aut == 0) {
//      valor_hombro += 10;
//      if (valor_hombro <= 180) { 
//        hombro.write(valor_hombro);        
//        digitalWrite(ledServo2, HIGH);
//        input = 0;
//      }
//
//    }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '7') {
    for (; valor_codo >= 90; valor_codo--) {
      codo.write(valor_codo);
      delay(10);
      digitalWrite(ledServo3, HIGH);
      if (digitalRead(boton) == HIGH) {
        estado = LOW;
        quieto3(valor_codo);
      }
    }
  }
  digitalWrite(ledServo3, LOW);
}

void restablecer(char entrada){
  if (entrada == 'A') {
    //if (aut == 0) {
      for (; valor_muneca >= 90; valor_muneca--) {
        muneca.write(valor_muneca);
        delay(10);
        digitalWrite(ledServo1, HIGH);
        if (digitalRead(boton) == HIGH) {
          estado = LOW;
          quieto1(valor_muneca);
        }
      }
//    } else if (aut == 0) {
//      valor_muneca -= 10;
//      if (valor_muneca >= 90) {
//        muneca.write(valor_muneca);
//        
//        digitalWrite(ledServo1, HIGH);
//       
//        input = 0;
//      }
//
//    }
    digitalWrite(ledServo1, LOW);
  }
  if (entrada == 'B') {
    //if (aut == 0) {
      for (; valor_muneca <= 90; valor_muneca++) {
        muneca.write(valor_muneca);
        delay(10);
        digitalWrite(ledServo1, HIGH);  
        if (digitalRead(boton) == HIGH) {
          estado = LOW;
          quieto1(valor_muneca);
        }
      }
//    } else if (aut == 0) {
//      valor_muneca += 10;
//      if (valor_muneca <= 90) {
//        muneca.write(valor_muneca);
//        
//        digitalWrite(ledServo1, HIGH);
//       
//        input = 0;
//      }
//
//    }
    digitalWrite(ledServo1, LOW);
  }
  
  
}

void abajo(char entrada) {
  if (entrada == '2') {
      for (; valor_muneca >= 30; valor_muneca--) {
      if (digitalRead(boton) == HIGH) {
        estado = LOW;
        quieto1(valor_muneca);
      }
      muneca.write(valor_muneca);
      delay(10);
      digitalWrite(ledServo1, HIGH);
      
    }
    digitalWrite(ledServo1, LOW);
  }
  if (entrada == '4') {
    for (; valor_pinza <= 120; valor_pinza++) {
      pinza.write(valor_pinza);
      delay(10);
      digitalWrite(ledServo4, HIGH);
      if (digitalRead(boton) == HIGH) {
        estado = LOW;
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
      if (digitalRead(boton) == HIGH) {
        estado = LOW;
        quieto2(valor_hombro);
      }
    }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '8') {
    for (; valor_codo <= 180; valor_codo++) {
      codo.write(valor_codo);
      delay(10);
      digitalWrite(ledServo3, HIGH);
      if (digitalRead(boton) == HIGH) {
          estado = LOW;
        quieto3(valor_codo);

      }
    }
  }
  digitalWrite(ledServo3, LOW);
}

void quieto1(int angulo) {
  
  while(estado == LOW){
    //estado = digitalRead(boton); 
    
  }
  
}
void quieto2(int angulo) {
  while(estado == LOW){
    //estado = digitalRead(boton); 
    
  }
}
void quieto3(int angulo) {
  while(estado == LOW){
    //estado = digitalRead(boton); 
    
  }
}
void quieto4(int angulo) {
  while(estado == LOW){
    //estado = digitalRead(boton); 
   
  }
}



void automatico() {
 if (Serial.available() > 0) {
    input = Serial.read();
    cont = cont+1;
    if (input == '1') {
      //aut = 0;
      arriba(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '2') {
      //aut = 0;
      abajo(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'A') {
      //aut = 0;
      restablecer(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'B') {
      //aut = 0;
      restablecer(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '3') {
      //aut = 0;
      arriba(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '4') {
      //aut = 0;
      abajo(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '5') {
      //aut = 0;
      arriba(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '6') {
      ///aut = 0;
      abajo(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '7') {
      //aut = 0;
      arriba(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    } else if (input == '8') {
      //aut = 0;
      abajo(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'C') {
      aut = 0;
      giroDer(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'D') {
      //aut = 0;
      giroDer(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }
    else if (input == 'E') {
      //aut = 0;
      giroDer(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'F') {
      //aut = 0;
      giroIzq(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'G') {
      //aut = 0;
      giroIzq(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'H') {
      //aut = 0;
      giroIzq(input);
      //cont = cont+1;
      EEPROM.write(cont, input);
    }else if (input == 'X') {
      //aut = 0;
      borrar();
    }
    automatico();
}
}

void giroDer(char entrada){

  if(entrada == 'C'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(512);
    digitalWrite(ledPasos, LOW);
    
   // EEPROM.write(cont+1, entrada);
   // EEPROM.write(cont+1, 512);
  delay(1000);
  }else if(entrada == 'D'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(1024);
    digitalWrite(ledPasos, LOW);
   // EEPROM.write(cont+1, entrada);
   // EEPROM.write(cont+1, 1024);
    delay(1000);
  }else if(entrada == 'E'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(2048);
    digitalWrite(ledPasos, LOW);
   // EEPROM.write(cont+1, entrada);
   // EEPROM.write(cont+1, 2048);
    delay(1000);
  } 
  
}

void giroIzq(char entrada){

  if(entrada == 'F'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(-512);
    digitalWrite(ledPasos, LOW);
    //EEPROM.write(cont+1, entrada);
   // EEPROM.write(cont+1, -512);
  delay(1000);
  }else if(entrada == 'G'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(-1024);
    digitalWrite(ledPasos, LOW);
    //EEPROM.write(cont+1, entrada);
    //EEPROM.write(cont+1, -1024);
    delay(1000);
  }else if(entrada == 'H'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(-2048);
    digitalWrite(ledPasos, LOW);
    //EEPROM.write(cont+1, entrada);
    //EEPROM.write(cont+1, -2048);
    delay(1000);
  }
  
}

 void getStatusSize( ){
  //byte amountOfStatus = EEPROM.read( addStatusSize );
  //return ( amountOfStatus == 255 )? 0 : amountOfStatus;
  for(int i=0;i<=EEPROM.length();i++){
    byte valor = EEPROM.read(i);
    if(valor!=0){
      cont3++;
    }
  }
}


void leer(){
  if(statusSize>0){
  while(cont2<=statusSize){
    cont2 = cont2+1;
  eepromEntrada = EEPROM.read(cont2);

  //if (eepromAngulo != 0 && eepromAngulo != 180){


    input = eepromEntrada;
    if (input == '1') {
      //aut = 0;
      //valor_muneca = eepromAngulo;
      arriba(input);
      delay(1000);
    } else if (input == '2') {
      //aut = 0;
      //valor_muneca = eepromAngulo;
      abajo(input);
      delay(1000);
    }else if (input == 'A') {
      //aut = 0;
      //valor_muneca = eepromAngulo;
      restablecer(input);
      delay(1000);
    }else if (input == 'B') {
      //aut = 0;
      //valor_muneca = eepromAngulo;
      restablecer(input);
      delay(1000);
    }else if (input == '3') {
      //aut = 0;
      //valor_pinza = eepromAngulo;
      arriba(input);
      delay(1000);
    } else if (input == '4') {
      //aut = 0;
      //valor_pinza = eepromAngulo;
      abajo(input);
      delay(1000);
    } else if (input == '5') {
      //aut = 0;
      //valor_hombro = eepromAngulo;
      arriba(input);
    } else if (input == '6') {
      //aut = 0;
      //valor_hombro = eepromAngulo;
      abajo(input);
      delay(1000);
    } else if (input == '7') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      arriba(input);
      delay(1000);
    } else if (input == '8') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      abajo(input);
      delay(1000);
    }else if (input == 'C') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      giroDer(input);
      delay(1000);
    }else if (input == 'D') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      giroDer(input);
      delay(1000);
    }else if (input == 'E') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      giroDer(input);
      delay(1000);
    }else if (input == 'F') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      giroIzq(input);
      delay(1000);
    }else if (input == 'G') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      giroIzq(input);
      delay(1000);
    }else if (input == 'H') {
      //aut = 0;
      //valor_codo = eepromAngulo;
      giroIzq(input);
      delay(1000);
    }else if (input == 'X') {
      //aut = 0;
      borrar();
    }
      }
    cont2=0;
  }
}

void borrar(){
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
   }
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
}
