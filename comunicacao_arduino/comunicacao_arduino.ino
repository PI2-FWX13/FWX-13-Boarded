#include<SoftwareSerial.h>
SoftwareSerial serial1(6, 7); // RX, TX

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}


void loop() {
  digitalWrite(8, LOW);
  delay(100);

  float x = 0;
  if(serial1.available()) {
        char c_ptr[sizeof(float)];
    	for(int i = 0; i < sizeof(float); i++)
    		*(c_ptr + i) = serial1.read();

	x = *((float *) c_ptr);
	// Serial.print(f_pointer);*/
  }
  
  digitalWrite(8, HIGH);
  delay(x * 10);
 

/* 
  if(recebe!=0 ){
    int i = 0; 
  while(i<(recebe*50)){
   //antihortio
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(freq);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(freq);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(freq);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(freq);
  i++;
  }
   i = 0;
  delay(1);
  while(i<(recebe*50)){
    //horario
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(20);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(20);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(20);
  
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  delay(20);
  i++;
  }
  i= 0;
  delay(1);
  
 } */
}

