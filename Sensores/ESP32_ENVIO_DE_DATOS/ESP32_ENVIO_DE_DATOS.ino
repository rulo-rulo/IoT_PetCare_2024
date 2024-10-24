#include <WiFi.h>
#include "AsyncUDP.h"
#include "HX711.h"
#include <TimeLib.h>

const char *ssid = "Mari"; // Tu red WiFi
const char *password = "iloveme0807"; // Tu contraseña WiFi

AsyncUDP udp;

const int DOUT = 21;
const int CLK = 22;
HX711 balanza;
#define PIR_PIN 36
#define BOYA_PIN 35

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando...");

    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nConectado a WiFi con IP: ");
    Serial.println(WiFi.localIP());

    if (udp.listen(1234)) {
        Serial.println("UDP Listening on IP: " + String(WiFi.localIP()));
    }

    balanza.begin(DOUT, CLK);
    balanza.set_scale(231113.75); // Ajustar la escala
    balanza.tare(20); // Tarear la báscula
    Serial.println("Báscula tareada");

    pinMode(PIR_PIN, INPUT);
    pinMode(BOYA_PIN, INPUT);
}

void loop() {
    // Lectura de los sensores
    int pirState = digitalRead(PIR_PIN);
    int boyaState = digitalRead(BOYA_PIN);
    float peso = balanza.get_units(20);

    // Preparar el mensaje para enviar
    String mensaje = String("Peso: ") + String(peso, 3) + " kg, Proximidad: " + String(pirState) + ", Boya: " + String(boyaState);

    // Enviar el mensaje
    udp.broadcastTo(mensaje.c_str(), 1234);

    Serial.println(mensaje); // Para depuración

    delay(200); // Ajustar el tiempo según sea necesario
}
