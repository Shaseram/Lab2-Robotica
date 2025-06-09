# Integrantes:

- Daniel Miranda
- Nikolai Navea
- Vicente Arratia
- Javier Sepúlveda

# Descripción del Proyecto

El Laboratorio 2 se enfoca en ampliar las capacidades del robot móvil desarrollado previamente. El objetivo es integrar un sensor ultrasónico HC-SR04 para la detección y evasión de obstáculos, y un sensor de color TCS34725 para la identificación de superficies. La meta es que el robot utilice la información de ambos sensores para navegar de forma autónoma, tomando decisiones en tiempo real para evitar colisiones y reaccionar ante colores específicos en su entorno.

# Solución Laboratorio 2

## Parte 1

### Explicación y conexión de componentes

### Codigo funcional con datos de sensores mostrados en el monitor serie

### Analisis de variaciones en las lecturas

### Preguntas Parte 1

- **¿Qué es la percepción en robótica y por qué es fundamental en los sistemas autónomos?**
	- La percepción es la capacidad de un robot para recopilar información de sus sensores y construir un modelo de su entorno y de su propio estado para entender qué está sucediendo a su alrededor. Es fundamental porque, sin percepción, un robot es "ciego y sordo" y no puede tomar decisiones informadas para cumplir sus tareas. La percepción le permite navegar sin chocar, interactuar con objetos, adaptarse a cambios en el entorno y, en general, operar de manera autónoma y segura.

- **En el sensor ultrasonico HC-SR04 Que parametro se mide para calcular la distancia?**
    - Se mide el tiempo que transcurre desde que el sensor emite un pulso de sonido ultrasónico hasta que recibe el eco de ese pulso después de rebotar en un objeto. La distancia se calcula usando este tiempo de vuelo y la velocidad del sonido.

- **¿Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo podría reducirse?**
    - El ruido puede causar lecturas de distancia erráticas e imprecisas. Esto se manifiesta como valores que fluctúan mucho, incluso si el objeto está quieto, o como mediciones completamente incorrectas (por ejemplo, si el eco se pierde o se recibe una señal falsa). Esto afecta directamente la fiabilidad del robot para detectar obstáculos. Para reducirlo, se pueden aplicar técnicas de filtrado de señales.

### Análisis de Mejoras

## Parte 2

### Algoritmo de planificaciíon de rutas reacivos: evitacion de obstaculos,  y deteccion de colores basado en reglas

### Implementacion correcta de umbrales de detección

### Pruebas y ajustes en entorno real

### Reflexión sobre posibles mejoras en la deteccion

### Preguntas Parte 2

- **Si el robot detecta el color rojo en el suelo ¿Qué acción deberá tomar? ¿Por qué?**
    - Al detectar el color rojo, el robot gira a la izquierda. La acción de girar a la izquierda se debe a que, dentro de nuestro algoritmo de planificación básica, hemos definido el color rojo como una señal o marcador que desencadena una regla de navegación específica. En este caso, la regla implementada es: "Si el sensor RGB detecta valores que corresponden al umbral del color rojo, entonces la acción a seguir es girar a la izquierda".

- **Si el sensor ultrasónico detecta valores erráticos ¿Qué estrategias podrías aplicar para mejorar la precisión?**
    - **Filtrado por promedio o mediana**: Tomar un conjunto de mediciones (ej. 5 lecturas rápidas), ordenarlas y usar el valor promedio o el del medio (mediana). La mediana es especialmente útil para descartar valores atípicos extremos.
    - **Filtro de media móvil**: Mantener un historial de las últimas 'N' lecturas y usar su promedio como la distancia actual. Esto suaviza las mediciones a lo largo del tiempo.
    - **Umbral de descarte**: Ignorar lecturas que sean drásticamente diferentes a la anterior. Por ejemplo, si la última lectura fue de 20 cm, una nueva lectura de 200 cm podría considerarse un error y descartarse.

- **Si tuvieras que integrar un nuevo sensor para mejorar la navegación del robot ¿Cuál elegirías y por qué?**
    - Colocaríamos encoders en las ruedas. La IMU es buena para medir la orientación, pero sufre de deriva y no mide la distancia recorrida. ¿Por qué? Los encoders permitirían al robot medir con alta precisión la distancia que ha recorrido y la velocidad real de cada rueda. Esto permitiría implementar un control de "bucle cerrado" mucho más robusto para moverse en líneas rectas o girar ángulos exactos, complementando perfectamente la detección de orientación de la IMU.

 - **¿Cuál es el tiempo de respuesta del robot al detectar un cambio de color?**
    - El tiempo de respuesta es la suma de varios factores:
        - **Tiempo de lectura del sensor**: El tiempo que tarda el TCS34725 en realizar una medición.
        - **Tiempo de procesamiento**: El tiempo que le toma al Arduino ejecutar el código para leer el sensor, procesar los valores RGB, compararlos con los umbrales y decidir una acción.
        - **Tiempo de ejecución del actuador**: El tiempo que tardan los motores en responder a los nuevos comandos (arrancar, detenerse, cambiar velocidad).
    - En general, este tiempo está en el orden de los milisegundos y depende de la eficiencia del código en el bucle principal (loop()). Un código con muchos delay() largos tendrá un tiempo de respuesta mayor.

### Análisis de mejoras

# Códigos utilizados

- movcolor.ino -> Código encargado de la navegación por detección de colores.
- hcsr04.ino -> Código que prueba el sensor hcsr04 y su capacidad de detección.
- rgb.ino -> Código que prueba el sensor rgb.
- movobstaculos.ino -> Código que maneja el movimiento y navegación con detección de obstaculos con el sensor hcsr04.
