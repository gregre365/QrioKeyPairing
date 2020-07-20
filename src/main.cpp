#include <Arduino.h>
#include <M5Stack.h>
#include <M5StackUpdater.h>

#define QRIO_LOCK_BTN 15
#define QRIO_OPEN_BTN 5 

void setup() {
  M5.begin();
  if (digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  pinMode(QRIO_LOCK_BTN, INPUT);    // QrioのLockボタンをHi-Zにする
  digitalWrite(QRIO_LOCK_BTN, LOW);
  pinMode(QRIO_OPEN_BTN, INPUT);    // QrioのOpenボタンをHi-Zにする
  digitalWrite(QRIO_OPEN_BTN, LOW);

  M5.Lcd.setTextSize(2);
  M5.Lcd.println("BTN A : QRIO Pairing");
  M5.Lcd.println("BTN B : Lock");
  M5.Lcd.println("BTN C : Open");
}

void enter_pairring_mode()
{
  pinMode(QRIO_LOCK_BTN, OUTPUT);   // QrioのLockボタンをLにする
  delay(6000);
  pinMode(QRIO_LOCK_BTN, INPUT);    // QrioのLockボタンをHi-Zにする
}

void qrio_press_button(uint8_t button)
{
  pinMode(button, OUTPUT);          // QrioのLockボタンをLにする
  delay(100);
  pinMode(button, INPUT);           // QrioのLockボタンをHi-Zにする
}

void loop() {
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.println("Enter Pairing mode");
    enter_pairring_mode();
  }
  if (M5.BtnB.wasPressed()) {
    M5.Lcd.println("Lock");
    qrio_press_button(QRIO_LOCK_BTN);
  }
  if (M5.BtnC.wasPressed()) {
    M5.Lcd.println("Open");
    qrio_press_button(QRIO_OPEN_BTN);
  }
  M5.update();
}
