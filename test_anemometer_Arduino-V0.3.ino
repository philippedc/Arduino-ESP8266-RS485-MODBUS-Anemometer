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
version 0.1  - 7 sept  2019   - first test 
version 0.2  - 7 nov 2023     - change RX TX pin connection
version 0.3  - 7 nov 2023     - add high bit to wind speed measure

*/

#define RX         2     // Serial Receive pin
#define TX         3     // Serial Transmit pin
#define RTS        4     // RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#include <SoftwareSerial.h> 
SoftwareSerial RS485Serial(RX, TX);

const byte request[] = {0x01, 0x03, 0x00, 0x16, 0x00, 0x01, 0x65, 0xCE}; // inquiry frame

void setup() {

  pinMode(RTS, OUTPUT);  
  
  // Start the built-in serial port, for Serial Monitor
  Serial.begin(250000);
  Serial.println("Anemometer"); 

  // Start the Modbus serial Port, for anemometer
  RS485Serial.begin(9600);   
  delay(1000);
}

void loop() {
  
  byte response[7] = { 0, 0, 0, 0, 0, 0, 0};
  while( !((response[0] == 0x01)&&(response[1] == 0x03)&&(response[2] == 0x02))) {   // if received message has an error
    // MODBUS Tramsmit by sending a request to the anemometer
    digitalWrite(RTS, RS485Transmit);     // init Transmit
    RS485Serial.write(request, sizeof(request));
    RS485Serial.flush();
    // MODBUS Reception of the anemometer's answer
    digitalWrite(RTS, RS485Receive);     // init Receive
    RS485Serial.readBytes(response, sizeof(response));
    delay(100);
  }
  for( byte i=0; i<(sizeof(response)); i++ ) {
    Serial.print(response[i], HEX);
    Serial.print(" ");
  }
  float windSpeed = (float)((response[3] << 8) + response[4])/10.0;
  Serial.print("\t==> ");
  Serial.print(windSpeed);
  Serial.print(" m/s");
  Serial.println();                  
}
