#include "arduino_secrets.h"

#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL no ESP32

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  if (mpu.begin() != 0) {
    Serial.println("â Erro ao inicializar MPU6050");
    while (1);
  }

  mpu.calcOffsets(); // CalibraÃ§Ã£o
  Serial.println("\nâ MPU6050 inicializado e calibrado!\n");
}

void loop() {
  mpu.update();
  digitalWrite(ledPin, HIGH);

  Serial.println("========== ð Leitura MPU6050 ==========");

  // AceleraÃ§Ã£o (convertida para m/sÂ²)
  Serial.printf("ð AceleraÃ§Ã£o (m/sÂ²)\n");
  Serial.printf("  X: %.2f\tY: %.2f\tZ: %.2f\n",
                mpu.getAccX() * 9.81,
                mpu.getAccY() * 9.81,
                mpu.getAccZ() * 9.81);

  // GiroscÃ³pio (Â°/s)
  Serial.printf("ð¯ GiroscÃ³pio (Â°/s)\n");
  Serial.printf("  X: %.2f\tY: %.2f\tZ: %.2f\n",
                mpu.getGyroX(),
                mpu.getGyroY(),
                mpu.getGyroZ());

  // Ãngulos (Â°)
  Serial.printf("ð Ãngulos\n");
  Serial.printf("  Roll: %.2fÂ°\tPitch: %.2fÂ°\tYaw: %.2fÂ°\n",
                mpu.getAngleX(),
                mpu.getAngleY(),
                mpu.getAngleZ());

  Serial.println("========================================\n");

  digitalWrite(ledPin, LOW);
  delay(500);
}
