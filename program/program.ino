// libraries that we use
#include "EEPROM.h"
#include "Separador.h"

Separador s;
// define the number of bytes you want to access
#define EEPROM_SIZE 3

// Define stepper motor 1 connections
#define PUL1 35 //define Pulse pin
#define DIR1 34 //define Direction pin

// Define stepper motor 2 connections
#define PUL2 33 //define Pulse pin
#define DIR2 32 //define Direction pin

// Define stepper motor 3 connections
#define PUL3 26 //define Pulse pin
#define DIR3 25 //define Direction pin


// Declarate the position of the motors
int positions [EEPROM_SIZE]= {};   
int PUL;  //define Pulse pin
int DIR;  //define Direction pin
int posi_final, posi_actual;

void setup() {
  
    Serial.begin(115200);
    // initialize EEPROM with predefined size
    Serial.println("Start...");
    EEPROM.begin(EEPROM_SIZE);
      
    // configurate pins of the step motor 1 
    pinMode (PUL1, OUTPUT);
    pinMode (DIR1, OUTPUT);
    digitalWrite(PUL1,LOW);
    digitalWrite(DIR1,LOW);
    
    // configurate pins of the step motor 2
    pinMode (PUL2, OUTPUT);
    pinMode (DIR2, OUTPUT);
    digitalWrite(PUL2,LOW);
    digitalWrite(DIR2,LOW);
    
    // configurate pins of the step motor 3
    pinMode (PUL3, OUTPUT);
    pinMode (DIR3, OUTPUT);
    digitalWrite(PUL3,LOW);
    digitalWrite(DIR3,LOW);

    ///////////////// Configure valve 1 //////////////////
    //////////////////////////////////////////////////////
    positions[0] = byte(EEPROM.read(0));
    Serial.print("Valve 1: ");
    Serial.println(positions[0]); 
    
    ///////////////// Configure valve 2 //////////////////
    //////////////////////////////////////////////////////
    positions[1] = byte(EEPROM.read(1));
    Serial.print("Valve 2: "); 
    Serial.println(positions[1]); 
    ///////////////// Configure valve 3 //////////////////
    //////////////////////////////////////////////////////
    positions[2] = byte(EEPROM.read(2));
    Serial.print("Valve 3: ");
    Serial.println(positions[2]); 

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
        //Separate the data serial 
        String valve = s.separa(get_data,',',0);
        String angle = s.separa(get_data,',',1);
        Serial.println("The valve is: "+ valve);
        Serial.println("The porcent is: "+ angle);
        // Change the variables to int
        int valve1  = valve.toInt()-1;
        int angle1  = angle.toInt();
        
        // function to open and close the valves
        positions[valve1] = give_position(valve1,positions[valve1],angle1);
        
        // Save in the EEPROM the last position
        EEPROM.write(valve1, positions[valve1]);
        EEPROM.commit();
        Serial.println("Level saved in memory, this is the actual position");
        // Show the positions of the valve
        Serial.print("You change the position of the valve");
        Serial.println(valve1+1);
        Serial.println(positions[valve1]);
        delay(500);
        Serial.println("");
        // Show the position of the system
        Serial.println("Now the positions of the valves are: ");
        Serial.print("Valve 1: ");
        Serial.println(positions[0]); 
        Serial.print("Valve 2: ");
        Serial.println(positions[1]); 
        Serial.print("Valve 3: ");
        Serial.println(positions[2]); 
        Serial.println("Please enter the valve and angle of motion separated by a comma");
    } 
}

// This function choose if the valve needs to open or close
int give_position(int valve, int posi_actual, int posi_final){
    delay(100);
    Serial.println("This is the position function");
    switch(valve){
    Serial.print("You select the valve:");
    Serial.print(valve+1); 
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
      Serial.println("This valve doesn't exist");
        break;
    }

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


