#include <WiFi.h>
#include "AsyncUDP.h"
#include <M5Stack.h>

const char *ssid = "Mari"; // Tu red WiFi
const char *password = "iloveme0807"; // Tu contraseña WiFi

AsyncUDP udp;

void setup() {
    M5.begin();
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        delay(1000);
    }

    if (udp.listen(1234)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            M5.Lcd.fillScreen(BLACK); // Limpiar la pantalla
            M5.Lcd.setCursor(0, 0);
            M5.Lcd.setTextColor(WHITE);
            M5.Lcd.print((char *)packet.data()); // Mostrar el mensaje en la pantalla
        });
    }
}

void loop() {
    // No se requiere código adicional aquí, ya que el manejo de paquetes se hace en el callback
}
