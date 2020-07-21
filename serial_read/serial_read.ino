#include "Separador.h"
#include "EEPROM.h"

Separador s;

// define the number of bytes you want to access
#define EEPROM_SIZE 3

// Declarate the position of the motors
int positions [EEPROM_SIZE]= {};   

void setup() {

  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  EEPROM.begin(EEPROM_SIZE);
  positions[0] = byte(EEPROM.read(0));
  Serial.println(positions[0]);
  
  Serial.println("Please enter the valve and angle of motion separated by a comma");
   
}

void loop() {

if (Serial.available()){

  String get_data = Serial.readString();
  String valve = s.separa(get_data,',',0);
  String angle = s.separa(get_data,',',1);
  Serial.println("The valve is: "+ valve);
  Serial.println("The porcent is: "+ angle);
  
  int valve1  = valve.toInt();
  int angle1  = angle.toInt();
  
  // Save in the EEPROM the last position
    EEPROM.write(valve1, angle1);
    EEPROM.commit();
    Serial.println("level saved in flash memory");
    Serial.println(valve1);
    Serial.println(angle1);
  delay(500);
  Serial.println("Please enter the valve and angle of motion separated by a comma");

      }
  
}
