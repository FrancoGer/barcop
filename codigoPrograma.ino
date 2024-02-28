#include <Stepper.h> //Incluir libreria

#define home 3 // defino pin 3 como home
double stepsPerRevolution = 2048;// especifica cuántos pasos se necesitan para que el eje del motor dé una vuelta completa.
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // Inversión de pines para que la biblioteca funcione

int vueltasmotorAdelante=8;//cantidad de giros del motor para el avance
int vueltasmotorAtras=8;//cantidad de giros del motor para el avance

int homingrealizado = 0;// Variable para verificar el valor del Homing  Si es 0 todavia no esta realizado ; si es 1 este ya se realizo

//Prototipos de las funciones
void funcionhome(); // Su objetivo llevar el carrito a la posicion "home"
void movimiento();// Su objetivo es realizar el desplazamiento del carro hacia ambos lados




void setup() {
 
  int vueltas = 0;// corrobora a cuantas vuetlas del home esta, NO SE USA ACTUALMENTE

  myStepper.setSpeed(10); //velocidad del motor 
  // Establece la velocidad máxima del motor en 100 pasos por segundo
 
  Serial.begin(9600); // inicializa la comunicación serie con una velocidad de 9600 baudios
  

  pinMode(home,INPUT); // defino el home como salida
  pinMode(2, OUTPUT);// defino Led
  pinMode(4, OUTPUT);// defino Led


homing();// llamo a la funcion Homing al iniciar el programa

}
void loop() {

  // Homing , corroboro que este echo en el setup
  Serial.println(homingrealizado);// imprimo por el Serial si es 0 o 1 depende si ya esta realizado o no 
  if(homingrealizado == 0){ // comparo si el homing no fue echo , en ese caso lo realizo
    Serial.println("Realizando Homing dentro del void loop");
    homing();// llamo a la funcion homing 
    homingrealizado = 1; // establesco al homing como realizado
  }
  else if(homingrealizado == 1) {  // comparo que el homing fue echo , en ese caso imprimo 
    Serial.println("Homing ya realizado");
  }
//_________
Serial.println("ingrese I para empezar el ciclo"); // pido por el serial la tecla I para seguir con el codigo ; Metodo de seguridad.

  while (Serial.available() == 0) { // Serial.available() es una función que se utiliza para verificar si hay datos disponibles para ser leídos desde el puerto serie.
    // No hace nada mientras no se reciba un carácter
  }

  char c = Serial.read(); // Lee el carácter enviado por el puerto serie
//_________

  if(c == 'i'){
    movimiento();
  }

}


void movimiento(){
  //una vuelta hacia adelante (Antiorario)
  for(int i=0;i<vueltasmotorAdelante;i++){
    Serial.println("en sentido anti-horario");
    myStepper.step(stepsPerRevolution); //hace que el motor realice un paso hacia adelante (en sentido antihorario) equivalente a una vuelta completa 
  }
  //digitalWrite(2 , HIGH); // prendo LED 
  Serial.println("Llenando el vaso");
  delay(5000); //tiempo de espera donde se cargaria el liquido
  //digitalWrite(2 , LOW); // apago el LED 
  Serial.println("Fin del llenando el vaso");

  // una vuelta hacia atras (Horario)
    for(int i=0;i<vueltasmotorAtras;i++){
      Serial.println("agujas del reloj");
      myStepper.step(-stepsPerRevolution);//hace que el motor realice un paso hacia atras (en sentido antihorario) equivalente a una vuelta completa 
  }

    }
  Serial.println("Llenando el vaso");
  //digitalWrite(4 , HIGH); // prendo LED 
  delay(5000);//tiempo de espera donde se cargaria el liquido
  //digitalWrite(4 , LOW); // apago LED 
  Serial.println("Fin del llenando el vaso");
}


void homing() {
  // Mueve el motor hacia adelante hasta que se active el sensor de límite
  int pasos = 0; // Variable que lleva la cuenta de cuántos pasos ha dado el motor mientras se realiza el homing.
  const int maxPasos = 8; // Número máximo de pasos
  int temp = 0;// Variable temporal utilizada para almacenar el estado del sensor de límite.(home)

  while (digitalRead(home) != 1 && pasos < maxPasos && temp != 1) { //el sensor home siga en 0 y las vueltas del motor sean menos a 8(las totales) y La variable temporal temp no es igual a 1  
    // Imprime el estado del sensor de límite
    Serial.println(digitalRead(home)); // imprime el estado del sensor home ; 0 o 1 
    temp == digitalRead(home); // verifica que el valor del sensor con la variable temp 
    Serial.println(temp); // imprime el estado de la variable temp 

    // Imprime un mensaje de que se está realizando el homing
    Serial.println("Realizando Homing");

    // Mueve el motor un paso
    myStepper.step(-stepsPerRevolution);

    // Incrementa el contador de pasos
    pasos++;

    delay(500);// mando a dormir al procesador durante 500ms
  }

  // Detiene el movimiento del motor
  myStepper.step(0);

  homingrealizado=1; // establesco al homing como realizado
}
