#define led 5

void setup() {
  pinMode(led, INPUT);
  Serial.begin(9600);
}

void loop() { 
  receberSinalEExecutar();
}

void receberSinalEExecutar() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'A') {
      digitalWrite(led, HIGH);
    } else if (c == 'a') {
      digitalWrite(led, LOW);
    }
  }
}
