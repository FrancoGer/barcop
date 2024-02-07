#include <Stepper.h> //Incluir libreria
//#include <AccelStepper.h>
#define home 12
double stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Inversión de pines para que la biblioteca funcione
//AccelStepper stepper(stepsPerRevolution, 8, 10, 9, 11);  // Inversión de pines para que la biblioteca funcione  <- Para utilizar la libreria AccelStepper.h
int vueltasmotorAdelante=8;//cantidad de giros del motor para el avance
int vueltasmotorAtras=8;//cantidad de giros del motor para el avance

int homingrealizado = 0;

//Prototipos de las funciones
void funcionhome();





void setup() {
  int vueltas = 0;// corrobora a cuantas vuetlas del home esta
  myStepper.setSpeed(10); //velocidad del motor 
  // Establece la velocidad máxima del motor en 100 pasos por segundo
  //stepper.setMaxSpeed(10); <- Para utilizar la libreria AccelStepper.h
  Serial.begin(9600);

  // Establece la aceleración del motor en 500 pasos por segundo al cuadrado
  //stepper.setAcceleration(50); <- Para utilizar la libreria AccelStepper.h

  pinMode(home,INPUT); // defino el home como salida
  pinMode(2, OUTPUT);// defino Led
  pinMode(3, OUTPUT);// defino Led

//Homing
//homing();  // <- Leer la aclaracion en void homing
homing();
/*
  //una vuelta hacia adelante (Antiorario)
   for(int i=0;i<vueltasmotorAdelante;i++){
    if(home == LOW){  //Cambiar si no se mueve el carrito a LOW
       for(int i=0;i<vueltasmotorAdelante;i++){
       Serial.println("Realizando Homing");
        myStepper.step(-stepsPerRevolution); // Cambiar si se mueve para el lado contrario del homing // sacando el menos
        vueltas = vueltas++; // cuenta las vueltas para volver al punto home 
       }
    }
   }
*/
}
void loop() {

  /*
  Ejemplo de como mover el motor con la libreria AccelStepper.h
  // Mueve el motor a la posición 500
  stepper.moveTo(500);

  // Inicia el movimiento del motor
  stepper.run();
  */

  // Homing
  Serial.println(homingrealizado);
  if(homingrealizado == 0){
    Serial.println("Realizando Homing dentro del void loop");
    homing();
    homingrealizado = 1;
  }
  else if(homingrealizado == 1) {
    Serial.println("Homing ya realizado");
  }
//_________
  while (Serial.available() == 0) {
    // No hace nada mientras no se reciba un carácter
  }

  // Lee el carácter enviado por el puerto serie
  char c = Serial.read();
//_________

  if(c == 'i'){
    movimiento();
  }

}


void movimiento(){
  //una vuelta hacia adelante (Antiorario)
  for(int i=0;i<vueltasmotorAdelante;i++){
    Serial.println("en sentido anti-horario");
    myStepper.step(stepsPerRevolution);
  }
  digitalWrite(2 , HIGH);
  Serial.println("Llenando el vaso");
  delay(5000); //tiempo de espera donde se cargaria el liquido
  digitalWrite(2 , LOW);
  Serial.println("Fin del llenando el vaso");

  // una vuelta hacia atras (Horario)
    for(int i=0;i<vueltasmotorAtras;i++){
      Serial.println("agujas del reloj");
      myStepper.step(-stepsPerRevolution);

    }
  Serial.println("Llenando el vaso");
  digitalWrite(3 , HIGH);
  delay(5000);//tiempo de espera donde se cargaria el liquido
  digitalWrite(3 , LOW);
  Serial.println("Fin del llenando el vaso");
}



 /*void funcionhome(){
  //vueltasmotorAdelante   -> Es una variable global, por eso no se nesesita pasar informacion a la funcion
  Serial.println("funcionhome");
  for(int i =0;i<vueltasmotorAdelante; i++){

    if(home==LOW){
      Serial.println("Realizando Homing");
      Serial.println("In if");
      myStepper.step(-stepsPerRevolution); // Cambiar si se mueve para el lado contrario del homing // sacando el menos
       


    }
    else if(home == HIGH){
      Serial.println("Else If");
      delay(1000);
    }
  }  
  homingrealizado=1;
}*/
void homing() {
    // Mueve el motor hacia adelante hasta que se active el sensor de límite
    while(!digitalRead(home)) {
      Serial.println(digitalRead(home));
    // Mueve el motor un paso hacia adelante
      if(digitalRead(home) == 0){
        for(int i=0;i<vueltasmotorAtras;i++){
          if(digitalRead(home) == 0){
            Serial.println(digitalRead(home));
            Serial.println("Realizando Homing");
            myStepper.step(-stepsPerRevolution);
          }
        }
      }
    }

    // Detiene el movimiento del motor
    myStepper.step(0);
    homingrealizado=1;
}