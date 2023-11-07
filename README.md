# Arduino-ESP8266-RS485-MODBUS-Anemometer
Here is a way to setup an anemometer that works with RS485 MODBUS communication protocol

The Anemometer will be a part of a bench of measures that will be added to the Wind Turbine MPPT Regulator. This bench of measures will work with a ESP8266, for its Wi-Fi availability.

For the moment, the objective is to find an easy way to implement RS485 on an Arduino Uno, them to adapt it to an ESP8266, the Wemos Lolin D1 mini for instance.

The code result seems very simple and cool, but I spent many and many hours to find a way to get something from this wind sensor.
So I think it will interest everyone that have to implement RS485.

Update the 7 november 2023:
---------------------------

After some tests, with IDE 1.8.16, SoftwareSerial is integrated in IDE. However this version of SoftSerial the code will not work anymore unless to change RX pin to 2 and TX pin to 3.
