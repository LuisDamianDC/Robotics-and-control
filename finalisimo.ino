/* Programación de prueba del robot
 * Robótica y Control
 * Anaya Martínez Luis Damián
 */
int salidas[]={11, 10, 7, 6, 5, 4, 2}; //Pines que se definirán como salidas
float distancia; //Creamos la variable para guardar la distancia y la velocidad
bool sderecha, sizquierda, scentro; //Variables de estado de los sensores

void setup() { //Inicializando
  Serial.begin(9600); //Iniciamos comunicación serial
  for(int i=0; i<=8; i++) pinMode(salidas[i], OUTPUT); //Declaramos los pines de salida
  for(int i=A0; i<=A5; i++)pinMode(i, INPUT); //Definimos pines de entrada
  pinMode(3, INPUT); //Declaramos el pin de entrada del sensor ultrasónico
  Serial.println("Hola");
}


void detente(){ //programa para detenerse
  digitalWrite(5, 0); //desactiva enable izquierdo
  digitalWrite(11, 0); //desactiva enable derecho
}

void adelante(){ //función para ir hacia adelante
  digitalWrite(5, 1); //activa enable izquierdo
  digitalWrite(11, 1); //activa enable derecho
  
  digitalWrite(6, 0); //derecha atrás desactivado
  digitalWrite(4, 1); //derecha adelante 
  
  digitalWrite(10, 1); //izquierda adelante
  digitalWrite(7, 0); //izquierda atrás desactivado
}

void atras(){ //programa para ir hacia atrás
  digitalWrite(5, 1); //activa enable izquierdo
  digitalWrite(11, 1); //activa enable derecho
  digitalWrite(6, 1); //derecha atrás 
  digitalWrite(4, 0); //derecha adelante desactivado
  digitalWrite(10, 0); //izquierda adelante desactivado
  digitalWrite(7, 1); //izquierda atrás
}

void derecha(){ //programa para ir hacia la derecha en el segundo giro
  digitalWrite(5, 1); //activa enable izquierdo
  analogWrite(11, 244); //activa enable derecho
  digitalWrite(6, 0); //derecha atrás
  digitalWrite(4, 1); //derecha adelante desactivado
  digitalWrite(10, 0); //izquierda adelante 
  digitalWrite(7, 1); //izquierda atras desactivado
}

void izquierda(){ //programa para ir hacia la derecha en el segundo giro
  analogWrite(11, 255); //activa enable derecho
  analogWrite(5, 241); //activa enable derecho
  digitalWrite(6, 1); //derecha atrás
  digitalWrite(4, 0); //derecha adelante desactivado
  digitalWrite(10, 1); //izquierda adelante 
  digitalWrite(7, 0); //izquierda atras desactivado
}

void derecha2(){ //programa para ir hacia la dereca en 90°
  digitalWrite(5, 1); //activa enable izquierdo
  analogWrite(11, 244); //activa enable derecho
  digitalWrite(6, 0); //derecha atrás
  digitalWrite(4, 1); //derecha adelante desactivado
  digitalWrite(10, 0); //izquierda adelante 
  digitalWrite(7, 1); //izquierda atras desactivado
}


void izquierda2(){ //programa para ir hacia la izquierda
  analogWrite(11, 255); //activa enable derecho
  analogWrite(5, 241); //activa enable derecho
  digitalWrite(6, 1); //derecha atrás
  digitalWrite(4, 0); //derecha adelante desactivado
  digitalWrite(10, 1); //izquierda adelante 
  digitalWrite(7, 0); //izquierda atras desactivado
  }

void medicion(){ //función para medir distancias con el sensor ultrasónico
  digitalWrite(2, LOW);//empezamos apagando la fuente del ultrasónico
  delayMicroseconds(2);//esperamos dos microsegundos
  digitalWrite(2, HIGH);//encendemos la fuente ultrasónica
  delayMicroseconds(10);//esperamos 10 microsegundos
  digitalWrite(2, LOW); //apagamos la fuente ultrasónica
  distancia=pulseIn(3, HIGH, 8000); //leemos lo que llegó al echo del sensor ultrasónico
  distancia=distancia/58; //dividimos entre la constante obtenida para tiempo-distancia
  if (distancia!=0.0){
  Serial.print("Distancia detectada: ");//Imprimimos la distancia detectada
  Serial.print(distancia,3); //Podemos indicar decimales deseados
  Serial.println("cm");//imprimimos la unidad de medida
  }
}

void loop() {//En el ciclo sin fin
  medicion();//hacemos el ciclo de medición
  sderecha=(digitalRead(A3));
  scentro=(digitalRead(A4));
  sizquierda=(digitalRead(A2));
  if(scentro and !sizquierda and !sderecha) adelante(); //si la del centro tiene la linea, avanza hacia adelante
  else if (sizquierda and !scentro and !sderecha) izquierda(); //si la linea está a la derecha, gira a la izquierda
  else if (!sizquierda and !scentro and sderecha) derecha(); //si la linea está a la izquierda, gira a la derecha
  else if (sizquierda and scentro and !sderecha) izquierda2(); //si está entre el centro y la derecha, gira a la izquierda más veloz
  else if (!sizquierda and scentro and sderecha) derecha2(); //si está entre el centro y la izquierda, girar a la derecha más rápido
  else if (!sizquierda and !scentro and !sderecha) delay(10); //Si no detecta la linea, mantiene el comando anterior
  else detente(); //Si llega al cuadro donde se activan todos los sensores, se detiene
  delay(10); //delay de referencia
}
