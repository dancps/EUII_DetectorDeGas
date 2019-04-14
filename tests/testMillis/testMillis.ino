#define MQ_analog A2
#define MQ_dig 7
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int valor_analog;
int valor_dig;

/*
 * SDA = A4
 * SCL = A5
 *
 *
 *
 */


LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

/*const int azul = 9;
const int verde = 10;
const int vermelho = 11;

//Funções responsáveis por executar o brilho selecionado
/*void vermelhoFuncao(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}
void azulFuncao(){
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}
void verdeFuncao(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, LOW);
}
void amareloFuncao(){
  analogWrite(azul, 0);
  analogWrite(verde, 50);
  analogWrite(vermelho, 255);
}
void roxoFuncao(){
  analogWrite(azul, 207);
  analogWrite(verde, 0);
  analogWrite(vermelho, 255);
}
void brancoFuncao(){
  digitalWrite(azul, HIGH);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, HIGH);
}*/

const int amarelo = 9;
const int verde = 10;
const int vermelho = 11;

void vermelhoFuncao(){
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
}
void amareloFuncao(){
  digitalWrite(amarelo, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}
void verdeFuncao(){
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, LOW);
}
unsigned long initTime = 0,actTime;
void setup() {
    pinMode(amarelo,OUTPUT);
    pinMode(verde,OUTPUT);
    pinMode(vermelho,OUTPUT);
    lcd.begin (16,2); // ou 20,4 se for o display 20x4
    //lcd.backlight();            // Ligando o BackLight do LCD
    initTime = millis();
}

void loop() {
    valor_analog = analogRead(MQ_analog); 
    valor_dig = digitalRead(MQ_dig);

    actTime = millis();
    lcd.setCursor(6,1);
    lcd.print((actTime-initTime)/1000);

    //Serial.print(valor_analog);
    //Serial.print(" || ");
    if(((actTime-initTime)/1000)<=(20)) amareloFuncao();
    else{
      if(valor_dig == 0){
          lcd.setCursor(0,0);
          lcd.print("Gas detectado");
          lcd.setCursor(0,1);
          lcd.print(valor_analog);
          vermelhoFuncao();
      }
      else{
          //Serial.println("");
          lcd.setCursor(0,0);
          lcd.print("Gas ausente");
          lcd.setCursor(0,1);
          lcd.print(valor_analog);
          verdeFuncao();
      } 
    }
    
    if((actTime-initTime)%1000==0) lcd.clear();

}
/*
 * https://www.fernandok.com/2017/12/arduino-e-esp8266-com-display-i2c-lcd.html
 * https://portal.vidadesilicio.com.br/sensor-de-gas-mq-135/
 * 
 * MQ-135:
 * https://img.filipeflop.com/files/download/Sensor_de_gas_MQ-135.pdf
 * 
 */
