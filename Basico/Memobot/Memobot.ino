/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * //////////////////////////////////////////////////////////////MEMOBOTS////////////////////////////////////////////////////////////////////////////////////////
 * ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 * 
 * ////////////////////////////////////////////////////          MOTORES        ////////////////////////////////////////////////////////////////////////////////
 * El robot posee dos motores. Se utilizan 3 pines para controlar cada motor:
 * 
 * Pines Motor 1: Enable 1(EN1), Entrada 1(IN1), Entrada 2(IN2)
 * Pines Motor 2: Enable 2(EN2), Entrada 2(IN3), Entrada 2(IN4)
 * 
 * Para mover cada motor, se debe asignar una señal PWM utilizando analogWrite(PIN, VALOR), donde PIN corresponde al Enable correspondiente
 * y VALOR corresponde a un numero entero entre 0 a 255 dependiendo de la velocidad deseada. 
 * Posteriormente, se debe utilizar digitalWrite(PIN, VALOR) dependiendo del sentido de giro de los motores.
 * Para mover el motor en un sentido, se debe asignar IN1 en HIGH e IN2 en LOW. Para mover el motor en sentido contrario, se asigna IN1 en LOW e IN2 en HIGH.
 * 
 * ////////////////////////////////////////////////////          "BIGOTES"        //////////////////////////////////////////////////////////////////////////////
 * Los "bigotes" del robot corresponden a dos pines (FRONTAL1 y FRONTAL2). Se deben conectar a los pines digitales del arduino y leerlos con digitalRead(PIN).
 * Al estar desactivados, entregan un valor 1 (HIGH) y al presionarlos, entregan un 0 (LOW).
 * 
 * ////////////////////////////////////////////////////          SENSOR ULTRASONICO      ///////////////////////////////////////////////////////////////////////
 * 
 * Los sensores ultrasonicos poseen cuatro pines: Gnd, Echo, Trigger, Vcc
 * Se debe conectar GND al GND de la placa y Vcc a 5v
 * 
 * Para obtener una medicion del sensor, se debe enviar un pulso que dure 10 microsegundos en el pin Trigger y posteriormente medir el pin Echo utilizando 
 * el comando pulseIn(Trig, HIGH) y luego multiplica 0.034/2 para obtener la distancia medida en cm.  
 * 
 * Francisco Lara
 */


//Definicion de los pines (define NOMBRE PIN)
#define EN1 5 
#define EN2 6
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 7
#define FRONTAL1 8
#define FRONTAL2 9
#define ECHO 10
#define TRIGGER 11

void setup() {
  //Asignacion de pines para los motores
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Asignacion de pines sensor frontal (bigotes)
  pinMode(FRONTAL1, INPUT);
  pinMode(FRONTAL2, INPUT);  

  //Asignacion de pines sensor ultrasonico
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);  
  digitalWrite(TRIGGER, LOW);
   
  Serial.begin(9600);
}

float distancia; //Variable para guardar medicion del sensor ultrasonico

void loop() {
  //Motor1
  analogWrite(EN1, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Motor2
  analogWrite(EN2, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //Medicion Sensor Ultrasonico
  digitalWrite(TRIGGER, HIGH); //Se asigna el estado HIGH en trigger
  delayMicroseconds(10);       //Esperamos 10 microsegundos
  digitalWrite(TRIGGER, LOW);  //Se asigna el estado LOW en trigger
  distancia = pulseIn(ECHO, HIGH); //Medimos el pulso del pin ECHO
  distancia = distancia*0.034/2; //Ajustamos la medicion para obtener centimetros


  //Envio de datos por puerto serial
  Serial.print("Distancia medida: ");
  Serial.print(distancia);
  Serial.print("cm; Sensor izquierdo:  ");
  Serial.print(digitalRead(FRONTAL1));
  Serial.print("; Sensor derecho: ");
  Serial.println(digitalRead(FRONTAL2));
  delay(50);
  
}
