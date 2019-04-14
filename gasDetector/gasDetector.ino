#define MQ_analog A2
#define MQ_dig 7
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

const int buzzer = 6;
const int amarelo = 9;
const int verde = 10;
const int vermelho = 11;

const int startupTime = 20; //180
const int prepareTime = 40; //86400


unsigned long initTime = 0,actTime;
void setup() {
    // Inicializa comunicacao serial
    Serial.begin(9600);
    // Define o modo dos pinos de LED
    pinMode(amarelo,OUTPUT);
    pinMode(verde,OUTPUT);
    pinMode(vermelho,OUTPUT);
    // Define o pino do Buzzer como Saida 
    pinMode(buzzer,OUTPUT);
    // Define o modo dos pinos do Sensor de gas
    pinMode(MQ_analog, INPUT);
    pinMode(MQ_dig, INPUT);
    // Inicializa o LCD
    lcd.begin (16,2); 
    lcd.backlight(); //liga a luz de fundo
    // Grava o inicio da contagem de tempo
    initTime = millis();
}

void loop() {
    valor_analog = analogRead(MQ_analog); 
    valor_dig = digitalRead(MQ_dig);

    actTime = millis();

    Serial.print(valor_analog);
    Serial.print(" || ");
    if(((actTime-initTime)/1000)<=(20)){
        digitalWrite(amarelo,LOW);
        digitalWrite(verde,HIGH);
        digitalWrite(vermelho,HIGH);

        lcd.setCursor(0,0);
        lcd.print("Ligando...");
        lcd.setCursor(1,1);
        lcd.print((actTime-initTime)/1000);
    }
    else{
        if(((actTime-initTime)/1000)<=prepareTime){
            digitalWrite(amarelo,LOW);
        }
        else{
            digitalWrite(amarelo,HIGH);
        }
        if(valor_dig == 0){
            lcd.setCursor(0,0);
            lcd.print("Gas detectado   ");
            lcd.setCursor(0,1);
            lcd.print(valor_analog);
            digitalWrite(vermelho,LOW);
            digitalWrite(verde,HIGH);
            tone(buzzer,110);

        }
        else{
            //Serial.println("");
            lcd.setCursor(0,0);
            lcd.print("Gas ausente     ");
            lcd.setCursor(0,1);
            lcd.print(valor_analog);
            digitalWrite(vermelho,HIGH);
            digitalWrite(verde,LOW);
            noTone(buzzer);
        } 
    
}    if((actTime-initTime)%1000==0) lcd.clear();

}
/*
 * https://www.fernandok.com/2017/12/arduino-e-esp8266-com-display-i2c-lcd.html
 * https://portal.vidadesilicio.com.br/sensor-de-gas-mq-135/
 * 
 * MQ-135:
 * https://img.filipeflop.com/files/download/Sensor_de_gas_MQ-135.pdf
 * 
 */
