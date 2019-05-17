//intializes libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//initializes the transceiver chip
RF24 radio(7,8); //CS,CSN

int dumbbell = 2;
int squat = 3;
int bench = 4;

//********************IMPORTANT*************************************
//the pipe address isn't the address of the transceiver chip, it is the address of the
//connection between two transceiver chips. This means that if the transmitter and
//receiver don't have the same pipe address, they won't communicate. So make sure they
//are the same in both pieces of code.
const byte address[6] = "00002";

void setup() {
  // put your setup code here, to run once:

  //starts up serial monitor
  Serial.begin(9600);

  //starts up the radio using the address from before
  radio.begin();
  radio.openReadingPipe(0, address);

  //set the PA level to minimum to stop it from jamming if too close to other transceivers
  radio.setPALevel(RF24_PA_MIN);

  //makes the chip start to listen for signals
  radio.startListening();

  //sets the pins connected to the ethernet shield arduino as outputs
  pinMode(dumbbell, OUTPUT);
  pinMode(squat, OUTPUT);
  pinMode(bench, OUTPUT);
}

void loop() {

  //if a signal is found
  if  (radio.available()) {

    //The number of characters in this string is the max amount that a received message can be.
    //So, if your text array is only 3 letters long. It will only save "Hel" from the message "Hello."
    const char text[] = "xxxxxxxxxxx"; //10

    //reads the message and stores it in text
    radio.read(&text, sizeof(text));

    //converts the received character array into a string
    String text2 = text;

    //Prints to the serial monitor both the unconverted and converted message for debugging purposes.
    //this line can be freely skipped or removed.
    Serial.println(text);
    Serial.println(text2);

    //checks to see if the message received was "dumbon" and sends a high signal if true
    if(text2.indexOf("dumbon")>-1){
      digitalWrite(dumbbell,HIGH);
    }

    //checks to see if the message received was "dumboff" and sends a low signal if true
    if(text2.indexOf("dumboff")>-1){
      digitalWrite(dumbbell,LOW);
    }

    //checks to see if the message received was "squaton" and sends a high signal if true
    if(text2.indexOf("squaton")>-1){
      digitalWrite(squat,HIGH);
    }

    //checks to see if the message received was "squatoff" and sends a low signal if true
    if(text2.indexOf("squatoff")>-1){
      digitalWrite(squat,LOW);
    }

    //checks to see if the message received was "benchon" and sends a high signal if true
    if(text2.indexOf("benchon")>-1){
      digitalWrite(bench,HIGH);
    }

    //checks to see if the message received was "benchoff" and sends a low signal if true
    if(text2.indexOf("benchoff")>-1){
      digitalWrite(bench,LOW);
    }
  }
}
