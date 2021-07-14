//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(8, 9);  // CE, CSN

//declaring and initializing variables for the joy_stick
int swtchbutton=4;
int x,y,bttnRead;

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  Serial.begin(9600);
  //setting pin mode for the joystick switch-button
  pinMode(swtchbutton,INPUT);
 
  //set the address
 radio.openWritingPipe(address);
 radio.setPALevel(RF24_PA_MAX);
 radio.setDataRate(RF24_1MBPS);
  //Set module as transmitter
 radio.stopListening();
}
void loop()
{
  //radio.begin();
  //reading values from the joystick
  x=analogRead(A0);
  y=analogRead(A1);
  bttnRead=digitalRead(swtchbutton);
  //Send message to receiver
  char joystickPos[10];
  sprintf(joystickPos, "%i,%i", x, y);
  radio.write(&joystickPos, sizeof(joystickPos));
  Serial.println(joystickPos);
  //delay(1000);
}
