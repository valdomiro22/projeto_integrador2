#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define buzzer 8

unsigned long tempoAnterior = 0;
char modoAtual = 'M';        // Começa em Manual por padrão
char valorRecebido = '1';
int pressaoAnterior = -1;
int pressaoAtual = 0;
int ciclosAtual = 0;

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
  // 1. LER O POTENCIÔMETRO CONSTANTEMENTE
  int valorLido = analogRead(potenciometro);
  pressaoAtual = map(valorLido, 0, 1023, 0, 100);

  // 2. SE A PRESSÃO MUDOU, ATUALIZA O DISPLAY
  if (pressaoAtual != pressaoAnterior) {
    pressaoAnterior = pressaoAtual;
    atualizarDisplayModo();
    
    if (pressaoAtual >= 80) {
        Serial.println("l");
    } else {
        Serial.println("f");
    }
  }

  // 3. SE CHEGOU ALGO NA SERIAL, ATUALIZA O MODO E O DISPLAY
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
  
  //tone(buzzer, 1319, 300); 
  tone(buzzer, 988, 80); 
  delay(150);
}

// Essa função agora apenas decide QUAL layout desenhar
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
  lcd.print("   "); // Limpa o que sobrou do número anterior, caso seja menor que 3 dígitos
  
  lcd.setCursor(0, 1);
  lcd.print("Press: ");
  lcd.print(pressaoAtual);
  lcd.print("   "); // Limpa o que sobrou do número anterior, caso seja menor que 3 dígitos
}

void mensagensModoAutomatico() {
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto | Ciclo: ");
  lcd.print(ciclosAtual);        // ← agora mostra o valor real!
  lcd.print("   "); // Limpa o que sobrou do número anterior, caso seja menor que 3 dígitos
  
  lcd.setCursor(0, 1);
  lcd.print("Pressao: ");
  lcd.print(pressaoAtual);
  lcd.print("   "); // Limpa o que sobrou do número anterior, caso seja menor que 3 dígitos
}

void mensagensDeInicializacao() {
  bipeInicial();
  // mensagemUniversidadeDiciplina();
  // delay(300);
  nomeRA();
  delay(300);
  // nomeEBoasVindas();
  // delay(300);
  bipeFinalInicializacao();

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
