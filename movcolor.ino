#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pines del Driver L298N
const int MOTOR_IZQ_IN1 = 7;
const int MOTOR_IZQ_IN2 = 6;
const int MOTOR_DER_IN3 = 5;
const int MOTOR_DER_IN4 = 4;
const int MOTOR_IZQ_ENA = 2; 
const int MOTOR_DER_ENB = 3;

// Pines del Sensor Ultrasónico HC-SR04
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

// Objeto del Sensor de Color TCS34725
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// --- CONSTANTES DE COMPORTAMIENTO ---
const int UMBRAL_OBSTACULO = 15;
const int VELOCIDAD_AVANCE = 90;  // Con ENA en pin 2, esto apagará el motor izq.
const int VELOCIDAD_GIRO   = 140; // Mayor a 128 para que el motor izq. encienda en giros.

// --- DECLARACIÓN DE FUNCIONES ---
void avanzar();
void retroceder();
void detenerse();
void girarDerecha();
void girarIzquierda();
void evadirObstaculo();
int leerDistancia();

// --- SETUP: INICIALIZACIÓN DE COMPONENTES ---
void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando Robot Navegante por Color...");

  // Inicializar Motor
  pinMode(MOTOR_IZQ_IN1, OUTPUT);
  pinMode(MOTOR_IZQ_IN2, OUTPUT);
  pinMode(MOTOR_DER_IN3, OUTPUT);
  pinMode(MOTOR_DER_IN4, OUTPUT);
  pinMode(MOTOR_IZQ_ENA, OUTPUT);
  pinMode(MOTOR_DER_ENB, OUTPUT);

  // Inicializar Sensor Ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializar Sensor de Color
  if (tcs.begin()) {
    Serial.println("Sensor de color TCS34725 encontrado!");
  } else {
    Serial.println("No se encontró el sensor TCS34725. Revisa las conexiones.");
    while (1);
  }

  detenerse();
  Serial.println("Robot listo.");
  delay(1000);
}

// --- LOOP: CICLO PRINCIPAL DEL ROBOT ---
void loop() {
  // 1. CHEQUEO DE SEGURIDAD PRIMERO: ¿Hay un obstáculo?
  int distancia = leerDistancia();
  if (distancia > 0 && distancia < UMBRAL_OBSTACULO) {
    evadirObstaculo();
  } else {
    // 2. SI NO HAY OBSTÁCULOS, NAVEGAR POR COLOR
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    Serial.print("R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.print(b);
    Serial.println();

    // LÓGICA DE DECISIÓN BASADA EN COLOR
    if (g > r && g > b && g > 80) {
      Serial.println("Camino VERDE detectado -> AVANZAR");
      avanzar();
    } else if (r > g && r > b && r > 80) {
      Serial.println("Señal ROJA detectada -> GIRAR DERECHA");
      girarDerecha();
      delay(500);
      detenerse();
      delay(200);
    } else if (b > r && b > g && b > 80) {
      Serial.println("Señal AZUL detectada -> GIRAR IZQUIERDA");
      girarIzquierda();
      delay(500);
      detenerse();
      delay(200);
    } else {
      Serial.println("Camino no definido -> DETENERSE");
      detenerse();
    }
  }

  delay(100);
}

// --- FUNCIONES DE MOVIMIENTO ---

void avanzar() {
  digitalWrite(MOTOR_IZQ_IN1, HIGH);
  digitalWrite(MOTOR_IZQ_IN2, LOW);
  digitalWrite(MOTOR_DER_IN3, HIGH);
  digitalWrite(MOTOR_DER_IN4, LOW);
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_AVANCE);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_AVANCE);
}

void retroceder() {
  digitalWrite(MOTOR_IZQ_IN1, LOW);
  digitalWrite(MOTOR_IZQ_IN2, HIGH);
  digitalWrite(MOTOR_DER_IN3, LOW);
  digitalWrite(MOTOR_DER_IN4, HIGH);
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_GIRO);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_GIRO);
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
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_GIRO);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_GIRO);
}

void girarIzquierda() {
  digitalWrite(MOTOR_IZQ_IN1, LOW);
  digitalWrite(MOTOR_IZQ_IN2, HIGH);
  digitalWrite(MOTOR_DER_IN3, HIGH);
  digitalWrite(MOTOR_DER_IN4, LOW);
  analogWrite(MOTOR_IZQ_ENA, VELOCIDAD_GIRO);
  analogWrite(MOTOR_DER_ENB, VELOCIDAD_GIRO);
}


// --- FUNCIONES DE SENSORES Y COMPORTAMIENTO ---

int leerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duracion = pulseIn(ECHO_PIN, HIGH);
  return duracion * 0.0343 / 2;
}

void evadirObstaculo() {
  Serial.println("¡OBSTÁCULO! Iniciando evasión...");
  detenerse();
  delay(300);
  retroceder();
  delay(700);
  girarDerecha();
  delay(700);
  detenerse();
  delay(300);
}