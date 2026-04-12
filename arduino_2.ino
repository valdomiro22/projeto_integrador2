#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define buzzer 8

unsigned long tempoAnterior = 0;
char modoAtual = 'M';        // Começa em Manual por padrão
char valorRecebido = '1';
int pressaoAnterior = -1;
int pressaoAtual = 0;
int ciclosAtual = 0;
int tempoDoRA = (5+1+3+4+4+9+4) * 1000; // 30 segundos

#define potenciometro A0

void setup() {
  pinMode(potenciometro, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  mensagensDeInicializacao();
  atualizarDisplayModo(); // Mostra o estado inicial
}
 
void loop() {
  // 1. ler o potenciômetro e atualizar a pressão atual
  int valorLido = analogRead(potenciometro);
  pressaoAtual = map(valorLido, 0, 1023, 0, 100);

  // 2.se a pressão mudou, atualiza o display
  if (pressaoAtual != pressaoAnterior) {
    pressaoAnterior = pressaoAtual;
    atualizarDisplayModo();

    // Envia "l" ou "f" apenas quando o estado realmente muda o modo de operação
    static bool estadoAnteriorAlta = false;   // lembra o estado anterior

    bool estadoAtualAlta = (pressaoAtual >= 80);

    if (estadoAtualAlta != estadoAnteriorAlta) {
        if (estadoAtualAlta) {
            Serial.println("l");     // Pressão subiu para alta
        } else {
            Serial.println("f");     // Pressão caiu para normal
        }
        estadoAnteriorAlta = estadoAtualAlta;
    }
}

  // 3. se chegou algo na serial, atualiza o modo e o display
  if (Serial.available() >= 3) {        // pelo menos "A1,0\n" ou maior
    char c = Serial.read();
    
    if (c == 'A' || c == 'M') {
      modoAtual = c;
      
      // Lê o número da válvula (pode ser 1 dígito ou mais no futuro)
      valorRecebido = Serial.read();   // ainda mantendo como char por enquanto
      
      // Lê a vírgula
      if (Serial.read() == ',') {
        // Lê os ciclos até o \n
        ciclosAtual = Serial.parseInt();   // lê o número inteiro
      }
      
      // Limpa o buffer até o \n (segurança)
      while (Serial.available() && Serial.read() != '\n');
      
      atualizarDisplayModo();
    }
  }
}

void bipeInicial() {
  tone(buzzer, 1319, 300); 
  delay(1000);
}

void bipeFinalInicializacao() {
  tone(buzzer, 988, 80); 
  delay(150);
  
  tone(buzzer, 988, 80); 
  delay(150);
}

// Decide qual mensagem mostrar no display com base no modo atual (A ou M)
void atualizarDisplayModo() {
  if (modoAtual == 'A') {
    mensagensModoAutomatico();
  } else {
    mensagensModoManual();
  }
}

void mensagensModoManual() {
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Man | Valv: ");
  lcd.print(valorRecebido);
  lcd.print("   "); // Limpa o que sobrou do número anterior, para 3 digitos
  
  lcd.setCursor(0, 1);
  lcd.print("Press: ");
  lcd.print(pressaoAtual);
  lcd.print("   "); // Limpa o que sobrou do número anterior, para 3 digitos
}

void mensagensModoAutomatico() {
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto | Ciclo: ");
  lcd.print(ciclosAtual);        // ← agora mostra o valor real!
  lcd.print("   "); // Limpa o que sobrou do número anterior, para 3 digitos
  
  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print(pressaoAtual);
  lcd.print("   "); // Limpa o que sobrou do número anterior, para 3 digitos
}

void mensagensDeInicializacao() {
  bipeInicial();
  mensagemUniversidadeDiciplina();
  delay(300);
  nomeRA();
  delay(1000);
  nomeEBoasVindas();
  delay(300);
  bipeFinalInicializacao();
  lcd.clear();

  Serial.println("on");
  delay(100);
}

void nomeRA() {
  lcd.clear();
  // lcd.setCursor(<Coluna>, <Linha>);
  
  // Linha 1
  lcd.setCursor(0, 0);
  lcd.print("Nome: Valdomiro");

  // Linha 2
  lcd.setCursor(0, 1);
  lcd.print("RA: 5134494");
}

void mensagemUniversidadeDiciplina() {
  lcd.clear();
  // lcd.setCursor(<Coluna>, <Linha>);

  // Linha 1
  lcd.setCursor(0, 0);
  lcd.print("     UNIUBE");

  // Linha 2
  String textoLinha2 = "Projetos Integradores 2 ";
  for (int posicaoNaString = 0; posicaoNaString <= textoLinha2.length() - 16; posicaoNaString++) {
    lcd.setCursor(0, 1);
    lcd.print(textoLinha2.substring(posicaoNaString, posicaoNaString + 16));
    delay(300);
  }
}

void nomeEBoasVindas() {
  lcd.clear();
  // lcd.setCursor(<Coluna>, <Linha>);

  // Linha 2
  lcd.setCursor(0, 1);
  lcd.print("   Bem Vindo!");
  
  // Linha 1
  String textoLinha1 = "Sequenciador eletronico para Limpeza de Filtro de Manga ";
  for (int posicaoNaString = 0; posicaoNaString <= textoLinha1.length() - 16; posicaoNaString++) {
    lcd.setCursor(0, 0);
    lcd.print(textoLinha1.substring(posicaoNaString, posicaoNaString + 16));
    delay(300);
  }
}
