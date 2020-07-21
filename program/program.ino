// libraries that we use
#include "EEPROM.h"
#include "Separador.h"

Separador s;
// define the number of bytes you want to access
#define EEPROM_SIZE 3

// Define stepper motor 1 connections
#define PUL1 34 //define Pulse pin
#define DIR1 39 //define Direction pin

// Define stepper motor 2 connections
#define PUL2 33 //define Pulse pin
#define DIR2 32 //define Direction pin

// Define stepper motor 3 connections
#define PUL3 27 //define Pulse pin
#define DIR3 26 //define Direction pin


// Declarate the position of the motors
int positions [EEPROM_SIZE]= {};   
int PUL;  //define Pulse pin
int DIR;  //define Direction pin
int incomingByte = 0; // for incoming serial data

void setup() {
  
    Serial.begin(115200);
    // initialize EEPROM with predefined size
    Serial.println("Start...");
    EEPROM.begin(EEPROM_SIZE);
      
    // configurate pins of the step motor 1 
    pinMode (PUL1, OUTPUT);
    pinMode (DIR1, OUTPUT);

    // configurate pins of the step motor 2
    pinMode (PUL2, OUTPUT);
    pinMode (DIR2, OUTPUT);

    // configurate pins of the step motor 3
    pinMode (PUL3, OUTPUT);
    pinMode (DIR3, OUTPUT);

    ///////////////// Configure valve 1 //////////////////
    //////////////////////////////////////////////////////
    positions[0] = byte(EEPROM.read(0));
    Serial.println(positions[0]); 
    //give position recive valve, position actual and position final
    positions[0] = give_position(0, positions[0], 10);
    //save_valve revice position EEPROM valve and value
    save_value(0, positions[0]);
    Serial.println(positions[0]); 

    ///////////////// Configure valve 2 //////////////////
    //////////////////////////////////////////////////////
    positions[1] = byte(EEPROM.read(1));
    Serial.println(positions[1]); 
    //give position recive valve, position actual and position final
    positions[1] = give_position(1, positions[1], 10);
    //save_valve revice position EEPROM valve and value
    save_value(1, positions[1]);
    Serial.println(positions[1]); 

    ///////////////// Configure valve 3 //////////////////
    //////////////////////////////////////////////////////
    positions[2] = byte(EEPROM.read(2));
    Serial.println(positions[2]); 
    //give position recive valve, position actual and position final
    positions[2] = give_position(2, positions[2], 10);
    //save_valve revice position EEPROM valve and value
    save_value(2, positions[2]);
    Serial.println(positions[2]); 

    EEPROM.commit();
    Serial.println();
    Serial.println("Positions are gotten");

    Serial.println("Please enter the valve and angle of motion separated by a comma");
  
    
    //delay(100);
}

void loop() {

        // send data only when you receive data:
    if (Serial.available()) {
        //Get data to the Serial
        String get_data = Serial.readString();
        String valve = s.separa(get_data,',',0);
        String angle = s.separa(get_data,',',1);
        Serial.println("The valve is: "+ valve);
        Serial.println("The porcent is: "+ angle);
        int valve1  = valve.toInt()-1;
        int angle1  = angle.toInt();
        posi_final = give_position(valve1,positions[valve1],angle1)
        // Save in the EEPROM the last position
        EEPROM.write(valve1, posi_final);
        EEPROM.commit();
        Serial.println("level saved in flash memory");
        Serial.println(valve1);
        Serial.println(angle1);
        delay(500);
        Serial.println("Please enter the valve and angle of motion separated by a comma");
    } 
}

int give_position(int valve, int posi_actual, int posi_final){
    switch(valve){
    case 0:
        PUL  = PUL1;
        DIR  = DIR1;
        break;
    case 1:
        PUL  = PUL2;
        DIR  = DIR2;
        break;
    case 2:
        PUL  = PUL3;
        DIR  = DIR3;
        break;
    
    default:
        break;
    }

    if (posi_actual > posi_final){
        //send PUL DIR ENA Position
        posi_final = closing(DIR, PUL, posi_final, posi_actual);
        Serial.Print("The valve is closing");
    }
    if (posi_actual > posi_final){
        //send PUL DIR ENA Position
        posi_final = opening(DIR, PUL, posi_final, posi_actual);
        Serial.Print("The valve is closing");
    }
    return posi_final;
}

int opening(int DIR, int PUL, int posi_final, int posi_actual){
     Serial.print("The valve is openning");
    while (posi_actual < posi_final)
    {
        digitalWrite(DIR,LOW);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL,LOW);
        delayMicroseconds(50);
        posi_actual++;
    }
    return posi_actual;
}


int closing(int DIR, int PUL, int posi_actual ,int posi_final, int posi_actual){
     Serial.print("The valve is closing");
     while (posi_actual > posi_final)
    {
        digitalWrite(DIR,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL,LOW);
        delayMicroseconds(50);
        posi_actual--;
    }
    return posi_actual;
}


