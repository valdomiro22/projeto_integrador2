#include <LiquidCrystal.h>

// Define os pinos do LCD 16x2 (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define chaveManualAutomatico 7 
#define ledModoManualAutomatico 13

// Variáveis para gerenciar o estado e evitar que o LCD pisque
int estadoAnteriorChave = -1; // Começa em -1 para forçar a primeira atualização na tela

void setup() {
  pinMode(chaveManualAutomatico, INPUT);
  pinMode(ledModoManualAutomatico, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  selecionarModoOperacao();
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

void selecionarModoOperacao() {
  // Lê o estado atual da chave
  int estadoAtualChave = digitalRead(chaveManualAutomatico);

  // Só atualiza o display e o LED SE o estado da chave mudou
  if (estadoAtualChave != estadoAnteriorChave) {
    
    if (estadoAtualChave == HIGH) {
      mensagensModoAutomatico();
      digitalWrite(ledModoManualAutomatico, HIGH);
    } else {
      mensagensModoManual();
      digitalWrite(ledModoManualAutomatico, LOW);
    }
    
    // Atualiza a memória com o estado atual
    estadoAnteriorChave = estadoAtualChave;
  }
}