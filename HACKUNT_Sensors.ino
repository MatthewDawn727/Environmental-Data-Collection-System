
#include <Wire.h>
#include "SparkFunCCS811.h" 
#include <Adafruit_MPL3115A2.h>

#define CCS811_ADDR 0x5B //Default I2C Address

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

CCS811 mySensor(CCS811_ADDR);


int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Variable for Soil moisture Power


void setup()
{
  Serial.begin(9600);
  Serial.println("CCS811 Basic Example");

  Wire.begin(); //Inialize I2C Hardware

  if (mySensor.begin() == false)
  {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
    while (1)
      ;
  }
  
  Serial.println("Adafruit_MPL3115A2 test!");



  Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
    Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  
  
}

void loop()
{
  //Check to see if data is ready with .dataAvailable()
  if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    mySensor.readAlgorithmResults();

//Display the time since program start
    Serial.print(" \n\nSeconds: ");
    Serial.print((millis())*0.001);
    Serial.print(" ");
    Serial.println();

    Serial.print("CO2: ");
    //Returns calculated CO2 reading
    Serial.print(mySensor.getCO2());
    Serial.print(" parts per Billion \ntVOC: ");
    //Returns calculated TVOC reading
    Serial.print(mySensor.getTVOC());
    Serial.println();
  }
  delay(10); //Don't spam the I2C bus

if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
  
  float pascals = baro.getPressure();
  // Our weather page presents pressure in Inches (Hg)
   Serial.print("Pressure: ");
  Serial.print(pascals/3377); 
  Serial.println(" Inches (Hg)");

  float altm = baro.getAltitude();
  Serial.print("Altitude: ");
  Serial.print(altm); Serial.println(" meters");

  float tempC = baro.getTemperature();
  Serial.print("Tempeture: ");
  Serial.print(tempC); Serial.println("*C");


Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
Serial.println(readSoil());

//This 1 second timefrme is used so you can test the sensor and see it change in real-time.
//For in-plant applications, you will want to take readings much less frequently.
delay(1000);//take a reading every second
}
//This is a function used to get the soil moisture content
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
    Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
Serial.println(readSoil());

//This 1 second timefrme is used so you can test the sensor and see it change in real-time.
//For in-plant applications, you will want to take readings much less frequently.


  delay(250);
  

}
