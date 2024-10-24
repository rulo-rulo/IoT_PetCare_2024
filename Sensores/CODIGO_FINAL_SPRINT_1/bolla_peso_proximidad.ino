#include <M5Stack.h>
#include "HX711.h"

#define PIR_PIN 36          // Pin para el sensor de proximidad
#define BOYA_PIN 35         // Pin para la boya
#define MOVEMENT_DELAY 500  // Tiempo en milisegundos para considerar que ya no hay movimiento

const int DOUT = 21; // Pin de datos de la balanza
const int CLK = 22;  // Pin de reloj de la balanza

HX711 balanza;

int pantallaActual = 0; // Variable para rastrear qué pantalla se muestra

void setup() {
    M5.begin();

    // Inicializa los pines
    pinMode(PIR_PIN, INPUT);
    pinMode(BOYA_PIN, INPUT);
    
    // Inicializa la balanza
    balanza.begin(DOUT, CLK);
    balanza.set_scale(221000.6667); // Establecemos la escala
    balanza.tare(20);  // El peso actual es considerado tara.

    M5.Lcd.setTextSize(2);
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Presiona un boton");
}

void loop() {
    M5.update(); // Actualiza el estado de los botones

    // Control de botones
    if (M5.BtnA.wasPressed()) {
        pantallaActual = 1; // Cambia a la pantalla de proximidad
        mostrarProximidad();
    }
    else if (M5.BtnB.wasPressed()) {
        pantallaActual = 2; // Cambia a la pantalla de la boya
        mostrarBolla();
    }
    else if (M5.BtnC.wasPressed()) {
        pantallaActual = 3; // Cambia a la pantalla de la balanza
        mostrarBalanza();
    }

    // Mantiene la pantalla actual activa
    if (pantallaActual == 1) {
        leerProximidad(); // Actualiza la lectura del sensor PIR
    }
    else if (pantallaActual == 2) {
        leerBolla(); // Actualiza la lectura del sensor de la boya
    }
    else if (pantallaActual == 3) {
        leerBalanza(); // Actualiza la lectura de la balanza
    }
}

void mostrarProximidad() {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Proximidad:");
}

void mostrarBolla() {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Bolla:");
}

void mostrarBalanza() {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Balanza:");
}

void leerProximidad() {
    int pirState = digitalRead(PIR_PIN);  // Leer el estado del sensor PIR
    Serial.print("Estado del PIR: ");
    Serial.println(pirState);  // Mostrar el estado del sensor en el monitor serie

    // Limpia la pantalla antes de mostrar el nuevo estado
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0); // Posiciona el cursor para mostrar el estado

    if (pirState == HIGH) {  // Si se detecta movimiento
        Serial.println("Movimiento detectado!");
        M5.Lcd.print("Movimiento detectado!");
    } else {  // Si no hay movimiento
        Serial.println("No hay movimiento");
        M5.Lcd.print("No hay movimiento");
    }

    delay(300); // Retardo para evitar lecturas excesivas
}

void leerBolla() {
    int boyaState = digitalRead(BOYA_PIN);  // Leer el estado del sensor Pico de Pato

    M5.Lcd.setCursor(0, 40);
    M5.Lcd.print("Estado: ");  // Mostrar estado en la pantalla

    if (boyaState == HIGH) {  // Si la bolla está arriba (circuito cerrado)
        M5.Lcd.print("Bolla arriba");
    } else {  // Si la bolla está abajo (circuito abierto)
        M5.Lcd.print("Bolla abajo");
    }
}

void leerBalanza() {
    M5.Lcd.setCursor(0, 40);  // Cambia la posición del cursor para mostrar el peso
    M5.Lcd.print("Peso: ");
    M5.Lcd.print(balanza.get_units(20), 3);  // Muestra el peso en kg
    M5.Lcd.println(" kg");

    Serial.print("Peso: ");
    Serial.print(balanza.get_units(20), 3);
    Serial.println(" kg");

    delay(500);  // Retardo para evitar lecturas excesivas
}
