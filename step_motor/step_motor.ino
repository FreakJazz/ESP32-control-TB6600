#include "EEPROM.h"

// define the number of bytes you want to access
#define EEPROM_SIZE 1

// Define stepper motor 1 connections
#define PUL1 3 //define Pulse pin
#define DIR1 4 //define Direction pin

// Declarate the position of the motors
int PUL;  //define Pulse pin
int DIR;  //define Direction pin
int a_valve;

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  // initialize EEPROM with predefined size
  Serial.println("Start...");
  EEPROM.begin(EEPROM_SIZE);

  a_valve = byte(EEPROM.read(0));
  Serial.print("Valve: ");
  Serial.println(a_valve); 

}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    String incomingByte = Serial.readString();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
    int n_valve  = incomingByte.toInt();
    a_valve = give_position(a_valve,n_valve);
    EEPROM.write(0, n_valve);
    EEPROM.commit();
    Serial.println("Level saved in memory, this is the actual position");
    // Show the positions of the valve
    Serial.print("You change the position of the valve");
    delay(500);
  }
}


// This function choose if the valve needs to open or close
int give_position(int posi_actual, int posi_final){
    delay(100);
    Serial.println("This is the position function");
    PUL = PUL1;
    DIR = DIR1;

    if (posi_actual >= posi_final){
        //send PUL DIR ENA Position
        posi_final = closing(DIR, PUL, posi_final, posi_actual);
        Serial.println("The valve is closed");
    }
    if (posi_actual <= posi_final){
        //send PUL DIR ENA Position
        posi_final = opening(DIR, PUL, posi_final, posi_actual);
        Serial.println("The valve is openned");
    }
    return posi_final;
}

// This is the open function
int opening(int DIR, int PUL, int posi_final, int posi_actual){
    Serial.println("The valve is openning");
    while (posi_actual < posi_final)
    {
        digitalWrite(DIR,LOW);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(500);
        digitalWrite(PUL,LOW);
        delayMicroseconds(500);
        posi_actual++;
    }
    return posi_actual;
}

// This is the close function
int closing(int DIR, int PUL, int posi_final, int posi_actual){
     Serial.println("The valve is closing");
     while (posi_actual > posi_final)
    {
        digitalWrite(DIR,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(500);
        digitalWrite(PUL,LOW);
        delayMicroseconds(500);
        posi_actual--;
    }
    return posi_actual;
}


