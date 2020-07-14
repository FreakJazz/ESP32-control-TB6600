// libraries that we use
#include <EEPROM.h>

// define the number of bytes you want to access
#define EEPROM_SIZE 3

// Define stepper motor 1 connections
#define PUL1 7 //define Pulse pin
#define DIR1 6 //define Direction pin
#define ENA1 5 //define Enable Pin
// Define stepper motor 2 connections
#define PUL2 7 //define Pulse pin
#define DIR2 6 //define Direction pin
#define ENA2 5 //define Enable Pin
// Define stepper motor 3 connections
#define PUL3 7 //define Pulse pin
#define DIR3 6 //define Direction pin
#define ENA3 5 //define Enable Pin

// Declarate the position of the motors
int position1 = 0;   
int position2 = 0;   
int position3 = 0;   
char data;

void setup() {
    Serial.begin(115200);
    // initialize EEPROM with predefined size
    EEPROM.begin(EEPROM_SIZE);

    // configurate pins of the step motor 1 
    pinMode (PUL1, OUTPUT);
    pinMode (DIR1, OUTPUT);
    pinMode (ENA1, OUTPUT);

    // configurate pins of the step motor 2
    pinMode (PUL2, OUTPUT);
    pinMode (DIR2, OUTPUT);
    pinMode (ENA2, OUTPUT);

    // configurate pins of the step motor 3
    pinMode (PUL3, OUTPUT);
    pinMode (DIR3, OUTPUT);
    pinMode (ENA3, OUTPUT);

    //Read the position od the motors 
    position1 = EEPROM.read(0);         // the position of the step motor1
    position2 = EEPROM.read(1);         // the position of the step motor2
    position3 = EEPROM.read(2);         // the position of the step motor3
    Serial.print("Position of the valve 1 is: ");
    Serial.println(position1);
    Serial.print("Position of the valve 2 is: ");
    Serial.println(position2);
    Serial.print("Position of the valve 3 is: ");
    Serial.println(position3);
    delay(3500);

}

void loop() {
    while(Serial.available()) {
        data = Serial.read();
        Serial.println(data);
        delay(1000);
    }
}

void opening(int DIR, int ENA, int PUL){
    for (int i=0; i<6400; i++)    //Forward 5000 steps
    {
        digitalWrite(DIR,LOW);
        digitalWrite(ENA,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL,LOW);
        delayMicroseconds(50);
    }
}

void closing(int DIR, int ENA, int PUL){
    for (int i=0; i<6400; i++)   //Backward 5000 steps
    {
        digitalWrite(DIR,HIGH);
        digitalWrite(ENA,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL,LOW);
        delayMicroseconds(50);
    }
}

void save_value(int position){
    // Save in the EEPROM the last position
    EEPROM.write(0, position);
    EEPROM.commit();
    Serial.println("level saved in flash memory");
    Serial.println(position1);
}

