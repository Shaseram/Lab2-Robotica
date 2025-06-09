#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Inicializar el sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 encontrado!");
  } else {
    Serial.println("No se encontró el sensor TCS34725... revisa las conexiones.");
    while (1); // Detener el programa si no se encuentra el sensor
  }
}

void loop() {
  uint16_t r, g, b, c; // r, g, b para los colores; c para la luz clara
  
  tcs.getRawData(&r, &g, &b, &c);

  // Imprimir los valores RGB crudos
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.println(b);

  // Lógica simple para identificar el color dominante
  if (r > g && r > b) {
    Serial.println("Color detectado: Rojo ❤️");
  } else if (g > r && g > b) {
    Serial.println("Color detectado: Verde 💚");
  } else if (b > r && b > g) {
    Serial.println("Color detectado: Azul 💙");
  } else if (r > 200 && g > 200 && b > 200) { // Umbrales pueden necesitar ajuste
     Serial.println("Color detectado: Blanco ⚪");
  } else if (r < 50 && g < 50 && b < 50){ // Umbrales pueden necesitar ajuste
     Serial.println("Color detectado: Negro ⚫");
  } else {
    Serial.println("Color detectado: Color Mixto");
  }

  Serial.println("-----------------------");
  delay(1000); // Esperar un segundo antes de la siguiente lectura
}