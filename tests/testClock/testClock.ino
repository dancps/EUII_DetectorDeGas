#include <Wire.h> 



void setup() {
    Wire.begin() ;
    Serial.begin(9600) ;

    Wire.beginTransmission( 0x68 ) ;
    Wire.write( 0x00 ) ; // Endereço 00h.
}

void loop() {
    

}
/*
 * https://www.embarcados.com.br/modulo-tiny-rtc-i2c-parte-1/
 * https://www.embarcados.com.br/modulo-tiny-rtc-i2c-parte-2/
 * https://www.embarcados.com.br/modulo-tiny-rtc-i2c-parte-3/
 */