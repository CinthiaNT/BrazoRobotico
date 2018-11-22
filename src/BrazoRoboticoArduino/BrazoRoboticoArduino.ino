//SE incluyen las librerias necesarias
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>
#include <Stepper.h>

///Boton
int val = 0; //val se emplea para almacenar el estado del boton
int state = 0; // 0 Robot mientras que 0 encendido
int old_val = 0; // almacena el antiguo valor de val


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
  
  getStatusSize();
  statusSize=cont3;
  leer();

  if (Serial.available() > 0) {
    input = Serial.read();
     if (input == '1') {
      arriba(input);
    } else if (input == '2') {
      abajo(input);      
    }else if (input == 'A') {
      restablecer(input);
    }else if (input == 'B') {
      restablecer(input);
    } else if (input == '3') {
      arriba(input);
    } else if (input == '4') {
      abajo(input);
    } else if (input == '5') {
      arriba(input);
    } else if (input == '6') {
      abajo(input);
    } else if (input == '7') {
      arriba(input);
    } else if (input == '8') {
      abajo(input);
    }else if (input == 'C') {
      giroDer(input);
    }else if (input == 'D') {
      giroDer(input);
    }else if (input == 'E') {
      giroDer(input);
    }else if (input == 'F') {
      giroIzq(input);
    }else if (input == 'G') {
      giroIzq(input);
    }else if (input == 'H') {
      giroIzq(input);
    }else if (input == 'X') {
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
    delay(1500);
  } else {

  }
 
 
}
void arriba(char entrada) {

  if (entrada == '1') {
    for (; valor_muneca <= 160; valor_muneca++) {
      val= digitalRead(boton); // lee el estado del Boton
      if((val == HIGH) && (old_val == LOW)){
      state=1-state;
      delay(10);
      }
      old_val = val; // valor del antiguo estado
        if (state==1){
          break;
        }else{
          muneca.write(valor_muneca);
          delay(5);
          digitalWrite(ledServo1, HIGH);
        }           
      }
    digitalWrite(ledServo1, LOW);
  }

  if (entrada == '3') {
    for (; valor_pinza >= 0; valor_pinza--) {
      pinza.write(valor_pinza);
      delay(5);
      digitalWrite(ledServo4, HIGH);
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '5') {
      for (; valor_hombro <= 180; valor_hombro++) {
        hombro.write(valor_hombro);
        delay(5);
        digitalWrite(ledServo2, HIGH);
      }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '7') {
    for (; valor_codo >= 90; valor_codo--) {
      codo.write(valor_codo);
      delay(5);
      digitalWrite(ledServo3, HIGH);
    }
  }
  digitalWrite(ledServo3, LOW);
}


void restablecer(char entrada){
  if (entrada == 'A') {

    for (; valor_muneca >= 90; valor_muneca--) {
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
        state=1-state;
        delay(10);
        }
        old_val = val; // valor del antiguo estado
        if (state==1){
          break;
        }else{
          muneca.write(valor_muneca);
          delay(5);
          digitalWrite(ledServo1, HIGH);
        } 
    }      
    digitalWrite(ledServo1, LOW);        
  }
  if (entrada == 'B') {
    for (; valor_muneca <= 90; valor_muneca++) {
           val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
      state=1-state;
      delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
        break;
      }else{
        muneca.write(valor_muneca);
        delay(5);
        digitalWrite(ledServo1, HIGH); 
      }        
      }
    digitalWrite(ledServo1, LOW);
}
  
}
    

void abajo(char entrada) {
  if (entrada == '2') {
      for (; valor_muneca >= 30; valor_muneca--) {
      val= digitalRead(boton); // lee el estado del Boton
        if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
          }
          old_val = val; // valor del antiguo estado
          if (state==1){
          break;
          }
          else{ 
          muneca.write(valor_muneca);
          delay(5);
          digitalWrite(ledServo1, HIGH);    
          }       
      }
      digitalWrite(ledServo1, LOW);     
  }
  if (entrada == '4') {
    for (; valor_pinza <= 120; valor_pinza++) {
      pinza.write(valor_pinza);
      delay(5);
      digitalWrite(ledServo4, HIGH);
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '6') {
    for (; valor_hombro >= 90; valor_hombro--) {
      hombro.write(valor_hombro);
      delay(5);
      digitalWrite(ledServo2, HIGH);
    }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '8') {
    for (; valor_codo <= 180; valor_codo++) {
      codo.write(valor_codo);
      delay(5);
      digitalWrite(ledServo3, HIGH);
    }
  }
  digitalWrite(ledServo3, LOW);
}

void automatico() {
 if (Serial.available() > 0) {
    input = Serial.read();
    cont = cont+1;
    if (input == '1') {
      arriba(input);
      EEPROM.write(cont, input);
    } else if (input == '2') {
      abajo(input);
      EEPROM.write(cont, input);
    }else if (input == 'A') {
      restablecer(input);
      EEPROM.write(cont, input);
    }else if (input == 'B') {
      restablecer(input);
      EEPROM.write(cont, input);
    } else if (input == '3') {
      arriba(input);
      EEPROM.write(cont, input);
    } else if (input == '4') {
      abajo(input);
      EEPROM.write(cont, input);
    } else if (input == '5') {
      arriba(input);
      EEPROM.write(cont, input);
    } else if (input == '6') {
      ///aut = 0;
      abajo(input);
      EEPROM.write(cont, input);
    } else if (input == '7') {
      arriba(input);
      EEPROM.write(cont, input);
    } else if (input == '8') {
      abajo(input);
      EEPROM.write(cont, input);
    }else if (input == 'C') {
      giroDer(input);
      EEPROM.write(cont, input);
    }else if (input == 'D') {
      giroDer(input);
      EEPROM.write(cont, input);
    }
    else if (input == 'E') {
      giroDer(input);
      EEPROM.write(cont, input);
    }else if (input == 'F') {
      giroIzq(input);
      EEPROM.write(cont, input);
    }else if (input == 'G') {
      giroIzq(input);
      EEPROM.write(cont, input);
    }else if (input == 'H') {
      giroIzq(input);
      EEPROM.write(cont, input);
    }else if (input == 'X') {
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
  delay(500);
  }else if(entrada == 'D'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(1024);
    digitalWrite(ledPasos, LOW);
    delay(500);
  }else if(entrada == 'E'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(2048);
    digitalWrite(ledPasos, LOW);
    delay(500);
  } 
  
}

void giroIzq(char entrada){

  if(entrada == 'F'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(-512);
    digitalWrite(ledPasos, LOW);
  delay(1000);
  }else if(entrada == 'G'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(-1024);
    digitalWrite(ledPasos, LOW);
    delay(1000);
  }else if(entrada == 'H'){
    digitalWrite(ledPasos, HIGH);
    vuelta.step(-2048);
    digitalWrite(ledPasos, LOW);
    delay(1000);
  }
  
}

 void getStatusSize( ){
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
  
    input = eepromEntrada;
    if (input == '1') {
      arriba(input);
      delay(500);
    } else if (input == '2') {
      abajo(input);
      delay(500);
    }else if (input == 'A') {
      restablecer(input);
      delay(500);
    }else if (input == 'B') {
      restablecer(input);
      delay(500);
    }else if (input == '3') {
      arriba(input);
      delay(500);
    } else if (input == '4') {
      abajo(input);
      delay(500);
    } else if (input == '5') {
      arriba(input);
    } else if (input == '6') {
      abajo(input);
      delay(500);
    } else if (input == '7') {
      arriba(input);
      delay(500);
    } else if (input == '8') {
      abajo(input);
      delay(500);
    }else if (input == 'C') {
      giroDer(input);
      delay(500);
    }else if (input == 'D') {
      giroDer(input);
      delay(500);
    }else if (input == 'E') {
      giroDer(input);
      delay(500);
    }else if (input == 'F') {
      giroIzq(input);
      delay(500);
    }else if (input == 'G') {
      giroIzq(input);
      delay(500);
    }else if (input == 'H') {
      giroIzq(input);
      delay(500);
    }else if (input == 'X') {
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
