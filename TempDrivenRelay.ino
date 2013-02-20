#include <DHT22.h> //Library found @ http://github.com/ringerc/Arduino-DHT22

#define TEMPSENSORPIN 7
#define RELAYPIN 5
#define TIMEDELAY 5000 //in ms

// Setup a DHT22 instance
DHT22 myDHT22(TEMPSENSORPIN);

int timeDelayMS = 60000;

const short int highTemp = 70;
const short int lowTemp = 68;

void setup(void)
{
  //The Serial port is just for logging debug statements.
  //No problem if nothing is on the other end to read the bytes.
  Serial.begin(9600);
  Serial.println("Arduino Starting...");
  
  //Set the Relay Pin to an output pin.
  pinMode(RELAYPIN, OUTPUT);

  //The default should have the relay off, but just in case...
  digitalWrite(RELAYPIN,LOW);
  
  // The sensor takes upto 2s to start responding, so wait 5...
  delay(5000);
}

void loop(void)
{ 
  DHT22_ERROR_t retunCode;
  
  Serial.print("Reading Temp...");
  retunCode = myDHT22.readData();
  switch(retunCode)
  {
    case DHT_ERROR_NONE:
      Serial.print("Data: ");
      Serial.print(myDHT22.getTemperatureF());
      Serial.print("F ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      timeDelayMS = TIMEDELAY;
      
      //If the Temp is lower than the lower threshold, turn the power on
      if (myDHT22.getTemperatureF() < lowTemp){
        
        Serial.println("Turning on Power (if not on already).");
        digitalWrite(RELAYPIN,HIGH);

      //If the temp is higher than upper theshold, cut the power
      } else if (myDHT22.getTemperatureF() > highTemp){
        
         Serial.println("Turning off Power (if not off already)");
         digitalWrite(RELAYPIN,LOW); 
      }
      
      break;
    default:
      Serial.print("Error Reading.  Delay 2s and try again.");
      timeDelayMS = 2000;
      break;
  }
  
  delay (timeDelayMS);
}
