/*
  Modbus-Arduino Example - TempSensor (Modbus Serial)
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/
 
#include <Modbus.h>
#include <ModbusSerial.h>


//Modbus Registers Offsets (0-9999)
const int SENSOR_IREG_0 = 100;
const int SENSOR_IREG_1 = 101;
//Used Pins
const int sensorPin_0 = A0;
const int sensorPin_1 = A1;
// ModbusSerial object
ModbusSerial mb;

long ts;

void setup() {
    // Config Modbus Serial (port, speed, byte format) 
    mb.config(&Serial, 38400, SERIAL_8N1);
    // Set the Slave ID (1-247)
    mb.setSlaveId(1);  

    // Add SENSOR_IREG register - Use addIreg() for analog Inputs
    mb.addIreg(SENSOR_IREG_0);
    mb.addIreg(SENSOR_IREG_1);

    ts = millis();
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();
   
   //Read each two seconds
   if (millis() > ts + 2000) {   
       ts = millis();
       //Setting raw value (0-1024)
       mb.Ireg(SENSOR_IREG_0, analogRead(sensorPin_0));
       mb.Ireg(SENSOR_IREG_1, analogRead(sensorPin_1));
   } 
}
