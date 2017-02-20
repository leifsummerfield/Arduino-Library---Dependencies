


// N+1 Bus controller
// by Leif Summerfield

// Using I2C "wire" library to communicate with N+1 motor device bus
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

#include <NplusOne.h>
#include <Wire.h>


// constants won't change. They're used here to 
NplusOne  Xstage(1);
int steps = 1000;

const int HomePin = 4;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin

// Variables will change and go here:
int HomeSenseState = 0;         // variable for reading the limit status



void setup()
{  // initialize the home sensor pin as an input:
  pinMode(HomePin, INPUT);     
  
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
  
  
  Serial.begin(9600);
  Serial.println("N+1 Position"); 
  Xstage.home();
  }



void loop()
{

  int N1 = Xstage.status();
  Serial.println(N1);
  delay(333);
  
  // read the state of the pushbutton value:
  HomeSenseState = digitalRead(HomePin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (HomeSenseState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    //and read the position we're located at this trip point and send it out 
    int Position =  Xstage.readPos();
    Serial.println(Position);
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
    //and move the stage some steps into that direction
    Xstage.movePlus(10);
  }







}  //main loop end
