/*
Anemometer with a RS485 wind sensor

from an idea of https://arduino.stackexchange.com/questions/62327/cannot-read-modbus-data-repetitively
https://www.cupidcontrols.com/2015/10/software-serial-modbus-master-over-rs485-transceiver/

_________________________________________________________________
|                                                               |
|       author : Philippe de Craene <dcphilippe@yahoo.fr        |
|       Any feedback is welcome                                 |
                                                                |
_________________________________________________________________

Materials :
• 1* Arduino Uno R3 - tested with IDE version 1.8.7 and 1.8.9
• 1* wind sensor - RS485 MODBUS protocol of communication
• 1* MAX485 DIP8

Versions chronology:
version 1 - 7 sept  2019   - first test 

*/

#include <SoftwareSerial.h>  // https://github.com/PaulStoffregen/SoftwareSerial

#define RX        10    //Serial Receive pin
#define TX        11    //Serial Transmit pin
#define RTS_pin    9    //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

SoftwareSerial RS485Serial(RX, TX);

void setup() {

  pinMode(RTS_pin, OUTPUT);  
  
  // Start the built-in serial port, for Serial Monitor
  Serial.begin(9600);
  Serial.println("Anemometer"); 

  // Start the Modbus serial Port, for anemometer
  RS485Serial.begin(9600);   
  delay(1000);
}

void loop() {

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte Anemometer_request[] = {0x01, 0x03, 0x00, 0x16, 0x00, 0x01, 0x65, 0xCE}; // inquiry frame
  RS485Serial.write(Anemometer_request, sizeof(Anemometer_request));
  RS485Serial.flush();
  
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte Anemometer_buf[8];
  RS485Serial.readBytes(Anemometer_buf, 8);
 
  Serial.print("wind speed : ");
  for( byte i=0; i<7; i++ ) {
  Serial.print(Anemometer_buf[i], HEX);
  Serial.print(" ");
  }
  Serial.print(" ==> ");
  Serial.print(Anemometer_buf[4]);
  Serial.print(" m/s");
  Serial.println();                  
  delay(100);

}
