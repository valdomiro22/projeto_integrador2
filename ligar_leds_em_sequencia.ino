#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define led6 7
#define led8 8
#define led9 9

int valorLido;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
}

void loop() {
  acenterLeds();
}

void acenterLeds() {
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led2, HIGH);
  delay(500);
  digitalWrite(led3, HIGH);
  delay(500);
  digitalWrite(led4, HIGH);
  delay(500);
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led6, HIGH);
  delay(500);
  digitalWrite(led8, HIGH);
  delay(500);
  digitalWrite(led9, HIGH);
  delay(500);
} 