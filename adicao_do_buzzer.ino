#define buzzer 13

void setup() {
  pinMode(buzzer, OUTPUT);
  acionarBuzzer();
}

void loop() {
}

void acionarBuzzer() {
  tone(buzzer, 988, 80); 
  delay(80);
  
  tone(buzzer, 1319, 300); 
  delay(300);
}