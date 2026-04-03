#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

unsigned long tempoAnterior = 0;
char modoAtual = ' ';  // para saber o último modo recebido

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // Lê a serial sem travar o resto
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'A' || c == 'a') {
      modoAtual = c;
      atualizarDisplayModo();
    }
  }
}

void atualizarDisplayModo() {
  lcd.clear();
  if (modoAtual == 'A') {
    mensagensModoAutomatico();
  } else if (modoAtual == 'a') {
    mensagensModoManual();
  }
}

void mensagensModoManual() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Man | Valvula:3");
  lcd.setCursor(0, 1);
  lcd.print("Pressao: 120");
}

void mensagensModoAutomatico() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto | Ciclo: 5");
  lcd.setCursor(0, 1);
  lcd.print("Pressao: 120");
}