#define led1 4
#define led2 5
#define led3 6
#define led4 7
#define led5 8
#define led6 9
#define led7 10
#define led8 11

#define ledVermelho 12
#define ledAmarelo 13

#define chaveManualAutomatico 3

#define select A0
#define test A1
#define reset A2

int valvulaSelecionada = 1;
int delayLedsVerdes = 200;
int estadoAnteriorChave = -1; // Começa em -1 para forçar a primeira atualização na tela

void setup() {
  Serial.begin(9600);

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
  pinMode(chaveManualAutomatico, INPUT);
  
  // Botões
  pinMode(select, INPUT); 
  pinMode(test, INPUT);
  pinMode(reset, INPUT);

  pinMode(ledAmarelo, OUTPUT);
}

void loop() {
  int estadoAtual = digitalRead(chaveManualAutomatico);

  if (estadoAtual != estadoAnteriorChave) {
    estadoAnteriorChave = estadoAtual;
    enviarDados();
  } 
    
  if (estadoAtual == HIGH) {
    modoAutomatico();
  } else {
    modoManual();
  }
  
}

void enviarDados() {
  char modo = (digitalRead(chaveManualAutomatico) == HIGH) ? 'A' : 'M';
  
  Serial.print(modo);              // Envia 'A' ou 'M'
  Serial.print(valvulaSelecionada); // Envia o número (1 a 9)
  Serial.print('\n');               // Caractere terminador para facilitar a leitura
}

void selecionarModoOperacao() {
  // Lê o estado atual da chave
  int estadoAtualChave = digitalRead(chaveManualAutomatico);

  // Só atualiza o display e o LED SE o estado da chave mudou
  if (estadoAtualChave != estadoAnteriorChave) {
    if (estadoAtualChave == HIGH) {
      modoAutomatico();
    } else {
      modoManual();
    }
    
    // Atualiza a memória com o estado atual
    estadoAnteriorChave = estadoAtualChave;
  }
}

void modoAutomatico() {
  acionarTodosLedsVerdes(); 
}

void modoManual() {
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

    enviarDados();
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
  delay(delayLedsVerdes);
  digitalWrite(led1, LOW);
}

/** Função para acionar o led 2. */
void acionarLed2() {
  digitalWrite(led2, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led2, LOW);
}

/** Função para acionar o led 3. */   
void acionarLed3() {
  digitalWrite(led3, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led3, LOW);
}

/** Função para acionar o led 4. */
void acionarLed4() {
  digitalWrite(led4, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led4, LOW);
}

/** Função para acionar o led 5. */
void acionarLed5() {
  digitalWrite(led5, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led5, LOW);
}

/** Função para acionar o led 6. */
void acionarLed6() {
  digitalWrite(led6, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led6, LOW);
}

/** Função para acionar o led 7. */
void acionarLed7() {
  digitalWrite(led7, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led7, LOW);
}

/** Função para acionar o led 8. */
void acionarLed8() {
  digitalWrite(led8, HIGH);
  delay(delayLedsVerdes);
  digitalWrite(led8, LOW);
}

/** Função para testar se os leds vermelho e amarelo estão funcionando. */
void testeLedVermelhoEAmarelo() {
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  delay(delayLedsVerdes);
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
  digitalWrite(ledAmarelo, HIGH);
  
  delay(delayLedsVerdes);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(ledAmarelo, LOW);
}
