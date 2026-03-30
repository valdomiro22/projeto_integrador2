#define botao 4

void setup() {
  pinMode(botao, INPUT);
  Serial.begin(9600);
}

void loop() {
  definirSeinal();
}

void definirSeinal() {
  if (digitalRead(botao) == HIGH) {
    Serial.write("A");
  } else {
    Serial.write("a");
  }
}
