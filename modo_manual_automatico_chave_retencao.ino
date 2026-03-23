#define modoOperacao 4
#define led 7

void setup() {
  pinMode(modoOperacao, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  modoManual();
}

void modoManual() {
  if (digitalRead(modoOperacao) == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}