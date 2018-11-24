/*Autores: Gonzalez Alcaraz Hernan Arturo
 *         Nava Torres Juana Cinthia Lizbeth
 *         Padilla Guerrero Paul Adrian
 *
 * SE incluyen las librerias necesarias
  Libreria EEPROM: Sirve para almacenar en memoria.
  Libreria Servo: Sirve para controlar el funcionamiento
                  de los servo motores
  Stepper: Sirve para controlar el motor a pasos
 */
#include <EEPROM.h>
#include <Servo.h>
#include <Stepper.h>

/*
 * Definicion de variables a utilizar para
 * controlar el funcionamiento del boton
 */
int val = 0; // Almacena el valor actual del boton
int state = 0; // Almacena el estado del robot: 0 cuando el robot esta funcionando
int old_val = 0; // Almacena el valor antiguo del boton


/*Se inicializan los servo motores utilizados:
 * muneca corresponde al servo que mueve la muñeca del brazo robotico
 * hombro corresponde al servo que mueve el hombro del brazo robotico
 * codo corresponde al servo que mueve el codo del brazo robotico
 * pinza corresponde al servo que mueve la pinza del brazo robotico
 * 
 */
Servo muneca;
Servo hombro;
Servo codo; 
Servo pinza;
Stepper vuelta(2048,2,4,3,5);

int input; //Guarda el identificador de cada motor 
int valor_muneca = 90; //valor inicial del servo muneca
int valor_hombro = 90; //valor inicial del servo hombro
int valor_codo = 90; //valor inicial del servo codo
int valor_pinza = 90; //valor inicial del servo pinza

int eepromEntrada; 

int cont=0;
int cont2=0;
int cont3=0;

/*
 * Definicion de pines:
 * Boton que controla el estado de ABORTAR: Pin 16
 * Led que indica el estado del servo muneca(ledServo1): Pin 13
 * Led que indica el estado del servo hombro(ledServo2): Pin 6
 * Led que indica el estado del servo codo(ledServo3): Pin 7
 * Led que indica el estado del servo pinza(ledServo4): Pin 11
 * Led que indica el estado del motor a pasos(ledPasos): Pin 15
 */
int boton = 16;
int ledServo1 = 13;
int ledPasos = 15;
int ledServo2 = 6;
int ledServo3 = 7;
int ledServo4 = 11;

char addStatusSize = 0;
byte statusSize;


void setup() {
   /*Parametros iniciales
    * Definicion de pines de Servo motores
    * muneca: Pin 10
    * hombro: Pin 9
    * codo: Pin 8
    * pinza: Pin 12
    * 
    * Velocidad con la que avanzara el motor a pasos: 7
    * 
    * Se defines los LEDS como pin de salida
    * Se define boton como pin de entrada
    */
  input = 0;
  getStatusSize();
  statusSize=cont3;
  Serial.begin(9600);
  muneca.attach(10);
  hombro.attach(9);
  codo.attach(8);
  pinza.attach(12);
  vuelta.setSpeed(7);
  pinMode(ledServo1, OUTPUT);
  pinMode(ledServo2, OUTPUT);
  pinMode(ledServo3, OUTPUT);
  pinMode(ledServo4, OUTPUT);
  pinMode(ledPasos, OUTPUT);
  pinMode(boton, INPUT);
}

void loop() {
  getStatusSize();
  statusSize=cont3;
  leer();
  /*
   * Si la interfaz grafica esta enviando datos asigna
   * el valor recibido a la variable input.
   * Al recibir 1: Mueve muñeca a la derecha
   * Al recibir 2: Mueve muñeca a la izquierda
   * Al recibir 3: Cierra pinza
   * Al recibir 4: Abre pinza 
   * Al recibir 5: Sube hombro
   * Al recibir 6: Baja hombro
   * Al recibir 7: Cerrar codo
   * Al recibir 8: Bajar codo
   * Al recibir 9: Movimiento automatico
   * Al recibir a: Alinea muñeca derecha
   * Al recibir b: Alinea muñeca izquierda
   * Al recibir c: Mueve cintura 90° Derecha
   * Al recibir d: Mueve cintura 180° Derecha
   * Al recibir e: Mueve cintura 360° Derecha
   * Al recibir f: Mueve cintura 90° Izquierda
   * Al recibir g: Mueve cintura 180° Izquierda
   * Al recibir h: Mueve cintura 360° Izquierda
   * Al recibir x: Borra Secuencia
   */
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
      /*
       * Estado inicial de los servos en 90°
       */
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
  /*
   * Metodo para mover servo motores hacia arriba
   * Recibe un valor dependiendo del servo que se
   * desea mover. 
   * Si se presiona el boton de abortar
   * guarda el estado del servo motor y cuando se 
   * vuelve a presionar el boton y continua en el estado que se quedo.
   */
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
            val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
          break;
      }else{
      pinza.write(valor_pinza);
      delay(5);
      digitalWrite(ledServo4, HIGH);
      }
      
      
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '5') {
      for (; valor_hombro <= 180; valor_hombro++) {
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
          break;
      }else{
        hombro.write(valor_hombro);
        delay(5);
        digitalWrite(ledServo2, HIGH);
      }
      }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '7') {
    for (; valor_codo >= 80; valor_codo--) {
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
        break;
      }else{
      codo.write(valor_codo);
      delay(5);
      digitalWrite(ledServo3, HIGH);
      }
      
      
    }
  }
  digitalWrite(ledServo3, LOW);
}


void restablecer(char entrada){
  /*
   * Metodo para restablecer la muñeca 
   * Si te envia A se restablece cuando esta a la derecha
   * Si te envia B se restablece cuando esta a la izquierda
   */
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
    /*
   * Metodo para mover servo motores hacia abajo
   * Recibe un valor dependiendo del servo que se
   * desea mover. 
   * Si se presiona el boton de abortar
   * guarda el estado del servo motor y cuando se 
   * vuelve a presionar el boton y continua en el estado que se quedo.
   */
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
    for (; valor_pinza <= 100; valor_pinza++) {
            val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
          break;
      }else{
      pinza.write(valor_pinza);
      delay(5);
      digitalWrite(ledServo4, HIGH);
      }
      
    }
    digitalWrite(ledServo4, LOW);
  }
  if (entrada == '6') {
    for (; valor_hombro >= 90; valor_hombro--) {
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
        break;
      }else{
      hombro.write(valor_hombro);
      delay(5);
      digitalWrite(ledServo2, HIGH);  
      }      
    }
    digitalWrite(ledServo2, LOW);
  }
  if (entrada == '8') {
    for (; valor_codo <= 180; valor_codo++) {
            val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
      break;
      }else{
        codo.write(valor_codo);
      delay(5);
      digitalWrite(ledServo3, HIGH);
      }
      
    }
    digitalWrite(ledServo3, LOW);
  }
  
}

void automatico() {
  /*
   * Se genera una secuencia automatica.
   * 
   * Lee lo que esta guardado en la memoria prom
   * y el valor lo envia a los servo motores y motor a pasos
   * 
   */
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
  /*
   * Metodo para mover el motor a pasos a la derecha
   * dependiendo de los grados que el usuario indique
   */
  if(entrada == 'C'){
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
      digitalWrite(ledPasos, LOW);
      }else{
      digitalWrite(ledPasos, HIGH);
      vuelta.step(512);
      }    
    digitalWrite(ledPasos, LOW);
    delay(500);
  }else if(entrada == 'D'){
          val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
       digitalWrite(ledPasos, LOW);
      }else{
    digitalWrite(ledPasos, HIGH);
    vuelta.step(1024);
      }
    digitalWrite(ledPasos, LOW);
    delay(500);
  }else if(entrada == 'E'){
          val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
          digitalWrite(ledPasos, LOW);
      }else{
      digitalWrite(ledPasos, HIGH);
      vuelta.step(2048);
      }
      digitalWrite(ledPasos, LOW);
      delay(500);
  } 
  
}

void giroIzq(char entrada){
  /*
   * Metodo para mover el motor a pasos a la izquierda
   * dependiendo de los grados que el usuario indique
   */
  if(entrada == 'F'){
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
      digitalWrite(ledPasos, LOW);
      }else{
      digitalWrite(ledPasos, HIGH);
      vuelta.step(-512);
      }   
      digitalWrite(ledPasos, LOW);
      delay(500);
  }else if(entrada == 'G'){
      val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
        digitalWrite(ledPasos, LOW);
      }else{
        digitalWrite(ledPasos, HIGH);
        vuelta.step(-1024);
      }  
    digitalWrite(ledPasos, LOW);
    delay(500);
  }else if(entrada == 'H'){
          val= digitalRead(boton); // lee el estado del Boton
      if ((val == HIGH) && (old_val == LOW)){
          state=1-state;
          delay(10);
      }
      old_val = val; // valor del antiguo estado
      if (state==1){
      digitalWrite(ledPasos, LOW);
      }else{
      digitalWrite(ledPasos, HIGH);
      vuelta.step(-2048);
  
      }
      digitalWrite(ledPasos, LOW);   
      delay(500);
  }
  
}

 void getStatusSize( ){
  /*
   * Lee lo que tiene la memoria Prom
   * y se lo asigna a valor.
   */
  for(int i=0;i<=EEPROM.length();i++){
    byte valor = EEPROM.read(i);
    if(valor!=0){
      cont3++;
    }
  }
}


void leer(){
  /*
   * Si la memoria tiene guardado algun valor
   * lo lee y termina hasta que ya no encuentra 
   * datos por leer.
   * Cada valor que lee lo guarda en una variable
   * que compara con el identificador de cada motor a mover
   */
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
  /*
   * Metodo parar borrar la secuencia guardada.
   * Reestablece los valores de los servo motores
   * en 90°, su posicion inicial.
   */
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
