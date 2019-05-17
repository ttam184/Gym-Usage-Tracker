#include <SPI.h>
#include <Ethernet.h>

//variables needed to configure the ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   
byte ip[] = { 192, 168, 1, 135 };                      
byte gateway[] = { 192, 168, 1, 1 };                   
byte subnet[] = { 255, 255, 255, 0 };                  
EthernetServer server(80);                                 

//initializes the gym equipment input ports, booleans and time arrays
int x = 0;
int dumbbell = 8;
bool dumbbellInUse = false;
int dumbbellUsage = 0;
int dumbbellTime[60] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int squat = 6;
bool squatInUse = false;
int squatUsage = 0;
int squatTime[60] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int bench = 4;
bool benchInUse = false;
int benchUsage = 0;
int benchTime[60] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void setup() {
  //connects the shield to the internet using variables
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  //starts the serial monitor
  Serial.begin(9600);

  //prints the ip address on the serial monitor
  Serial.print("IP Adress: ");
  Serial.println(Ethernet.localIP());

  //sets the wires connected to the receiver arduino as inputs
  pinMode(dumbbell,INPUT);
  pinMode(squat, INPUT);
  pinMode(bench, INPUT);
}

void loop() { 

  //activates the server
  EthernetClient client = server.available();

  //if a user visits the webpage
  if(client){
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
         if (c == '\n') {          

           //sets up the page
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");

           //the title on the tab
           client.println("<HEAD>");
           client.println("<TITLE>Gym Usage Tracker</TITLE>");
           client.println("</HEAD>");

           //starts the text section
           client.println("<BODY>");

           //title
           client.println("<H1>Gym Usage Tracker</H1>");
           client.println("<br />");

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

           //kettle bell information
           client.println("<H2>Kettle Bell</H2>");

           //prints whether the kettle bell is in use or not
           if(dumbbellInUse == true){
            client.println("The kettle bell is currently in use.");
           }

           if(dumbbellInUse == false){
            client.println("The kettle bell is not currently in use.");
           }

           //prints how long the kettle bell has been in use
           client.println("<br />");
           client.print("The kettle bell been in use for ");
           client.print(dumbbellUsage);
           client.print(" seconds in the last minute.");

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

           //squat rack information
           client.println("<H2>Squat Rack</H2>");

           //prints whether the squat rack is in use or not
           if(squatInUse == true){
            client.println("The squat rack is currently in use.");
           }

           if(squatInUse == false){
            client.println("The squat rack is not currently in use.");
           }

           //prints how long the squat rack has been in use
           client.println("<br />");
           client.print("The squat rack has been in use for ");
           client.print(squatUsage);
           client.print(" seconds in the last minute.");

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

           //bench press information
           client.println("<H2>Bench Press</H2>");

           //prints whether the bench press is in use or not
           if(benchInUse == true){
            client.println("The bench press is currently in use.");
           }

           if(benchInUse == false){
            client.println("The bench press is not currently in use.");
           }
           client.println("<br />");

           //prints how long the bench press has been in use
           client.print("The bench press has been in use for ");
           client.print(benchUsage);
           client.print(" seconds in the last minute.");

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

           //ends the text section
           client.println("</BODY>");

           //ends the webpage
           client.println("</HTML>");

           //refreshes the webpage every millisecond
           delay(1);
           client.stop();
  }
      }
    }
  }

  //1 second delay
  delay(1000); 

  //changes the boolean of whether its in use or not and adds whether it was in use into the time array at the second value x is currently at
  if(digitalRead(dumbbell) == HIGH){
    dumbbellInUse = true;
    dumbbellTime[x] = 1;
  }

  if(digitalRead(dumbbell) == LOW){
    dumbbellInUse = false;
    dumbbellTime[x] = 0;
  }

  //counts how many seconds its been in use in the last minute based on the time array
  dumbbellUsage = 0;
  int i = 0;
  while(i<60){
    if(dumbbellTime[i] == 1){
      dumbbellUsage++;
    }
    i++;
  }

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

  //changes the boolean of whether its in use or not and adds whether it was in use into the time array at the second value x is currently at
  if(digitalRead(squat) == HIGH){
    squatInUse = true;
    squatTime[x] = 1;
  }

  if(digitalRead(squat) == LOW){
    squatInUse = false;
    squatTime[x] = 0;
  }

  //counts how many seconds its been in use in the last minute based on the time array
  squatUsage = 0;
  i = 0;
  while(i<60){
    if(squatTime[i] == 1){
      squatUsage++;
    }
    i++;
  }

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

  //changes the boolean of whether its in use or not and adds whether it was in use into the time array at the second value x is currently at
  if(digitalRead(bench) == HIGH){
    benchInUse = true;
    benchTime[x] = 1;
  }

  if(digitalRead(bench) == LOW){
    benchInUse = false;
    benchTime[x] = 0;
  }

  //counts how many seconds its been in use in the last minute based on the time array
  benchUsage = 0;
  i = 0;
  while(i<60){
    if(benchTime[i] == 1){
      benchUsage++;
    }
    i++;
  }

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

  //counts 60 seconds and then resets
  //is the pointer for all of the time arrays
  x++;

  if(x>=60){
    x = 0;
  }
  
}
