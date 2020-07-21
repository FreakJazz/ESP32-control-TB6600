
// Define stepper motor 1 connections
#define PUL1 34 //define Pulse pin
#define DIR1 39 //define Direction pin
#define ENA1 36 //define Enable Pin
// Define stepper motor 2 connections
#define PUL2 33 //define Pulse pin
#define DIR2 32 //define Direction pin
#define ENA2 35 //define Enable Pin
// Define stepper motor 3 connections
#define PUL3 27 //define Pulse pin
#define DIR3 26 //define Direction pin
#define ENA3 25 //define Enable Pin
// Declarate the position of the motors
int PUL;  //define Pulse pin
int DIR;  //define Direction pin
int ENA; //define Enable Pin
//int cont; //define the count of the steps

void setup() {
    Serial.begin(115200);

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


}

void loop() {

    // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  
}


int give_position(int valve, int posi_actual, int posi_final){
    switch(valve){
    case 0:
        PUL  = PUL1;
        DIR  = DIR1;
        ENA  = ENA1;
        break;
    case 1:
        PUL  = PUL2;
        DIR  = DIR2;
        ENA  = ENA2;
        break;
    case 2:
        PUL  = PUL3;
        DIR  = DIR3;
        ENA  = ENA3;
        break;
    
    default:
        break;
    }

    if (posi_actual > posi_final){
        //send PUL DIR ENA Position
        closing(PUL, DIR, ENA, posi_actual, posi_final);
    }
    if (posi_actual < posi_final){
        //send PUL DIR ENA Position
        opening(PUL, DIR, ENA, posi_actual, posi_final);
    }
    return posi_final;
}

void opening(int DIR, int ENA, int PUL, int posi_actual,int posi_final){
    while (posi_actual < posi_final)
    {
        digitalWrite(DIR,LOW);
        digitalWrite(ENA,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL,LOW);
        delayMicroseconds(50);
    }
}

void closing(int DIR, int ENA, int PUL, int posi_actual ,int posi_final){
     while (posi_actual > posi_final)
    {
        digitalWrite(DIR,HIGH);
        digitalWrite(ENA,HIGH);
        digitalWrite(PUL,HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL,LOW);
        delayMicroseconds(50);
    }
}