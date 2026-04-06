#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

unsigned long tempoAnterior = 0;
char modoAtual = 'M';        // Começa em Manual por padrão
char valorRecebido = '1';
int pressaoAnterior = -1;
int pressaoAtual = 0;

#define potenciometro A0

void setup() {
  pinMode(potenciometro, INPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  atualizarDisplayModo(); // Mostra o estado inicial
}

void loop() {
  // 1. LER O POTENCIÔMETRO CONSTANTEMENTE
  int valorLido = analogRead(potenciometro);
  pressaoAtual = map(valorLido, 0, 1023, 0, 100);

  // 2. SE A PRESSÃO MUDOU, ATUALIZA O DISPLAY
  if (pressaoAtual != pressaoAnterior) {
    pressaoAnterior = pressaoAtual;
    atualizarDisplayModo();
  }

  // 3. SE CHEGOU ALGO NA SERIAL, ATUALIZA O MODO E O DISPLAY
  if (Serial.available() >= 2) {
    char c = Serial.read();
    if (c == 'A' || c == 'M') {
      modoAtual = c;
      valorRecebido = Serial.read(); 
      atualizarDisplayModo();
    }
  }
}

// Essa função agora apenas decide QUAL layout desenhar
void atualizarDisplayModo() {
  if (modoAtual == 'A') {
    mensagensModoAutomatico();
  } else {
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
  lcd.print(pressaoAtual);
  lcd.print("   "); // Espaços extras para apagar números antigos (ex: mudar de 100 para 99)
}

void mensagensModoAutomatico() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto | Ciclo: ");
  lcd.print("14");
  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print(pressaoAtual);
  lcd.print("   "); // Limpa o rastro de dígitos
}