#define buzzer 13

void setup() {
  pinMode(buzzer, OUTPUT);
  bipeInicial();
  delay(200);  // Menagens de inicialização
  bipeFinalInicializacao();
}

void loop() {
}

void bipeInicial() {
  
  tone(buzzer, 1319, 300); 
  delay(2000);
}

void bipeFinalInicializacao() {
  tone(buzzer, 988, 80); 
  delay(150);
  
  // tone(buzzer, 1319, 300); 
  tone(buzzer, 988, 80); 
  delay(150);
}