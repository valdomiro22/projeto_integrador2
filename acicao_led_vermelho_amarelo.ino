#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define led6 7
#define led7 8
#define led8 9

#define ledVermelho 10
#define ledAmarelo 11

#define select A0
#define test A1
#define reset A2

int val;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(select, INPUT);
  pinMode(test, INPUT);
  pinMode(reset, INPUT);
}

void loop() {
  acionamentoDosLeds();
  logicaParaLedVermelhoAmarelo();
}

void acionamentoDosLeds() {
  acionamentoLed1();
  acenderLedAmarelo();
  delay(5000);
  acionamentoLed2();
  delay(5000);
  acionamentoLed3();
  delay(5000);
  acionamentoLed4();
  delay(5000);
  acionamentoLed5();
  delay(5000);
  acionamentoLed6();
  delay(5000);
  acionamentoLed7();
  delay(5000);
  acionamentoLed8();
  apagarLedAmarelo();
  delay(calcularTempoComRA());
}

void acionamentoLed1() {
  digitalWrite(led1, HIGH);
  delay(2000);
  digitalWrite(led1, LOW);
}

void acionamentoLed2() {
  digitalWrite(led2, HIGH);
  delay(2000);
  digitalWrite(led2, LOW);
}

void acionamentoLed3() {
  digitalWrite(led3, HIGH);
  delay(2000);
  digitalWrite(led3, LOW);
}

void acionamentoLed4() {
  digitalWrite(led4, HIGH);
  delay(2000);
  digitalWrite(led4, LOW);
}

void acionamentoLed5() {
  digitalWrite(led5, HIGH);
  delay(2000);
  digitalWrite(led5, LOW);
}

void acionamentoLed6() {
  digitalWrite(led6, HIGH);
  delay(2000);
  digitalWrite(led6, LOW);
}

void acionamentoLed7() {
  digitalWrite(led7, HIGH);
  delay(2000);
  digitalWrite(led7, LOW);
}

void acionamentoLed8() {
  digitalWrite(led8, HIGH);
  delay(2000);
  digitalWrite(led8, LOW);
}

void logicaParaLedVermelhoAmarelo() {
  if (digitalRead(select) == HIGH) {
    acenderLedVermelho();
  } 
  
  if (digitalRead(test) == HIGH) {
    acenderLedAmarelo();
  }
  
  if (digitalRead(reset) == HIGH) {
    apagarLedvermelho();
    apagarLedAmarelo();
  }
}

void acenderLedVermelho() {
  digitalWrite(ledVermelho, HIGH);
}

void acenderLedAmarelo() {
  digitalWrite(ledAmarelo, HIGH);
}

void apagarLedvermelho() {
  digitalWrite(ledVermelho, LOW);
}

void apagarLedAmarelo() {
  digitalWrite(ledAmarelo, LOW);
}

int calcularTempoComRA(){
  int somatorio = 5 + 1 + 3 + 4 + 4 + 9 + 4;  // 30 milissegundos
  int tempoEmSegundos = somatorio * 1000;  // Convertendo para segundos - 30 segundos
  return tempoEmSegundos;
}