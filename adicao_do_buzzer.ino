#define buzzer 13

void setup() {
  pinMode(buzzer, OUTPUT);
  bipeInicial();
  delay(1000);  // Menagens de inicialização
  bipeFinalInicializacao();
}

void loop() {
}

void bipeInicial() {
  // tone(buzzer, 988, 80); 
  // delay(80);
  
  tone(buzzer, 1319, 300); 
  delay(2000);
}

void bipeFinalInicializacao() {
  tone(buzzer, 988, 80); 
  delay(80);
  
  tone(buzzer, 1319, 300); 
  delay(300);
}