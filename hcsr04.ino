const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;

void setup() {
  // Configurar pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Iniciar comunicación serial
  Serial.begin(9600);
  Serial.println("Prueba del sensor HC-SR04");
  Serial.println("Midiendo distancia...");
}

void loop() {
  // Limpiar el pin Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Generar el pulso ultrasónico de 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer la duración del pulso en el pin Echo
  duration = pulseIn(echoPin, HIGH);

  // Calcular la distancia en centímetros
  // La velocidad del sonido es 343 m/s, o 0.0343 cm/µs
  // Se divide por 2 porque la onda va y vuelve
  distance = duration * 0.0343 / 2;

  // Mostrar la distancia en el Monitor Serie
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // Esperar medio segundo antes de la siguiente medición
}