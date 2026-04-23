#include <EEPROM.h>
#include <LiquidCrystal.h>

// LCD (mantido como no Arduino 2)
LiquidCrystal lcd(48, 46, 44, 42, 40, 38);

// Pinos do antigo Arduino 1
#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define led6 7
#define led7 8
#define led8 9
#define ledVermelho 32
#define ledAmarelo 33
#define chaveManualAutomatico 36 
#define select 10
#define test 11
#define reset 12

// Pinos do antigo Arduino 2
#define buzzer 14
#define potenciometro A0

// Variáveis do Arduino 1
bool modoAutomaticoAtivo = false;
int valvulaSelecionada = 1;
int tempoLedLigado = 2000;
int tempoEntreLeds = 5000;
int tempoDoRA = (5+1+3+4+4+9+4) * 1000;  // 30 segundos
int qtCiclos = 0;
int enderecoCiclos = 0;
int ultimoEstadoBotao = HIGH;

int etapaAutomatica = 1;
unsigned long tempoReferenciaAutomatico = 0;
bool ledLigadoAutomatico = false;
bool aguardandoProximoLed = false;
bool aguardandoNovoCiclo = false;

// Variáveis do Arduino 2
unsigned long tempoAnterior = 0;
char modoAtual = 'M';
char valorRecebido = '1';
int pressaoAnterior = -1;
int pressaoAtual = 0;
int ciclosAtual = 0;

void setup() {
  Serial.begin(9600);

  // Leds
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);

  // Botão do modo com pullup
  pinMode(chaveManualAutomatico, INPUT_PULLUP);

  // Botões
  pinMode(select, INPUT);
  pinMode(test, INPUT);
  pinMode(reset, INPUT);

  pinMode(potenciometro, INPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  EEPROM.get(enderecoCiclos, qtCiclos);
  ciclosAtual = qtCiclos;

  mensagensDeInicializacao();
  enviarDados();
}

void loop() {
  processarComandosPressao();
  verificarBotaoModo();
  verificarBotaoReset();

  if (modoAutomaticoAtivo) {
    modoAutomatico();
  } else {
    modoManual();
  }
}

// Pressão local
void processarComandosPressao() {
  int valorLido = analogRead(potenciometro);
  pressaoAtual = map(valorLido, 0, 1023, 0, 100);

  if (pressaoAtual >= 80) {
    digitalWrite(ledVermelho, HIGH);
  } else {
    digitalWrite(ledVermelho, LOW);
  }

  if (pressaoAtual != pressaoAnterior) {
    pressaoAnterior = pressaoAtual;
    atualizarDisplayModo();
  }
}

void verificarBotaoModo() {
  int estadoAtualBotao = digitalRead(chaveManualAutomatico);

  if (estadoAtualBotao == LOW && ultimoEstadoBotao == HIGH) {
    delay(30);
    if (digitalRead(chaveManualAutomatico) == LOW) {
      modoAutomaticoAtivo = !modoAutomaticoAtivo;

      if (modoAutomaticoAtivo) {
        etapaAutomatica = 1;
        ledLigadoAutomatico = false;
        aguardandoProximoLed = false;
        aguardandoNovoCiclo = false;
        digitalWrite(ledAmarelo, HIGH);
      } else {
        digitalWrite(ledAmarelo, LOW);
      }

      enviarDados();
    }
  }

  ultimoEstadoBotao = estadoAtualBotao;
}

// Agora usa a variável do modo, não o pino do botão
void enviarDados() {
  int quantidadeCiclosSalva;
  EEPROM.get(enderecoCiclos, quantidadeCiclosSalva);

  modoAtual = modoAutomaticoAtivo ? 'A' : 'M';
  valorRecebido = char('0' + valvulaSelecionada);
  ciclosAtual = quantidadeCiclosSalva;

  atualizarDisplayModo();
}

// Não lê mais o botão para decidir o modo
// só sincroniza display/estado
void selecionarModoOperacao() {
  modoAtual = modoAutomaticoAtivo ? 'A' : 'M';
  atualizarDisplayModo();
}

void modoAutomatico() {
  digitalWrite(ledAmarelo, HIGH);
  executarSequenciaAutomatica();
}

void modoManual() {
  digitalWrite(ledAmarelo, LOW);
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
    delay(200);
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
    delay(200);
  }
}

/** Função para acionar o led 1. */
void acionarLed1() {
  digitalWrite(led1, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led1, LOW);
}

/** Função para acionar o led 2. */
void acionarLed2() {
  digitalWrite(led2, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led2, LOW);
}

/** Função para acionar o led 3. */   
void acionarLed3() {
  digitalWrite(led3, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led3, LOW);
}

/** Função para acionar o led 4. */
void acionarLed4() {
  digitalWrite(led4, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led4, LOW);
}

/** Função para acionar o led 5. */
void acionarLed5() {
  digitalWrite(led5, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led5, LOW);
}

/** Função para acionar o led 6. */
void acionarLed6() {
  digitalWrite(led6, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led6, LOW);
}

/** Função para acionar o led 7. */
void acionarLed7() {
  digitalWrite(led7, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led7, LOW);
}

/** Função para acionar o led 8. */
void acionarLed8() {
  digitalWrite(led8, HIGH);
  delay(tempoLedLigado);
  digitalWrite(led8, LOW);
}

/** Função para testar se os leds vermelho e amarelo estão funcionando. */
void testeLedVermelhoEAmarelo() {
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  delay(tempoLedLigado);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
}

void executarSequenciaAutomatica() {
  unsigned long agora = millis();

  if (!modoAutomaticoAtivo) {
    digitalWrite(ledAmarelo, LOW);
    return;
  }

  // AQUI está o tempo do RA
  if (aguardandoNovoCiclo) {
    if (agora - tempoReferenciaAutomatico >= tempoDoRA) {
      aguardandoNovoCiclo = false;
      etapaAutomatica = 1;
    }
    return;
  }

  if (aguardandoProximoLed) {
    if (agora - tempoReferenciaAutomatico >= tempoEntreLeds) {
      aguardandoProximoLed = false;
    }
    return;
  }

  if (!ledLigadoAutomatico) {
    switch (etapaAutomatica) {
      case 1: digitalWrite(led1, HIGH); break;
      case 2: digitalWrite(led2, HIGH); break;
      case 3: digitalWrite(led3, HIGH); break;
      case 4: digitalWrite(led4, HIGH); break;
      case 5: digitalWrite(led5, HIGH); break;
      case 6: digitalWrite(led6, HIGH); break;
      case 7: digitalWrite(led7, HIGH); break;
      case 8: digitalWrite(led8, HIGH); break;
    }

    ledLigadoAutomatico = true;
    tempoReferenciaAutomatico = agora;
    return;
  }

  if (ledLigadoAutomatico && (agora - tempoReferenciaAutomatico >= tempoLedLigado)) {
    switch (etapaAutomatica) {
      case 1: digitalWrite(led1, LOW); break;
      case 2: digitalWrite(led2, LOW); break;
      case 3: digitalWrite(led3, LOW); break;
      case 4: digitalWrite(led4, LOW); break;
      case 5: digitalWrite(led5, LOW); break;
      case 6: digitalWrite(led6, LOW); break;
      case 7: digitalWrite(led7, LOW); break;
      case 8: digitalWrite(led8, LOW); break;
    }

    ledLigadoAutomatico = false;

    if (etapaAutomatica < 8) {
      etapaAutomatica++;
      aguardandoProximoLed = true;
      tempoReferenciaAutomatico = agora;
    } else {
      qtCiclos++;
      EEPROM.put(enderecoCiclos, qtCiclos);
      enviarDados();

      aguardandoNovoCiclo = true;
      tempoReferenciaAutomatico = agora; // começa a contar o tempo do RA aqui
    }
  }
}



// BLOCO DO LCD / BUZZER

void bipeInicial() {
  tone(buzzer, 1319, 2000);
  delay(1000);
}

void bipeFinalInicializacao() {
  tone(buzzer, 988, 120);
  delay(200);

  tone(buzzer, 988, 120);
  delay(200);
}

void atualizarDisplayModo() {
  if (modoAtual == 'A') {
    mensagensModoAutomatico();
  } else {
    mensagensModoManual();
  }
}

void resetarContagemCiclos() {
  qtCiclos = 0;
  ciclosAtual = 0;
  EEPROM.put(enderecoCiclos, qtCiclos);
  enviarDados();
}

void mensagensModoManual() {
  lcd.setCursor(0, 0);
  lcd.print("Man | Valv: ");
  lcd.print(valvulaSelecionada);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Press: ");
  lcd.print(pressaoAtual);
  lcd.print(" %");
  lcd.print("   ");
}

void mensagensModoAutomatico() {
  lcd.setCursor(0, 0);
  lcd.print("Auto | Ciclo: ");
  lcd.print(ciclosAtual);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print(pressaoAtual);
  lcd.print(" %");
  lcd.print("   ");
}

void mensagensDeInicializacao() {
  bipeInicial();
  delay(2000);
  mensagemUniversidadeDiciplina();
  delay(3000);
  nomeRA();
  delay(3000);
  nomeEBoasVindas();
  delay(3000);
  bipeFinalInicializacao();
  lcd.clear();
  delay(100);
}

void nomeRA() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nome: Valdomiro");
  lcd.setCursor(0, 1);
  lcd.print("RA: 5134494");
}

void mensagemUniversidadeDiciplina() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" UNIUBE");

  String textoLinha2 = "Projetos Integradores 2 ";
  for (int posicaoNaString = 0; posicaoNaString <= textoLinha2.length() - 16; posicaoNaString++) {
    lcd.setCursor(0, 1);
    lcd.print(textoLinha2.substring(posicaoNaString, posicaoNaString + 16));
    delay(300);
  }
}

void nomeEBoasVindas() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Bem Vindo!");

  String textoLinha1 = "Sequenciador eletronico para Limpeza de Filtro de Manga ";
  for (int posicaoNaString = 0; posicaoNaString <= textoLinha1.length() - 16; posicaoNaString++) {
    lcd.setCursor(0, 0);
    lcd.print(textoLinha1.substring(posicaoNaString, posicaoNaString + 16));
    delay(300);
  }
}

void verificarBotaoReset() {
  if (modoAutomaticoAtivo && digitalRead(reset) == HIGH) {
    qtCiclos = 0;
    ciclosAtual = 0;
    EEPROM.put(enderecoCiclos, qtCiclos);
    enviarDados();
    delay(200);
  }
}