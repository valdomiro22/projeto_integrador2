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

int valvulaSelecionada = 1;
int tempoValvulaLigada = 200;

void setup() {
  // Leds
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);

  // Botões
  pinMode(select, INPUT); 
  pinMode(test, INPUT);
  pinMode(reset, INPUT);

}

void loop() {
  selecionarLed();
  acionarLed(); 
}

/** Função para selecionar o led a ser acionado. */
void selecionarLed() {
  if (digitalRead(select) == HIGH) {
    valvulaSelecionada++;
    if (valvulaSelecionada > 9) {
      valvulaSelecionada = 1;
    }
    delay(200);  // Tempo entre um clique e outro para evitar múltiplas seleções acidentais
  }
}

/** Função para acionar o led selecionado. */
void acionarLed() {
  if (digitalRead(test) == HIGH) {
    switch (valvulaSelecionada) {
      case 1:
        acionarLed1();
        break;
      case 2:
        acionarLed2();
        break;
      case 3:
        acionarLed3();
        break;
      case 4:
        acionarLed4();
        break;
      case 5:
        acionarLed5();
        break;
      case 6:
        acionarLed6();
        break;
      case 7:
        acionarLed7();
        break;
      case 8:
        acionarLed8();
        break;
      case 9:
        testeLedVermelhoEAmarelo();
        break;
    }
    delay(200);  // Deley entre cliques para evitar múltiplas ativações acidentais
  }

  if (digitalRead(reset) == HIGH) {
    acionarTodosLedsVerdes();
    valvulaSelecionada = 1; // Reseta a seleção para o primeiro led
    delay(200);  // Deley entre cliques para evitar múltiplas ativações acidentais
  }
}

/** Função para acionar o led 1. */
void acionarLed1() {
  digitalWrite(led1, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led1, LOW);
}

/** Função para acionar o led 2. */
void acionarLed2() {
  digitalWrite(led2, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led2, LOW);
}

/** Função para acionar o led 3. */   
void acionarLed3() {
  digitalWrite(led3, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led3, LOW);
}

/** Função para acionar o led 4. */
void acionarLed4() {
  digitalWrite(led4, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led4, LOW);
}

/** Função para acionar o led 5. */
void acionarLed5() {
  digitalWrite(led5, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led5, LOW);
}

/** Função para acionar o led 6. */
void acionarLed6() {
  digitalWrite(led6, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led6, LOW);
}

/** Função para acionar o led 7. */
void acionarLed7() {
  digitalWrite(led7, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led7, LOW);
}

/** Função para acionar o led 8. */
void acionarLed8() {
  digitalWrite(led8, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(led8, LOW);
}

/** Função para testar se os leds vermelho e amarelo estão funcionando. */
void testeLedVermelhoEAmarelo() {
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  delay(tempoValvulaLigada);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
}

///** Função para acionar todos os leds verdes ao mesmo tempo. */
void acionarTodosLedsVerdes() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led8, HIGH);

  delay(tempoValvulaLigada);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
}
