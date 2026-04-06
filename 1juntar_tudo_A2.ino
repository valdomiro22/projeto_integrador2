#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

unsigned long tempoAnterior = 0;
char modoAtual = ' ';  // para saber o último modo recebido
char valorRecebido = '1';

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // Lê a serial sem travar o resto
  if (Serial.available() >= 2) {
    char c = Serial.read();
    if (c == 'A' || c == 'M') {
      modoAtual = c;
      valorRecebido = Serial.read(); // Lê o número da válvula
      atualizarDisplayModo();
    }
  }
}

void atualizarDisplayModo() {
  lcd.clear();
  if (modoAtual == 'A') {
    mensagensModoAutomatico();
  } else if (modoAtual == 'M') {
    mensagensModoManual();
  }
}

void mensagensModoManual() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Man | Valvula: ");
  lcd.print(valorRecebido);
  
  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print("120");
}

void mensagensModoAutomatico() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto | Ciclo: ");
  lcd.print("14");
  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print("120");
}