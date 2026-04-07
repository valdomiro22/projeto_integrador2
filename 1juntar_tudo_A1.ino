#include <EEPROM.h>

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

bool modoAutomaticoAtivo = false;
int valvulaSelecionada = 1;
int delayLedsVerdes = 200;
int estadoAnteriorChave = -1; // Começa em -1 para forçar a primeira atualização na tela
int tempoDoRA = 1000; // Tempo que os leds ficam acesos no modo automático (pode ser ajustado conforme necessário)
int qtCiclos = 0; // Variável para contar os ciclos no modo automático
int enderecoCiclos = 0; // Endereço na EEPROM para armazenar a quantidade de ciclos

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

  bool inicializado = false;
  
  while (!inicializado) {
    if (Serial.available() > 0) {
      // Lê o que chegou até a quebra de linha (enviada pelo println)
      String comando = Serial.readStringUntil('\n');
      
      // Remove espaços vazios ou caracteres de retorno de carro (\r)
      comando.trim(); 
      
      if (comando == "on") {
        inicializado = true; // Quebra o laço e libera o Arduino 1
      }
    }
  }
}

void loop() {
  int estadoAtual = digitalRead(chaveManualAutomatico);

  if (estadoAtual != estadoAnteriorChave) {
    estadoAnteriorChave = estadoAtual;
    enviarDados();
  } 
    
  if (estadoAtual == HIGH) {
    modoAutomaticoAtivo = true;
    modoAutomatico();
  } else {
    modoAutomaticoAtivo = false;
    modoManual();
  }
  
}

void enviarDados() {
  int quantidadeCiclosSalva;
  EEPROM.get(enderecoCiclos, quantidadeCiclosSalva); 
  int qtCiclosRecuperada = quantidadeCiclosSalva; 

  char modo = (digitalRead(chaveManualAutomatico) == HIGH) ? 'A' : 'M';
  
  Serial.print(modo);              // Envia 'A' ou 'M'
  Serial.print(valvulaSelecionada); // Envia o número (1 a 9)
  Serial.print(',');                     // separador
  Serial.print(quantidadeCiclosSalva);   // quantidade de ciclos
  Serial.print('\n');               // Caractere terminador para facilitar a leitura
}

void selecionarModoOperacao() {
  // Lê o estado atual da chave
  int estadoAtualChave = digitalRead(chaveManualAutomatico);

  // Só atualiza o display e o LED SE o estado da chave mudou
  if (estadoAtualChave != estadoAnteriorChave) {
    if (estadoAtualChave == HIGH) {
      modoAutomaticoAtivo = true;
      modoAutomatico();
    } else {
      modoAutomaticoAtivo = false;
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
  digitalWrite(ledAmarelo, LOW); // Apaga o led amarelo para indicar que não está mais no modo automático
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
  while (modoAutomaticoAtivo){
    digitalWrite(ledAmarelo, HIGH);
    acionarLed1();
    if (!modoAutomaticoAtivo) break;

    acionarLed2();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    acionarLed3();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    acionarLed4();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    acionarLed5();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    acionarLed6();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    acionarLed7();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    acionarLed8();
    selecionarModoOperacao();
    if (!modoAutomaticoAtivo) break;

    qtCiclos++; // Incrementa o contador de ciclos no modo automático
    EEPROM.put(enderecoCiclos, qtCiclos); // Salva a quantidade de ciclos na EEPROM
    enviarDados(); // Envia os dados atualizados para o Arduino 2
    
    delay(tempoDoRA);
  }
}
