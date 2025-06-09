#include <Arduino.h>

// --- PINES Y CONSTANTES ---
const int TRIG_PIN         = 9;
const int ECHO_PIN         = 10;
const int UMBRAL_OBSTACULO = 15; // cm

const int MOTOR_IZQ_IN1  = 7;
const int MOTOR_IZQ_IN2  = 6;
const int MOTOR_DER_IN3  = 5;
const int MOTOR_DER_IN4  = 4;
const int MOTOR_IZQ_ENA  = 2; // PWM
const int MOTOR_DER_ENB  = 3; // PWM

const int VELOCIDAD_MOTOR = 40; // 0-255

// --- SETUP ---
void setup() {
  Serial.begin(9600);

  // Motores
  pinMode(MOTOR_IZQ_IN1, OUTPUT);
  pinMode(MOTOR_IZQ_IN2, OUTPUT);
  pinMode(MOTOR_DER_IN3, OUTPUT);
  pinMode(MOTOR_DER_IN4, OUTPUT);
  pinMode(MOTOR_IZQ_ENA, OUTPUT);
  pinMode(MOTOR_DER_ENB, OUTPUT);

  // Sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  detenerse();
  Serial.println("Robot listo. Iniciando detección de obstáculos...");
  delay(2000);
}

// --- LOOP ---
void loop() {
  long duracion;
  int distancia_cm;

  // Emite pulso ultrasónico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lee eco
  duracion = pulseIn(ECHO_PIN, HIGH);
  distancia_cm = duracion * 0.0343 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia_cm);
  Serial.println(" cm");

  if (distancia_cm > 0 && distancia_cm < UMBRAL_OBSTACULO) {
    Serial.println("¡OBSTÁCULO DETECTADO! Evasión...");
    detenerse();
    delay(500);
    retroceder();
    delay(800);
    detenerse();
    delay(300);
    girarDerecha();
    delay(800);
    detenerse();
    delay(500);
  } else {
    avanzar();
  }

  delay(150);
}

// --- FUNCIONES DE MOVIMIENTO ---

void avanzar() {
  digitalWrite(MOTOR_IZQ_IN1, HIGH);
  digitalWrite(MOTOR_IZQ_IN2, LOW);
  digitalWrite(MOTOR_DER_IN3, HIGH);
  digitalWrite(MOTOR_DER_IN4, LOW);
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_MOTOR);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_MOTOR);
}

void retroceder() {
  digitalWrite(MOTOR_IZQ_IN1, LOW);
  digitalWrite(MOTOR_IZQ_IN2, HIGH);
  digitalWrite(MOTOR_DER_IN3, LOW);
  digitalWrite(MOTOR_DER_IN4, HIGH);
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_MOTOR);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_MOTOR);
}

void detenerse() {
  analogWrite(MOTOR_IZQ_ENA, 0);
  analogWrite(MOTOR_DER_ENB, 0);
}

void girarDerecha() {
  digitalWrite(MOTOR_IZQ_IN1, HIGH);
  digitalWrite(MOTOR_IZQ_IN2, LOW);
  digitalWrite(MOTOR_DER_IN3, LOW);
  digitalWrite(MOTOR_DER_IN4, HIGH);
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_MOTOR);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_MOTOR);
}
