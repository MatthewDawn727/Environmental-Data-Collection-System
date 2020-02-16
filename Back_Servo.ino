//www.elegoo.com

#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A1;  
int Trig = A2; 
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;
  Serial.print("Distance: ");
  Serial.println(Fdistance);       
  return (int)Fdistance;
}  

void setup() { 
  myservo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
} 

void loop() { 
    myservo.write(90);  //setservo position according to scaled value
    delay(500); 
    middleDistance = Distance_test();

    if(middleDistance <= 40) {     
      delay(500);                         
      myservo.write(10);          
      delay(360);      
      rightDistance = Distance_test();
      
      delay(500);
      myservo.write(90);              
      delay(1000);                                                  
      myservo.write(180);              
      delay(360); 
      leftDistance = Distance_test();
      
      delay(500);
      myservo.write(90);              
      delay(360);
    }                
}
