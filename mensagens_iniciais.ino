#include <LiquidCrystal.h>

// Define os pinos do LCD 16x2 (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Inicializando...");
  delay(500);
}

void loop() {
  mensagemUniversidadeDiciplina();
  delay(3000);
  nomeRA();
  delay(3000);
  nomeEBoasVindas();
  delay(3000);
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
