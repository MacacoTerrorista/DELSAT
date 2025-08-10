#include "arduino_secrets.h"

#include <HardwareSerial.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(2); // RX = GPIO16, TX = GPIO17 (TX nÃ£o precisa ligar se sÃ³ ler)

#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17(pinagem na esp32)
  pinMode(LED_PIN, OUTPUT);

  Serial.println("ð Iniciando leitura do GPS NEO-6M...");
  Serial.println("---------------------------------------");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    // Pisca LED rÃ¡pido
    digitalWrite(LED_PIN, HIGH);
    delay(50); // 50 ms aceso
    digitalWrite(LED_PIN, LOW);

    // Exibe dados formatados de forma mais ''legivel'' e divertida
    Serial.println("ð¡ NOVOS DADOS GPS ð¡");
    Serial.print("ð Latitude:  ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("ð Longitude: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("ðºï¸ PrecisÃ£o:  ");
    Serial.print(gps.hdop.hdop(), 2);
    Serial.println(" m");

    Serial.print("ð Altitude:  ");
    Serial.print(gps.altitude.meters(), 2);
    Serial.println(" m");

    Serial.print("ð°ï¸ SatÃ©lites: ");
    Serial.println(gps.satellites.value());

    Serial.print("â° HorÃ¡rio (UTC): ");
    if (gps.time.isValid()) {
      Serial.printf("%02d:%02d:%02d\n",
                    gps.time.hour(),
                    gps.time.minute(),
                    gps.time.second());
    } else {
      Serial.println("IndisponÃ­vel");
    }

    Serial.println("---------------------------------------");
  }
}
