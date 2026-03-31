#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define potenciometro A0
#define chaveManualAutomatico 7 
#define ledModoManualAutomatico 13

int estadoAnteriorChave = -1; 
int qtCiclos = 0; 
int enderecoCiclos = 0; 
int pressaoAnterior = -1;

void setup() {
  pinMode(chaveManualAutomatico, INPUT);
  pinMode(ledModoManualAutomatico, OUTPUT);
  pinMode(potenciometro, INPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();

  // RECUPERA o valor de ciclos da EEPROM ao ligar
  EEPROM.get(enderecoCiclos, qtCiclos);
  // Se o valor for inválido (nunca gravado), inicia em 0
  if (qtCiclos < 0) qtCiclos = 0; 
}

void loop() {
  // Chamando as duas funções essenciais
  selecionarModoOperacao();
  mapeamentoPotenciometro();
}

void mapeamentoPotenciometro() {
  int valorLido = analogRead(potenciometro);
  int pressao = map(valorLido, 0, 1023, 0, 100);

  // Atualiza apenas se o valor mudar ou se a chave mudar
  if (pressao != pressaoAnterior) {
    pressaoAnterior = pressao;
    atualizarDisplay(pressao);
  }
}

void selecionarModoOperacao() {
  int estadoAtualChave = digitalRead(chaveManualAutomatico);

  if (estadoAtualChave != estadoAnteriorChave) {
    if (estadoAtualChave == HIGH) {
      digitalWrite(ledModoManualAutomatico, HIGH);
    } else {
      digitalWrite(ledModoManualAutomatico, LOW);
    }
    
    // Incrementa ciclo e salva
    qtCiclos++; 
    EEPROM.put(enderecoCiclos, qtCiclos); 
    
    estadoAnteriorChave = estadoAtualChave;
    
    // Força atualização do display quando muda o modo ou ciclo
    int valorLido = analogRead(potenciometro);
    atualizarDisplay(map(valorLido, 0, 1023, 0, 100));
  }
}

// Unifiquei as funções de mensagem para evitar repetição de código
void atualizarDisplay(int pressao) {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (digitalRead(chaveManualAutomatico) == HIGH) {
    lcd.print("Man | Ciclo: ");
  } else {
    lcd.print("Auto | Ciclo: ");
  }
  lcd.print(qtCiclos);

  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print(pressao);
  lcd.print(" PSI");
  
  Serial.println(pressao);
}