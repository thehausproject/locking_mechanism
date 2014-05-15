/**
*  Russell Stephens
*  Senior Design
*  HAUS - Locking Mechanism v1.0
*  Decemeber 2, 2013
*/
#include <Ethernet.h>
#include <SPI.h>
#include "RestClient.h"

//init RestClient with HAUS domain
RestClient client = RestClient("www.yoursite.com/haus");
//init strikePlateTransitor Pin
int strikePlateTransistor = 3;

//Setup
void setup() {
  Serial.begin(9600);
  // Connect via DHCP
  Serial.println("connect to network");
  client.dhcp();
  Serial.println("Initialization complete");
  // initialize the strikePlateTransistor digital pin as an output.
  pinMode(strikePlateTransistor, OUTPUT);
}

//Main Loop
void loop(){
  String response = "";
  int statusCode = client.get("/devicecheckin.php?passcode=1234567890123456", &response);
  
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  
  int colonIndex = response.indexOf(":");//guarenteed to be state:whatineed
  char stateValue = response.substring(colonIndex+2).charAt(0); //get first character after :"
  if(stateValue == 'U') {
    Serial.println("unlocking");
    digitalWrite(strikePlateTransistor, HIGH);   // turn the strikePlateTransistor on (HIGH is the voltage level)
    delay(5000);               // wait for 5 seconds (strikePlateTransistor delay value)
    digitalWrite(strikePlateTransistor, LOW);    // turn the strikePlateTransistor off by making the voltage LOW
  }else {
    // recheck every 5 seconds
    delay(5000);
  }
  
  
}
